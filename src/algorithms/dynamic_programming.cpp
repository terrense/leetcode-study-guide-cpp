#include "leetcode_study_guide/algorithms/dynamic_programming.h"
#include <algorithm>
#include <climits>

namespace leetcode_study_guide {
namespace algorithms {

// Static member initialization
std::unordered_map<int, long long> DynamicProgramming::fibMemo;

// Fibonacci with memoization (top-down)
long long DynamicProgramming::fibonacciMemo(int n) {
    fibMemo.clear();
    return fibonacciMemoHelper(n);
}

long long DynamicProgramming::fibonacciMemoHelper(int n) {
    if (n <= 1) return n;
    
    auto it = fibMemo.find(n);
    if (it != fibMemo.end()) {
        return it->second;
    }
    
    long long result = fibonacciMemoHelper(n - 1) + fibonacciMemoHelper(n - 2);
    fibMemo[n] = result;
    return result;
}

// Fibonacci with tabulation (bottom-up)
long long DynamicProgramming::fibonacciTabulation(int n) {
    if (n <= 1) return n;
    
    std::vector<long long> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// Climbing stairs
int DynamicProgramming::climbStairs(int n) {
    if (n <= 2) return n;
    
    std::vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// Climbing stairs optimized (O(1) space)
int DynamicProgramming::climbStairsOptimized(int n) {
    if (n <= 2) return n;
    
    int prev2 = 1, prev1 = 2;
    
    for (int i = 3; i <= n; i++) {
        int current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
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