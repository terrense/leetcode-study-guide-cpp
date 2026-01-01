/**
 * @file array_examples.cpp
 * @brief Example usage of Array data structure and algorithms
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/array.h"
#include <iostream>
#include <vector>

using namespace leetcode_study_guide::data_structures;

void demonstrate_basic_operations() {
    std::cout << "=== Basic Array Operations ===" << std::endl;
    
    Array<int> arr{1, 2, 3, 4, 5};
    
    std::cout << "Initial array: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Insert and delete operations
    arr.insert(2, 10);
    std::cout << "After inserting 10 at index 2: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    arr.erase(2);
    std::cout << "After removing element at index 2: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Search operations
    int search_value = 3;
    int index = arr.linear_search(search_value);
    std::cout << "Linear search for " << search_value << ": index " << index << std::endl;
    
    index = arr.binary_search(search_value);
    std::cout << "Binary search for " << search_value << ": index " << index << std::endl;
}

void demonstrate_two_pointers() {
    std::cout << "\n=== Two Pointers Algorithms ===" << std::endl;
    
    // Two sum on sorted array
    Array<int> sorted_arr{1, 2, 3, 4, 6, 8, 9};
    int target = 10;
    auto result = sorted_arr.two_sum_sorted(target);
    
    std::cout << "Two sum for target " << target << ": ";
    if (result.first != -1) {
        std::cout << "indices " << result.first << " and " << result.second 
                  << " (values " << sorted_arr[result.first] << " + " 
                  << sorted_arr[result.second] << ")" << std::endl;
    } else {
        std::cout << "not found" << std::endl;
    }
    
    // Remove duplicates
    Array<int> dup_arr{1, 1, 2, 2, 2, 3, 4, 4, 5};
    std::cout << "Array with duplicates: ";
    for (size_t i = 0; i < dup_arr.size(); ++i) {
        std::cout << dup_arr[i] << " ";
    }
    std::cout << std::endl;
    
    size_t new_length = dup_arr.remove_duplicates_sorted();
    std::cout << "After removing duplicates (length " << new_length << "): ";
    for (size_t i = 0; i < dup_arr.size(); ++i) {
        std::cout << dup_arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Palindrome check
    Array<int> palindrome{1, 2, 3, 2, 1};
    std::cout << "Is [1, 2, 3, 2, 1] a palindrome? " 
              << (palindrome.is_palindrome() ? "Yes" : "No") << std::endl;
}

void demonstrate_sliding_window() {
    std::cout << "\n=== Sliding Window Algorithms ===" << std::endl;
    
    Array<int> arr{2, 1, 5, 1, 3, 2};
    size_t k = 3;
    
    int max_sum = arr.max_sum_subarray(k);
    std::cout << "Maximum sum of subarray of size " << k << ": " << max_sum << std::endl;
    
    // Longest subarray with k distinct elements
    Array<int> distinct_arr{1, 2, 1, 2, 3};
    size_t max_distinct = 2;
    size_t longest = distinct_arr.longest_subarray_k_distinct(max_distinct);
    std::cout << "Longest subarray with at most " << max_distinct 
              << " distinct elements: " << longest << std::endl;
}

void demonstrate_sorting() {
    std::cout << "\n=== Sorting Algorithms ===" << std::endl;
    
    // Merge sort
    Array<int> merge_arr{64, 34, 25, 12, 22, 11, 90};
    std::cout << "Before merge sort: ";
    for (size_t i = 0; i < merge_arr.size(); ++i) {
        std::cout << merge_arr[i] << " ";
    }
    std::cout << std::endl;
    
    merge_arr.merge_sort();
    std::cout << "After merge sort: ";
    for (size_t i = 0; i < merge_arr.size(); ++i) {
        std::cout << merge_arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Quick sort
    Array<int> quick_arr{64, 34, 25, 12, 22, 11, 90};
    std::cout << "Before quick sort: ";
    for (size_t i = 0; i < quick_arr.size(); ++i) {
        std::cout << quick_arr[i] << " ";
    }
    std::cout << std::endl;
    
    quick_arr.quick_sort();
    std::cout << "After quick sort: ";
    for (size_t i = 0; i < quick_arr.size(); ++i) {
        std::cout << quick_arr[i] << " ";
    }
    std::cout << std::endl;
}

void demonstrate_advanced_algorithms() {
    std::cout << "\n=== Advanced Array Algorithms ===" << std::endl;
    
    // Maximum subarray sum (Kadane's algorithm)
    std::vector<int> kadane_arr{-2, -3, 4, -1, -2, 1, 5, -3};
    int max_sum = max_subarray_sum(kadane_arr);
    std::cout << "Maximum subarray sum: " << max_sum << std::endl;
    
    // Dutch flag partitioning
    std::vector<int> dutch_arr{0, 1, 2, 0, 1, 2, 1, 0};
    std::cout << "Before Dutch flag partition: ";
    for (int val : dutch_arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    dutch_flag_partition(dutch_arr, 1);
    std::cout << "After Dutch flag partition (pivot=1): ";
    for (int val : dutch_arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Array rotation
    std::vector<int> rotate_arr{1, 2, 3, 4, 5, 6, 7};
    std::cout << "Before rotation: ";
    for (int val : rotate_arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    rotate_array(rotate_arr, 3);
    std::cout << "After rotating right by 3: ";
    for (int val : rotate_arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Find all pairs with target sum
    std::vector<int> pairs_arr{1, 5, 7, -1, 5};
    int target = 6;
    auto pairs = find_all_pairs_sum(pairs_arr, target);
    std::cout << "All pairs with sum " << target << ": ";
    for (const auto& pair : pairs) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "LeetCode Study Guide - Array Data Structure Examples" << std::endl;
    std::cout << "====================================================" << std::endl;
    
    demonstrate_basic_operations();
    demonstrate_two_pointers();
    demonstrate_sliding_window();
    demonstrate_sorting();
    demonstrate_advanced_algorithms();
    
    std::cout << "\nAll array examples completed successfully!" << std::endl;
    return 0;
}