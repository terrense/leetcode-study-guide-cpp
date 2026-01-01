/**
 * @file heap.h
 * @brief Heap data structure implementations for the LeetCode Study Guide
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_HEAP_H
#define LEETCODE_STUDY_GUIDE_HEAP_H

#include "../common.h"
#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <memory>

namespace leetcode_study_guide {
namespace data_structures {

/**
 * @brief Generic Heap implementation (Min-Heap and Max-Heap)
 * 
 * This class provides a comprehensive implementation of heap operations
 * commonly used in LeetCode problems, including heap sort, priority queue
 * operations, and heap property maintenance.
 */
template<typename T, typename Compare = std::less<T>>
class Heap {
public:
    /**
     * @brief Default constructor (creates empty heap)
     */
    Heap() = default;
    
    /**
     * @brief Constructor with custom comparator
     * @param comp Comparator function for heap ordering
     */
    explicit Heap(const Compare& comp) : compare_(comp) {}
    
    /**
     * @brief Constructor from vector (heapify)
     * @param data Initial data to heapify
     * @param comp Comparator function for heap ordering
     */
    explicit Heap(const std::vector<T>& data, const Compare& comp = Compare());
    
    /**
     * @brief Constructor from initializer list
     * @param init_list Initial values
     * @param comp Comparator function for heap ordering
     */
    Heap(std::initializer_list<T> init_list, const Compare& comp = Compare());
    
    // Basic Heap Operations
    
    /**
     * @brief Insert element into heap
     * @param value Value to insert
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    void push(const T& value);
    
    /**
     * @brief Remove and return top element
     * @return Top element (min for min-heap, max for max-heap)
     * @throws std::runtime_error if heap is empty
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    T pop();
    
    /**
     * @brief Get top element without removing
     * @return Reference to top element
     * @throws std::runtime_error if heap is empty
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    const T& top() const;
    
    /**
     * @brief Check if heap is empty
     * @return True if heap is empty
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool empty() const { return data_.empty(); }
    
    /**
     * @brief Get size of heap
     * @return Number of elements in heap
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    size_t size() const { return data_.size(); }
    
    /**
     * @brief Clear all elements from heap
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void clear() { data_.clear(); }
    
    // Heap Property Operations
    
    /**
     * @brief Build heap from current data (heapify)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void heapify();
    
    /**
     * @brief Check if current data satisfies heap property
     * @return True if heap property is satisfied
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool is_heap() const;
    
    /**
     * @brief Merge with another heap
     * @param other Other heap to merge with
     * Time Complexity: O(n + m) where n, m are sizes
     * Space Complexity: O(1)
     */
    void merge(const Heap& other);
    
    // Heap Sort Implementation
    
    /**
     * @brief Sort elements using heap sort (in-place)
     * @return Sorted vector of elements
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     */
    std::vector<T> heap_sort();
    
    /**
     * @brief Sort given vector using heap sort
     * @param arr Vector to sort
     * @param comp Comparator for sorting order
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     */
    static void heap_sort_array(std::vector<T>& arr, const Compare& comp = Compare());
    
    // Advanced Operations
    
    /**
     * @brief Replace top element with new value
     * @param new_value New value to replace top
     * @return Old top value
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    T replace_top(const T& new_value);
    
    /**
     * @brief Remove element at specific index
     * @param index Index of element to remove
     * @throws std::out_of_range if index is invalid
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    void remove_at(size_t index);
    
    /**
     * @brief Update element at specific index
     * @param index Index of element to update
     * @param new_value New value
     * @throws std::out_of_range if index is invalid
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     */
    void update_at(size_t index, const T& new_value);
    
    /**
     * @brief Find k largest elements
     * @param k Number of largest elements to find
     * @return Vector of k largest elements
     * Time Complexity: O(n log k)
     * Space Complexity: O(k)
     */
    std::vector<T> find_k_largest(int k) const;
    
    /**
     * @brief Find k smallest elements
     * @param k Number of smallest elements to find
     * @return Vector of k smallest elements
     * Time Complexity: O(n log k)
     * Space Complexity: O(k)
     */
    std::vector<T> find_k_smallest(int k) const;
    
    // Utility Methods
    
    /**
     * @brief Get underlying data (for testing/debugging)
     * @return Reference to internal vector
     */
    const std::vector<T>& data() const { return data_; }
    
    /**
     * @brief Print heap structure
     */
    void print_heap() const;
    
    /**
     * @brief Get parent index
     * @param index Child index
     * @return Parent index
     */
    static size_t parent(size_t index) { return (index - 1) / 2; }
    
    /**
     * @brief Get left child index
     * @param index Parent index
     * @return Left child index
     */
    static size_t left_child(size_t index) { return 2 * index + 1; }
    
    /**
     * @brief Get right child index
     * @param index Parent index
     * @return Right child index
     */
    static size_t right_child(size_t index) { return 2 * index + 2; }

private:
    std::vector<T> data_;
    Compare compare_;
    
    // Helper methods
    void heapify_up(size_t index);
    void heapify_down(size_t index);
    void build_heap();
    bool is_heap_helper(size_t index) const;
};

/**
 * @brief Min-Heap specialization
 */
template<typename T>
using MinHeap = Heap<T, std::less<T>>;

/**
 * @brief Max-Heap specialization
 */
template<typename T>
using MaxHeap = Heap<T, std::greater<T>>;

/**
 * @brief Trie (Prefix Tree) implementation for string operations
 * 
 * This class provides a comprehensive implementation of Trie operations
 * commonly used in LeetCode problems, including word search, prefix matching,
 * and autocomplete functionality.
 */
class Trie {
public:
    /**
     * @brief Trie Node structure
     */
    struct TrieNode {
        std::vector<std::unique_ptr<TrieNode>> children;
        bool is_end_of_word;
        int word_count;  // Number of words ending at this node
        int prefix_count; // Number of words with this prefix
        
        /**
         * @brief Constructor for TrieNode
         */
        TrieNode() : children(26), is_end_of_word(false), word_count(0), prefix_count(0) {}
    };
    
    /**
     * @brief Default constructor
     */
    Trie();
    
    /**
     * @brief Destructor
     */
    ~Trie() = default;
    
    // Basic Trie Operations
    
    /**
     * @brief Insert word into trie
     * @param word Word to insert
     * Time Complexity: O(m) where m is word length
     * Space Complexity: O(m) in worst case
     */
    void insert(const std::string& word);
    
    /**
     * @brief Search for exact word in trie
     * @param word Word to search for
     * @return True if word exists
     * Time Complexity: O(m) where m is word length
     * Space Complexity: O(1)
     */
    bool search(const std::string& word) const;
    
    /**
     * @brief Check if any word starts with given prefix
     * @param prefix Prefix to check
     * @return True if prefix exists
     * Time Complexity: O(m) where m is prefix length
     * Space Complexity: O(1)
     */
    bool starts_with(const std::string& prefix) const;
    
    /**
     * @brief Remove word from trie
     * @param word Word to remove
     * @return True if word was removed
     * Time Complexity: O(m) where m is word length
     * Space Complexity: O(m) for recursion
     */
    bool remove(const std::string& word);
    
    // Advanced Trie Operations
    
    /**
     * @brief Get all words with given prefix
     * @param prefix Prefix to search for
     * @return Vector of all words with the prefix
     * Time Complexity: O(p + n) where p is prefix length, n is number of nodes in subtree
     * Space Complexity: O(n)
     */
    std::vector<std::string> get_words_with_prefix(const std::string& prefix) const;
    
    /**
     * @brief Get all words in trie
     * @return Vector of all words
     * Time Complexity: O(n) where n is total number of characters
     * Space Complexity: O(n)
     */
    std::vector<std::string> get_all_words() const;
    
    /**
     * @brief Count words with given prefix
     * @param prefix Prefix to count
     * @return Number of words with the prefix
     * Time Complexity: O(m) where m is prefix length
     * Space Complexity: O(1)
     */
    int count_words_with_prefix(const std::string& prefix) const;
    
    /**
     * @brief Find longest common prefix of all words
     * @return Longest common prefix
     * Time Complexity: O(n) where n is total characters
     * Space Complexity: O(1)
     */
    std::string longest_common_prefix() const;
    
    /**
     * @brief Auto-complete suggestions for given prefix
     * @param prefix Prefix to get suggestions for
     * @param max_suggestions Maximum number of suggestions
     * @return Vector of suggested completions
     * Time Complexity: O(p + k) where p is prefix length, k is suggestions
     * Space Complexity: O(k)
     */
    std::vector<std::string> auto_complete(const std::string& prefix, int max_suggestions = 10) const;
    
    /**
     * @brief Find shortest unique prefix for each word
     * @param words Vector of words
     * @return Vector of shortest unique prefixes
     * Time Complexity: O(n * m) where n is number of words, m is average length
     * Space Complexity: O(n * m)
     */
    static std::vector<std::string> shortest_unique_prefixes(const std::vector<std::string>& words);
    
    // Utility Methods
    
    /**
     * @brief Check if trie is empty
     * @return True if trie is empty
     */
    bool empty() const;
    
    /**
     * @brief Get total number of words in trie
     * @return Number of words
     */
    int size() const;
    
    /**
     * @brief Clear all words from trie
     */
    void clear();
    
    /**
     * @brief Print all words in trie (for debugging)
     */
    void print_words() const;

private:
    std::unique_ptr<TrieNode> root_;
    int total_words_;
    
    // Helper methods
    TrieNode* find_node(const std::string& prefix) const;
    void collect_words(TrieNode* node, const std::string& prefix, std::vector<std::string>& words) const;
    void collect_words_limited(TrieNode* node, const std::string& prefix, 
                              std::vector<std::string>& words, int& count, int limit) const;
    bool remove_helper(TrieNode* node, const std::string& word, int index);
    void print_words_helper(TrieNode* node, const std::string& prefix) const;
};

// Heap Utility Functions

/**
 * @brief Check if array represents a valid heap
 * @param arr Array to check
 * @param comp Comparator for heap property
 * @return True if array is a valid heap
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
template<typename T, typename Compare = std::less<T>>
bool is_heap_array(const std::vector<T>& arr, const Compare& comp = Compare());

/**
 * @brief Convert array to heap in-place
 * @param arr Array to heapify
 * @param comp Comparator for heap property
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
template<typename T, typename Compare = std::less<T>>
void heapify_array(std::vector<T>& arr, const Compare& comp = Compare());

/**
 * @brief Find kth largest element using heap
 * @param arr Input array
 * @param k Position (1-indexed)
 * @return kth largest element
 * Time Complexity: O(n log k)
 * Space Complexity: O(k)
 */
template<typename T>
T find_kth_largest(const std::vector<T>& arr, int k);

/**
 * @brief Find kth smallest element using heap
 * @param arr Input array
 * @param k Position (1-indexed)
 * @return kth smallest element
 * Time Complexity: O(n log k)
 * Space Complexity: O(k)
 */
template<typename T>
T find_kth_smallest(const std::vector<T>& arr, int k);

/**
 * @brief Merge k sorted arrays using heap
 * @param arrays Vector of sorted arrays
 * @return Merged sorted array
 * Time Complexity: O(n log k) where n is total elements, k is number of arrays
 * Space Complexity: O(k)
 */
template<typename T>
std::vector<T> merge_k_sorted_arrays(const std::vector<std::vector<T>>& arrays);

} // namespace data_structures
} // namespace leetcode_study_guide

// Include template implementation
#include "heap.tpp"

#endif // LEETCODE_STUDY_GUIDE_HEAP_H