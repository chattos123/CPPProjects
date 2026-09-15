/**
 * @file SMergeSortAlgo.tpp
 * @brief Template implementation of SMergeSortAlgo.
 */

/**
 * @file SMergeSortAlgo.tpp
 * @brief Template implementation of SMergeSortAlgo using Merge Sort.
 * @author Soumyajit
 * @date 2026
 *
 * @remark Implements a generic merge sort algorithm for random-access iterators.
 *         The algorithm recursively divides the range into halves, sorts each half,
 *         and merges them back together using a temporary buffer.
 */

#pragma once
#include <vector>
#include <iterator>
#include <algorithm> // for std::move

/**
 * @brief Merges two sorted halves of a range into a single sorted sequence.
 *
 * @tparam Iterator Random-access iterator type.
 * @param[in] begin Iterator pointing to the first element of the left half.
 * @param[in] mid   Iterator pointing to the start of the right half.
 * @param[in] end   Iterator pointing past the last element of the right half.
 *
 * @return void
 *
 * @remark Uses a temporary buffer to merge elements from both halves and moves
 *         them back into the original range.
 */
template <typename Iterator>
void SMergeSortAlgo<Iterator>::merge(Iterator begin, Iterator mid, Iterator end) 
{
    using ValueType = typename std::iterator_traits<Iterator>::value_type;
    std::vector<ValueType> mergedBuffer;

    Iterator left = begin;
    Iterator right = mid;

    // Merge elements from both halves into the buffer
    while (left != mid && right != end) 
    {
        if (*left <= *right) 
        {
            mergedBuffer.push_back(*left++);
        } 
        else 
        {
            mergedBuffer.push_back(*right++);
        }
    }

    // Copy remaining elements from the left half
    while (left != mid) {
        mergedBuffer.push_back(*left++);
    }

    // Copy remaining elements from the right half
    while (right != end) 
    {
        mergedBuffer.push_back(*right++);
    }

    // Move merged elements back into the original range
    std::move(mergedBuffer.begin(), mergedBuffer.end(), begin);
}

/**
 * @brief Recursively sorts a range using merge sort.
 *
 * @tparam Iterator Random-access iterator type.
 * @param[in] begin Iterator pointing to the first element of the range.
 * @param[in] end   Iterator pointing past the last element of the range.
 *
 * @return void
 *
 * @remark Splits the range into halves, recursively sorts each half,
 *         and merges them using the merge() function.
 */
template <typename Iterator>
void SMergeSortAlgo<Iterator>::mergesort(Iterator begin, Iterator end) 
{
    typename std::iterator_traits<Iterator>::difference_type elementCount = std::distance(begin, end);

    // Base case: ranges of size 0 or 1 are already sorted
    if (elementCount > 1) 
    {
        // Find the midpoint of the range
        Iterator mid = begin;
        std::advance(mid, elementCount / 2);

        // Recursively sort both halves
        mergesort(begin, mid);
        mergesort(mid, end);

        // Merge the sorted halves
        merge(begin, mid, end);
    }
}

/**
 * @brief Executes the merge sort algorithm on the given range.
 *
 * @tparam Iterator Random-access iterator type.
 * @param[in] begin Iterator pointing to the first element of the range.
 * @param[in] end   Iterator pointing past the last element of the range.
 *
 * @return void
 *
 * @remark Entry point for merge sort. Calls mergesort() internally.
 */
template <typename Iterator>
void SMergeSortAlgo<Iterator>::execute(Iterator begin, Iterator end) 
{
    mergesort(begin, end);
}
