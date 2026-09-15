/**
 * @file SBubbleSortAlgo.tpp
 * @brief Template implementation of SBubbleSortAlgo using Bubble Sort.
 * @author Soumyajit
 * @date 2026
 *
 * @complexity
 *   - Best Case:    O(n)       (already sorted; early exit optimization possible)
 *   - Worst Case:   O(n^2)     (reverse order input)
 *   - Average Case: O(n^2)     (typical random input)
 *
 * @space
 *   - Auxiliary Space: O(1) (in-place sorting, only uses a few extra variables)
 */

#pragma once
#include <iterator>
#include <algorithm> // for std::iter_swap

/**
 * @brief Executes the Bubble Sort algorithm on the given range.
 *
 * @tparam Iterator Random-access iterator type (e.g., std::vector<T>::iterator).
 * @param[in] begin Iterator pointing to the first element of the range.
 * @param[in] end   Iterator pointing past the last element of the range.
 *
 * @return void
 *
 * @remark Performs Bubble Sort in-place. The algorithm repeatedly traverses
 *         the range, swapping adjacent elements until the sequence is sorted.
 *         Inefficient for large datasets, but useful for educational purposes
 *         and small collections.
 */
template <typename Iterator>
void SBubbleSortAlgo<Iterator>::execute(Iterator begin, Iterator end) 
{
    // Calculate the number of elements in the range [begin, end)
    typename std::iterator_traits<Iterator>::difference_type elementCount = std::distance(begin, end);

    // If the range has 0 or 1 elements, it is already sorted
    if (elementCount <= 1) return;

    // Outer loop: perform (elementCount - 1) passes
    for (typename std::iterator_traits<Iterator>::difference_type pass = 0; pass < elementCount - 1; ++pass) 
    {
        bool swapped = false; // optimization: track if any swap occurred

        // Inner loop: bubble the largest element to the end of the unsorted portion
        for (Iterator current = begin; current < end - pass - 1; ++current) 
        {
            Iterator next = current + 1;

            // Swap adjacent elements if they are out of order
            if (*current > *next) 
            {
                std::iter_swap(current, next);
                swapped = true;
            }
        }

        // Early exit: if no swaps occurred in this pass, the range is already sorted
        if (!swapped) break;
    }
}
