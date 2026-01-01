/**
 * @file heap_test.cpp
 * @brief Unit tests for Heap and Trie data structures
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/heap.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace leetcode_study_guide::data_structures;

class MinHeapTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create min heap with values: 4, 1, 3, 2, 16, 9, 10, 14, 8, 7
        std::vector<int> values = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        min_heap = MinHeap<int>(values);
    }
    
    MinHeap<int> min_heap;
};

class MaxHeapTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create max heap with values: 4, 1, 3, 2, 16, 9, 10, 14, 8, 7
        std::vector<int> values = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        max_heap = MaxHeap<int>(values);
    }
    
    MaxHeap<int> max_heap;
};

class TrieTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Insert test words
        trie.insert("cat");
        trie.insert("car");
        trie.insert("card");
        trie.insert("care");
        trie.insert("careful");
        trie.insert("dog");
        trie.insert("dodge");
    }
    
    Trie trie;
};

// Min Heap Tests

TEST_F(MinHeapTest, BasicOperations) {
    EXPECT_FALSE(min_heap.empty());
    EXPECT_EQ(min_heap.size(), 10);
    EXPECT_EQ(min_heap.top(), 1); // Min element should be at top
    
    // Test push
    min_heap.push(0);
    EXPECT_EQ(min_heap.top(), 0);
    EXPECT_EQ(min_heap.size(), 11);
    
    // Test pop
    int min_val = min_heap.pop();
    EXPECT_EQ(min_val, 0);
    EXPECT_EQ(min_heap.top(), 1);
    EXPECT_EQ(min_heap.size(), 10);
}

TEST_F(MinHeapTest, HeapProperty) {
    EXPECT_TRUE(min_heap.is_heap());
    
    // Test heapify
    min_heap.heapify();
    EXPECT_TRUE(min_heap.is_heap());
    EXPECT_EQ(min_heap.top(), 1);
}

TEST_F(MinHeapTest, HeapSort) {
    std::vector<int> sorted = min_heap.heap_sort();
    
    // Min heap sort should return elements in ascending order
    EXPECT_TRUE(std::is_sorted(sorted.begin(), sorted.end()));
    EXPECT_EQ(sorted.size(), 10);
}

TEST_F(MinHeapTest, AdvancedOperations) {
    // Test replace top
    int old_top = min_heap.replace_top(0);
    EXPECT_EQ(old_top, 1);
    EXPECT_EQ(min_heap.top(), 0);
    
    // Test find k largest
    std::vector<int> k_largest = min_heap.find_k_largest(3);
    EXPECT_EQ(k_largest.size(), 3);
    EXPECT_TRUE(std::is_sorted(k_largest.rbegin(), k_largest.rend()));
    
    // Test find k smallest
    std::vector<int> k_smallest = min_heap.find_k_smallest(3);
    EXPECT_EQ(k_smallest.size(), 3);
    EXPECT_TRUE(std::is_sorted(k_smallest.begin(), k_smallest.end()));
}

TEST_F(MinHeapTest, MergeHeaps) {
    MinHeap<int> other_heap({5, 15, 25});
    size_t original_size = min_heap.size();
    
    min_heap.merge(other_heap);
    EXPECT_EQ(min_heap.size(), original_size + 3);
    EXPECT_TRUE(min_heap.is_heap());
}

// Max Heap Tests

TEST_F(MaxHeapTest, BasicOperations) {
    EXPECT_FALSE(max_heap.empty());
    EXPECT_EQ(max_heap.size(), 10);
    EXPECT_EQ(max_heap.top(), 16); // Max element should be at top
    
    // Test push
    max_heap.push(20);
    EXPECT_EQ(max_heap.top(), 20);
    EXPECT_EQ(max_heap.size(), 11);
    
    // Test pop
    int max_val = max_heap.pop();
    EXPECT_EQ(max_val, 20);
    EXPECT_EQ(max_heap.top(), 16);
    EXPECT_EQ(max_heap.size(), 10);
}

TEST_F(MaxHeapTest, HeapProperty) {
    EXPECT_TRUE(max_heap.is_heap());
    
    // Test heapify
    max_heap.heapify();
    EXPECT_TRUE(max_heap.is_heap());
    EXPECT_EQ(max_heap.top(), 16);
}

TEST_F(MaxHeapTest, UpdateAndRemove) {
    // Test update at index
    max_heap.update_at(0, 5); // Update root to smaller value
    EXPECT_TRUE(max_heap.is_heap());
    
    // Test remove at index
    size_t original_size = max_heap.size();
    max_heap.remove_at(0);
    EXPECT_EQ(max_heap.size(), original_size - 1);
    EXPECT_TRUE(max_heap.is_heap());
}

// Trie Tests

TEST_F(TrieTest, BasicOperations) {
    EXPECT_FALSE(trie.empty());
    EXPECT_EQ(trie.size(), 7);
    
    // Test search
    EXPECT_TRUE(trie.search("cat"));
    EXPECT_TRUE(trie.search("car"));
    EXPECT_TRUE(trie.search("careful"));
    EXPECT_FALSE(trie.search("ca")); // Prefix but not complete word
    EXPECT_FALSE(trie.search("cats")); // Not in trie
    
    // Test starts_with
    EXPECT_TRUE(trie.starts_with("ca"));
    EXPECT_TRUE(trie.starts_with("car"));
    EXPECT_TRUE(trie.starts_with("do"));
    EXPECT_FALSE(trie.starts_with("bat"));
}

TEST_F(TrieTest, InsertAndRemove) {
    // Test insert new word
    trie.insert("bat");
    EXPECT_TRUE(trie.search("bat"));
    EXPECT_EQ(trie.size(), 8);
    
    // Test insert duplicate
    trie.insert("cat"); // Already exists
    EXPECT_EQ(trie.size(), 8); // Size shouldn't change
    
    // Test remove
    EXPECT_TRUE(trie.remove("bat"));
    EXPECT_FALSE(trie.search("bat"));
    EXPECT_EQ(trie.size(), 7);
    
    // Test remove non-existent word
    EXPECT_FALSE(trie.remove("xyz"));
    EXPECT_EQ(trie.size(), 7);
}

TEST_F(TrieTest, PrefixOperations) {
    // Test get words with prefix
    std::vector<std::string> car_words = trie.get_words_with_prefix("car");
    EXPECT_GE(car_words.size(), 3); // car, card, care, careful
    
    for (const std::string& word : car_words) {
        EXPECT_TRUE(word.substr(0, 3) == "car");
    }
    
    // Test count words with prefix
    int car_count = trie.count_words_with_prefix("car");
    EXPECT_EQ(car_count, car_words.size());
    
    // Test get all words
    std::vector<std::string> all_words = trie.get_all_words();
    EXPECT_EQ(all_words.size(), 7);
}

TEST_F(TrieTest, AutoComplete) {
    std::vector<std::string> suggestions = trie.auto_complete("ca", 3);
    EXPECT_LE(suggestions.size(), 3);
    
    for (const std::string& suggestion : suggestions) {
        EXPECT_TRUE(suggestion.substr(0, 2) == "ca");
        EXPECT_TRUE(trie.search(suggestion));
    }
}

TEST_F(TrieTest, LongestCommonPrefix) {
    // Create trie with words that have common prefix
    Trie prefix_trie;
    prefix_trie.insert("flower");
    prefix_trie.insert("flow");
    prefix_trie.insert("flight");
    
    std::string lcp = prefix_trie.longest_common_prefix();
    EXPECT_EQ(lcp, "fl");
}

TEST_F(TrieTest, ShortestUniquePrefixes) {
    std::vector<std::string> words = {"cat", "car", "dog"};
    std::vector<std::string> prefixes = Trie::shortest_unique_prefixes(words);
    
    EXPECT_EQ(prefixes.size(), 3);
    EXPECT_EQ(prefixes[0], "cat"); // "cat" needs full word to be unique from "car"
    EXPECT_EQ(prefixes[1], "car"); // "car" needs full word to be unique from "cat"
    EXPECT_EQ(prefixes[2], "d");   // "d" is enough to distinguish "dog"
}

// Heap Utility Function Tests

TEST(HeapUtilityTest, IsHeapArray) {
    std::vector<int> min_heap_array = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_TRUE(is_heap_array(min_heap_array, std::less<int>()));
    
    std::vector<int> max_heap_array = {7, 6, 5, 4, 3, 2, 1};
    EXPECT_TRUE(is_heap_array(max_heap_array, std::greater<int>()));
    
    std::vector<int> not_heap = {1, 3, 2, 0, 5, 6, 4}; // 0 < 3, so this violates min heap property
    EXPECT_FALSE(is_heap_array(not_heap, std::less<int>()));
}

TEST(HeapUtilityTest, HeapifyArray) {
    std::vector<int> arr = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    heapify_array(arr, std::less<int>());
    
    EXPECT_TRUE(is_heap_array(arr, std::less<int>()));
}

TEST(HeapUtilityTest, FindKthElements) {
    std::vector<int> arr = {3, 2, 1, 5, 6, 4};
    
    // Find kth largest
    EXPECT_EQ(find_kth_largest(arr, 1), 6);
    EXPECT_EQ(find_kth_largest(arr, 2), 5);
    EXPECT_EQ(find_kth_largest(arr, 6), 1);
    
    // Find kth smallest
    EXPECT_EQ(find_kth_smallest(arr, 1), 1);
    EXPECT_EQ(find_kth_smallest(arr, 2), 2);
    EXPECT_EQ(find_kth_smallest(arr, 6), 6);
    
    // Test out of range
    EXPECT_THROW(find_kth_largest(arr, 0), std::out_of_range);
    EXPECT_THROW(find_kth_largest(arr, 7), std::out_of_range);
}

TEST(HeapUtilityTest, MergeKSortedArrays) {
    std::vector<std::vector<int>> arrays = {
        {1, 4, 5},
        {1, 3, 4},
        {2, 6}
    };
    
    std::vector<int> merged = merge_k_sorted_arrays(arrays);
    std::vector<int> expected = {1, 1, 2, 3, 4, 4, 5, 6};
    
    EXPECT_EQ(merged, expected);
}

// Edge Cases and Error Handling

TEST(HeapEdgeCasesTest, EmptyHeapOperations) {
    MinHeap<int> empty_heap;
    
    EXPECT_TRUE(empty_heap.empty());
    EXPECT_EQ(empty_heap.size(), 0);
    EXPECT_THROW(empty_heap.top(), std::runtime_error);
    EXPECT_THROW(empty_heap.pop(), std::runtime_error);
    
    // Operations that should work on empty heap
    empty_heap.clear();
    EXPECT_TRUE(empty_heap.is_heap());
}

TEST(HeapEdgeCasesTest, SingleElementHeap) {
    MinHeap<int> single_heap;
    single_heap.push(42);
    
    EXPECT_FALSE(single_heap.empty());
    EXPECT_EQ(single_heap.size(), 1);
    EXPECT_EQ(single_heap.top(), 42);
    EXPECT_TRUE(single_heap.is_heap());
    
    int popped = single_heap.pop();
    EXPECT_EQ(popped, 42);
    EXPECT_TRUE(single_heap.empty());
}

TEST(TrieEdgeCasesTest, EmptyTrieOperations) {
    Trie empty_trie;
    
    EXPECT_TRUE(empty_trie.empty());
    EXPECT_EQ(empty_trie.size(), 0);
    EXPECT_FALSE(empty_trie.search("anything"));
    EXPECT_FALSE(empty_trie.starts_with("anything"));
    EXPECT_FALSE(empty_trie.remove("anything"));
    
    std::vector<std::string> words = empty_trie.get_all_words();
    EXPECT_TRUE(words.empty());
}

TEST(TrieEdgeCasesTest, SingleCharacterWords) {
    Trie single_char_trie;
    single_char_trie.insert("a");
    single_char_trie.insert("b");
    single_char_trie.insert("c");
    
    EXPECT_EQ(single_char_trie.size(), 3);
    EXPECT_TRUE(single_char_trie.search("a"));
    EXPECT_TRUE(single_char_trie.search("b"));
    EXPECT_TRUE(single_char_trie.search("c"));
    
    EXPECT_TRUE(single_char_trie.starts_with("a"));
    EXPECT_FALSE(single_char_trie.starts_with("d"));
}

TEST(HeapUtilityEdgeCasesTest, EmptyArrayOperations) {
    std::vector<int> empty_arr;
    
    EXPECT_TRUE(is_heap_array(empty_arr));
    heapify_array(empty_arr); // Should not crash
    EXPECT_TRUE(empty_arr.empty());
    
    EXPECT_THROW(find_kth_largest(empty_arr, 1), std::out_of_range);
    EXPECT_THROW(find_kth_smallest(empty_arr, 1), std::out_of_range);
}

TEST(HeapUtilityEdgeCasesTest, MergeEmptyArrays) {
    std::vector<std::vector<int>> empty_arrays;
    std::vector<int> result = merge_k_sorted_arrays(empty_arrays);
    EXPECT_TRUE(result.empty());
    
    std::vector<std::vector<int>> arrays_with_empty = {{1, 3}, {}, {2, 4}};
    result = merge_k_sorted_arrays(arrays_with_empty);
    std::vector<int> expected = {1, 2, 3, 4};
    EXPECT_EQ(result, expected);
}