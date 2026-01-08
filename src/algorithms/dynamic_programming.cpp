#include "leetcode_study_guide/algorithms/dynamic_programming.h"
#include <algorithm>
#include <climits>

namespace leetcode_study_guide {
namespace algorithms {

// Static member initialization for memoization
std::unordered_map<int, long long> DynamicProgramming::fibMemo;

/**
 * FIBONACCI SEQUENCE IMPLEMENTATIONS
 * 
 * The Fibonacci sequence is a classic example to demonstrate different DP approaches:
 * F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2) for n > 1
 * 
 * This problem has optimal substructure and overlapping subproblems,
 * making it perfect for dynamic programming optimization.
 */

/**
 * Fibonacci with Memoization (Top-Down Dynamic Programming)
 * 
 * Approach: Start from the target and recursively break down into subproblems.
 * Use a hash map to store computed results to avoid redundant calculations.
 * 
 * Time Complexity: O(n) - each subproblem computed only once
 * Space Complexity: O(n) - memoization table + recursion stack
 * 
 * When to use: When you naturally think recursively about the problem
 */
long long DynamicProgramming::fibonacciMemo(int n) {
    // Clear any previous memoization data for fresh calculation
    fibMemo.clear();
    // Start the memoized recursive calculation
    return fibonacciMemoHelper(n);
}

/**
 * Recursive helper function with memoization
 * This function implements the core memoization logic
 */
long long DynamicProgramming::fibonacciMemoHelper(int n) {
    // Base cases: F(0) = 0, F(1) = 1
    if (n <= 1) return n;
    
    // Check if we've already computed this value (memoization lookup)
    auto it = fibMemo.find(n);
    if (it != fibMemo.end()) {
        return it->second;  // Return cached result
    }
    
    // Compute the result recursively
    // F(n) = F(n-1) + F(n-2)
    long long result = fibonacciMemoHelper(n - 1) + fibonacciMemoHelper(n - 2);
    
    // Store the result in memoization table for future use
    fibMemo[n] = result;
    
    return result;
}

/**
 * Fibonacci with Tabulation (Bottom-Up Dynamic Programming)
 * 
 * Approach: Start from base cases and build up to the target iteratively.
 * Use an array to store intermediate results in a systematic order.
 * 
 * Time Complexity: O(n) - single loop from 2 to n
 * Space Complexity: O(n) - DP table of size n+1
 * 
 * When to use: When you can easily identify the order of subproblem computation
 * Advantages: No recursion overhead, easier to optimize space
 */
long long DynamicProgramming::fibonacciTabulation(int n) {
    // Handle base cases
    if (n <= 1) return n;
    
    // Create DP table to store intermediate results
    // dp[i] represents F(i)
    std::vector<long long> dp(n + 1);
    
    // Initialize base cases
    dp[0] = 0;  // F(0) = 0
    dp[1] = 1;  // F(1) = 1
    
    // Fill the DP table bottom-up
    // For each position i, compute F(i) using previously computed values
    for (int i = 2; i <= n; i++) {
        // F(i) = F(i-1) + F(i-2)
        // We can safely use dp[i-1] and dp[i-2] because they're already computed
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    // Return the final result
    return dp[n];
}

/**
 * CLIMBING STAIRS PROBLEM
 * 
 * Problem: You're climbing a staircase with n steps. You can climb either 1 or 2 steps at a time.
 * How many distinct ways can you climb to the top?
 * 
 * Analysis: This is essentially Fibonacci in disguise!
 * - To reach step n, you can come from step (n-1) with 1 step, or step (n-2) with 2 steps
 * - ways(n) = ways(n-1) + ways(n-2)
 * - Base cases: ways(1) = 1, ways(2) = 2
 */

/**
 * Climbing Stairs - Standard DP Approach
 * Uses tabulation to build up the solution from base cases.
 * 
 * Time Complexity: O(n) - single pass through all steps
 * Space Complexity: O(n) - DP array of size n+1
 */
int DynamicProgramming::climbStairs(int n) {
    // Handle base cases
    if (n <= 2) return n;
    
    // Create DP table where dp[i] = number of ways to reach step i
    std::vector<int> dp(n + 1);
    
    // Base cases
    dp[1] = 1;  // Only one way to reach step 1: take 1 step
    dp[2] = 2;  // Two ways to reach step 2: (1+1) or (2)
    
    // Fill DP table for steps 3 to n
    for (int i = 3; i <= n; i++) {
        // To reach step i, we can:
        // 1. Come from step (i-1) and take 1 step
        // 2. Come from step (i-2) and take 2 steps
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

/**
 * Climbing Stairs - Space Optimized Version
 * 
 * Key Insight: We only need the previous two values to compute the current value.
 * Instead of storing all intermediate results, we can use just two variables.
 * 
 * Time Complexity: O(n) - same as before
 * Space Complexity: O(1) - only using constant extra space
 * 
 * This is a common optimization technique in DP when the recurrence relation
 * only depends on a fixed number of previous states.
 */
int DynamicProgramming::climbStairsOptimized(int n) {
    // Handle base cases
    if (n <= 2) return n;
    
    // Only keep track of the last two values
    int prev2 = 1;  // ways to reach step 1
    int prev1 = 2;  // ways to reach step 2
    
    // Compute for steps 3 to n
    for (int i = 3; i <= n; i++) {
        // Current ways = ways from (i-1) + ways from (i-2)
        int current = prev1 + prev2;
        
        // Slide the window: update prev2 and prev1 for next iteration
        prev2 = prev1;      // What was prev1 becomes prev2
        prev1 = current;    // Current result becomes prev1
    }
    
    return prev1;  // prev1 now contains ways to reach step n
}

// House robber
int DynamicProgramming::rob(const std::vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];
    
    std::vector<int> dp(nums.size());
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);
    
    for (size_t i = 2; i < nums.size(); i++) {
        dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
    }
    
    return dp[nums.size() - 1];
}

// House robber optimized (O(1) space)
int DynamicProgramming::robOptimized(const std::vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];
    
    int prev2 = nums[0];
    int prev1 = std::max(nums[0], nums[1]);
    
    for (size_t i = 2; i < nums.size(); i++) {
        int current = std::max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

// Unique paths
int DynamicProgramming::uniquePaths(int m, int n) {
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));
    
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    
    return dp[m - 1][n - 1];
}

// Unique paths optimized (O(n) space)
int DynamicProgramming::uniquePathsOptimized(int m, int n) {
    std::vector<int> dp(n, 1);
    
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[j] += dp[j - 1];
        }
    }
    
    return dp[n - 1];
}

// Longest Common Subsequence
int DynamicProgramming::longestCommonSubsequence(const std::string& text1, const std::string& text2) {
    int m = text1.length(), n = text2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
}

// LCS optimized (O(min(m,n)) space)
int DynamicProgramming::lcsOptimized(const std::string& text1, const std::string& text2) {
    if (text1.length() < text2.length()) {
        return lcsOptimized(text2, text1);
    }
    
    int m = text1.length(), n = text2.length();
    std::vector<int> prev(n + 1, 0), curr(n + 1, 0);
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = std::max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }
    
    return curr[n];
}

// Edit Distance
int DynamicProgramming::editDistance(const std::string& word1, const std::string& word2) {
    int m = word1.length(), n = word2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    
    // Initialize base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j],     // delete
                                        dp[i][j - 1],     // insert
                                        dp[i - 1][j - 1]}); // replace
            }
        }
    }
    
    return dp[m][n];
}

// Edit Distance optimized (O(min(m,n)) space)
int DynamicProgramming::editDistanceOptimized(const std::string& word1, const std::string& word2) {
    if (word1.length() < word2.length()) {
        return editDistanceOptimized(word2, word1);
    }
    
    int m = word1.length(), n = word2.length();
    std::vector<int> prev(n + 1), curr(n + 1);
    
    // Initialize base case
    for (int j = 0; j <= n; j++) prev[j] = j;
    
    for (int i = 1; i <= m; i++) {
        curr[0] = i;
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                curr[j] = prev[j - 1];
            } else {
                curr[j] = 1 + std::min({prev[j], curr[j - 1], prev[j - 1]});
            }
        }
        prev = curr;
    }
    
    return curr[n];
}

// 0/1 Knapsack
int DynamicProgramming::knapsack01(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    int n = weights.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i - 1][w], 
                                   dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

// 0/1 Knapsack optimized (O(W) space)
int DynamicProgramming::knapsack01Optimized(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    std::vector<int> dp(capacity + 1, 0);
    
    for (size_t i = 0; i < weights.size(); i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    
    return dp[capacity];
}

// Matrix Chain Multiplication
int DynamicProgramming::matrixChainMultiplication(const std::vector<int>& dimensions) {
    int n = dimensions.size() - 1; // Number of matrices
    if (n < 2) return 0;
    
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    
    // l is chain length
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + 
                          dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                dp[i][j] = std::min(dp[i][j], cost);
            }
        }
    }
    
    return dp[0][n - 1];
}

} // namespace algorithms
} // namespace leetcode_study_guide