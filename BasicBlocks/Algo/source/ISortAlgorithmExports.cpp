#include <vector>
#include "ISortAlgorithm.h"


// Explicit instantiation for std::vector<int>::iterator
template class ALGO_API ISortAlgorithm<std::vector<int>::iterator>;
template class ALGO_API ISortAlgorithm<std::vector<double>::iterator>;
template class ALGO_API ISortAlgorithm<std::vector<char>::iterator>;
