/**
 * @file ISortAlgorithm.h
 * @brief Declares a generic interface for sorting algorithms using iterators.
 * @author Soumyajit
 * @date 2026
 */

#pragma once

#include <iterator>
#include "ExportMacro_Algo.h"

/**
 * @class ISortAlgorithm
 * @brief Abstract interface for sorting algorithms operating on iterators.
 *
 * @tparam Iterator Iterator type (random-access preferred).
 */
template <typename Iterator>
class ALGO_API ISortAlgorithm 
{
public:
    /**
     * @brief Executes the sorting algorithm on the given range.
     *
     * @param[in] begin Iterator pointing to the first element.
     * @param[in] end Iterator pointing past the last element.
     */
    virtual void execute(Iterator begin, Iterator end) = 0;

    /// Virtual destructor for safe polymorphic cleanup.
    virtual ~ISortAlgorithm() = default;
};
