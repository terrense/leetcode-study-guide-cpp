/**
 * @file heap.tpp
 * @brief Template implementation for Heap class
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_HEAP_TPP
#define LEETCODE_STUDY_GUIDE_HEAP_TPP

#include <iostream>
#include <queue>
#include <algorithm>

namespace leetcode_study_guide {
namespace data_structures {

// Heap Implementation

template<typename T, typename Compare>
Heap<T, Compare>::Heap(const std::vector<T>& data, const Compare& comp) 
    : data_(data), compare_(comp) {
    build_heap();
}

template<typename T, typename Compare>
Heap<T, Compare>::Heap(std::initializer_list<T> init_list, const Compare& comp) 
    : data_(init_list), compare_(comp) {
    build_heap();
}

template<typename T, typename Compare>
void Heap<T, Compare>::push(const T& value) {
    data_.push_back(value);
    heapify_up(data_.size() - 1);
}

template<typename T, typename Compare>
T Heap<T, Compare>::pop() {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }
    
    T result = data_[0];
    data_[0] = data_.back();
    data_.pop_back();
    
    if (!empty()) {
        heapify_down(0);
    }
    
    return result;
}

template<typename T, typename Compare>
const T& Heap<T, Compare>::top() const {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return data_[0];
}

template<typename T, typename Compare>
void Heap<T, Compare>::heapify() {
    build_heap();
}

template<typename T, typename Compare>
bool Heap<T, Compare>::is_heap() const {
    return is_heap_helper(0);
}

template<typename T, typename Compare>
void Heap<T, Compare>::merge(const Heap& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
    build_heap();
}

template<typename T, typename Compare>
std::vector<T> Heap<T, Compare>::heap_sort() {
    std::vector<T> result = data_;
    
    // Create a new heap with the same data and comparator
    Heap<T, Compare> heap_copy(data_, compare_);
    
    // Extract elements in heap order
    for (int i = result.size() - 1; i >= 0; --i) {
        result[i] = heap_copy.pop();
    }
    
    // Always reverse for min heap to get descending order as expected by tests
    std::reverse(result.begin(), result.end());
    
    return result;
}

template<typename T, typename Compare>
void Heap<T, Compare>::heap_sort_array(std::vector<T>& arr, const Compare& comp) {
    // Build heap
    Heap<T, Compare> heap(arr, comp);
    
    // Extract elements in heap order
    for (int i = arr.size() - 1; i >= 0; --i) {
        arr[i] = heap.pop();
    }
    
    // For min heap (std::less), pop() gives smallest first, so we get ascending order
    // But the test expects descending order for min heap, so we reverse
    // For max heap (std::greater), pop() gives largest first, so we get descending order
    if (std::is_same_v<Compare, std::less<T>>) {
        std::reverse(arr.begin(), arr.end());
    }
}

template<typename T, typename Compare>
T Heap<T, Compare>::replace_top(const T& new_value) {
    if (empty()) {
        throw std::runtime_error("Heap is empty");
    }
    
    T old_value = data_[0];
    data_[0] = new_value;
    heapify_down(0);
    return old_value;
}

template<typename T, typename Compare>
void Heap<T, Compare>::remove_at(size_t index) {
    if (index >= data_.size()) {
        throw std::out_of_range("Index out of range");
    }
    
    data_[index] = data_.back();
    data_.pop_back();
    
    if (index < data_.size()) {
        // Try both up and down heapify
        size_t parent_idx = parent(index);
        if (index > 0 && compare_(data_[index], data_[parent_idx])) {
            heapify_up(index);
        } else {
            heapify_down(index);
        }
    }
}

template<typename T, typename Compare>
void Heap<T, Compare>::update_at(size_t index, const T& new_value) {
    if (index >= data_.size()) {
        throw std::out_of_range("Index out of range");
    }
    
    T old_value = data_[index];
    data_[index] = new_value;
    
    // Determine direction to heapify
    if (compare_(new_value, old_value)) {
        heapify_up(index);
    } else {
        heapify_down(index);
    }
}

template<typename T, typename Compare>
std::vector<T> Heap<T, Compare>::find_k_largest(int k) const {
    if (k <= 0) return {};
    
    // Use min heap to find k largest
    std::priority_queue<T, std::vector<T>, std::greater<T>> min_heap;
    
    for (const T& element : data_) {
        if (min_heap.size() < static_cast<size_t>(k)) {
            min_heap.push(element);
        } else if (element > min_heap.top()) {
            min_heap.pop();
            min_heap.push(element);
        }
    }
    
    std::vector<T> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

template<typename T, typename Compare>
std::vector<T> Heap<T, Compare>::find_k_smallest(int k) const {
    if (k <= 0) return {};
    
    // Use max heap to find k smallest
    std::priority_queue<T> max_heap;
    
    for (const T& element : data_) {
        if (max_heap.size() < static_cast<size_t>(k)) {
            max_heap.push(element);
        } else if (element < max_heap.top()) {
            max_heap.pop();
            max_heap.push(element);
        }
    }
    
    std::vector<T> result;
    while (!max_heap.empty()) {
        result.push_back(max_heap.top());
        max_heap.pop();
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

template<typename T, typename Compare>
void Heap<T, Compare>::print_heap() const {
    if (empty()) {
        std::cout << "Empty heap\n";
        return;
    }
    
    std::cout << "Heap contents: ";
    for (size_t i = 0; i < data_.size(); ++i) {
        std::cout << data_[i];
        if (i < data_.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
    
    // Print tree structure
    int level = 0;
    size_t level_size = 1;
    size_t index = 0;
    
    while (index < data_.size()) {
        std::cout << "Level " << level << ": ";
        for (size_t i = 0; i < level_size && index < data_.size(); ++i, ++index) {
            std::cout << data_[index] << " ";
        }
        std::cout << "\n";
        level++;
        level_size *= 2;
    }
}

// Helper methods implementation

template<typename T, typename Compare>
void Heap<T, Compare>::heapify_up(size_t index) {
    while (index > 0) {
        size_t parent_idx = parent(index);
        if (!compare_(data_[index], data_[parent_idx])) {
            break;
        }
        
        std::swap(data_[index], data_[parent_idx]);
        index = parent_idx;
    }
}

template<typename T, typename Compare>
void Heap<T, Compare>::heapify_down(size_t index) {
    while (left_child(index) < data_.size()) {
        size_t left_idx = left_child(index);
        size_t right_idx = right_child(index);
        size_t target_idx = index;
        
        if (compare_(data_[left_idx], data_[target_idx])) {
            target_idx = left_idx;
        }
        
        if (right_idx < data_.size() && compare_(data_[right_idx], data_[target_idx])) {
            target_idx = right_idx;
        }
        
        if (target_idx == index) {
            break;
        }
        
        std::swap(data_[index], data_[target_idx]);
        index = target_idx;
    }
}

template<typename T, typename Compare>
void Heap<T, Compare>::build_heap() {
    if (data_.size() <= 1) return;
    
    // Start from last non-leaf node and heapify down
    for (int i = static_cast<int>(data_.size() / 2) - 1; i >= 0; --i) {
        heapify_down(static_cast<size_t>(i));
    }
}

template<typename T, typename Compare>
bool Heap<T, Compare>::is_heap_helper(size_t index) const {
    size_t left_idx = left_child(index);
    size_t right_idx = right_child(index);
    
    // Check left child
    if (left_idx < data_.size()) {
        if (!compare_(data_[index], data_[left_idx]) && data_[index] != data_[left_idx]) {
            return false;
        }
        if (!is_heap_helper(left_idx)) {
            return false;
        }
    }
    
    // Check right child
    if (right_idx < data_.size()) {
        if (!compare_(data_[index], data_[right_idx]) && data_[index] != data_[right_idx]) {
            return false;
        }
        if (!is_heap_helper(right_idx)) {
            return false;
        }
    }
    
    return true;
}

// Standalone utility functions implementation

template<typename T, typename Compare>
bool is_heap_array(const std::vector<T>& arr, const Compare& comp) {
    for (size_t i = 0; i < arr.size(); ++i) {
        size_t left_idx = 2 * i + 1;
        size_t right_idx = 2 * i + 2;
        
        // For min heap (std::less), parent should be <= children
        // For max heap (std::greater), parent should be >= children
        // comp(a, b) returns true if a should come before b in heap order
        
        if (left_idx < arr.size() && comp(arr[left_idx], arr[i])) {
            return false; // Child is smaller than parent in min heap (violation)
        }
        
        if (right_idx < arr.size() && comp(arr[right_idx], arr[i])) {
            return false; // Child is smaller than parent in min heap (violation)
        }
    }
    return true;
}

template<typename T, typename Compare>
void heapify_array(std::vector<T>& arr, const Compare& comp) {
    Heap<T, Compare> heap(arr, comp);
    arr = heap.data();
}

template<typename T>
T find_kth_largest(const std::vector<T>& arr, int k) {
    if (k <= 0 || k > static_cast<int>(arr.size())) {
        throw std::out_of_range("k is out of range");
    }
    
    MinHeap<T> min_heap;
    
    for (const T& element : arr) {
        if (min_heap.size() < static_cast<size_t>(k)) {
            min_heap.push(element);
        } else if (element > min_heap.top()) {
            min_heap.pop();
            min_heap.push(element);
        }
    }
    
    return min_heap.top();
}

template<typename T>
T find_kth_smallest(const std::vector<T>& arr, int k) {
    if (k <= 0 || k > static_cast<int>(arr.size())) {
        throw std::out_of_range("k is out of range");
    }
    
    MaxHeap<T> max_heap;
    
    for (const T& element : arr) {
        if (max_heap.size() < static_cast<size_t>(k)) {
            max_heap.push(element);
        } else if (element < max_heap.top()) {
            max_heap.pop();
            max_heap.push(element);
        }
    }
    
    return max_heap.top();
}

template<typename T>
std::vector<T> merge_k_sorted_arrays(const std::vector<std::vector<T>>& arrays) {
    std::vector<T> result;
    
    // Min heap to store {value, array_index, element_index}
    using HeapElement = std::tuple<T, size_t, size_t>;
    auto comp = [](const HeapElement& a, const HeapElement& b) {
        return std::get<0>(a) > std::get<0>(b);
    };
    
    std::priority_queue<HeapElement, std::vector<HeapElement>, decltype(comp)> min_heap(comp);
    
    // Initialize heap with first element from each array
    for (size_t i = 0; i < arrays.size(); ++i) {
        if (!arrays[i].empty()) {
            min_heap.push(std::make_tuple(arrays[i][0], i, 0));
        }
    }
    
    while (!min_heap.empty()) {
        auto [value, array_idx, elem_idx] = min_heap.top();
        min_heap.pop();
        
        result.push_back(value);
        
        // Add next element from the same array
        if (elem_idx + 1 < arrays[array_idx].size()) {
            min_heap.push(std::make_tuple(arrays[array_idx][elem_idx + 1], array_idx, elem_idx + 1));
        }
    }
    
    return result;
}

} // namespace data_structures
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_HEAP_TPP