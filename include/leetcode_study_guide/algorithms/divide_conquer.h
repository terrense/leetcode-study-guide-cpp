#ifndef LEETCODE_STUDY_GUIDE_DIVIDE_CONQUER_H
#define LEETCODE_STUDY_GUIDE_DIVIDE_CONQUER_H

#include <vector>
#include <string>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Divide and Conquer Algorithm Patterns
 * 
 * This module implements common divide and conquer strategies for
 * recursive problem solving commonly found in LeetCode problems.
 */
class DivideConquer {
public:
    /**
     * Merge Sort - Classic divide and conquer sorting
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static void mergeSort(std::vector<int>& nums);
    static void mergeSortRange(std::vector<int>& nums, int left, int right);
    static void merge(std::vector<int>& nums, int left, int mid, int right);
    
    /**
     * Quick Sort - Divide and conquer with partitioning
     * Time Complexity: O(n log n) average, O(n^2) worst
     * Space Complexity: O(log n) average
     */
    static void quickSort(std::vector<int>& nums);
    static void quickSortRange(std::vector<int>& nums, int left, int right);
    static int partition(std::vector<int>& nums, int left, int right);
    
    /**
     * Maximum Subarray (Kadane's Algorithm using D&C)
     * Time Complexity: O(n log n)
     * Space Complexity: O(log n)
     */
    static int maxSubArray(const std::vector<int>& nums);
    static int maxSubArrayHelper(const std::vector<int>& nums, int left, int right);
    static int maxCrossingSum(const std::vector<int>& nums, int left, int mid, int right);
    
    /**
     * Closest Pair of Points
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    struct Point {
        double x, y;
        Point(double x = 0, double y = 0) : x(x), y(y) {}
    };
    
    static double closestPair(std::vector<Point>& points);
    static double closestPairHelper(std::vector<Point>& pointsX, std::vector<Point>& pointsY);
    static double distance(const Point& p1, const Point& p2);
    static double stripClosest(std::vector<Point>& strip, double minDist);
    
    /**
     * Strassen's Matrix Multiplication
     * Time Complexity: O(n^2.807)
     * Space Complexity: O(n^2)
     */
    static std::vector<std::vector<int>> matrixMultiply(const std::vector<std::vector<int>>& A,
                                                       const std::vector<std::vector<int>>& B);
    static std::vector<std::vector<int>> strassenMultiply(const std::vector<std::vector<int>>& A,
                                                         const std::vector<std::vector<int>>& B);
    
    /**
     * Count Inversions in Array
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static int countInversions(std::vector<int>& nums);
    static int countInversionsHelper(std::vector<int>& nums, int left, int right);
    static int mergeAndCount(std::vector<int>& nums, int left, int mid, int right);
    
    /**
     * Majority Element (Boyer-Moore using D&C approach)
     * Time Complexity: O(n log n)
     * Space Complexity: O(log n)
     */
    static int majorityElement(const std::vector<int>& nums);
    static int majorityElementHelper(const std::vector<int>& nums, int left, int right);
    static int countInRange(const std::vector<int>& nums, int target, int left, int right);
    
    /**
     * Pow(x, n) - Fast Exponentiation
     * Time Complexity: O(log n)
     * Space Complexity: O(log n)
     */
    static double myPow(double x, int n);
    static double powHelper(double x, long long n);
    
    /**
     * Kth Largest Element (QuickSelect)
     * Time Complexity: O(n) average, O(n^2) worst
     * Space Complexity: O(log n) average
     */
    static int findKthLargest(std::vector<int>& nums, int k);
    static int quickSelect(std::vector<int>& nums, int left, int right, int k);
    
    /**
     * Different Ways to Add Parentheses
     * Time Complexity: O(4^n / n^(3/2))
     * Space Complexity: O(4^n / n^(3/2))
     */
    static std::vector<int> diffWaysToCompute(const std::string& expression);
    static std::vector<int> computeHelper(const std::string& expression, int start, int end);
    static bool isOperator(char c);
    static int compute(int left, int right, char op);
    
    /**
     * Unique Binary Search Trees II
     * Time Complexity: O(4^n / n^(3/2))
     * Space Complexity: O(4^n / n^(3/2))
     */
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    
    static std::vector<TreeNode*> generateTrees(int n);
    static std::vector<TreeNode*> generateTreesHelper(int start, int end);
    
    /**
     * Median of Two Sorted Arrays
     * Time Complexity: O(log(min(m,n)))
     * Space Complexity: O(1)
     */
    static double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2);

private:
    // Helper functions for matrix operations
    static std::vector<std::vector<int>> addMatrices(const std::vector<std::vector<int>>& A,
                                                    const std::vector<std::vector<int>>& B);
    static std::vector<std::vector<int>> subtractMatrices(const std::vector<std::vector<int>>& A,
                                                         const std::vector<std::vector<int>>& B);
    static std::vector<std::vector<int>> getSubMatrix(const std::vector<std::vector<int>>& matrix,
                                                     int row, int col, int size);
    static void setSubMatrix(std::vector<std::vector<int>>& matrix,
                            const std::vector<std::vector<int>>& subMatrix,
                            int row, int col);
};

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_DIVIDE_CONQUER_H