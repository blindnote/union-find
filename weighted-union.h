#ifndef WeightedQU_h
#define WeightedQU_h

#include "quick-union.h"

/**
  * modify QuickUnion to avoid tall trees
  * keep track of size of each component
  * balance by linking small tree below large one
  * depth is at most lgN
  * - Find:  lgN
  * - Union: lgN*
  */
template <typename T>
class WeightedQU: virtual public QuickUnion<T> {
public:
  // FIND: time proportional to depth of p and q
  //       depth is at most lgN
  virtual void Join(DisjointSet<T>& data, const T& x, const T& y) override {
    const T& xr = QuickUnion<T>::Root(data, x);
    const T& yr = QuickUnion<T>::Root(data, y);
    if (xr == yr) return;
    // merge smaller tree into larger tree
    // UNION: takes constant time, given roots
    int xrsz = data.Size(xr);
    int yrsz = data.Size(yr);
    if (xrsz < yrsz) {
      data.SetParent(xr, yr);
    } else {
      data.SetParent(yr, xr);
    }
  }
};

#endif /* WeightedQU_h */
