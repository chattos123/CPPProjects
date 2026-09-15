/**
 * @file SQuickSortAlgo.tpp
 * @brief Template implementation of SQuickSortAlgo using Quick Sort.
 * @author Soumyajit
 * @date 2026
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
#include <iterator>
#include <algorithm> // for std::iter_swap

/**
 * @brief Partitions the range around a pivot element.
 *
 * @tparam Iterator Random-access iterator type.
 * @param[in] begin Iterator pointing to the first element of the range.
 * @param[in] end   Iterator pointing past the last element of the range.
 *
 * @return Iterator pointing to the pivot’s final position.
 *
 * @remark Elements less than or equal to the pivot are moved before it,
 *         and elements greater than the pivot are moved after it.
 */
template <typename Iterator>
Iterator SQuickSortAlgo<Iterator>::partition(Iterator begin, Iterator end) 
{
    // Choose the last element as pivot
    Iterator pivotIterator = end - 1;
    Iterator smallerElementBoundary = begin;

    // Traverse elements before pivot
    for (Iterator current = begin; current < pivotIterator; ++current) 
    {
        if (*current <= *pivotIterator) 
        {
            // Place smaller element at the boundary
            std::iter_swap(smallerElementBoundary, current);
            ++smallerElementBoundary;
        }
    }

    // Place pivot in its correct sorted position
    std::iter_swap(smallerElementBoundary, pivotIterator);
    return smallerElementBoundary; // pivot’s final position
}

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
template <typename Iterator>
Iterator SQuickSortAlgo<Iterator>::partitionMedian(Iterator begin, Iterator end) 
{
    Iterator first = begin;
    Iterator last = end - 1;
    Iterator middle = begin + std::distance(begin, end) / 2;

    // Median-of-three pivot selection
    if (*middle < *first) std::iter_swap(middle, first);
    if (*last   < *first) std::iter_swap(last, first);
    if (*last   < *middle) std::iter_swap(last, middle);

    Iterator pivotIterator = middle; // pivot chosen as median
    Iterator smallerElementBoundary = begin;

    // Traverse elements before pivot
    for (Iterator current = begin; current < end; ++current) 
    {
        if (current == pivotIterator) continue; // skip pivot itself

        if (*current <= *pivotIterator) 
        {
            std::iter_swap(smallerElementBoundary, current);
            ++smallerElementBoundary;
        }
    }

    // Place pivot in its correct sorted position
    std::iter_swap(smallerElementBoundary, pivotIterator);
    return smallerElementBoundary; // pivot’s final position
}


template <typename Iterator>
Iterator SQuickSortAlgo<Iterator>::partitionBSort(Iterator begin, Iterator end) 
{
    // Choose the middle element as pivot
    Iterator middle = begin + std::distance(begin, end) / 2;
    Iterator pivotIterator = middle;

    // Move pivot to the end temporarily
    std::iter_swap(pivotIterator, end - 1);
    pivotIterator = end - 1;

    Iterator smallerElementBoundary = begin;

    // Traverse elements before pivot
    for (Iterator current = begin; current < pivotIterator; ++current) 
    {
        if (*current <= *pivotIterator) 
        {
            std::iter_swap(smallerElementBoundary, current);
            ++smallerElementBoundary;
        }
    }

    // Place pivot in its correct sorted position
    std::iter_swap(smallerElementBoundary, pivotIterator);
    return smallerElementBoundary; // pivot’s final position
}


/**
 * @brief Recursively sorts a range using quick sort.
 *
 * @tparam Iterator Random-access iterator type.
 * @param[in] begin Iterator pointing to the first element of the range.
 * @param[in] end   Iterator pointing past the last element of the range.
 *
 * @return void
 *
 * @remark Splits the range into partitions and recursively sorts each side.
 */
template <typename Iterator>
void SQuickSortAlgo<Iterator>::quicksort(Iterator begin, Iterator end) 
{
    typename std::iterator_traits<Iterator>::difference_type elementCount = std::distance(begin, end);

    // Base case: ranges of size 0 or 1 are already sorted
    if (elementCount > 1) 
    {
        // Partition the range and get pivot position
        Iterator pivotPosition = partition(begin, end);

        // Recursively sort elements before and after pivot
        quicksort(begin, pivotPosition);
        quicksort(pivotPosition + 1, end);
    }
}

/**
 * @brief Executes the quick sort algorithm on the given range.
 *
 * @tparam Iterator Random-access iterator type.
 * @param[in] begin Iterator pointing to the first element of the range.
 * @param[in] end   Iterator pointing past the last element of the range.
 *
 * @return void
 *
 * @remark Entry point for quick sort. Calls quicksort() internally.
 */
template <typename Iterator>
void SQuickSortAlgo<Iterator>::execute(Iterator begin, Iterator end) 
{
    quicksort(begin, end);
}
