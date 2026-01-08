/**
 * @file stack_queue.h
 * @brief Stack and Queue data structure implementations for the LeetCode Study Guide
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_STACK_QUEUE_H
#define LEETCODE_STUDY_GUIDE_STACK_QUEUE_H

#include "../common.h"
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <initializer_list>
#include <stdexcept>

namespace leetcode_study_guide {
namespace data_structures {

/**
 * @brief Stack implementation with LIFO (Last In, First Out) operations
 * 
 * This class provides a comprehensive stack implementation using STL containers
 * as the underlying storage, along with common stack-based algorithms and
 * applications frequently seen in LeetCode problems.
 */
template<typename T>
class Stack {
public:
    /**
     * @brief Default constructor
     */
    Stack() = default;

    /**
     * @brief Constructor with initializer list
     * @param init_list Initializer list of values (first element becomes bottom)
     */
    Stack(std::initializer_list<T> init_list);

    /**
     * @brief Constructor from vector
     * @param values Vector of values (first element becomes bottom)
     */
    Stack(const std::vector<T>& values);

    // Basic Stack Operations

    /**
     * @brief Push element onto stack
     * @param value Value to push
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void push(const T& value);

    /**
     * @brief Pop element from stack
     * @return Value that was popped
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     * @throws std::runtime_error if stack is empty
     */
    T pop();

    /**
     * @brief Get top element without removing it
     * @return Reference to top element
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     * @throws std::runtime_error if stack is empty
     */
    T& top();
    const T& top() const;

    /**
     * @brief Check if stack is empty
     * @return True if stack is empty, false otherwise
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool empty() const { return data_.empty(); }

    /**
     * @brief Get current size of stack
     * @return Number of elements in stack
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    size_t size() const { return data_.size(); }

    /**
     * @brief Clear all elements from stack
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void clear() { data_.clear(); }

    // Stack-based Algorithms

    /**
     * @brief Check if parentheses are balanced
     * @param expression String containing parentheses
     * @return True if balanced, false otherwise
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static bool is_balanced_parentheses(const std::string& expression);

    /**
     * @brief Evaluate postfix expression
     * @param expression Vector of tokens in postfix notation
     * @return Result of evaluation
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static double evaluate_postfix(const std::vector<std::string>& expression);

    /**
     * @brief Convert infix to postfix notation
     * @param infix Infix expression as vector of tokens
     * @return Postfix expression as vector of tokens
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static std::vector<std::string> infix_to_postfix(const std::vector<std::string>& infix);

    /**
     * @brief Find next greater element for each element in array
     * @param arr Input array
     * @return Vector where result[i] is next greater element for arr[i], or -1 if none
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static std::vector<T> next_greater_element(const std::vector<T>& arr);

    /**
     * @brief Find largest rectangle area in histogram
     * @param heights Vector of histogram heights
     * @return Maximum rectangle area
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static int largest_rectangle_histogram(const std::vector<int>& heights);

    /**
     * @brief Convert to vector (bottom to top order)
     * @return Vector representation of stack
     */
    std::vector<T> to_vector() const;

private:
    std::vector<T> data_;

    // Helper functions
    static int precedence(const std::string& op);
    static bool is_operator(const std::string& token);
    static double apply_operator(const std::string& op, double a, double b);
};

/**
 * @brief Queue implementation with FIFO (First In, First Out) operations
 * 
 * This class provides a comprehensive queue implementation using STL containers
 * as the underlying storage, along with common queue-based algorithms and
 * variations frequently seen in LeetCode problems.
 */
template<typename T>
class Queue {
public:
    /**
     * @brief Default constructor
     */
    Queue() = default;

    /**
     * @brief Constructor with initializer list
     * @param init_list Initializer list of values (first element becomes front)
     */
    Queue(std::initializer_list<T> init_list);

    /**
     * @brief Constructor from vector
     * @param values Vector of values (first element becomes front)
     */
    Queue(const std::vector<T>& values);

    // Basic Queue Operations

    /**
     * @brief Add element to back of queue
     * @param value Value to enqueue
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void enqueue(const T& value);

    /**
     * @brief Remove element from front of queue
     * @return Value that was dequeued
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     * @throws std::runtime_error if queue is empty
     */
    T dequeue();

    /**
     * @brief Get front element without removing it
     * @return Reference to front element
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     * @throws std::runtime_error if queue is empty
     */
    T& front();
    const T& front() const;

    /**
     * @brief Get back element without removing it
     * @return Reference to back element
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     * @throws std::runtime_error if queue is empty
     */
    T& back();
    const T& back() const;

    /**
     * @brief Check if queue is empty
     * @return True if queue is empty, false otherwise
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool empty() const { return data_.empty(); }

    /**
     * @brief Get current size of queue
     * @return Number of elements in queue
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    size_t size() const { return data_.size(); }

    /**
     * @brief Clear all elements from queue
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void clear() { data_.clear(); }

    /**
     * @brief Convert to vector (front to back order)
     * @return Vector representation of queue
     */
    std::vector<T> to_vector() const;

private:
    std::deque<T> data_;
};

/**
 * @brief Circular Queue implementation with fixed capacity
 * 
 * This class provides a circular queue implementation where the queue
 * wraps around when it reaches the end of the allocated space.
 */
template<typename T>
class CircularQueue {
public:
    /**
     * @brief Constructor with capacity
     * @param capacity Maximum number of elements the queue can hold
     */
    explicit CircularQueue(size_t capacity);

    /**
     * @brief Add element to queue
     * @param value Value to enqueue
     * @return True if successful, false if queue is full
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool enqueue(const T& value);

    /**
     * @brief Remove element from queue
     * @return True if successful, false if queue is empty
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    bool dequeue();

    /**
     * @brief Get front element
     * @return Front element
     * @throws std::runtime_error if queue is empty
     */
    T front() const;

    /**
     * @brief Get back element
     * @return Back element
     * @throws std::runtime_error if queue is empty
     */
    T back() const;

    /**
     * @brief Check if queue is empty
     * @return True if empty, false otherwise
     */
    bool empty() const { return size_ == 0; }

    /**
     * @brief Check if queue is full
     * @return True if full, false otherwise
     */
    bool full() const { return size_ == capacity_; }

    /**
     * @brief Get current size
     * @return Number of elements in queue
     */
    size_t size() const { return size_; }

    /**
     * @brief Get capacity
     * @return Maximum capacity of queue
     */
    size_t capacity() const { return capacity_; }

private:
    std::vector<T> data_;
    size_t front_;
    size_t back_;
    size_t size_;
    size_t capacity_;
};

/**
 * @brief Deque (Double-ended Queue) implementation
 * 
 * This class provides a deque implementation that allows insertion
 * and deletion at both ends efficiently.
 */
template<typename T>
class Deque {
public:
    /**
     * @brief Default constructor
     */
    Deque() = default;

    /**
     * @brief Constructor with initializer list
     * @param init_list Initializer list of values
     */
    Deque(std::initializer_list<T> init_list);

    // Operations at front

    /**
     * @brief Add element to front
     * @param value Value to add
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void push_front(const T& value);

    /**
     * @brief Remove element from front
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     * @throws std::runtime_error if deque is empty
     */
    void pop_front();

    /**
     * @brief Get front element
     * @return Reference to front element
     * @throws std::runtime_error if deque is empty
     */
    T& front();
    const T& front() const;

    // Operations at back

    /**
     * @brief Add element to back
     * @param value Value to add
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    void push_back(const T& value);

    /**
     * @brief Remove element from back
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     * @throws std::runtime_error if deque is empty
     */
    void pop_back();

    /**
     * @brief Get back element
     * @return Reference to back element
     * @throws std::runtime_error if deque is empty
     */
    T& back();
    const T& back() const;

    // Utility methods

    /**
     * @brief Check if deque is empty
     * @return True if empty, false otherwise
     */
    bool empty() const { return data_.empty(); }

    /**
     * @brief Get current size
     * @return Number of elements in deque
     */
    size_t size() const { return data_.size(); }

    /**
     * @brief Clear all elements
     */
    void clear() { data_.clear(); }

    /**
     * @brief Convert to vector
     * @return Vector representation of deque
     */
    std::vector<T> to_vector() const;

    // Deque-specific algorithms

    /**
     * @brief Sliding window maximum using deque
     * @param arr Input array
     * @param k Window size
     * @return Vector of maximum elements in each window
     * Time Complexity: O(n)
     * Space Complexity: O(k)
     */
    static std::vector<T> sliding_window_maximum(const std::vector<T>& arr, size_t k);

private:
    std::deque<T> data_;
};

// Standalone Stack and Queue Algorithms

/**
 * @brief Implement queue using two stacks
 */
template<typename T>
class QueueUsingStacks {
public:
    void enqueue(const T& value);
    T dequeue();
    T front();
    bool empty() const;

private:
    std::stack<T> input_stack_;
    std::stack<T> output_stack_;
    
    void transfer_if_needed();
};

/**
 * @brief Implement stack using two queues
 */
template<typename T>
class StackUsingQueues {
public:
    void push(const T& value);
    T pop();
    T top();
    bool empty() const;

private:
    std::queue<T> main_queue_;
    std::queue<T> temp_queue_;
};

/**
 * @brief Min Stack that supports getMin() in O(1)
 */
template<typename T>
class MinStack {
public:
    void push(const T& value);
    void pop();
    T top() const;
    T get_min() const;
    bool empty() const;

private:
    std::stack<T> data_stack_;
    std::stack<T> min_stack_;
};

} // namespace data_structures
} // namespace leetcode_study_guide

// Include template implementation
#include "stack_queue.tpp"

#endif // LEETCODE_STUDY_GUIDE_STACK_QUEUE_H