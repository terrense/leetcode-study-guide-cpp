#ifndef LEETCODE_STUDY_GUIDE_TWO_POINTERS_H
#define LEETCODE_STUDY_GUIDE_TWO_POINTERS_H

#include <vector>
#include <string>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Two Pointers Technique Patterns
 * 
 * This module implements various two pointers patterns commonly used
 * in LeetCode problems for array, string, and linked list problems.
 */
class TwoPointers {
public:
    /**
     * Opposite Direction Two Pointers
     * Pointers start from both ends and move towards each other
     */
    
    /**
     * Two Sum II - Input array is sorted
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static std::vector<int> twoSum(const std::vector<int>& numbers, int target);
    
    /**
     * Valid Palindrome
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static bool isPalindrome(const std::string& s);
    
    /**
     * Reverse String
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static void reverseString(std::vector<char>& s);
    
    /**
     * Container With Most Water
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int maxArea(const std::vector<int>& height);
    
    /**
     * 3Sum - Find all unique triplets that sum to zero
     * Time Complexity: O(n^2)
     * Space Complexity: O(1) excluding output
     */
    static std::vector<std::vector<int>> threeSum(std::vector<int>& nums);
    
    /**
     * 3Sum Closest
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    static int threeSumClosest(std::vector<int>& nums, int target);
    
    /**
     * 4Sum - Find all unique quadruplets that sum to target
     * Time Complexity: O(n^3)
     * Space Complexity: O(1) excluding output
     */
    static std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target);
    
    /**
     * Same Direction Two Pointers (Fast and Slow)
     * Both pointers start from same position and move in same direction
     */
    
    /**
     * Remove Duplicates from Sorted Array
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int removeDuplicates(std::vector<int>& nums);
    
    /**
     * Remove Element
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int removeElement(std::vector<int>& nums, int val);
    
    /**
     * Move Zeroes
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static void moveZeroes(std::vector<int>& nums);
    
    /**
     * Sort Colors (Dutch National Flag)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static void sortColors(std::vector<int>& nums);
    
    /**
     * Linked List Cycle Detection (Floyd's Algorithm)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };
    
    static bool hasCycle(ListNode* head);
    static ListNode* detectCycle(ListNode* head);
    
    /**
     * Find Middle of Linked List
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static ListNode* findMiddle(ListNode* head);
    
    /**
     * Remove Nth Node From End
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static ListNode* removeNthFromEnd(ListNode* head, int n);
    
    /**
     * Intersection of Two Linked Lists
     * Time Complexity: O(m + n)
     * Space Complexity: O(1)
     */
    static ListNode* getIntersectionNode(ListNode* headA, ListNode* headB);
    
    /**
     * String Two Pointers Problems
     */
    
    /**
     * Longest Palindromic Substring (Expand Around Centers)
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    static std::string longestPalindrome(const std::string& s);
    
    /**
     * Valid Palindrome II (At most one deletion)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static bool validPalindrome(const std::string& s);
    
    /**
     * Reverse Words in a String III
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static std::string reverseWords(std::string s);
    
    /**
     * Partition Labels
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static std::vector<int> partitionLabels(const std::string& s);
    
    /**
     * Advanced Two Pointers Problems
     */
    
    /**
     * Trapping Rain Water
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int trap(const std::vector<int>& height);
    
    /**
     * Minimum Window Substring
     * Time Complexity: O(m + n)
     * Space Complexity: O(m + n)
     */
    static std::string minWindow(const std::string& s, const std::string& t);
    
    /**
     * Substring with Concatenation of All Words
     * Time Complexity: O(n * m * k) where n is s length, m is words count, k is word length
     * Space Complexity: O(m * k)
     */
    static std::vector<int> findSubstring(const std::string& s, const std::vector<std::string>& words);

private:
    // Helper functions
    static bool isAlphanumeric(char c);
    static char toLowerCase(char c);
    static int expandAroundCenter(const std::string& s, int left, int right);
    static bool isPalindromeRange(const std::string& s, int left, int right);
    static void reverseRange(std::string& s, int start, int end);
};

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_TWO_POINTERS_H