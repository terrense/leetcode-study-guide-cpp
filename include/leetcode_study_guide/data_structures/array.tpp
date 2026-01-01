/**
 * @file array.tpp
 * @brief Template implementation for Array class
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

namespace leetcode_study_guide {
namespace data_structures {

// Constructor implementations
template<typename T>
Array<T>::Array(size_t capacity) {
    data_.reserve(capacity);
}

template<typename T>
Array<T>::Array(const std::vector<T>& values) : data_(values) {}

template<typename T>
Array<T>::Array(std::initializer_list<T> init_list) : data_(init_list) {}

// Basic Operations
template<typename T>
void Array<T>::push_back(const T& value) {
    data_.push_back(value);
}

template<typename T>
void Array<T>::insert(size_t index, const T& value) {
    if (index > data_.size()) {
        throw std::out_of_range("Index out of range");
    }
    data_.insert(data_.begin() + index, value);
}

template<typename T>
void Array<T>::pop_back() {
    if (data_.empty()) {
        throw std::runtime_error("Cannot pop from empty array");
    }
    data_.pop_back();
}

template<typename T>
void Array<T>::erase(size_t index) {
    if (index >= data_.size()) {
        throw std::out_of_range("Index out of range");
    }
    data_.erase(data_.begin() + index);
}

template<typename T>
int Array<T>::linear_search(const T& value) const {
    for (size_t i = 0; i < data_.size(); ++i) {
        if (data_[i] == value) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template<typename T>
int Array<T>::binary_search(const T& value) const {
    int left = 0;
    int right = static_cast<int>(data_.size()) - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (data_[mid] == value) {
            return mid;
        } else if (data_[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Two Pointers Algorithms
template<typename T>
std::pair<int, int> Array<T>::two_sum_sorted(const T& target) const {
    int left = 0;
    int right = static_cast<int>(data_.size()) - 1;
    
    while (left < right) {
        T sum = data_[left] + data_[right];
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return {-1, -1};
}

template<typename T>
size_t Array<T>::remove_duplicates_sorted() {
    if (data_.empty()) return 0;
    
    size_t write_index = 1;
    for (size_t read_index = 1; read_index < data_.size(); ++read_index) {
        if (data_[read_index] != data_[read_index - 1]) {
            data_[write_index] = data_[read_index];
            write_index++;
        }
    }
    
    data_.resize(write_index);
    return write_index;
}

template<typename T>
bool Array<T>::is_palindrome() const {
    int left = 0;
    int right = static_cast<int>(data_.size()) - 1;
    
    while (left < right) {
        if (data_[left] != data_[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Sliding Window Algorithms
template<typename T>
T Array<T>::max_sum_subarray(size_t k) const {
    if (k > data_.size()) {
        throw std::invalid_argument("Window size larger than array size");
    }
    
    // Calculate sum of first window
    T window_sum = T{};
    for (size_t i = 0; i < k; ++i) {
        window_sum += data_[i];
    }
    
    T max_sum = window_sum;
    
    // Slide the window
    for (size_t i = k; i < data_.size(); ++i) {
        window_sum = window_sum - data_[i - k] + data_[i];
        max_sum = std::max(max_sum, window_sum);
    }
    
    return max_sum;
}

template<typename T>
size_t Array<T>::longest_subarray_k_distinct(size_t k) const {
    if (k == 0) return 0;
    
    std::unordered_map<T, int> freq;
    size_t left = 0, max_length = 0;
    
    for (size_t right = 0; right < data_.size(); ++right) {
        freq[data_[right]]++;
        
        while (freq.size() > k) {
            freq[data_[left]]--;
            if (freq[data_[left]] == 0) {
                freq.erase(data_[left]);
            }
            left++;
        }
        
        max_length = std::max(max_length, right - left + 1);
    }
    
    return max_length;
}

// Sorting Algorithms
template<typename T>
void Array<T>::merge_sort() {
    if (data_.size() <= 1) return;
    merge_sort_helper(0, static_cast<int>(data_.size()) - 1);
}

template<typename T>
void Array<T>::merge_sort_helper(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(left, mid);
        merge_sort_helper(mid + 1, right);
        merge(left, mid, right);
    }
}

template<typename T>
void Array<T>::merge(int left, int mid, int right) {
    std::vector<T> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (data_[i] <= data_[j]) {
            temp[k++] = data_[i++];
        } else {
            temp[k++] = data_[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = data_[i++];
    }
    
    while (j <= right) {
        temp[k++] = data_[j++];
    }
    
    for (int i = left; i <= right; ++i) {
        data_[i] = temp[i - left];
    }
}

template<typename T>
void Array<T>::quick_sort() {
    if (data_.size() <= 1) return;
    quick_sort_helper(0, static_cast<int>(data_.size()) - 1);
}

template<typename T>
void Array<T>::quick_sort_helper(int left, int right) {
    if (left < right) {
        int pivot_index = partition(left, right);
        quick_sort_helper(left, pivot_index - 1);
        quick_sort_helper(pivot_index + 1, right);
    }
}

template<typename T>
int Array<T>::partition(int left, int right) {
    T pivot = data_[right];
    int i = left - 1;
    
    for (int j = left; j < right; ++j) {
        if (data_[j] <= pivot) {
            i++;
            std::swap(data_[i], data_[j]);
        }
    }
    
    std::swap(data_[i + 1], data_[right]);
    return i + 1;
}

template<typename T>
void Array<T>::heap_sort() {
    int n = static_cast<int>(data_.size());
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(n, i);
    }
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        std::swap(data_[0], data_[i]);
        heapify(i, 0);
    }
}

template<typename T>
void Array<T>::heapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && data_[left] > data_[largest]) {
        largest = left;
    }
    
    if (right < n && data_[right] > data_[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        std::swap(data_[i], data_[largest]);
        heapify(n, largest);
    }
}

// Utility Methods
template<typename T>
T& Array<T>::operator[](size_t index) {
    return data_[index];
}

template<typename T>
const T& Array<T>::operator[](size_t index) const {
    return data_[index];
}

template<typename T>
T& Array<T>::at(size_t index) {
    if (index >= data_.size()) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
const T& Array<T>::at(size_t index) const {
    if (index >= data_.size()) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

// Standalone Algorithm Functions
template<typename T>
T max_subarray_sum(const std::vector<T>& arr) {
    if (arr.empty()) {
        throw std::invalid_argument("Array cannot be empty");
    }
    
    T max_sum = arr[0];
    T current_sum = arr[0];
    
    for (size_t i = 1; i < arr.size(); ++i) {
        current_sum = std::max(arr[i], current_sum + arr[i]);
        max_sum = std::max(max_sum, current_sum);
    }
    
    return max_sum;
}

template<typename T>
void dutch_flag_partition(std::vector<T>& arr, const T& pivot) {
    int low = 0, mid = 0;
    int high = static_cast<int>(arr.size()) - 1;
    
    while (mid <= high) {
        if (arr[mid] < pivot) {
            std::swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] > pivot) {
            std::swap(arr[mid], arr[high]);
            high--;
        } else {
            mid++;
        }
    }
}

template<typename T>
void rotate_array(std::vector<T>& arr, int k) {
    int n = static_cast<int>(arr.size());
    if (n == 0) return;
    
    k = k % n;
    if (k == 0) return;
    
    // Reverse entire array
    std::reverse(arr.begin(), arr.end());
    
    // Reverse first k elements
    std::reverse(arr.begin(), arr.begin() + k);
    
    // Reverse remaining elements
    std::reverse(arr.begin() + k, arr.end());
}

template<typename T>
std::vector<std::pair<int, int>> find_all_pairs_sum(const std::vector<T>& arr, const T& target) {
    std::vector<std::pair<int, int>> result;
    std::unordered_map<T, std::vector<int>> value_indices;
    
    // Build map of values to their indices
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        value_indices[arr[i]].push_back(i);
    }
    
    // Find all pairs
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        T complement = target - arr[i];
        
        if (value_indices.find(complement) != value_indices.end()) {
            for (int j : value_indices[complement]) {
                if (i < j) {  // Avoid duplicates and self-pairing
                    result.push_back({i, j});
                }
            }
        }
    }
    
    return result;
}

} // namespace data_structures
} // namespace leetcode_study_guide