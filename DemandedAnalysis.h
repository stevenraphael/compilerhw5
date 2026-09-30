//===- DemandedAnalysis.h - Sparse forward analysis over DemandedState ------------===//

#ifndef DEMANDED_ANALYSIS_H
#define DEMANDED_ANALYSIS_H

#include "DemandedDomain.h"
#include "mlir/Analysis/DataFlow/SparseAnalysis.h"

namespace demanded {

using DemandedLattice = mlir::dataflow::Lattice<DemandedState>;

class DemandedAnalysis
    : public mlir::dataflow::SparseBackwardDataFlowAnalysis<DemandedLattice> {
public:
  using SparseBackwardDataFlowAnalysis::SparseBackwardDataFlowAnalysis;

  /// Transfer function: given the states of `op`'s operands, set the states of
  /// its results.  Must be monotone in the operand states.
  mlir::LogicalResult
  visitOperation(mlir::Operation *op,
                 llvm::ArrayRef<DemandedLattice *> operands,
                 llvm::ArrayRef<const DemandedLattice *> results) override;

  /// The state of anything entering the analysis from outside: function
  /// arguments, and results the transfer function declines to reason about.
  void setToExitState(DemandedLattice *lattice) override;

  void visitBranchOperand(mlir::OpOperand &operand) override;
  void visitCallOperand(mlir::OpOperand &operand) override;
  void visitNonControlFlowArguments(
      mlir::RegionSuccessor &successor,
      llvm::ArrayRef<mlir::BlockArgument> arguments) override;

};

} // namespace demanded

#endif
