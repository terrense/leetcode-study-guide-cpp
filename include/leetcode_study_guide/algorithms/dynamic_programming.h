#ifndef LEETCODE_STUDY_GUIDE_DYNAMIC_PROGRAMMING_H
#define LEETCODE_STUDY_GUIDE_DYNAMIC_PROGRAMMING_H

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Dynamic Programming Algorithm Patterns
 * 
 * This module implements common dynamic programming patterns including
 * memoization (top-down) and tabulation (bottom-up) approaches for
 * optimization problems commonly found in LeetCode.
 */
class DynamicProgramming {
public:
    /**
     * 1D DP: Fibonacci sequence with memoization
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static long long fibonacciMemo(int n);
    static long long fibonacciTabulation(int n);
    
    /**
     * 1D DP: Climbing stairs problem
     * Time Complexity: O(n)
     * Space Complexity: O(1) for optimized version
     */
    static int climbStairs(int n);
    static int climbStairsOptimized(int n);
    
    /**
     * 1D DP: House robber problem
     * Time Complexity: O(n)
     * Space Complexity: O(1) for optimized version
     */
    static int rob(const std::vector<int>& nums);
    static int robOptimized(const std::vector<int>& nums);
    
    /**
     * 2D DP: Unique paths in grid
     * Time Complexity: O(m*n)
     * Space Complexity: O(m*n), O(n) for optimized version
     */
    static int uniquePaths(int m, int n);
    static int uniquePathsOptimized(int m, int n);
    
    /**
     * 2D DP: Longest Common Subsequence
     * Time Complexity: O(m*n)
     * Space Complexity: O(m*n), O(min(m,n)) for optimized version
     */
    static int longestCommonSubsequence(const std::string& text1, const std::string& text2);
    static int lcsOptimized(const std::string& text1, const std::string& text2);
    
    /**
     * 2D DP: Edit Distance (Levenshtein Distance)
     * Time Complexity: O(m*n)
     * Space Complexity: O(m*n), O(min(m,n)) for optimized version
     */
    static int editDistance(const std::string& word1, const std::string& word2);
    static int editDistanceOptimized(const std::string& word1, const std::string& word2);
    
    /**
     * Knapsack DP: 0/1 Knapsack problem
     * Time Complexity: O(n*W)
     * Space Complexity: O(n*W), O(W) for optimized version
     */
    static int knapsack01(const std::vector<int>& weights, const std::vector<int>& values, int capacity);
    static int knapsack01Optimized(const std::vector<int>& weights, const std::vector<int>& values, int capacity);
    
    /**
     * Interval DP: Matrix Chain Multiplication
     * Time Complexity: O(n^3)
     * Space Complexity: O(n^2)
     */
    static int matrixChainMultiplication(const std::vector<int>& dimensions);
    
    /**
     * Generic memoization helper
     */
    template<typename Key, typename Value>
    class Memoizer {
    private:
        std::unordered_map<Key, Value> cache;
        std::function<Value(const Key&)> func;
        
    public:
        Memoizer(std::function<Value(const Key&)> f) : func(f) {}
        
        Value operator()(const Key& key) {
            auto it = cache.find(key);
            if (it != cache.end()) {
                return it->second;
            }
            Value result = func(key);
            cache[key] = result;
            return result;
        }
        
        void clear() { cache.clear(); }
        size_t size() const { return cache.size(); }
    };

private:
    // Helper functions for memoization
    static std::unordered_map<int, long long> fibMemo;
    static long long fibonacciMemoHelper(int n);
};

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_DYNAMIC_PROGRAMMING_H