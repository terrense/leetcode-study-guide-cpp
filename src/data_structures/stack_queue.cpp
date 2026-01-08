/**
 * @file stack_queue.cpp
 * @brief Implementation file for Stack and Queue data structures
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/stack_queue.h"
#include <iostream>
#include <cmath>

namespace leetcode_study_guide {
namespace data_structures {

// Explicit template instantiations for common types
template class Stack<int>;
template class Stack<double>;
template class Stack<std::string>;
template class Stack<char>;

template class Queue<int>;
template class Queue<double>;
template class Queue<std::string>;
template class Queue<char>;

template class CircularQueue<int>;
template class CircularQueue<double>;
template class CircularQueue<std::string>;

template class Deque<int>;
template class Deque<double>;
template class Deque<std::string>;

template class QueueUsingStacks<int>;
template class QueueUsingStacks<double>;
template class QueueUsingStacks<std::string>;

template class StackUsingQueues<int>;
template class StackUsingQueues<double>;
template class StackUsingQueues<std::string>;

template class MinStack<int>;
template class MinStack<double>;

// Explicit instantiations for static methods
template bool Stack<int>::is_balanced_parentheses(const std::string& expression);
template double Stack<int>::evaluate_postfix(const std::vector<std::string>& expression);
template std::vector<std::string> Stack<int>::infix_to_postfix(const std::vector<std::string>& infix);

template std::vector<int> Stack<int>::next_greater_element(const std::vector<int>& arr);
template std::vector<double> Stack<double>::next_greater_element(const std::vector<double>& arr);

template int Stack<int>::largest_rectangle_histogram(const std::vector<int>& heights);

template std::vector<int> Deque<int>::sliding_window_maximum(const std::vector<int>& arr, size_t k);
template std::vector<double> Deque<double>::sliding_window_maximum(const std::vector<double>& arr, size_t k);

} // namespace data_structures
} // namespace leetcode_study_guide