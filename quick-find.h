#ifndef QuickFind_h
#define QuickFind_h

#include "union-find.h"

/**
  * "Eager approach"
  * - Find:  O(1)
  * - Union: worst case O(N), too expensive
  */
template <typename T>
class QuickFind: public UnionFind<T> {
public:
  virtual bool Find(DisjointSet<T>& data, const T& x, const T& y) override {
    return data.Parent(x) == data.Parent(y);  // 1 operation
  }
  
  // merge all objects in the same group of x into group of y
  virtual void Join(DisjointSet<T>& data, const T& x, const T& y) override {
    const T& xp = data.Parent(x);
    const T& yp = data.Parent(y);
    if (xp == yp) return;
    // many values can change
    // Trees are flat, but too expensive to keep them flat.
    data.ChangeParents(xp, yp);              // N operations
  }
};


#endif /* QuickFind_h */
