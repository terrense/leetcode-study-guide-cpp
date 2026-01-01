/**
 * @file array.h
 * @brief Array data structure implementations and algorithms for the LeetCode Study Guide
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_ARRAY_H
#define LEETCODE_STUDY_GUIDE_ARRAY_H

#include "../common.h"
#include <vector>
#include <algorithm>
#include <functional>

namespace leetcode_study_guide {
namespace data_structures {

/**
 * @brief Dynamic array implementation with common operations and algorithms
 * 
 * This class provides a comprehensive implementation of array operations
 * commonly used in LeetCode problems, including two pointers technique,
 * sliding window, and various sorting algorithms.
 */
template<typename T>
class Array {
public:
    /**
     * @brief Default constructor
     */
    Array() = default;

    /**
     * @brief Constructor with initial capacity
     * @param capacity Initial capacity of the array
     */
    explicit Array(size_t capacity);

    /**
     * @brief Constructor with initial values
     * @param values Initial values to populate the array
     */
    Array(const std::vector<T>& values);

    /**
     * @brief Constructor with initializer list
     * @param init_list Initializer list of values
     */
    Array(std::initializer_list<T> init_list);

    // Basic Operations

    /**
     * @brief Insert element at the end
     * @param value Value to insert
     * Time Complexity: O(1) amortized
     * Space Complexity: O(1)
     */
    void push_back(const T& value);

    /**
     * @brief Insert element at specific index
     * @param index Index to insert at
     * @param value Value to insert
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void insert(size_t index, const T& value);

    /**
     * @brief Remove element from the end
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void pop_back();

    /**
     * @brief Remove element at specific index
     * @param index Index to remove from
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void erase(size_t index);

    /**
     * @brief Search for element using linear search
     * @param value Value to search for
     * @return Index of first occurrence, or -1 if not found
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int linear_search(const T& value) const;

    /**
     * @brief Search for element using binary search (requires sorted array)
     * @param value Value to search for
     * @return Index of element, or -1 if not found
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    int binary_search(const T& value) const;

    // Two Pointers Algorithms

    /**
     * @brief Two sum problem using two pointers (requires sorted array)
     * @param target Target sum
     * @return Pair of indices that sum to target, or {-1, -1} if not found
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    std::pair<int, int> two_sum_sorted(const T& target) const;

    /**
     * @brief Remove duplicates from sorted array in-place
     * @return New length of array after removing duplicates
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    size_t remove_duplicates_sorted();

    /**
     * @brief Check if array is palindrome using two pointers
     * @return True if array is palindrome, false otherwise
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool is_palindrome() const;

    // Sliding Window Algorithms

    /**
     * @brief Find maximum sum of subarray of size k
     * @param k Size of the window
     * @return Maximum sum of subarray of size k
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    T max_sum_subarray(size_t k) const;

    /**
     * @brief Find length of longest subarray with at most k distinct elements
     * @param k Maximum number of distinct elements
     * @return Length of longest valid subarray
     * Time Complexity: O(n)
     * Space Complexity: O(k)
     */
    size_t longest_subarray_k_distinct(size_t k) const;

    // Sorting Algorithms

    /**
     * @brief Sort array using merge sort
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    void merge_sort();

    /**
     * @brief Sort array using quick sort
     * Time Complexity: O(n log n) average, O(n²) worst case
     * Space Complexity: O(log n) average
     */
    void quick_sort();

    /**
     * @brief Sort array using heap sort
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     */
    void heap_sort();

    // Utility Methods

    /**
     * @brief Get element at index
     * @param index Index to access
     * @return Reference to element at index
     */
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    /**
     * @brief Get element at index with bounds checking
     * @param index Index to access
     * @return Reference to element at index
     * @throws std::out_of_range if index is invalid
     */
    T& at(size_t index);
    const T& at(size_t index) const;

    /**
     * @brief Get current size of array
     * @return Number of elements in array
     */
    size_t size() const { return data_.size(); }

    /**
     * @brief Check if array is empty
     * @return True if array is empty, false otherwise
     */
    bool empty() const { return data_.empty(); }

    /**
     * @brief Clear all elements from array
     */
    void clear() { data_.clear(); }

    /**
     * @brief Get iterator to beginning
     */
    typename std::vector<T>::iterator begin() { return data_.begin(); }
    typename std::vector<T>::const_iterator begin() const { return data_.begin(); }

    /**
     * @brief Get iterator to end
     */
    typename std::vector<T>::iterator end() { return data_.end(); }
    typename std::vector<T>::const_iterator end() const { return data_.end(); }

    /**
     * @brief Convert to std::vector
     * @return Copy of internal vector
     */
    std::vector<T> to_vector() const { return data_; }

private:
    std::vector<T> data_;

    // Helper methods for sorting algorithms
    void merge_sort_helper(int left, int right);
    void merge(int left, int mid, int right);
    void quick_sort_helper(int left, int right);
    int partition(int left, int right);
    void heapify(int n, int i);
};

// Common Array Algorithms (standalone functions)

/**
 * @brief Kadane's algorithm for maximum subarray sum
 * @param arr Input array
 * @return Maximum sum of contiguous subarray
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
template<typename T>
T max_subarray_sum(const std::vector<T>& arr);

/**
 * @brief Dutch National Flag algorithm for three-way partitioning
 * @param arr Array to partition
 * @param pivot Pivot value for partitioning
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
template<typename T>
void dutch_flag_partition(std::vector<T>& arr, const T& pivot);

/**
 * @brief Rotate array to the right by k positions
 * @param arr Array to rotate
 * @param k Number of positions to rotate
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
template<typename T>
void rotate_array(std::vector<T>& arr, int k);

/**
 * @brief Find all pairs in array that sum to target
 * @param arr Input array
 * @param target Target sum
 * @return Vector of pairs that sum to target
 * Time Complexity: O(n²) brute force, O(n) with hash map
 * Space Complexity: O(n)
 */
template<typename T>
std::vector<std::pair<int, int>> find_all_pairs_sum(const std::vector<T>& arr, const T& target);

} // namespace data_structures
} // namespace leetcode_study_guide

// Include template implementation
#include "array.tpp"

#endif // LEETCODE_STUDY_GUIDE_ARRAY_H