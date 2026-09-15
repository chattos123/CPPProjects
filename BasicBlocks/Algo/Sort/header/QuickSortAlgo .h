/**
 * @file QuickSortAlgo.h
 * @brief Declares QuickSort algorithm implementation using STL sort.
 */

#pragma once
#include "ISortAlgorithm.h"
#include <algorithm>

template <typename Iterator>
class QuickSortAlgo : public ISortAlgorithm<Iterator> 
{
public:
    void execute(Iterator begin, Iterator end) override;
};

#include "QuickSortAlgo.tpp"  // include template implementation
