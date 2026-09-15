/**
 * @file QuickSortAlgo.tpp
 * @brief Template implementation of QuickSortAlgo.
 */

#pragma once

template <typename Iterator>
void QuickSortAlgo<Iterator>::execute(Iterator begin, Iterator end) 
{
    std::sort(begin, end);
}