#ifndef UnionFind_h
#define UnionFind_h

#include <iostream>
#include "disjoint-set.h"

template <typename T>
class UnionFind {
public:
  virtual bool Find(DisjointSet<T>& data, const T& x, const T& y) = 0;
  virtual void Join(DisjointSet<T>& data, const T& x, const T& y) = 0;
};


#endif /* UnionFind_h */
