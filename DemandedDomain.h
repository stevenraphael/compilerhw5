//===- ZeroDomain.h - The abstract domain ---------------------------------===//
//
// A four-point lattice recording whether an integer value is known to be zero.
//
//        Top          nothing is known
//       /   \
//    Zero  NonZero
//       \   /
//       Bottom       unreachable, or not yet analyzed
//
// This is the file to replace first when building a different analysis.  MLIR's
// dataflow framework asks only three things of a lattice value:
//
//   * a default constructor, which must produce the bottom element, because the
//     solver starts every value optimistically and lowers it as facts arrive;
//   * a static join(), which must be commutative, associative, idempotent, and
//     monotone -- assertions in Lattice<> check monotonicity in debug builds;
//   * operator== and print().
//
//===----------------------------------------------------------------------===//

#ifndef DEMANDED_DOMAIN_H
#define DEMANDED_DOMAIN_H

#include "llvm/Support/raw_ostream.h"

namespace demanded {

typedef uint64_t Kind;


static std::string name(Kind kind) {
  std::string s;
  s.reserve(64);
  for(int i=63;i>=0;i--){
    s+=(((kind>>i)%2)==1)?"1":"0";
  }
  return s;
}

struct DemandedState {
  Kind kind = 0;

  DemandedState() = default;
  /* implicit */ DemandedState(Kind kind) : kind(kind) {}

  static DemandedState bottom() { return 0; }
  static DemandedState top() { return ~(static_cast<uint64_t>(0)); }

  bool isBottom() const { return kind == 0; }

  /// Least upper bound.  Two disagreeing facts lose all information.
  static DemandedState join(const DemandedState &lhs, const DemandedState &rhs) {
    DemandedState s(lhs.kind | rhs.kind);
    return s;
  }

  bool operator==(const DemandedState &other) const { return kind == other.kind; }
  bool operator!=(const DemandedState &other) const { return kind != other.kind; }

  void print(llvm::raw_ostream &os) const { os << name(kind); }
};

inline llvm::raw_ostream &operator<<(llvm::raw_ostream &os,
                                     const DemandedState &state) {
  state.print(os);
  return os;
}

} // namespace demanded

#endif
