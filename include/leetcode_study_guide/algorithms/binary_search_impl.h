#ifndef LEETCODE_STUDY_GUIDE_BINARY_SEARCH_IMPL_H
#define LEETCODE_STUDY_GUIDE_BINARY_SEARCH_IMPL_H

#include <vector>
#include <functional>

namespace leetcode_study_guide {
namespace algorithms {

#ifndef LEETCODE_STUDY_GUIDE_BINARY_SEARCH_IMPL_H
#define LEETCODE_STUDY_GUIDE_BINARY_SEARCH_IMPL_H

#include <vector>
#include <functional>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Classic Binary Search Implementation
 * The fundamental binary search algorithm for finding a target in a sorted array.
 * 
 * Algorithm Logic:
 * 1. Compare target with middle element
 * 2. If equal, found the target
 * 3. If target is smaller, search left half
 * 4. If target is larger, search right half
 * 5. Repeat until found or search space is empty
 * 
 * Key Insights:
 * - Array must be sorted for binary search to work
 * - Each comparison eliminates half of remaining elements
 * - Use left + (right - left) / 2 to avoid integer overflow
 */
template<typename T>
int BinarySearch::search(const std::vector<T>& nums, const T& target) {
    // Initialize search boundaries
    int left = 0, right = nums.size() - 1;
    
    // Continue searching while search space is valid
    while (left <= right) {
        // Calculate middle index, avoiding overflow
        // Using (left + right) / 2 could overflow for large indices
        int mid = left + (right - left) / 2;
        
        // Check if we found the target
        if (nums[mid] == target) {
            return mid;  // Target found, return its index
        } 
        // Target is in the right half
        else if (nums[mid] < target) {
            left = mid + 1;  // Eliminate left half including mid
        } 
        // Target is in the left half
        else {
            right = mid - 1; // Eliminate right half including mid
        }
    }
    
    // Target not found in array
    return -1;
}

/**
 * Find First Occurrence (Left Boundary) Binary Search
 * Finds the leftmost (first) occurrence of target in a sorted array with duplicates.
 * 
 * Key Difference from Classic Binary Search:
 * - When we find target, we don't return immediately
 * - Instead, we continue searching left to find the first occurrence
 * - This ensures we get the leftmost index of the target
 * 
 * Use Cases:
 * - Finding insertion point for maintaining sorted order
 * - Finding first occurrence in array with duplicates
 * - Lower bound operations
 */
template<typename T>
int BinarySearch::searchFirst(const std::vector<T>& nums, const T& target) {
    int left = 0, right = nums.size() - 1;
    int result = -1;  // Store the result, -1 means not found
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            // Found target, but continue searching left for first occurrence
            result = mid;           // Update result with current position
            right = mid - 1;        // Continue searching in left half
        } else if (nums[mid] < target) {
            left = mid + 1;         // Target is in right half
        } else {
            right = mid - 1;        // Target is in left half
        }
    }
    
    return result;  // Returns leftmost occurrence or -1 if not found
}

/**
 * Find Last Occurrence (Right Boundary) Binary Search
 * Finds the rightmost (last) occurrence of target in a sorted array with duplicates.
 * 
 * Key Difference from searchFirst:
 * - When we find target, we continue searching right instead of left
 * - This ensures we get the rightmost index of the target
 * 
 * Use Cases:
 * - Finding last occurrence in array with duplicates
 * - Upper bound operations
 * - Range queries (combine with searchFirst to get range)
 */
template<typename T>
int BinarySearch::searchLast(const std::vector<T>& nums, const T& target) {
    int left = 0, right = nums.size() - 1;
    int result = -1;  // Store the result, -1 means not found
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            // Found target, but continue searching right for last occurrence
            result = mid;           // Update result with current position
            left = mid + 1;         // Continue searching in right half
        } else if (nums[mid] < target) {
            left = mid + 1;         // Target is in right half
        } else {
            right = mid - 1;        // Target is in left half
        }
    }
    
    return result;  // Returns rightmost occurrence or -1 if not found
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