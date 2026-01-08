#ifndef LEETCODE_STUDY_GUIDE_BINARY_SEARCH_H
#define LEETCODE_STUDY_GUIDE_BINARY_SEARCH_H

#include <vector>
#include <functional>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Binary Search Algorithm Patterns
 * 
 * This module implements various binary search scenarios commonly
 * encountered in LeetCode problems, including classic binary search,
 * search in rotated arrays, and finding boundaries.
 */
class BinarySearch {
public:
    /**
     * Classic binary search in sorted array
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    template<typename T>
    static int search(const std::vector<T>& nums, const T& target);
    
    /**
     * Find first occurrence of target (left boundary)
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    template<typename T>
    static int searchFirst(const std::vector<T>& nums, const T& target);
    
    /**
     * Find last occurrence of target (right boundary)
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    template<typename T>
    static int searchLast(const std::vector<T>& nums, const T& target);
    
    /**
     * Search in rotated sorted array
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    template<typename T>
    static int searchRotated(const std::vector<T>& nums, const T& target);
    
    /**
     * Find minimum in rotated sorted array
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    template<typename T>
    static int findMin(const std::vector<T>& nums);
    
    /**
     * Search in 2D matrix (sorted rows and columns)
     * Time Complexity: O(log(m*n))
     * Space Complexity: O(1)
     */
    template<typename T>
    static bool searchMatrix(const std::vector<std::vector<T>>& matrix, const T& target);
    
    /**
     * Generic binary search with custom predicate
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    template<typename T>
    static int binarySearchGeneric(const std::vector<T>& nums, 
                                   std::function<bool(const T&)> predicate);
};

} // namespace algorithms
} // namespace leetcode_study_guide

#include "binary_search_impl.h"

#endif // LEETCODE_STUDY_GUIDE_BINARY_SEARCH_H