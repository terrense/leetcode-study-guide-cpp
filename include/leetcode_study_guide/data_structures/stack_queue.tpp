/**
 * @file stack_queue.tpp
 * @brief Template implementation for Stack and Queue classes
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cmath>

namespace leetcode_study_guide {
namespace data_structures {

// Stack Implementation

template<typename T>
Stack<T>::Stack(std::initializer_list<T> init_list) : data_(init_list) {}

template<typename T>
Stack<T>::Stack(const std::vector<T>& values) : data_(values) {}

template<typename T>
void Stack<T>::push(const T& value) {
    data_.push_back(value);
}

template<typename T>
T Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Cannot pop from empty stack");
    }
    T value = data_.back();
    data_.pop_back();
    return value;
}

template<typename T>
T& Stack<T>::top() {
    if (empty()) {
        throw std::runtime_error("Cannot access top of empty stack");
    }
    return data_.back();
}

template<typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Cannot access top of empty stack");
    }
    return data_.back();
}

template<typename T>
std::vector<T> Stack<T>::to_vector() const {
    return data_;
}

// Stack-based Algorithm Implementations

template<typename T>
bool Stack<T>::is_balanced_parentheses(const std::string& expression) {
    std::stack<char> stack;
    std::unordered_map<char, char> pairs = {
        {')', '('}, {']', '['}, {'}', '{'}
    };
    
    for (char c : expression) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (stack.empty() || stack.top() != pairs[c]) {
                return false;
            }
            stack.pop();
        }
    }
    
    return stack.empty();
}

template<typename T>
double Stack<T>::evaluate_postfix(const std::vector<std::string>& expression) {
    std::stack<double> stack;
    
    for (const std::string& token : expression) {
        if (is_operator(token)) {
            if (stack.size() < 2) {
                throw std::invalid_argument("Invalid postfix expression");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(apply_operator(token, a, b));
        } else {
            stack.push(std::stod(token));
        }
    }
    
    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression");
    }
    
    return stack.top();
}

template<typename T>
std::vector<std::string> Stack<T>::infix_to_postfix(const std::vector<std::string>& infix) {
    std::vector<std::string> result;
    std::stack<std::string> operators;
    
    for (const std::string& token : infix) {
        if (!is_operator(token) && token != "(" && token != ")") {
            // Operand
            result.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                result.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop(); // Remove the "("
            }
        } else if (is_operator(token)) {
            while (!operators.empty() && operators.top() != "(" &&
                   precedence(operators.top()) >= precedence(token)) {
                result.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }
    
    while (!operators.empty()) {
        result.push_back(operators.top());
        operators.pop();
    }
    
    return result;
}

template<typename T>
std::vector<T> Stack<T>::next_greater_element(const std::vector<T>& arr) {
    std::vector<T> result(arr.size(), T(-1));
    std::stack<int> stack; // Stack of indices
    
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        while (!stack.empty() && arr[stack.top()] < arr[i]) {
            result[stack.top()] = arr[i];
            stack.pop();
        }
        stack.push(i);
    }
    
    return result;
}

template<typename T>
int Stack<T>::largest_rectangle_histogram(const std::vector<int>& heights) {
    std::stack<int> stack; // Stack of indices
    int max_area = 0;
    int n = static_cast<int>(heights.size());
    
    for (int i = 0; i <= n; ++i) {
        int current_height = (i == n) ? 0 : heights[i];
        
        while (!stack.empty() && heights[stack.top()] > current_height) {
            int height = heights[stack.top()];
            stack.pop();
            int width = stack.empty() ? i : i - stack.top() - 1;
            max_area = std::max(max_area, height * width);
        }
        
        stack.push(i);
    }
    
    return max_area;
}

// Helper functions for Stack
template<typename T>
int Stack<T>::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

template<typename T>
bool Stack<T>::is_operator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || 
           token == "/" || token == "^";
}

template<typename T>
double Stack<T>::apply_operator(const std::string& op, double a, double b) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    if (op == "^") return std::pow(a, b);
    throw std::invalid_argument("Unknown operator: " + op);
}

// Queue Implementation

template<typename T>
Queue<T>::Queue(std::initializer_list<T> init_list) : data_(init_list) {}

template<typename T>
Queue<T>::Queue(const std::vector<T>& values) : data_(values.begin(), values.end()) {}

template<typename T>
void Queue<T>::enqueue(const T& value) {
    data_.push_back(value);
}

template<typename T>
T Queue<T>::dequeue() {
    if (empty()) {
        throw std::runtime_error("Cannot dequeue from empty queue");
    }
    T value = data_.front();
    data_.pop_front();
    return value;
}

template<typename T>
T& Queue<T>::front() {
    if (empty()) {
        throw std::runtime_error("Cannot access front of empty queue");
    }
    return data_.front();
}

template<typename T>
const T& Queue<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Cannot access front of empty queue");
    }
    return data_.front();
}

template<typename T>
T& Queue<T>::back() {
    if (empty()) {
        throw std::runtime_error("Cannot access back of empty queue");
    }
    return data_.back();
}

template<typename T>
const T& Queue<T>::back() const {
    if (empty()) {
        throw std::runtime_error("Cannot access back of empty queue");
    }
    return data_.back();
}

template<typename T>
std::vector<T> Queue<T>::to_vector() const {
    return std::vector<T>(data_.begin(), data_.end());
}

// CircularQueue Implementation

template<typename T>
CircularQueue<T>::CircularQueue(size_t capacity) 
    : data_(capacity), front_(0), back_(0), size_(0), capacity_(capacity) {}

template<typename T>
bool CircularQueue<T>::enqueue(const T& value) {
    if (full()) {
        return false;
    }
    
    data_[back_] = value;
    back_ = (back_ + 1) % capacity_;
    size_++;
    return true;
}

template<typename T>
bool CircularQueue<T>::dequeue() {
    if (empty()) {
        return false;
    }
    
    front_ = (front_ + 1) % capacity_;
    size_--;
    return true;
}

template<typename T>
T CircularQueue<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Cannot access front of empty queue");
    }
    return data_[front_];
}

template<typename T>
T CircularQueue<T>::back() const {
    if (empty()) {
        throw std::runtime_error("Cannot access back of empty queue");
    }
    size_t back_index = (back_ - 1 + capacity_) % capacity_;
    return data_[back_index];
}

// Deque Implementation

template<typename T>
Deque<T>::Deque(std::initializer_list<T> init_list) : data_(init_list) {}

template<typename T>
void Deque<T>::push_front(const T& value) {
    data_.push_front(value);
}

template<typename T>
void Deque<T>::pop_front() {
    if (empty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }
    data_.pop_front();
}

template<typename T>
T& Deque<T>::front() {
    if (empty()) {
        throw std::runtime_error("Cannot access front of empty deque");
    }
    return data_.front();
}

template<typename T>
const T& Deque<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Cannot access front of empty deque");
    }
    return data_.front();
}

template<typename T>
void Deque<T>::push_back(const T& value) {
    data_.push_back(value);
}

template<typename T>
void Deque<T>::pop_back() {
    if (empty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }
    data_.pop_back();
}

template<typename T>
T& Deque<T>::back() {
    if (empty()) {
        throw std::runtime_error("Cannot access back of empty deque");
    }
    return data_.back();
}

template<typename T>
const T& Deque<T>::back() const {
    if (empty()) {
        throw std::runtime_error("Cannot access back of empty deque");
    }
    return data_.back();
}

template<typename T>
std::vector<T> Deque<T>::to_vector() const {
    return std::vector<T>(data_.begin(), data_.end());
}

template<typename T>
std::vector<T> Deque<T>::sliding_window_maximum(const std::vector<T>& arr, size_t k) {
    if (arr.empty() || k == 0) return {};
    
    std::vector<T> result;
    std::deque<int> dq; // Store indices
    
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        // Remove indices outside current window
        while (!dq.empty() && dq.front() <= i - static_cast<int>(k)) {
            dq.pop_front();
        }
        
        // Remove indices of smaller elements
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Add to result if window is complete
        if (i >= static_cast<int>(k) - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    
    return result;
}

// QueueUsingStacks Implementation

template<typename T>
void QueueUsingStacks<T>::enqueue(const T& value) {
    input_stack_.push(value);
}

template<typename T>
T QueueUsingStacks<T>::dequeue() {
    transfer_if_needed();
    if (output_stack_.empty()) {
        throw std::runtime_error("Cannot dequeue from empty queue");
    }
    T value = output_stack_.top();
    output_stack_.pop();
    return value;
}

template<typename T>
T QueueUsingStacks<T>::front() {
    transfer_if_needed();
    if (output_stack_.empty()) {
        throw std::runtime_error("Cannot access front of empty queue");
    }
    return output_stack_.top();
}

template<typename T>
bool QueueUsingStacks<T>::empty() const {
    return input_stack_.empty() && output_stack_.empty();
}

template<typename T>
void QueueUsingStacks<T>::transfer_if_needed() {
    if (output_stack_.empty()) {
        while (!input_stack_.empty()) {
            output_stack_.push(input_stack_.top());
            input_stack_.pop();
        }
    }
}

// StackUsingQueues Implementation

template<typename T>
void StackUsingQueues<T>::push(const T& value) {
    temp_queue_.push(value);
    
    // Move all elements from main to temp
    while (!main_queue_.empty()) {
        temp_queue_.push(main_queue_.front());
        main_queue_.pop();
    }
    
    // Swap the queues
    std::swap(main_queue_, temp_queue_);
}

template<typename T>
T StackUsingQueues<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Cannot pop from empty stack");
    }
    T value = main_queue_.front();
    main_queue_.pop();
    return value;
}

template<typename T>
T StackUsingQueues<T>::top() {
    if (empty()) {
        throw std::runtime_error("Cannot access top of empty stack");
    }
    return main_queue_.front();
}

template<typename T>
bool StackUsingQueues<T>::empty() const {
    return main_queue_.empty();
}

// MinStack Implementation

template<typename T>
void MinStack<T>::push(const T& value) {
    data_stack_.push(value);
    
    if (min_stack_.empty() || value <= min_stack_.top()) {
        min_stack_.push(value);
    }
}

template<typename T>
void MinStack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Cannot pop from empty stack");
    }
    
    if (data_stack_.top() == min_stack_.top()) {
        min_stack_.pop();
    }
    data_stack_.pop();
}

template<typename T>
T MinStack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Cannot access top of empty stack");
    }
    return data_stack_.top();
}

template<typename T>
T MinStack<T>::get_min() const {
    if (empty()) {
        throw std::runtime_error("Cannot get min of empty stack");
    }
    return min_stack_.top();
}

template<typename T>
bool MinStack<T>::empty() const {
    return data_stack_.empty();
}

} // namespace data_structures
} // namespace leetcode_study_guide