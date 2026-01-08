#ifndef LEETCODE_STUDY_GUIDE_BACKTRACKING_H
#define LEETCODE_STUDY_GUIDE_BACKTRACKING_H

#include <vector>
#include <string>
#include <unordered_set>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Backtracking Algorithm Patterns
 * 
 * This module implements common backtracking patterns for combinatorial
 * problems and constraint satisfaction problems commonly found in LeetCode.
 */
class Backtracking {
public:
    /**
     * Permutations - Generate all permutations of array
     * Time Complexity: O(n! * n)
     * Space Complexity: O(n)
     */
    static std::vector<std::vector<int>> permute(std::vector<int>& nums);
    static std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums);
    
    /**
     * Combinations - Generate all combinations of size k
     * Time Complexity: O(C(n,k) * k)
     * Space Complexity: O(k)
     */
    static std::vector<std::vector<int>> combine(int n, int k);
    static std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target);
    static std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target);
    
    /**
     * Subsets - Generate all possible subsets
     * Time Complexity: O(2^n * n)
     * Space Complexity: O(n)
     */
    static std::vector<std::vector<int>> subsets(std::vector<int>& nums);
    static std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums);
    
    /**
     * N-Queens Problem
     * Time Complexity: O(N!)
     * Space Complexity: O(N)
     */
    static std::vector<std::vector<std::string>> solveNQueens(int n);
    static int totalNQueens(int n);
    
    /**
     * Sudoku Solver
     * Time Complexity: O(9^(n*n)) where n is empty cells
     * Space Complexity: O(1)
     */
    static bool solveSudoku(std::vector<std::vector<char>>& board);
    
    /**
     * Word Search in Grid
     * Time Complexity: O(m*n*4^L) where L is word length
     * Space Complexity: O(L)
     */
    static bool exist(std::vector<std::vector<char>>& board, const std::string& word);
    static std::vector<std::string> findWords(std::vector<std::vector<char>>& board, 
                                             std::vector<std::string>& words);
    
    /**
     * Palindrome Partitioning
     * Time Complexity: O(2^n * n)
     * Space Complexity: O(n)
     */
    static std::vector<std::vector<std::string>> partition(const std::string& s);
    
    /**
     * Generate Parentheses
     * Time Complexity: O(4^n / sqrt(n))
     * Space Complexity: O(n)
     */
    static std::vector<std::string> generateParenthesis(int n);
    
    /**
     * Letter Combinations of Phone Number
     * Time Complexity: O(4^n)
     * Space Complexity: O(n)
     */
    static std::vector<std::string> letterCombinations(const std::string& digits);
    
    /**
     * Restore IP Addresses
     * Time Complexity: O(3^4)
     * Space Complexity: O(1)
     */
    static std::vector<std::string> restoreIpAddresses(const std::string& s);

private:
    // Helper functions for permutations
    static void permuteHelper(std::vector<int>& nums, std::vector<std::vector<int>>& result,
                             std::vector<int>& current, std::vector<bool>& used);
    static void permuteUniqueHelper(std::vector<int>& nums, std::vector<std::vector<int>>& result,
                                   std::vector<int>& current, std::vector<bool>& used);
    
    // Helper functions for combinations
    static void combineHelper(int n, int k, int start, std::vector<int>& current,
                             std::vector<std::vector<int>>& result);
    static void combinationSumHelper(std::vector<int>& candidates, int target, int start,
                                    std::vector<int>& current, std::vector<std::vector<int>>& result);
    static void combinationSum2Helper(std::vector<int>& candidates, int target, int start,
                                     std::vector<int>& current, std::vector<std::vector<int>>& result);
    
    // Helper functions for subsets
    static void subsetsHelper(std::vector<int>& nums, int start, std::vector<int>& current,
                             std::vector<std::vector<int>>& result);
    static void subsetsWithDupHelper(std::vector<int>& nums, int start, std::vector<int>& current,
                                    std::vector<std::vector<int>>& result);
    
    // Helper functions for N-Queens
    static void solveNQueensHelper(int n, int row, std::vector<int>& queens,
                                  std::vector<std::vector<std::string>>& result);
    static void totalNQueensHelper(int n, int row, std::vector<int>& queens, int& count);
    static bool isValidQueenPlacement(const std::vector<int>& queens, int row, int col);
    static std::vector<std::string> generateBoard(const std::vector<int>& queens, int n);
    
    // Helper functions for Sudoku
    static bool solveSudokuHelper(std::vector<std::vector<char>>& board);
    static bool isValidSudoku(const std::vector<std::vector<char>>& board, int row, int col, char num);
    
    // Helper functions for Word Search
    static bool existHelper(std::vector<std::vector<char>>& board, const std::string& word,
                           int row, int col, int index);
    
    // Trie structure for Word Search II
    struct TrieNode {
        TrieNode* children[26];
        std::string word;
        TrieNode() : word("") {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };
    
    static void buildTrie(TrieNode* root, const std::vector<std::string>& words);
    static void findWordsHelper(std::vector<std::vector<char>>& board, int row, int col,
                               TrieNode* node, std::unordered_set<std::string>& result);
    
    // Helper functions for Palindrome Partitioning
    static void partitionHelper(const std::string& s, int start, std::vector<std::string>& current,
                               std::vector<std::vector<std::string>>& result);
    static bool isPalindrome(const std::string& s, int start, int end);
    
    // Helper functions for Generate Parentheses
    static void generateParenthesisHelper(int n, int open, int close, std::string& current,
                                         std::vector<std::string>& result);
    
    // Helper functions for Letter Combinations
    static void letterCombinationsHelper(const std::string& digits, int index,
                                        const std::vector<std::string>& mapping,
                                        std::string& current, std::vector<std::string>& result);
    
    // Helper functions for Restore IP Addresses
    static void restoreIpHelper(const std::string& s, int start, int parts,
                               std::string& current, std::vector<std::string>& result);
    static bool isValidIpPart(const std::string& s, int start, int length);
};

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_BACKTRACKING_H