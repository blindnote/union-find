//
//  Ref.: https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf

#include <vector>
#include "disjoint-set.h"
#include "quick-find.h"
#include "quick-union.h"
#include "weighted-union.h"
#include "quick-union-with-path-compression.h"
#include "weighted-union-with-path-compression.h"

using namespace std;

/*
class UnionFind {
public:
  UnionFind(int n)
  : count(n) {
    id = new int[n];
    for (int i = 0; i < n; i++) {
      id[i] = i; // set rep id of each object to itself
    }
  }
  
  ~UnionFind() {
    delete[] id;
  }
  
  virtual bool find(int p, int q) = 0;
  virtual void join(int p, int q) = 0;
  
  
protected:
  int count = 0;
  int* id = nullptr;
};


// eager approach
class QuickFind: public UnionFind {
public:
  QuickFind(int n)
    : UnionFind(n) {}
  
  virtual bool find(int p, int q) override {
    return id[p] == id[q]; // O(1)
  }
  
  // merge all objects in the same group of p into group of q
  virtual void join(int p, int q) override {
    int pid = id[p];
    int qid = id[q];
    // many values can change
    // UNION too expensive (could be N)
    // Trees are flat, but too expensive to keep them flat.
    for(int i = 0; i < count ; i++) { // O(N)
      if (id[i] == pid)
        id[i] = qid;
    }
  }
};

// lazy approach
class QuickUnion: public UnionFind {
public:
  QuickUnion(int n)
  : UnionFind(n) {}
  
  virtual bool find(int p, int q) override {
    // time proportional to depth of p and q
    // FIND too expensive (could be N)
    return root(p) == root(q);
  }
  
  virtual void join(int p, int q) override {
    // time proportional to depth of p and q
    // nned to do "FIND" to do "UNION"
    int prid = root(p);
    int qrid = root(q);
    id[prid] = qrid; // only 1 value changes, trees can get tall
  }
  
protected:
  virtual int root(int i) {
    // Root of i is id[id[id[....id[i]....]]]
    // keep going until it doesn't change
    while (i != id[i])
      i = id[i];
    return i;
  }
};


// to avoid tall trees
// keep track of size of each component
// balance by linking small tree below large one
class WeightedQU: virtual public QuickUnion {
public:
  WeightedQU(int n)
  : QuickUnion(n) {
    sz = new int[n];
    memset(sz, 0, sizeof(int) * n);
  }
  
  ~WeightedQU() {
    delete[] sz;
  }
  
  // FIND: time proportional to depth of p and q
  //       depth is at most lgN

  virtual void join(int p, int q) override {
    int prid = root(p);
    int qrid = root(q);
    // merge smaller tree into larger tree
    // UNION: takes constant time, given roots
    if (sz[prid] < sz[qrid]) {
      id[prid] = qrid;
      sz[qrid] += sz[prid];
    } else {
      id[qrid] = prid;
      sz[prid] += sz[qrid];
    }
  }
  
protected:
  int* sz = nullptr;
};


class QUWithPathCompression: virtual public QuickUnion {
public:
  QUWithPathCompression(int n)
    : QuickUnion(n) {
  }
  
protected:
  int root(int i) override {
    return root_in_practice(i);
  }
  
  // just after computing the root of i,
  // set the id of each examined node to root(i)
  int root_standard(int i) {
    int rid = i;
    // Root of i is id[id[id[....id[i]....]]]
    // keep going until it doesn't change
    while (rid != id[rid]) {
      rid = id[rid];
    }
    
    while (i != rid) {
      int parent = id[i];
      id[i] = rid;
      i = parent;
    }
    return rid;
  }
  
  int root_standard_recur(int i) {
    if (id[i] == i)
      return i;
    
    return id[i] = root_standard_recur(id[i]);
  }
  
  int root_in_practice(int i) {
    while (i != id[i]) {
      // make every other node in path point to its grandparent
      // keep tree almost completely flat
      id[i] = id[id[i]];
      i = id[i];
    }
    return i;
  }
  
};


class WeightedQUWithPathCompression: public WeightedQU, public QUWithPathCompression {
public:
  WeightedQUWithPathCompression(int n)
  : QuickUnion(n), WeightedQU(n), QUWithPathCompression(n) {
  }
};

*/

int main(int argc, const char * argv[]) {
//  WeightedQUWithPathCompression wqupc(10);
//  wqupc.find(2, 3);
  
  DisjointSet<int> dataset;
  for (int i = 0; i < 10; i++)
    dataset.Add(std::forward<int>(i));
  
  DisjointSet<char> charset;
  for (char c = 'a'; c < 'h'; c++)
    charset.Add(std::forward<char>(c));
  cout << charset;
  
  QuickUnion<char> quc;
  quc.Find(charset, 'c', 'd');
  quc.Join(charset, 'd', 'e');
  cout << charset;
  
  cout << "------------------- Quick Find --------------------" << endl;
  QuickFind<int> qf;
  qf.Find(dataset, 2, 3);
  qf.Join(dataset, 2, 3);
  qf.Join(dataset, 3, 4);
  cout << dataset;
  qf.Join(dataset, 2, 1);
  qf.Find(dataset, 2, 4);
  cout << dataset;

  cout << "------------------- Quick Union --------------------" << endl;
  QuickUnion<int> qu;
  cout << qu.Find(dataset, 1, 7) << endl;
  qu.Join(dataset, 1, 7);
  cout << dataset;
  cout << qu.Find(dataset, 1, 7) << endl;

  cout << "--------------- Weighted Quick Union ----------------" << endl;
  WeightedQU<int> wqu;
  cout << qu.Find(dataset, 0, 9) << endl;
  wqu.Join(dataset, 0, 9);
  cout << dataset;
  cout << qu.Find(dataset, 0, 9) << endl;
  wqu.Join(dataset, 0, 7);
  cout << dataset;

  cout << "------------ Path Compressed Quick Union --------------" << endl;
  PathCompressedQU<int> pcqu;
  cout << pcqu.Find(dataset, 4, 8) << endl;
  cout << dataset;
  pcqu.Join(dataset, 4, 8);
  cout << dataset;

  cout << "------------ Weighted Quick Union with Path Compression --------------" << endl;
  WeightedAndPathCompressedQU<int> wpcqu;
  cout << pcqu.Find(dataset, 5, 6) << endl;
  cout << dataset;
  pcqu.Join(dataset, 5, 6);
  cout << dataset;
  pcqu.Join(dataset, 5, 4);
  cout << dataset;
 
  return 0;
}
