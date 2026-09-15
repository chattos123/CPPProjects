/**
 * @file SBubbleSortAlgo.h
 * @brief Declares the BubbleSort algorithm implementation class.
 * @author Soumyajit
 * @date 2026
 *
 * @remark This class provides a generic implementation of the Bubble Sort
 *         algorithm for random-access iterators. It inherits from the
 *         ISortAlgorithm interface and overrides the execute() method.
 *
 * @complexity
 *   - Best Case:    O(n)       (when the input is already sorted; optimized with early exit)
 *   - Worst Case:   O(n^2)     (when the input is in reverse order)
 *   - Average Case: O(n^2)     (typical performance across random inputs)
 *
 * @space
 *   - Auxiliary Space: O(1) (in-place sorting, only uses a few extra variables)
 */

#pragma once
#include "ISortAlgorithm.h"

/**
 * @class SBubbleSortAlgo
 * @brief Implements the Bubble Sort algorithm for a given iterator type.
 *
 * @tparam Iterator Random-access iterator type (e.g., std::vector<T>::iterator).
 *
 * @remark The class provides a simple in-place sorting algorithm that repeatedly
 *         swaps adjacent elements if they are out of order. While inefficient
 *         for large datasets, Bubble Sort is useful for educational purposes
 *         and small collections.
 */
template <typename Iterator>
class SBubbleSortAlgo : public ISortAlgorithm<Iterator> 
{
public:
    /**
     * @brief Executes the Bubble Sort algorithm on the given range.
     *
     * @param[in] begin Iterator pointing to the first element of the range.
     * @param[in] end   Iterator pointing past the last element of the range.
     *
     * @return void
     *
     * @remark Performs Bubble Sort in-place. The algorithm repeatedly traverses
     *         the range, swapping adjacent elements until the sequence is sorted.
     */
    void execute(Iterator begin, Iterator end) override;
};

// Include template implementation
#include "SBubbleSortAlgo.tpp"
