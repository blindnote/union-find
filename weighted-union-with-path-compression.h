#ifndef WeightedAndPathCompressedQU_h
#define WeightedAndPathCompressedQU_h

#include "weighted-union.h"
#include "quick-union-with-path-compression.h"

/**
 * Starting from an empty data structure, any sequence of
 * M union/find operations on N items takes O(N + M*lgN) time
 * (Proof is very difficult)
 * - In theory, WQUPC is not quite linear
 * - In practice, WQUPC is linear (because lg*N is a constant in this universe)
 */
template <typename T>
class WeightedAndPathCompressedQU: public WeightedQU<T>
                                 , public PathCompressedQU<T> {
};

#endif /* WeightedAndPathCompressedQU_h */
