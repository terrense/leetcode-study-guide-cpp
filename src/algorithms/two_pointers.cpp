#include "leetcode_study_guide/algorithms/two_pointers.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>

namespace leetcode_study_guide {
namespace algorithms {

// ===== OPPOSITE DIRECTION TWO POINTERS =====

std::vector<int> TwoPointers::twoSum(const std::vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            return {left + 1, right + 1}; // 1-indexed
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {}; // No solution found
}

bool TwoPointers::isPalindrome(const std::string& s) {
    int left = 0, right = s.length() - 1;
    
    while (left < right) {
        while (left < right && !isAlphanumeric(s[left])) {
            left++;
        }
        while (left < right && !isAlphanumeric(s[right])) {
            right--;
        }
        
        if (toLowerCase(s[left]) != toLowerCase(s[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

void TwoPointers::reverseString(std::vector<char>& s) {
    int left = 0, right = s.size() - 1;
    
    while (left < right) {
        std::swap(s[left], s[right]);
        left++;
        right--;
    }
}

int TwoPointers::maxArea(const std::vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        int width = right - left;
        int currentWater = width * std::min(height[left], height[right]);
        maxWater = std::max(maxWater, currentWater);
        
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return maxWater;
}

std::vector<std::vector<int>> TwoPointers::threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::sort(nums.begin(), nums.end());
    
    for (size_t i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue; // Skip duplicates
        }
        
        int left = i + 1, right = nums.size() - 1;
        int target = -nums[i];
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                result.push_back({nums[i], nums[left], nums[right]});
                
                // Skip duplicates
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}

int TwoPointers::threeSumClosest(std::vector<int>& nums, int target) {
    std::sort(nums.begin(), nums.end());
    int closestSum = nums[0] + nums[1] + nums[2];
    
    for (size_t i = 0; i < nums.size() - 2; i++) {
        int left = i + 1, right = nums.size() - 1;
        
        while (left < right) {
            int currentSum = nums[i] + nums[left] + nums[right];
            
            if (std::abs(currentSum - target) < std::abs(closestSum - target)) {
                closestSum = currentSum;
            }
            
            if (currentSum < target) {
                left++;
            } else if (currentSum > target) {
                right--;
            } else {
                return currentSum; // Exact match
            }
        }
    }
    
    return closestSum;
}

std::vector<std::vector<int>> TwoPointers::fourSum(std::vector<int>& nums, int target) {
    std::vector<std::vector<int>> result;
    std::sort(nums.begin(), nums.end());
    
    for (size_t i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        for (size_t j = i + 1; j < nums.size(); j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            
            int left = j + 1, right = nums.size() - 1;
            long long twoSumTarget = (long long)target - nums[i] - nums[j];
            
            while (left < right) {
                long long sum = nums[left] + nums[right];
                if (sum == twoSumTarget) {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    
                    left++;
                    right--;
                } else if (sum < twoSumTarget) {
                    left++;
                } else {
                    right--;
                }
            }
        }
    }
    
    return result;
}

// ===== SAME DIRECTION TWO POINTERS =====

int TwoPointers::removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int slow = 0;
    for (size_t fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    
    return slow + 1;
}

int TwoPointers::removeElement(std::vector<int>& nums, int val) {
    int slow = 0;
    for (size_t fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    
    return slow;
}

void TwoPointers::moveZeroes(std::vector<int>& nums) {
    int slow = 0;
    
    // Move all non-zero elements to the front
    for (size_t fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    
    // Fill remaining positions with zeros
    while (slow < nums.size()) {
        nums[slow] = 0;
        slow++;
    }
}

void TwoPointers::sortColors(std::vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    
    while (mid <= high) {
        if (nums[mid] == 0) {
            std::swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else { // nums[mid] == 2
            std::swap(nums[mid], nums[high]);
            high--;
            // Don't increment mid as we need to check the swapped element
        }
    }
}

// ===== LINKED LIST TWO POINTERS =====

bool TwoPointers::hasCycle(ListNode* head) {
    if (!head || !head->next) return false;
    
    ListNode* slow = head;
    ListNode* fast = head->next;
    
    while (fast && fast->next) {
        if (slow == fast) return true;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return false;
}

TwoPointers::ListNode* TwoPointers::detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // Detect if cycle exists
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    if (!fast || !fast->next) return nullptr; // No cycle
    
    // Find the start of the cycle
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}

TwoPointers::ListNode* TwoPointers::findMiddle(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

TwoPointers::ListNode* TwoPointers::removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    
    ListNode* slow = dummy;
    ListNode* fast = dummy;
    
    // Move fast n+1 steps ahead
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }
    
    // Move both pointers until fast reaches end
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    // Remove the nth node from end
    ListNode* nodeToDelete = slow->next;
    slow->next = slow->next->next;
    delete nodeToDelete;
    
    ListNode* result = dummy->next;
    delete dummy;
    return result;
}

TwoPointers::ListNode* TwoPointers::getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    ListNode* ptrA = headA;
    ListNode* ptrB = headB;
    
    while (ptrA != ptrB) {
        ptrA = ptrA ? ptrA->next : headB;
        ptrB = ptrB ? ptrB->next : headA;
    }
    
    return ptrA;
}

// ===== STRING TWO POINTERS =====

std::string TwoPointers::longestPalindrome(const std::string& s) {
    if (s.empty()) return "";
    
    int start = 0, maxLen = 1;
    
    for (size_t i = 0; i < s.length(); i++) {
        // Check for odd length palindromes
        int len1 = expandAroundCenter(s, i, i);
        // Check for even length palindromes
        int len2 = expandAroundCenter(s, i, i + 1);
        
        int len = std::max(len1, len2);
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;
        }
    }
    
    return s.substr(start, maxLen);
}

bool TwoPointers::validPalindrome(const std::string& s) {
    int left = 0, right = s.length() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            // Try skipping left character or right character
            return isPalindromeRange(s, left + 1, right) || 
                   isPalindromeRange(s, left, right - 1);
        }
        left++;
        right--;
    }
    
    return true;
}

std::string TwoPointers::reverseWords(std::string s) {
    int start = 0;
    
    for (size_t i = 0; i <= s.length(); i++) {
        if (i == s.length() || s[i] == ' ') {
            reverseRange(s, start, i - 1);
            start = i + 1;
        }
    }
    
    return s;
}

std::vector<int> TwoPointers::partitionLabels(const std::string& s) {
    std::vector<int> lastIndex(26, -1);
    
    // Record the last index of each character
    for (size_t i = 0; i < s.length(); i++) {
        lastIndex[s[i] - 'a'] = i;
    }
    
    std::vector<int> result;
    int start = 0, end = 0;
    
    for (size_t i = 0; i < s.length(); i++) {
        end = std::max(end, lastIndex[s[i] - 'a']);
        
        if (i == end) {
            result.push_back(end - start + 1);
            start = i + 1;
        }
    }
    
    return result;
}

// ===== ADVANCED TWO POINTERS =====

int TwoPointers::trap(const std::vector<int>& height) {
    if (height.empty()) return 0;
    
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;
    
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }
    
    return water;
}

std::string TwoPointers::minWindow(const std::string& s, const std::string& t) {
    if (s.empty() || t.empty()) return "";
    
    std::unordered_map<char, int> tCount, windowCount;
    for (char c : t) {
        tCount[c]++;
    }
    
    int left = 0, right = 0;
    int minLen = INT_MAX, minStart = 0;
    int formed = 0;
    int required = tCount.size();
    
    while (right < s.length()) {
        char c = s[right];
        windowCount[c]++;
        
        if (tCount.count(c) && windowCount[c] == tCount[c]) {
            formed++;
        }
        
        while (left <= right && formed == required) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            
            char leftChar = s[left];
            windowCount[leftChar]--;
            if (tCount.count(leftChar) && windowCount[leftChar] < tCount[leftChar]) {
                formed--;
            }
            left++;
        }
        
        right++;
    }
    
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

std::vector<int> TwoPointers::findSubstring(const std::string& s, const std::vector<std::string>& words) {
    std::vector<int> result;
    if (s.empty() || words.empty()) return result;
    
    int wordLen = words[0].length();
    int totalLen = wordLen * words.size();
    
    if (s.length() < totalLen) return result;
    
    std::unordered_map<std::string, int> wordCount;
    for (const std::string& word : words) {
        wordCount[word]++;
    }
    
    for (int i = 0; i <= (int)s.length() - totalLen; i++) {
        std::unordered_map<std::string, int> seen;
        int j = 0;
        
        while (j < words.size()) {
            std::string word = s.substr(i + j * wordLen, wordLen);
            if (wordCount.find(word) == wordCount.end()) {
                break;
            }
            
            seen[word]++;
            if (seen[word] > wordCount[word]) {
                break;
            }
            
            j++;
        }
        
        if (j == words.size()) {
            result.push_back(i);
        }
    }
    
    return result;
}

// ===== HELPER FUNCTIONS =====

bool TwoPointers::isAlphanumeric(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

char TwoPointers::toLowerCase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

int TwoPointers::expandAroundCenter(const std::string& s, int left, int right) {
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

bool TwoPointers::isPalindromeRange(const std::string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

void TwoPointers::reverseRange(std::string& s, int start, int end) {
    while (start < end) {
        std::swap(s[start], s[end]);
        start++;
        end--;
    }
}

} // namespace algorithms
} // namespace leetcode_study_guide