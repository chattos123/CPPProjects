/**
 * @file SMergeSortAlgo.h
 * @brief Declares the MergeSort algorithm implementation class.
 * @author Soumyajit
 * @date 2026
 *
 * @remark This class provides a generic implementation of the Merge Sort
 *         algorithm for random-access iterators. It inherits from the
 *         ISortAlgorithm interface and overrides the execute() method.
 *
 * @complexity
 *   - Best Case:    O(n log n)  (even if the data is already sorted, merge sort still divides and merges)
 *   - Worst Case:   O(n log n)  (always divides into halves and merges)
 *   - Average Case: O(n log n)  (typical performance across random inputs)
 *
 * @space
 *   - Auxiliary Space: O(n) due to temporary buffer used during merging.
 */
#pragma once
#include "ISortAlgorithm.h"
#include <vector>
#include <iterator>

/**
 * @class SMergeSortAlgo
 * @brief Implements the Merge Sort algorithm for a given iterator type.
 *
 * @tparam Iterator Random-access iterator type (e.g., std::vector<T>::iterator).
 *
 * @remark The class provides private helper functions merge() and mergesort()
 *         to perform recursive sorting and merging of ranges. The public
 *         execute() method serves as the entry point for sorting.
 */
template <typename Iterator>
class SMergeSortAlgo : public ISortAlgorithm<Iterator> 
{
private:
    /**
     * @brief Merges two sorted halves of a range into a single sorted sequence.
     *
     * @param[in] begin Iterator pointing to the first element of the left half.
     * @param[in] mid   Iterator pointing to the start of the right half.
     * @param[in] end   Iterator pointing past the last element of the right half.
     *
     * @return void
     *
     * @remark Uses a temporary buffer to merge elements from both halves and
     *         moves them back into the original range.
     */
    void merge(Iterator begin, Iterator mid, Iterator end);

    /**
     * @brief Recursively sorts a range using merge sort.
     *
     * @param[in] begin Iterator pointing to the first element of the range.
     * @param[in] end   Iterator pointing past the last element of the range.
     *
     * @return void
     *
     * @remark Splits the range into halves, recursively sorts each half,
     *         and merges them using the merge() function.
     */
    void mergesort(Iterator begin, Iterator end);

public:
    /**
     * @brief Executes the merge sort algorithm on the given range.
     *
     * @param[in] begin Iterator pointing to the first element of the range.
     * @param[in] end   Iterator pointing past the last element of the range.
     *
     * @return void
     *
     * @remark Entry point for merge sort. Calls mergesort() internally.
     */
    void execute(Iterator begin, Iterator end) override;
};

// Include template implementation
#include "SMergeSortAlgo.tpp"
