/**
 * @file SQuickSortAlgo.h
 * @brief Declares the QuickSort algorithm implementation class.
 * @author Soumyajit
 * @date 2026
 *
 * @remark This class provides a generic implementation of the Quick Sort
 *         algorithm for random-access iterators. It inherits from the
 *         ISortAlgorithm interface and overrides the execute() method.
 *
 * @complexity
 *   - Best Case:    O(n log n)   (balanced partitions)
 *   - Worst Case:   O(n^2)       (highly unbalanced partitions, e.g., sorted input with poor pivot choice)
 *   - Average Case: O(n log n)   (typical random input)
 *
 * @space
 *   - Auxiliary Space: O(log n) due to recursion stack.
 */

#pragma once
#include "ISortAlgorithm.h"
#include <iterator>

/**
 * @class SQuickSortAlgo
 * @brief Implements the Quick Sort algorithm for a given iterator type.
 *
 * @tparam Iterator Random-access iterator type (e.g., std::vector<T>::iterator).
 *
 * @remark The class provides private helper functions partition() and quicksort()
 *         to perform recursive sorting. The public execute() method serves as
 *         the entry point for sorting.
 */
template <typename Iterator>
class SQuickSortAlgo : public ISortAlgorithm<Iterator> 
{
private:
    /**
     * @brief Partitions the range around a pivot element.
     *
     * @param[in] begin Iterator pointing to the first element of the range.
     * @param[in] end   Iterator pointing past the last element of the range.
     *
     * @return Iterator pointing to the pivot’s final position.
     *
     * @remark Elements less than the pivot are moved before it, and elements
     *         greater than the pivot are moved after it.
     */
    Iterator partition(Iterator begin, Iterator end);

    /**
     * @brief Partitions the range around a pivot element using median-of-three strategy.
     *
     * @tparam Iterator Random-access iterator type.
     * @param[in] begin Iterator pointing to the first element of the range.
     * @param[in] end   Iterator pointing past the last element of the range.
     *
     * @return Iterator pointing to the pivot’s final position.
     *
     * @remark Median-of-three chooses the pivot as the median of the first,
     *         middle, and last elements. This reduces the likelihood of
     *         worst-case O(n^2) behavior on sorted input.
     */
    Iterator partitionMedian(Iterator begin, Iterator end);

    Iterator partitionBSort(Iterator begin, Iterator end);

    /**
     * @brief Recursively sorts a range using quick sort.
     *
     * @param[in] begin Iterator pointing to the first element of the range.
     * @param[in] end   Iterator pointing past the last element of the range.
     *
     * @return void
     *
     * @remark Splits the range into partitions and recursively sorts each side.
     */
    void quicksort(Iterator begin, Iterator end);

public:
    /**
     * @brief Executes the quick sort algorithm on the given range.
     *
     * @param[in] begin Iterator pointing to the first element of the range.
     * @param[in] end   Iterator pointing past the last element of the range.
     *
     * @return void
     *
     * @remark Entry point for quick sort. Calls quicksort() internally.
     */
    void execute(Iterator begin, Iterator end) override;
};

// Include template implementation
#include "SQuickSortAlgo.tpp"
