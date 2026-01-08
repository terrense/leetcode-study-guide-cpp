#ifndef LEETCODE_STUDY_GUIDE_SLIDING_WINDOW_H
#define LEETCODE_STUDY_GUIDE_SLIDING_WINDOW_H

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Sliding Window Technique Patterns
 * 
 * This module implements various sliding window patterns commonly used
 * in LeetCode problems for array and string optimization problems.
 */
class SlidingWindow {
public:
    /**
     * Fixed Size Sliding Window
     * Window size is predetermined and constant
     */
    
    /**
     * Maximum Sum Subarray of Size K
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int maxSumSubarray(const std::vector<int>& nums, int k);
    
    /**
     * Average of Subarrays of Size K
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static std::vector<double> findAverages(const std::vector<int>& nums, int k);
    
    /**
     * Maximum of All Subarrays of Size K
     * Time Complexity: O(n)
     * Space Complexity: O(k)
     */
    static std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k);
    
    /**
     * Variable Size Sliding Window
     * Window size changes based on conditions
     */
    
    /**
     * Longest Substring Without Repeating Characters
     * Time Complexity: O(n)
     * Space Complexity: O(min(m,n)) where m is charset size
     */
    static int lengthOfLongestSubstring(const std::string& s);
    
    /**
     * Longest Substring with At Most K Distinct Characters
     * Time Complexity: O(n)
     * Space Complexity: O(k)
     */
    static int lengthOfLongestSubstringKDistinct(const std::string& s, int k);
    
    /**
     * Longest Substring with At Most Two Distinct Characters
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int lengthOfLongestSubstringTwoDistinct(const std::string& s);
    
    /**
     * Minimum Window Substring
     * Time Complexity: O(|s| + |t|)
     * Space Complexity: O(|s| + |t|)
     */
    static std::string minWindow(const std::string& s, const std::string& t);
    
    /**
     * Longest Repeating Character Replacement
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int characterReplacement(const std::string& s, int k);
    
    /**
     * Subarray Problems with Sliding Window
     */
    
    /**
     * Minimum Size Subarray Sum
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int minSubArrayLen(int target, const std::vector<int>& nums);
    
    /**
     * Maximum Length of Repeated Subarray
     * Time Complexity: O(m * n)
     * Space Complexity: O(min(m, n))
     */
    static int findLength(const std::vector<int>& nums1, const std::vector<int>& nums2);
    
    /**
     * Subarray Product Less Than K
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int numSubarrayProductLessThanK(const std::vector<int>& nums, int k);
    
    /**
     * Fruit Into Baskets (At Most Two Types)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int totalFruit(const std::vector<int>& fruits);
    
    /**
     * Permutation in String
     * Time Complexity: O(|s1| + |s2|)
     * Space Complexity: O(|s1|)
     */
    static bool checkInclusion(const std::string& s1, const std::string& s2);
    
    /**
     * Find All Anagrams in a String
     * Time Complexity: O(|s| + |p|)
     * Space Complexity: O(|p|)
     */
    static std::vector<int> findAnagrams(const std::string& s, const std::string& p);
    
    /**
     * Advanced Sliding Window Problems
     */
    
    /**
     * Sliding Window Maximum with Deque
     * Time Complexity: O(n)
     * Space Complexity: O(k)
     */
    static std::vector<int> maxSlidingWindowDeque(const std::vector<int>& nums, int k);
    
    /**
     * Sliding Window Median
     * Time Complexity: O(n log k)
     * Space Complexity: O(k)
     */
    static std::vector<double> medianSlidingWindow(const std::vector<int>& nums, int k);
    
    /**
     * Constrained Subsequence Sum
     * Time Complexity: O(n)
     * Space Complexity: O(k)
     */
    static int constrainedSubsetSum(const std::vector<int>& nums, int k);
    
    /**
     * Shortest Subarray with Sum at Least K
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static int shortestSubarray(const std::vector<int>& nums, int k);
    
    /**
     * Get Equal Substrings Within Budget
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int equalSubstring(const std::string& s, const std::string& t, int maxCost);
    
    /**
     * Max Consecutive Ones III
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int longestOnes(const std::vector<int>& nums, int k);
    
    /**
     * Binary Subarrays With Sum
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int numSubarraysWithSum(const std::vector<int>& nums, int goal);

private:
    // Helper functions
    static bool isAnagram(const std::unordered_map<char, int>& map1, 
                         const std::unordered_map<char, int>& map2);
    static int atMostK(const std::vector<int>& nums, int k);
    static double findMedian(std::vector<int>& window);
};

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_SLIDING_WINDOW_H