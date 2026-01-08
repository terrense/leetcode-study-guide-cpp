#ifndef LEETCODE_STUDY_GUIDE_BINARY_SEARCH_IMPL_H
#define LEETCODE_STUDY_GUIDE_BINARY_SEARCH_IMPL_H

#include <vector>
#include <functional>

namespace leetcode_study_guide {
namespace algorithms {

template<typename T>
int BinarySearch::search(const std::vector<T>& nums, const T& target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Target not found
}

template<typename T>
int BinarySearch::searchFirst(const std::vector<T>& nums, const T& target) {
    int left = 0, right = nums.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            result = mid;
            right = mid - 1; // Continue searching left for first occurrence
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

template<typename T>
int BinarySearch::searchLast(const std::vector<T>& nums, const T& target) {
    int left = 0, right = nums.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            result = mid;
            left = mid + 1; // Continue searching right for last occurrence
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

template<typename T>
int BinarySearch::searchRotated(const std::vector<T>& nums, const T& target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        // Check which half is sorted
        if (nums[left] <= nums[mid]) {
            // Left half is sorted
            if (target >= nums[left] && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            // Right half is sorted
            if (target > nums[mid] && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return -1;
}

template<typename T>
int BinarySearch::findMin(const std::vector<T>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[right]) {
            // Minimum is in right half
            left = mid + 1;
        } else {
            // Minimum is in left half (including mid)
            right = mid;
        }
    }
    
    return left;
}

template<typename T>
bool BinarySearch::searchMatrix(const std::vector<std::vector<T>>& matrix, const T& target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }
    
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / n;
        int col = mid % n;
        
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}

template<typename T>
int BinarySearch::binarySearchGeneric(const std::vector<T>& nums, 
                                      std::function<bool(const T&)> predicate) {
    int left = 0, right = nums.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (predicate(nums[mid])) {
            result = mid;
            right = mid - 1; // Continue searching for first occurrence
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_BINARY_SEARCH_IMPL_H