#ifndef QuickUnion_h
#define QuickUnion_h

#include "union-find.h"

/**
  * "Lasy approach"
  * need to do "FIND" to do "UNION"
  * - Find:  time proportional to depth of x and y,  could be N in worst case
  * - Union: time proportional to depth of x and y,  could be N in worst case
  */
template <typename T>
class QuickUnion: public UnionFind<T> {
public:
  virtual bool Find(DisjointSet<T>& data, const T& x, const T& y) override {
    // "Find" too expensive, could be N steps in worst case
    return Root(data, x) == Root(data, y);
  }
  
  virtual void Join(DisjointSet<T>& data, const T& x, const T& y) override {
    // need to do "find root" to do "union"
    const T& xr = Root(data, x);
    const T& yr = Root(data, y);
    if (xr == yr) return;
    // only 1 value changes, trees can get tall
    data.SetParent(xr, yr);
  }
  
protected:
  // Root of item is parent[parent[parent[....parent[item]....]]]
  // keep going until it doesn't change
  virtual const T& Root(DisjointSet<T>& data, const T& item) {
    int currId = data.Id(item);
    int parentId = currId;
    do {
      currId = parentId;
      parentId = data.Id(data.ParentOf(currId));
    } while (currId != parentId);
    
    return data.ParentOf(currId);
  }
};


#endif /* QuickUnion_h */

