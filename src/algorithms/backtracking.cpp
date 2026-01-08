#include "leetcode_study_guide/algorithms/backtracking.h"
#include <algorithm>

namespace leetcode_study_guide {
namespace algorithms {

// ===== PERMUTATIONS =====

std::vector<std::vector<int>> Backtracking::permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    std::vector<bool> used(nums.size(), false);
    permuteHelper(nums, result, current, used);
    return result;
}

void Backtracking::permuteHelper(std::vector<int>& nums, std::vector<std::vector<int>>& result,
                                std::vector<int>& current, std::vector<bool>& used) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }
    
    for (size_t i = 0; i < nums.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(nums[i]);
            permuteHelper(nums, result, current, used);
            current.pop_back();
            used[i] = false;
        }
    }
}

std::vector<std::vector<int>> Backtracking::permuteUnique(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    std::vector<bool> used(nums.size(), false);
    permuteUniqueHelper(nums, result, current, used);
    return result;
}

void Backtracking::permuteUniqueHelper(std::vector<int>& nums, std::vector<std::vector<int>>& result,
                                      std::vector<int>& current, std::vector<bool>& used) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }
    
    for (size_t i = 0; i < nums.size(); i++) {
        if (used[i] || (i > 0 && nums[i] == nums[i-1] && !used[i-1])) {
            continue;
        }
        
        used[i] = true;
        current.push_back(nums[i]);
        permuteUniqueHelper(nums, result, current, used);
        current.pop_back();
        used[i] = false;
    }
}

// ===== COMBINATIONS =====

std::vector<std::vector<int>> Backtracking::combine(int n, int k) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    combineHelper(n, k, 1, current, result);
    return result;
}

void Backtracking::combineHelper(int n, int k, int start, std::vector<int>& current,
                                std::vector<std::vector<int>>& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }
    
    for (int i = start; i <= n; i++) {
        current.push_back(i);
        combineHelper(n, k, i + 1, current, result);
        current.pop_back();
    }
}

std::vector<std::vector<int>> Backtracking::combinationSum(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    std::sort(candidates.begin(), candidates.end());
    combinationSumHelper(candidates, target, 0, current, result);
    return result;
}

void Backtracking::combinationSumHelper(std::vector<int>& candidates, int target, int start,
                                       std::vector<int>& current, std::vector<std::vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    
    for (size_t i = start; i < candidates.size() && candidates[i] <= target; i++) {
        current.push_back(candidates[i]);
        combinationSumHelper(candidates, target - candidates[i], i, current, result);
        current.pop_back();
    }
}

std::vector<std::vector<int>> Backtracking::combinationSum2(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    std::sort(candidates.begin(), candidates.end());
    combinationSum2Helper(candidates, target, 0, current, result);
    return result;
}

void Backtracking::combinationSum2Helper(std::vector<int>& candidates, int target, int start,
                                        std::vector<int>& current, std::vector<std::vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    
    for (size_t i = start; i < candidates.size() && candidates[i] <= target; i++) {
        if (i > start && candidates[i] == candidates[i-1]) {
            continue; // Skip duplicates
        }
        
        current.push_back(candidates[i]);
        combinationSum2Helper(candidates, target - candidates[i], i + 1, current, result);
        current.pop_back();
    }
}

// ===== SUBSETS =====

std::vector<std::vector<int>> Backtracking::subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    subsetsHelper(nums, 0, current, result);
    return result;
}

void Backtracking::subsetsHelper(std::vector<int>& nums, int start, std::vector<int>& current,
                                std::vector<std::vector<int>>& result) {
    result.push_back(current);
    
    for (size_t i = start; i < nums.size(); i++) {
        current.push_back(nums[i]);
        subsetsHelper(nums, i + 1, current, result);
        current.pop_back();
    }
}

std::vector<std::vector<int>> Backtracking::subsetsWithDup(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    subsetsWithDupHelper(nums, 0, current, result);
    return result;
}

void Backtracking::subsetsWithDupHelper(std::vector<int>& nums, int start, std::vector<int>& current,
                                       std::vector<std::vector<int>>& result) {
    result.push_back(current);
    
    for (size_t i = start; i < nums.size(); i++) {
        if (i > start && nums[i] == nums[i-1]) {
            continue; // Skip duplicates
        }
        
        current.push_back(nums[i]);
        subsetsWithDupHelper(nums, i + 1, current, result);
        current.pop_back();
    }
}

// ===== N-QUEENS =====

std::vector<std::vector<std::string>> Backtracking::solveNQueens(int n) {
    std::vector<std::vector<std::string>> result;
    std::vector<int> queens(n, -1);
    solveNQueensHelper(n, 0, queens, result);
    return result;
}

void Backtracking::solveNQueensHelper(int n, int row, std::vector<int>& queens,
                                     std::vector<std::vector<std::string>>& result) {
    if (row == n) {
        result.push_back(generateBoard(queens, n));
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isValidQueenPlacement(queens, row, col)) {
            queens[row] = col;
            solveNQueensHelper(n, row + 1, queens, result);
            queens[row] = -1;
        }
    }
}

int Backtracking::totalNQueens(int n) {
    int count = 0;
    std::vector<int> queens(n, -1);
    totalNQueensHelper(n, 0, queens, count);
    return count;
}

void Backtracking::totalNQueensHelper(int n, int row, std::vector<int>& queens, int& count) {
    if (row == n) {
        count++;
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isValidQueenPlacement(queens, row, col)) {
            queens[row] = col;
            totalNQueensHelper(n, row + 1, queens, count);
            queens[row] = -1;
        }
    }
}

bool Backtracking::isValidQueenPlacement(const std::vector<int>& queens, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (queens[i] == col || 
            queens[i] - i == col - row || 
            queens[i] + i == col + row) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> Backtracking::generateBoard(const std::vector<int>& queens, int n) {
    std::vector<std::string> board(n, std::string(n, '.'));
    for (int i = 0; i < n; i++) {
        board[i][queens[i]] = 'Q';
    }
    return board;
}

// ===== SUDOKU SOLVER =====

bool Backtracking::solveSudoku(std::vector<std::vector<char>>& board) {
    return solveSudokuHelper(board);
}

bool Backtracking::solveSudokuHelper(std::vector<std::vector<char>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') {
                for (char num = '1'; num <= '9'; num++) {
                    if (isValidSudoku(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudokuHelper(board)) {
                            return true;
                        }
                        board[row][col] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool Backtracking::isValidSudoku(const std::vector<std::vector<char>>& board, int row, int col, char num) {
    // Check row
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == num) return false;
    }
    
    // Check column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) return false;
    }
    
    // Check 3x3 box
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int i = boxRow; i < boxRow + 3; i++) {
        for (int j = boxCol; j < boxCol + 3; j++) {
            if (board[i][j] == num) return false;
        }
    }
    
    return true;
}

// ===== WORD SEARCH =====

bool Backtracking::exist(std::vector<std::vector<char>>& board, const std::string& word) {
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[0].size(); j++) {
            if (existHelper(board, word, i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

bool Backtracking::existHelper(std::vector<std::vector<char>>& board, const std::string& word,
                               int row, int col, int index) {
    if (index == word.length()) return true;
    
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() ||
        board[row][col] != word[index]) {
        return false;
    }
    
    char temp = board[row][col];
    board[row][col] = '#'; // Mark as visited
    
    bool found = existHelper(board, word, row + 1, col, index + 1) ||
                 existHelper(board, word, row - 1, col, index + 1) ||
                 existHelper(board, word, row, col + 1, index + 1) ||
                 existHelper(board, word, row, col - 1, index + 1);
    
    board[row][col] = temp; // Restore
    return found;
}

// Word Search II with Trie
std::vector<std::string> Backtracking::findWords(std::vector<std::vector<char>>& board, 
                                                std::vector<std::string>& words) {
    TrieNode* root = new TrieNode();
    buildTrie(root, words);
    
    std::unordered_set<std::string> result;
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[0].size(); j++) {
            findWordsHelper(board, i, j, root, result);
        }
    }
    
    return std::vector<std::string>(result.begin(), result.end());
}

void Backtracking::buildTrie(TrieNode* root, const std::vector<std::string>& words) {
    for (const std::string& word : words) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->word = word;
    }
}

void Backtracking::findWordsHelper(std::vector<std::vector<char>>& board, int row, int col,
                                  TrieNode* node, std::unordered_set<std::string>& result) {
    if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() ||
        board[row][col] == '#') {
        return;
    }
    
    char ch = board[row][col];
    int index = ch - 'a';
    if (!node->children[index]) return;
    
    node = node->children[index];
    if (!node->word.empty()) {
        result.insert(node->word);
    }
    
    board[row][col] = '#'; // Mark as visited
    
    findWordsHelper(board, row + 1, col, node, result);
    findWordsHelper(board, row - 1, col, node, result);
    findWordsHelper(board, row, col + 1, node, result);
    findWordsHelper(board, row, col - 1, node, result);
    
    board[row][col] = ch; // Restore
}

// ===== PALINDROME PARTITIONING =====

std::vector<std::vector<std::string>> Backtracking::partition(const std::string& s) {
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> current;
    partitionHelper(s, 0, current, result);
    return result;
}

void Backtracking::partitionHelper(const std::string& s, int start, std::vector<std::string>& current,
                                  std::vector<std::vector<std::string>>& result) {
    if (start == s.length()) {
        result.push_back(current);
        return;
    }
    
    for (size_t end = start; end < s.length(); end++) {
        if (isPalindrome(s, start, end)) {
            current.push_back(s.substr(start, end - start + 1));
            partitionHelper(s, end + 1, current, result);
            current.pop_back();
        }
    }
}

bool Backtracking::isPalindrome(const std::string& s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return false;
        start++;
        end--;
    }
    return true;
}

// ===== GENERATE PARENTHESES =====

std::vector<std::string> Backtracking::generateParenthesis(int n) {
    std::vector<std::string> result;
    std::string current;
    generateParenthesisHelper(n, 0, 0, current, result);
    return result;
}

void Backtracking::generateParenthesisHelper(int n, int open, int close, std::string& current,
                                            std::vector<std::string>& result) {
    if (current.length() == 2 * n) {
        result.push_back(current);
        return;
    }
    
    if (open < n) {
        current.push_back('(');
        generateParenthesisHelper(n, open + 1, close, current, result);
        current.pop_back();
    }
    
    if (close < open) {
        current.push_back(')');
        generateParenthesisHelper(n, open, close + 1, current, result);
        current.pop_back();
    }
}

// ===== LETTER COMBINATIONS =====

std::vector<std::string> Backtracking::letterCombinations(const std::string& digits) {
    if (digits.empty()) return {};
    
    std::vector<std::string> mapping = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };
    
    std::vector<std::string> result;
    std::string current;
    letterCombinationsHelper(digits, 0, mapping, current, result);
    return result;
}

void Backtracking::letterCombinationsHelper(const std::string& digits, int index,
                                           const std::vector<std::string>& mapping,
                                           std::string& current, std::vector<std::string>& result) {
    if (index == digits.length()) {
        result.push_back(current);
        return;
    }
    
    int digit = digits[index] - '0';
    const std::string& letters = mapping[digit];
    
    for (char letter : letters) {
        current.push_back(letter);
        letterCombinationsHelper(digits, index + 1, mapping, current, result);
        current.pop_back();
    }
}

// ===== RESTORE IP ADDRESSES =====

std::vector<std::string> Backtracking::restoreIpAddresses(const std::string& s) {
    std::vector<std::string> result;
    std::string current;
    restoreIpHelper(s, 0, 0, current, result);
    return result;
}

void Backtracking::restoreIpHelper(const std::string& s, int start, int parts,
                                  std::string& current, std::vector<std::string>& result) {
    if (parts == 4) {
        if (start == s.length()) {
            result.push_back(current.substr(0, current.length() - 1)); // Remove last dot
        }
        return;
    }
    
    for (int len = 1; len <= 3 && start + len <= s.length(); len++) {
        if (isValidIpPart(s, start, len)) {
            std::string part = s.substr(start, len);
            int originalSize = current.size();
            current += part + ".";
            restoreIpHelper(s, start + len, parts + 1, current, result);
            current.resize(originalSize);
        }
    }
}

bool Backtracking::isValidIpPart(const std::string& s, int start, int length) {
    if (length == 0 || length > 3) return false;
    if (length > 1 && s[start] == '0') return false; // No leading zeros
    
    int num = 0;
    for (int i = start; i < start + length; i++) {
        if (!isdigit(s[i])) return false;
        num = num * 10 + (s[i] - '0');
    }
    
    return num <= 255;
}

} // namespace algorithms
} // namespace leetcode_study_guide