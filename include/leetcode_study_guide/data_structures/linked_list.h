/**
 * @file linked_list.h
 * @brief LinkedList data structure implementations for the LeetCode Study Guide
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_LINKED_LIST_H
#define LEETCODE_STUDY_GUIDE_LINKED_LIST_H

#include "../common.h"
#include <memory>
#include <initializer_list>
#include <vector>

namespace leetcode_study_guide {
namespace data_structures {

/**
 * @brief Node structure for singly linked list
 */
template<typename T>
struct ListNode {
    T data;
    std::shared_ptr<ListNode<T>> next;
    
    ListNode(const T& value) : data(value), next(nullptr) {}
    ListNode(const T& value, std::shared_ptr<ListNode<T>> next_node) 
        : data(value), next(next_node) {}
};

/**
 * @brief Node structure for doubly linked list
 */
template<typename T>
struct DoublyListNode {
    T data;
    std::shared_ptr<DoublyListNode<T>> next;
    std::weak_ptr<DoublyListNode<T>> prev;
    
    DoublyListNode(const T& value) : data(value), next(nullptr) {}
    DoublyListNode(const T& value, std::shared_ptr<DoublyListNode<T>> next_node,
                   std::shared_ptr<DoublyListNode<T>> prev_node = nullptr)
        : data(value), next(next_node), prev(prev_node) {}
};

/**
 * @brief Singly Linked List implementation
 * 
 * This class provides a comprehensive implementation of singly linked list
 * operations commonly used in LeetCode problems, including traversal,
 * manipulation, and cycle detection algorithms.
 */
template<typename T>
class SinglyLinkedList {
public:
    using NodePtr = std::shared_ptr<ListNode<T>>;

    /**
     * @brief Default constructor
     */
    SinglyLinkedList() : head_(nullptr), size_(0) {}

    /**
     * @brief Constructor with initializer list
     * @param init_list Initializer list of values
     */
    SinglyLinkedList(std::initializer_list<T> init_list);

    /**
     * @brief Constructor from vector
     * @param values Vector of values to create list from
     */
    SinglyLinkedList(const std::vector<T>& values);

    /**
     * @brief Destructor
     */
    ~SinglyLinkedList() = default;

    // Basic Operations

    /**
     * @brief Insert element at the beginning
     * @param value Value to insert
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void push_front(const T& value);

    /**
     * @brief Insert element at the end
     * @param value Value to insert
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void push_back(const T& value);

    /**
     * @brief Insert element at specific position
     * @param position Position to insert at (0-indexed)
     * @param value Value to insert
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void insert(size_t position, const T& value);

    /**
     * @brief Remove element from the beginning
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void pop_front();

    /**
     * @brief Remove element from the end
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void pop_back();

    /**
     * @brief Remove element at specific position
     * @param position Position to remove from (0-indexed)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void erase(size_t position);

    /**
     * @brief Remove all occurrences of a value
     * @param value Value to remove
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void remove(const T& value);

    // Search Operations

    /**
     * @brief Search for element
     * @param value Value to search for
     * @return Position of first occurrence, or -1 if not found
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int find(const T& value) const;

    /**
     * @brief Get element at specific position
     * @param position Position to get element from
     * @return Reference to element at position
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    T& at(size_t position);
    const T& at(size_t position) const;

    // Advanced Algorithms

    /**
     * @brief Reverse the linked list iteratively
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void reverse();

    /**
     * @brief Reverse the linked list recursively
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    void reverse_recursive();

    /**
     * @brief Detect cycle in linked list using Floyd's algorithm
     * @return True if cycle exists, false otherwise
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool has_cycle() const;

    /**
     * @brief Find the start of cycle in linked list
     * @return Node where cycle begins, or nullptr if no cycle
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    NodePtr find_cycle_start() const;

    /**
     * @brief Find middle node using slow-fast pointer technique
     * @return Middle node (for even length, returns second middle)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    NodePtr find_middle() const;

    /**
     * @brief Remove nth node from end
     * @param n Position from end (1-indexed)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void remove_nth_from_end(size_t n);

    /**
     * @brief Merge with another sorted linked list
     * @param other Another sorted linked list
     * @return New merged sorted linked list
     * Time Complexity: O(m + n)
     * Space Complexity: O(1)
     */
    SinglyLinkedList<T> merge_sorted(const SinglyLinkedList<T>& other) const;

    /**
     * @brief Check if linked list is palindrome
     * @return True if palindrome, false otherwise
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    bool is_palindrome() const;

    // Utility Methods

    /**
     * @brief Get current size of list
     * @return Number of elements in list
     */
    size_t size() const { return size_; }

    /**
     * @brief Check if list is empty
     * @return True if list is empty, false otherwise
     */
    bool empty() const { return head_ == nullptr; }

    /**
     * @brief Clear all elements from list
     */
    void clear();

    /**
     * @brief Get head node
     * @return Shared pointer to head node
     */
    NodePtr head() const { return head_; }

    /**
     * @brief Convert to vector
     * @return Vector containing all elements
     */
    std::vector<T> to_vector() const;

    /**
     * @brief Print list for debugging
     */
    void print() const;

private:
    NodePtr head_;
    size_t size_;

    // Helper methods
    NodePtr reverse_recursive_helper(NodePtr node);
    NodePtr get_node_at(size_t position) const;
};

/**
 * @brief Doubly Linked List implementation
 * 
 * This class provides a comprehensive implementation of doubly linked list
 * operations with forward and backward traversal capabilities.
 */
template<typename T>
class DoublyLinkedList {
public:
    using NodePtr = std::shared_ptr<DoublyListNode<T>>;

    /**
     * @brief Default constructor
     */
    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

    /**
     * @brief Constructor with initializer list
     * @param init_list Initializer list of values
     */
    DoublyLinkedList(std::initializer_list<T> init_list);

    /**
     * @brief Constructor from vector
     * @param values Vector of values to create list from
     */
    DoublyLinkedList(const std::vector<T>& values);

    /**
     * @brief Destructor
     */
    ~DoublyLinkedList() = default;

    // Basic Operations

    /**
     * @brief Insert element at the beginning
     * @param value Value to insert
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void push_front(const T& value);

    /**
     * @brief Insert element at the end
     * @param value Value to insert
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void push_back(const T& value);

    /**
     * @brief Insert element at specific position
     * @param position Position to insert at (0-indexed)
     * @param value Value to insert
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void insert(size_t position, const T& value);

    /**
     * @brief Remove element from the beginning
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void pop_front();

    /**
     * @brief Remove element from the end
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void pop_back();

    /**
     * @brief Remove element at specific position
     * @param position Position to remove from (0-indexed)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void erase(size_t position);

    // Search and Access Operations

    /**
     * @brief Search for element
     * @param value Value to search for
     * @return Position of first occurrence, or -1 if not found
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    int find(const T& value) const;

    /**
     * @brief Get element at specific position
     * @param position Position to get element from
     * @return Reference to element at position
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    T& at(size_t position);
    const T& at(size_t position) const;

    // Advanced Operations

    /**
     * @brief Reverse the doubly linked list
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void reverse();

    // Utility Methods

    /**
     * @brief Get current size of list
     * @return Number of elements in list
     */
    size_t size() const { return size_; }

    /**
     * @brief Check if list is empty
     * @return True if list is empty, false otherwise
     */
    bool empty() const { return head_ == nullptr; }

    /**
     * @brief Clear all elements from list
     */
    void clear();

    /**
     * @brief Get head node
     * @return Shared pointer to head node
     */
    NodePtr head() const { return head_; }

    /**
     * @brief Get tail node
     * @return Shared pointer to tail node
     */
    NodePtr tail() const { return tail_; }

    /**
     * @brief Convert to vector
     * @return Vector containing all elements
     */
    std::vector<T> to_vector() const;

    /**
     * @brief Print list forward
     */
    void print_forward() const;

    /**
     * @brief Print list backward
     */
    void print_backward() const;

private:
    NodePtr head_;
    NodePtr tail_;
    size_t size_;

    // Helper methods
    NodePtr get_node_at(size_t position) const;
};

/**
 * @brief Circular Linked List implementation
 * 
 * This class provides a circular linked list where the last node
 * points back to the first node, creating a circular structure.
 */
template<typename T>
class CircularLinkedList {
public:
    using NodePtr = std::shared_ptr<ListNode<T>>;

    /**
     * @brief Default constructor
     */
    CircularLinkedList() : head_(nullptr), size_(0) {}

    /**
     * @brief Constructor with initializer list
     * @param init_list Initializer list of values
     */
    CircularLinkedList(std::initializer_list<T> init_list);

    /**
     * @brief Destructor
     */
    ~CircularLinkedList() = default;

    // Basic Operations

    /**
     * @brief Insert element at the beginning
     * @param value Value to insert
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void push_front(const T& value);

    /**
     * @brief Insert element at the end
     * @param value Value to insert
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void push_back(const T& value);

    /**
     * @brief Remove element from the beginning
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void pop_front();

    /**
     * @brief Remove element from the end
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void pop_back();

    // Utility Methods

    /**
     * @brief Get current size of list
     * @return Number of elements in list
     */
    size_t size() const { return size_; }

    /**
     * @brief Check if list is empty
     * @return True if list is empty, false otherwise
     */
    bool empty() const { return head_ == nullptr; }

    /**
     * @brief Clear all elements from list
     */
    void clear();

    /**
     * @brief Convert to vector (one complete traversal)
     * @return Vector containing all elements
     */
    std::vector<T> to_vector() const;

    /**
     * @brief Print list (one complete traversal)
     */
    void print() const;

private:
    NodePtr head_;
    size_t size_;
};

// Standalone LinkedList Algorithms

/**
 * @brief Merge k sorted linked lists
 * @param lists Vector of sorted linked lists
 * @return Merged sorted linked list
 * Time Complexity: O(n log k) where n is total nodes, k is number of lists
 * Space Complexity: O(1)
 */
template<typename T>
SinglyLinkedList<T> merge_k_sorted_lists(const std::vector<SinglyLinkedList<T>>& lists);

/**
 * @brief Add two numbers represented as linked lists
 * @param num1 First number as linked list (least significant digit first)
 * @param num2 Second number as linked list (least significant digit first)
 * @return Sum as linked list
 * Time Complexity: O(max(m, n))
 * Space Complexity: O(max(m, n))
 */
SinglyLinkedList<int> add_two_numbers(const SinglyLinkedList<int>& num1, 
                                      const SinglyLinkedList<int>& num2);

/**
 * @brief Rotate linked list to the right by k places
 * @param list Input linked list
 * @param k Number of places to rotate
 * @return Rotated linked list
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
template<typename T>
SinglyLinkedList<T> rotate_right(const SinglyLinkedList<T>& list, int k);

} // namespace data_structures
} // namespace leetcode_study_guide

// Include template implementation
#include "linked_list.tpp"

#endif // LEETCODE_STUDY_GUIDE_LINKED_LIST_H