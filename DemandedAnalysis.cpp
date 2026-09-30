#include "DemandedAnalysis.h"

#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/IR/Matchers.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include <bit>

using namespace mlir;

namespace demanded {

void DemandedAnalysis::setToExitState(DemandedLattice *lattice) {
  propagateIfChanged(lattice, lattice->join(DemandedState::bottom()));
}

void DemandedAnalysis::visitBranchOperand(mlir::OpOperand &operand) {
    propagateIfChanged(getLatticeElement(operand.get()), getLatticeElement(operand.get())->join(DemandedState::top()));
}

void DemandedAnalysis::visitCallOperand(mlir::OpOperand &operand) {
    propagateIfChanged(getLatticeElement(operand.get()), getLatticeElement(operand.get())->join(DemandedState::top()));
}

void DemandedAnalysis::visitNonControlFlowArguments(RegionSuccessor &successor, ArrayRef<BlockArgument> arguments) {
    for (BlockArgument arg : arguments) {
        propagateIfChanged(getLatticeElement(arg), getLatticeElement(arg)->join(DemandedState::top()));
    }
}

LogicalResult
  DemandedAnalysis::visitOperation(Operation *op,
                 ArrayRef<DemandedLattice *> operands,
                 ArrayRef<const DemandedLattice *> results){
    auto unknowngood = [&] {
        setAllToExitStates(operands);
        return success();
    };

    auto unknownbad = [&] {
        for(DemandedLattice *lattice : operands){
                propagateIfChanged(lattice, lattice->join(DemandedState::top()));
        }
        return success();
    };

    

    // assume we need all bits at the end of each basic block (backwards analysis is hard)
    if (op->hasTrait<mlir::OpTrait::IsTerminator>()) { 
        return unknownbad();
    }

    // Only single-result integer operations are interesting here.  Calls, loads,
    // floats, and vectors all land in `unknown`.
    if (op->getNumResults() != 1 || !op->getResult(0).getType().isIntOrIndex()){
        // If the operation is unknown, assume we need all bits unless the result has no demanded bits
        if(op->getNumResults()==1&&results[0]->getValue().isBottom()){
            return unknowngood();
        }
        return unknownbad();
    }

    
        
    const DemandedLattice *result = results[0];

    APInt lconst;
    APInt rconst;
    IntegerAttr var;

    if(matchPattern(op, m_Op<LLVM::AndOp>(matchers::m_Any(), m_ConstantInt(&rconst)))) {
        DemandedState d((uint64_t)rconst.getLimitedValue()&result->getValue().kind);
        propagateIfChanged(operands[0], operands[0]->join(d));
        propagateIfChanged(operands[1], operands[1]->join(result->getValue()));
        return success();
        
    }

    //return unknownbad();

    if(matchPattern(op, m_Op<LLVM::AndOp>(m_ConstantInt(&lconst), matchers::m_Any()))) {
        DemandedState d((uint64_t)lconst.getLimitedValue()&result->getValue().kind);
        propagateIfChanged(operands[1], operands[1]->join(d));
        propagateIfChanged(operands[0], operands[0]->join(result->getValue()));
        return success();
        
    }

    if(matchPattern(op, m_Op<LLVM::OrOp>(matchers::m_Any(), m_ConstantInt(&rconst)))) {
        DemandedState d(~((uint64_t)rconst.getLimitedValue())&result->getValue().kind);
        propagateIfChanged(operands[0], operands[0]->join(d));
        propagateIfChanged(operands[1], operands[1]->join(result->getValue()));
        return success();
        
    }

    if(matchPattern(op, m_Op<LLVM::OrOp>(m_ConstantInt(&lconst), matchers::m_Any()))) {
        DemandedState d(~((uint64_t)lconst.getLimitedValue())&result->getValue().kind);
        propagateIfChanged(operands[1], operands[1]->join(d));
        propagateIfChanged(operands[0], operands[0]->join(result->getValue()));
        return success();
        
    }

    if(matchPattern(op, m_Op<LLVM::LShrOp>(matchers::m_Any(), m_ConstantInt(&rconst)))){
        DemandedState d(((~((uint64_t)0))<<(uint64_t)rconst.getLimitedValue()) & (result->getValue().kind<<(uint64_t)rconst.getLimitedValue()));
        propagateIfChanged(operands[0], operands[0]->join(d));
        propagateIfChanged(operands[1], operands[1]->join(DemandedState::top()));
        return success();

    }

    // All bits to the left of the MSB are irrelevant
    if(matchPattern(op, m_Op<LLVM::AddOp>(matchers::m_Any(), matchers::m_Any()))) {
        DemandedState d((1ULL << std::bit_width(result->getValue().kind)) - 1);
        propagateIfChanged(operands[1], operands[1]->join(d));
        propagateIfChanged(operands[0], operands[0]->join(d));
        return success();
        
    }

    if(matchPattern(op, m_Op<LLVM::SubOp>(matchers::m_Any(), matchers::m_Any()))) {
        DemandedState d((1ULL << std::bit_width(result->getValue().kind)) - 1);
        propagateIfChanged(operands[1], operands[1]->join(d));
        propagateIfChanged(operands[0], operands[0]->join(d));
        return success();
    }

    if(matchPattern(op, m_Op<LLVM::MulOp>(matchers::m_Any(), matchers::m_Any()))) {
        DemandedState d((1ULL << std::bit_width(result->getValue().kind)) - 1);
        propagateIfChanged(operands[1], operands[1]->join(d));
        propagateIfChanged(operands[0], operands[0]->join(d));
        return success();
    }

    if(matchPattern(op, m_Op<LLVM::AndOp>(matchers::m_Any(), matchers::m_Any()))) {
        DemandedState d(result->getValue().kind);
        propagateIfChanged(operands[1], operands[1]->join(d));
        propagateIfChanged(operands[0], operands[0]->join(d));
        return success();
    }

    if(matchPattern(op, m_Op<LLVM::OrOp>(matchers::m_Any(), matchers::m_Any()))) {
        DemandedState d(result->getValue().kind);
        propagateIfChanged(operands[1], operands[1]->join(d));
        propagateIfChanged(operands[0], operands[0]->join(d));
        return success();
    }

    if(matchPattern(op, m_Op<LLVM::XOrOp>(matchers::m_Any(), matchers::m_Any()))) {
        DemandedState d(result->getValue().kind);
        propagateIfChanged(operands[1], operands[1]->join(d));
        propagateIfChanged(operands[0], operands[0]->join(d));
        return success();
    }



    if(op->getNumResults()==1&&results[0]->getValue().isBottom()){
        return unknowngood();
    }
    return unknownbad();



}

}