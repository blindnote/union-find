#ifndef PathCompressedQU_h
#define PathCompressedQU_h

#define ROOT_IN_PRACTICE

#include "quick-union.h"

template <typename T>
class PathCompressedQU: virtual public QuickUnion<T> {
protected:
  virtual const T& Root(DisjointSet<T>& data, const T& item) override {
#ifdef ROOT_IN_PRACTICE
    return RootInPractice(data, item);
#else
    return RootStandard(data, item);
//    return RootRecursion(data, item);
#endif
  }

private:
  const T& RootInPractice(DisjointSet<T>& data, const T& item) {
    // make every other node in path point to its grandparent
    // keep tree almost completely flat
    int currId = data.Id(item);
    int parentId = currId;
    do {
      currId = parentId;
      data.ChangeParentToGrandPa(currId);
      parentId = data.Id(data.ParentOf(currId));
    } while (currId != parentId);
    
    return data.ParentOf(currId);
  }
  
  const T& RootStandard(DisjointSet<T>& data, const T& item) {
    const T& root = QuickUnion<T>::Root(data, item);
    const int rootId = data.Id(root);
    // just after computing the root of i,
    // set the id of each examined node to root(i)
    int currId = data.Id(item);
    while (currId != rootId) {
      int parentId = data.Id(data.ParentOf(currId));
      data.ChangeParentToRoot(currId, root);
      currId = parentId;
    }
    
    return root;
  }
  
  // essentially same with RootStandard
  const T& RootRecursion(DisjointSet<T>& data, const T& item) {
    if (data.Id(item) == data.ParentId(item))
      return data.Parent(item);
    
    const T& root = RootRecursion(data, data.Parent(item));
    data.ChangeParentToRoot(data.Id(item), root);
    return root;
  }
};

#endif /* PathCompressedQU_h */
