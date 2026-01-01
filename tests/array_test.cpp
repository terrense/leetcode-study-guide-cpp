/**
 * @file array_test.cpp
 * @brief Unit tests for Array data structure
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/array.h"
#include <gtest/gtest.h>
#include <vector>

using namespace leetcode_study_guide::data_structures;

class ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test data
        test_array = Array<int>{1, 2, 3, 4, 5};
        sorted_array = Array<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    }
    
    Array<int> test_array;
    Array<int> sorted_array;
};

// Basic Operations Tests
TEST_F(ArrayTest, BasicOperations) {
    EXPECT_EQ(test_array.size(), 5);
    EXPECT_FALSE(test_array.empty());
    
    // Test element access
    EXPECT_EQ(test_array[0], 1);
    EXPECT_EQ(test_array[4], 5);
    
    // Test push_back
    test_array.push_back(6);
    EXPECT_EQ(test_array.size(), 6);
    EXPECT_EQ(test_array[5], 6);
    
    // Test insert
    test_array.insert(2, 10);
    EXPECT_EQ(test_array[2], 10);
    EXPECT_EQ(test_array.size(), 7);
    
    // Test erase
    test_array.erase(2);
    EXPECT_EQ(test_array[2], 3);
    EXPECT_EQ(test_array.size(), 6);
}

// Search Tests
TEST_F(ArrayTest, SearchOperations) {
    // Linear search
    EXPECT_EQ(test_array.linear_search(3), 2);
    EXPECT_EQ(test_array.linear_search(10), -1);
    
    // Binary search (on sorted array)
    EXPECT_EQ(sorted_array.binary_search(5), 4);
    EXPECT_EQ(sorted_array.binary_search(1), 0);
    EXPECT_EQ(sorted_array.binary_search(10), 9);
    EXPECT_EQ(sorted_array.binary_search(15), -1);
}

// Two Pointers Tests
TEST_F(ArrayTest, TwoPointersAlgorithms) {
    // Two sum on sorted array
    auto result = sorted_array.two_sum_sorted(11);
    EXPECT_NE(result.first, -1);
    EXPECT_EQ(sorted_array[result.first] + sorted_array[result.second], 11);
    
    // Two sum not found
    result = sorted_array.two_sum_sorted(25);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
    
    // Remove duplicates
    Array<int> dup_array{1, 1, 2, 2, 3, 3, 4};
    size_t new_length = dup_array.remove_duplicates_sorted();
    EXPECT_EQ(new_length, 4);
    EXPECT_EQ(dup_array[0], 1);
    EXPECT_EQ(dup_array[1], 2);
    EXPECT_EQ(dup_array[2], 3);
    EXPECT_EQ(dup_array[3], 4);
    
    // Palindrome check
    Array<int> palindrome{1, 2, 3, 2, 1};
    EXPECT_TRUE(palindrome.is_palindrome());
    
    Array<int> not_palindrome{1, 2, 3, 4, 5};
    EXPECT_FALSE(not_palindrome.is_palindrome());
}

// Sliding Window Tests
TEST_F(ArrayTest, SlidingWindowAlgorithms) {
    Array<int> window_array{2, 1, 5, 1, 3, 2};
    
    // Maximum sum subarray of size k
    int max_sum = window_array.max_sum_subarray(3);
    EXPECT_EQ(max_sum, 9); // [5, 1, 3]
    
    // Longest subarray with k distinct elements
    Array<int> distinct_array{1, 2, 1, 2, 3};
    size_t longest = distinct_array.longest_subarray_k_distinct(2);
    EXPECT_EQ(longest, 4); // [1, 2, 1, 2]
}

// Sorting Tests
TEST_F(ArrayTest, SortingAlgorithms) {
    Array<int> unsorted{5, 2, 8, 1, 9, 3};
    std::vector<int> expected{1, 2, 3, 5, 8, 9};
    
    // Test merge sort
    Array<int> merge_test = unsorted;
    merge_test.merge_sort();
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(merge_test[i], expected[i]);
    }
    
    // Test quick sort
    Array<int> quick_test = unsorted;
    quick_test.quick_sort();
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(quick_test[i], expected[i]);
    }
    
    // Test heap sort
    Array<int> heap_test = unsorted;
    heap_test.heap_sort();
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(heap_test[i], expected[i]);
    }
}

// Standalone Algorithm Tests
TEST(StandaloneAlgorithmsTest, MaxSubarraySum) {
    std::vector<int> arr{-2, -3, 4, -1, -2, 1, 5, -3};
    int max_sum = max_subarray_sum(arr);
    EXPECT_EQ(max_sum, 7); // [4, -1, -2, 1, 5]
}

TEST(StandaloneAlgorithmsTest, DutchFlagPartition) {
    std::vector<int> arr{0, 1, 2, 0, 1, 2, 1, 0};
    dutch_flag_partition(arr, 1);
    
    // Check that all 0s come before 1s, and all 2s come after 1s
    bool found_one = false, found_two = false;
    for (int val : arr) {
        if (val == 1) found_one = true;
        if (val == 2) found_two = true;
        
        if (found_two && val != 2) {
            FAIL() << "Found non-2 value after 2";
        }
        if (found_one && !found_two && val == 0) {
            FAIL() << "Found 0 after 1 but before 2";
        }
    }
}

TEST(StandaloneAlgorithmsTest, RotateArray) {
    std::vector<int> arr{1, 2, 3, 4, 5, 6, 7};
    std::vector<int> expected{5, 6, 7, 1, 2, 3, 4};
    
    rotate_array(arr, 3);
    
    EXPECT_EQ(arr.size(), expected.size());
    for (size_t i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(StandaloneAlgorithmsTest, FindAllPairsSum) {
    std::vector<int> arr{1, 5, 7, -1, 5};
    int target = 6;
    
    auto pairs = find_all_pairs_sum(arr, target);
    
    // Should find pairs (0,2) -> 1+5=6 and (1,3) -> 5+(-1)=4... wait, that's wrong
    // Let me recalculate: 1+5=6, 5+1=6, 7+(-1)=6, -1+7=6, 5+1=6
    // So pairs should be (0,1), (0,4), (2,3)
    EXPECT_GE(pairs.size(), 1);
    
    // Verify each pair sums to target
    for (const auto& pair : pairs) {
        EXPECT_EQ(arr[pair.first] + arr[pair.second], target);
    }
}