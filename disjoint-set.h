#ifndef disjoint_set_h
#define disjoint_set_h

#include <iostream>
#include <map>
#include <unordered_map>
#include <functional>

template <typename T>
class DisjointSet {
public:
  DisjointSet()  = default;
  ~DisjointSet() = default;
  
  void Add(const T&& item) {
    int id = Size();
    const auto& result = ids.emplace(item, id);
    if (!result.second)
      return;
    
    parents.emplace(id, std::cref((result.first)->first));
    sizes.emplace(id, 1);
  }
  
  int Id(const T& item) const {
    assert(ids.count(item) != 0);
    return ids.at(item);
  }
  
  const T& Parent(const T& item) const {
// Won't compile since there's no viable constructor for std::reference_wrapper<T>
// this is because operator[] requires the default initialization of the value type
////    return parents[ids[item]];
    return parents.at(Id(item));
  }
  
  const T& ParentOf(int id) const {
    assert(parents.count(id) != 0);
    return parents.at(id);
  }
  
  int ParentId(const T& item) const {
    return Id(Parent(item));
  }
  
  void ChangeParents(const T& oldParent, const T& newParent) {
    sizes.at(Id(newParent)) += sizes.at(Id(oldParent));
    for (auto& p : parents) {
      if (p.second == oldParent) {
        p.second = newParent;
        sizes.at(Id(p.first)) = 1;
      }
    }
  }
  
  void SetParent(const T& item, const T& parent) {
    parents.at(Id(item)) = parent;
    sizes.at(Id(parent)) += sizes.at(Id(item));
  }
  
  void ChangeParentToGrandPa(int id) {
    const T& parent = ParentOf(id);
    if (Id(parent) == id)
      return;
    
    const T& grandpa = Parent(parent);
    if (Id(parent) == Id(grandpa))
      return;
    
    parents.at(id) = grandpa;
    sizes.at(Id(parent)) -= sizes.at(id);
  }
  
  void ChangeParentToRoot(int id, const T& root) {
    const T& parent = ParentOf(id);
    if (Id(parent) == id || parent == root)
      return;
    
    parents.at(id) = root;
    sizes.at(Id(parent)) -= sizes.at(id);
  }
  
  int Size(const T& item) const {
    return sizes.at(Id(item));
  }
  
  int Size() const {
    return (int)ids.size();
  }
  
  bool Empty() const {
    return ids.empty();
  }
  
  void Clear() {
    ids.clear();
    parents.clear();
    sizes.clear();
  }
  
  
  friend std::ostream& operator<<(std::ostream& os, const DisjointSet& dataset) {
    for (auto& obj : dataset.ids) {
      os << "item:\"" << obj.first << "\", id:" << obj.second
         << ", parentId:" << dataset.ParentId(obj.first)
         << ", parent:" << dataset.Parent(obj.first)
        << ", # of nodes:" << dataset.Size(obj.first) << std::endl;
    }
    os << std::endl;
    return os;
  }

  
private:
  std::unordered_map<T, int> ids;       // <item, id>
  std::unordered_map<int, std::reference_wrapper<const T>> parents; // <id, parent>
  std::unordered_map<int, int> sizes;   // <root_id, #>
};

#endif /* disjoint_set_h */
