#ifndef LEETCODE_STUDY_GUIDE_SORTING_H
#define LEETCODE_STUDY_GUIDE_SORTING_H

#include <vector>
#include <functional>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Sorting Algorithm Patterns
 * 
 * This module implements various sorting algorithms commonly used
 * in LeetCode problems, including comparison-based and non-comparison
 * based sorting algorithms with different time and space complexities.
 */
class Sorting {
public:
    /**
     * Bubble Sort - Simple comparison-based sorting
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    static void bubbleSort(std::vector<int>& nums);
    
    /**
     * Selection Sort - Find minimum and place at beginning
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    static void selectionSort(std::vector<int>& nums);
    
    /**
     * Insertion Sort - Build sorted array one element at a time
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    static void insertionSort(std::vector<int>& nums);
    
    /**
     * Merge Sort - Divide and conquer approach
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static void mergeSort(std::vector<int>& nums);
    static void mergeSortHelper(std::vector<int>& nums, int left, int right);
    static void merge(std::vector<int>& nums, int left, int mid, int right);
    
    /**
     * Quick Sort - Partition-based divide and conquer
     * Time Complexity: O(n log n) average, O(n^2) worst
     * Space Complexity: O(log n) average
     */
    static void quickSort(std::vector<int>& nums);
    static void quickSortHelper(std::vector<int>& nums, int left, int right);
    static int partition(std::vector<int>& nums, int left, int right);
    static int randomizedPartition(std::vector<int>& nums, int left, int right);
    
    /**
     * Heap Sort - Using heap data structure
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     */
    static void heapSort(std::vector<int>& nums);
    static void heapify(std::vector<int>& nums, int n, int i);
    static void buildMaxHeap(std::vector<int>& nums);
    
    /**
     * Counting Sort - Non-comparison based for integers
     * Time Complexity: O(n + k) where k is range
     * Space Complexity: O(k)
     */
    static void countingSort(std::vector<int>& nums);
    static void countingSortRange(std::vector<int>& nums, int minVal, int maxVal);
    
    /**
     * Radix Sort - Non-comparison based for integers
     * Time Complexity: O(d * (n + k)) where d is digits, k is radix
     * Space Complexity: O(n + k)
     */
    static void radixSort(std::vector<int>& nums);
    static void countingSortForRadix(std::vector<int>& nums, int exp);
    static int getMax(const std::vector<int>& nums);
    
    /**
     * Bucket Sort - Distribute elements into buckets
     * Time Complexity: O(n + k) average, O(n^2) worst
     * Space Complexity: O(n + k)
     */
    static void bucketSort(std::vector<double>& nums);
    
    /**
     * Custom sorting with comparator
     * Time Complexity: O(n log n)
     * Space Complexity: O(log n)
     */
    template<typename T>
    static void customSort(std::vector<T>& nums, std::function<bool(const T&, const T&)> compare);
    
    /**
     * Sorting-related LeetCode problems
     */
    
    /**
     * Sort Colors (Dutch National Flag)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static void sortColors(std::vector<int>& nums);
    
    /**
     * Merge Intervals
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    struct Interval {
        int start, end;
        Interval(int s, int e) : start(s), end(e) {}
    };
    
    static std::vector<Interval> mergeIntervals(std::vector<Interval>& intervals);
    
    /**
     * Largest Number - Custom sorting problem
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static std::string largestNumber(std::vector<int>& nums);
    
    /**
     * Meeting Rooms II - Interval scheduling
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static int minMeetingRooms(std::vector<Interval>& intervals);
    
    /**
     * Kth Largest Element in Array
     * Time Complexity: O(n) average using QuickSelect
     * Space Complexity: O(1)
     */
    static int findKthLargest(std::vector<int>& nums, int k);
    static int quickSelect(std::vector<int>& nums, int left, int right, int k);
    
    /**
     * Top K Frequent Elements
     * Time Complexity: O(n log k)
     * Space Complexity: O(n + k)
     */
    static std::vector<int> topKFrequent(std::vector<int>& nums, int k);
    
    /**
     * Sort Array by Parity
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static std::vector<int> sortArrayByParity(std::vector<int>& nums);
    
    /**
     * Pancake Sorting
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    static std::vector<int> pancakeSort(std::vector<int>& nums);
    static void flip(std::vector<int>& nums, int k);
    
    /**
     * Wiggle Sort II
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static void wiggleSort(std::vector<int>& nums);

private:
    // Helper functions
    static bool customCompare(const std::string& a, const std::string& b);
    static int findMaxIndex(const std::vector<int>& nums, int end);
};

// Template implementation
template<typename T>
void Sorting::customSort(std::vector<T>& nums, std::function<bool(const T&, const T&)> compare) {
    std::sort(nums.begin(), nums.end(), compare);
}

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_SORTING_H