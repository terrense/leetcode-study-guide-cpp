#include "leetcode_study_guide/algorithms/sliding_window.h"
#include <algorithm>
#include <deque>
#include <climits>
#include <set>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * SLIDING WINDOW TECHNIQUE - FIXED SIZE WINDOW
 * 
 * Fixed size sliding window maintains a constant window size throughout the process.
 * The window "slides" by removing the leftmost element and adding a new rightmost element.
 * 
 * Common Pattern:
 * 1. Calculate result for first window of size k
 * 2. Slide window: remove left element, add right element
 * 3. Update result based on new window
 * 4. Repeat until end of array
 * 
 * Time Complexity: Usually O(n) - each element added and removed exactly once
 * Space Complexity: Usually O(1) or O(k) depending on what we store
 */

/**
 * Maximum Sum Subarray of Size K
 * 
 * Problem: Find the maximum sum of any contiguous subarray of size k.
 * 
 * Algorithm Logic:
 * 1. Calculate sum of first k elements (initial window)
 * 2. Slide window: subtract leftmost, add rightmost
 * 3. Keep track of maximum sum seen
 * 
 * Key Insight: Instead of recalculating sum for each window (O(k) per window),
 * we maintain running sum by adding/removing one element (O(1) per window).
 * 
 * Time Complexity: O(n) - single pass through array
 * Space Complexity: O(1) - only storing sum and max values
 */
int SlidingWindow::maxSumSubarray(const std::vector<int>& nums, int k) {
    // Handle edge case: array smaller than window size
    if (nums.size() < k) return 0;
    
    // Step 1: Calculate sum of first window
    int windowSum = 0;
    for (int i = 0; i < k; i++) {
        windowSum += nums[i];
    }
    
    // Initialize max sum with first window's sum
    int maxSum = windowSum;
    
    // Step 2: Slide the window through rest of array
    for (size_t i = k; i < nums.size(); i++) {
        // Slide window: remove leftmost element, add rightmost element
        // This maintains window size k while moving it one position right
        windowSum = windowSum - nums[i - k] + nums[i];
        //          ^remove left  ^add right
        
        // Update maximum sum if current window is better
        maxSum = std::max(maxSum, windowSum);
    }
    
    return maxSum;
}

std::vector<double> SlidingWindow::findAverages(const std::vector<int>& nums, int k) {
    std::vector<double> result;
    if (nums.size() < k) return result;
    
    int windowSum = 0;
    // Calculate sum of first window
    for (int i = 0; i < k; i++) {
        windowSum += nums[i];
    }
    
    result.push_back((double)windowSum / k);
    
    // Slide the window
    for (size_t i = k; i < nums.size(); i++) {
        windowSum = windowSum - nums[i - k] + nums[i];
        result.push_back((double)windowSum / k);
    }
    
    return result;
}

std::vector<int> SlidingWindow::maxSlidingWindow(const std::vector<int>& nums, int k) {
    return maxSlidingWindowDeque(nums, k);
}

/**
 * SLIDING WINDOW TECHNIQUE - VARIABLE SIZE WINDOW
 * 
 * Variable size sliding window adjusts its size based on certain conditions.
 * The window can expand (move right pointer) or contract (move left pointer).
 * 
 * Common Pattern:
 * 1. Expand window by moving right pointer
 * 2. Check if current window satisfies condition
 * 3. If not, contract window by moving left pointer
 * 4. Update result based on current valid window
 * 5. Repeat until right pointer reaches end
 * 
 * Time Complexity: Usually O(n) - each element added and removed at most once
 * Space Complexity: Depends on what we track (often O(k) for character/element counts)
 */

/**
 * Longest Substring Without Repeating Characters
 * 
 * Problem: Find the length of the longest substring without repeating characters.
 * 
 * Algorithm Logic:
 * 1. Use a set to track characters in current window
 * 2. Expand window by adding characters to set
 * 3. If duplicate found, contract window from left until duplicate removed
 * 4. Track maximum window size seen
 * 
 * Key Insight: Use set for O(1) duplicate detection and removal
 * 
 * Time Complexity: O(n) - each character added and removed at most once
 * Space Complexity: O(min(m,n)) - set size limited by charset size or string length
 */
int SlidingWindow::lengthOfLongestSubstring(const std::string& s) {
    // Use set to track characters in current window
    std::unordered_set<char> window;
    int left = 0, maxLen = 0;
    
    // Expand window with right pointer
    for (int right = 0; right < s.length(); right++) {
        // Contract window while we have duplicate character
        // This ensures window always has unique characters
        while (window.count(s[right])) {
            // Remove leftmost character and move left pointer
            window.erase(s[left]);
            left++;
        }
        
        // Add current character to window
        window.insert(s[right]);
        
        // Update maximum length with current window size
        maxLen = std::max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

int SlidingWindow::lengthOfLongestSubstringKDistinct(const std::string& s, int k) {
    if (k == 0) return 0;
    
    std::unordered_map<char, int> window;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        window[s[right]]++;
        
        while (window.size() > k) {
            window[s[left]]--;
            if (window[s[left]] == 0) {
                window.erase(s[left]);
            }
            left++;
        }
        
        maxLen = std::max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

int SlidingWindow::lengthOfLongestSubstringTwoDistinct(const std::string& s) {
    return lengthOfLongestSubstringKDistinct(s, 2);
}

/**
 * Minimum Window Substring
 * 
 * Problem: Find the minimum window in string s that contains all characters of string t.
 * 
 * Algorithm Logic:
 * 1. Count characters needed from string t
 * 2. Expand window until all characters of t are included
 * 3. Contract window while maintaining all characters of t
 * 4. Track minimum window that satisfies condition
 * 
 * Key Techniques:
 * - Two hash maps: one for target counts, one for window counts
 * - "formed" counter: tracks how many unique characters have required count
 * - Expand-contract pattern: expand to find valid window, contract to minimize
 * 
 * Time Complexity: O(|s| + |t|) - each character in s added and removed at most once
 * Space Complexity: O(|s| + |t|) - hash maps for character counts
 */
std::string SlidingWindow::minWindow(const std::string& s, const std::string& t) {
    if (s.empty() || t.empty()) return "";
    
    // Count characters needed from string t
    std::unordered_map<char, int> tCount, windowCount;
    for (char c : t) {
        tCount[c]++;
    }
    
    // Window pointers and result tracking
    int left = 0, right = 0;
    int minLen = INT_MAX, minStart = 0;
    
    // Track how many unique characters in window have desired frequency
    int formed = 0;                    // Current count of satisfied characters
    int required = tCount.size();      // Total unique characters needed
    
    // Expand window with right pointer
    while (right < s.length()) {
        // Add character from right to window
        char c = s[right];
        windowCount[c]++;
        
        // Check if frequency of current character matches desired count in t
        if (tCount.count(c) && windowCount[c] == tCount[c]) {
            formed++;  // One more character requirement satisfied
        }
        
        // Contract window while it's valid (contains all characters of t)
        while (left <= right && formed == required) {
            // Update minimum window if current is smaller
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            
            // Remove character from left of window
            char leftChar = s[left];
            windowCount[leftChar]--;
            
            // Check if removing this character breaks a requirement
            if (tCount.count(leftChar) && windowCount[leftChar] < tCount[leftChar]) {
                formed--;  // One character requirement no longer satisfied
            }
            
            left++;  // Contract window
        }
        
        right++;  // Expand window
    }
    
    // Return minimum window or empty string if no valid window found
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

int SlidingWindow::characterReplacement(const std::string& s, int k) {
    std::unordered_map<char, int> count;
    int left = 0, maxCount = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        count[s[right]]++;
        maxCount = std::max(maxCount, count[s[right]]);
        
        // If window size - max frequency > k, shrink window
        if (right - left + 1 - maxCount > k) {
            count[s[left]]--;
            left++;
        }
        
        maxLen = std::max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

// ===== SUBARRAY PROBLEMS =====

int SlidingWindow::minSubArrayLen(int target, const std::vector<int>& nums) {
    int left = 0, sum = 0, minLen = INT_MAX;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        while (sum >= target) {
            minLen = std::min(minLen, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    
    return minLen == INT_MAX ? 0 : minLen;
}

int SlidingWindow::findLength(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    int maxLen = 0;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLen = std::max(maxLen, dp[i][j]);
            }
        }
    }
    
    return maxLen;
}

int SlidingWindow::numSubarrayProductLessThanK(const std::vector<int>& nums, int k) {
    if (k <= 1) return 0;
    
    int left = 0, product = 1, count = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        product *= nums[right];
        
        while (product >= k) {
            product /= nums[left];
            left++;
        }
        
        count += right - left + 1;
    }
    
    return count;
}

int SlidingWindow::totalFruit(const std::vector<int>& fruits) {
    return lengthOfLongestSubstringKDistinct(
        std::string(fruits.begin(), fruits.end()), 2);
}

bool SlidingWindow::checkInclusion(const std::string& s1, const std::string& s2) {
    if (s1.length() > s2.length()) return false;
    
    std::unordered_map<char, int> s1Count, windowCount;
    for (char c : s1) {
        s1Count[c]++;
    }
    
    int windowSize = s1.length();
    
    // Initialize first window
    for (int i = 0; i < windowSize; i++) {
        windowCount[s2[i]]++;
    }
    
    if (isAnagram(s1Count, windowCount)) return true;
    
    // Slide the window
    for (int i = windowSize; i < s2.length(); i++) {
        // Add new character
        windowCount[s2[i]]++;
        
        // Remove old character
        char oldChar = s2[i - windowSize];
        windowCount[oldChar]--;
        if (windowCount[oldChar] == 0) {
            windowCount.erase(oldChar);
        }
        
        if (isAnagram(s1Count, windowCount)) return true;
    }
    
    return false;
}

std::vector<int> SlidingWindow::findAnagrams(const std::string& s, const std::string& p) {
    std::vector<int> result;
    if (p.length() > s.length()) return result;
    
    std::unordered_map<char, int> pCount, windowCount;
    for (char c : p) {
        pCount[c]++;
    }
    
    int windowSize = p.length();
    
    // Initialize first window
    for (int i = 0; i < windowSize; i++) {
        windowCount[s[i]]++;
    }
    
    if (isAnagram(pCount, windowCount)) {
        result.push_back(0);
    }
    
    // Slide the window
    for (int i = windowSize; i < s.length(); i++) {
        // Add new character
        windowCount[s[i]]++;
        
        // Remove old character
        char oldChar = s[i - windowSize];
        windowCount[oldChar]--;
        if (windowCount[oldChar] == 0) {
            windowCount.erase(oldChar);
        }
        
        if (isAnagram(pCount, windowCount)) {
            result.push_back(i - windowSize + 1);
        }
    }
    
    return result;
}

// ===== ADVANCED SLIDING WINDOW =====

std::vector<int> SlidingWindow::maxSlidingWindowDeque(const std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::deque<int> dq; // Store indices
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove indices outside current window
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        
        // Remove indices of smaller elements
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Add to result if window is complete
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

std::vector<double> SlidingWindow::medianSlidingWindow(const std::vector<int>& nums, int k) {
    std::vector<double> result;
    std::vector<int> window;
    
    for (int i = 0; i < nums.size(); i++) {
        window.push_back(nums[i]);
        
        if (window.size() > k) {
            window.erase(std::find(window.begin(), window.end(), nums[i - k]));
        }
        
        if (window.size() == k) {
            std::vector<int> sortedWindow = window;
            std::sort(sortedWindow.begin(), sortedWindow.end());
            result.push_back(findMedian(sortedWindow));
        }
    }
    
    return result;
}

int SlidingWindow::constrainedSubsetSum(const std::vector<int>& nums, int k) {
    std::deque<int> dq;
    std::vector<int> dp(nums.size());
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove indices outside window
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        
        dp[i] = nums[i] + (dq.empty() ? 0 : std::max(0, dp[dq.front()]));
        
        // Maintain decreasing order in deque
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return *std::max_element(dp.begin(), dp.end());
}

int SlidingWindow::shortestSubarray(const std::vector<int>& nums, int k) {
    int n = nums.size();
    std::vector<long long> prefixSum(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }
    
    std::deque<int> dq;
    int minLen = INT_MAX;
    
    for (int i = 0; i <= n; i++) {
        while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= k) {
            minLen = std::min(minLen, i - dq.front());
            dq.pop_front();
        }
        
        while (!dq.empty() && prefixSum[i] <= prefixSum[dq.back()]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return minLen == INT_MAX ? -1 : minLen;
}

int SlidingWindow::equalSubstring(const std::string& s, const std::string& t, int maxCost) {
    int left = 0, cost = 0, maxLen = 0;
    
    for (int right = 0; right < s.length(); right++) {
        cost += std::abs(s[right] - t[right]);
        
        while (cost > maxCost) {
            cost -= std::abs(s[left] - t[left]);
            left++;
        }
        
        maxLen = std::max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

int SlidingWindow::longestOnes(const std::vector<int>& nums, int k) {
    int left = 0, zeros = 0, maxLen = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) {
            zeros++;
        }
        
        while (zeros > k) {
            if (nums[left] == 0) {
                zeros--;
            }
            left++;
        }
        
        maxLen = std::max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

int SlidingWindow::numSubarraysWithSum(const std::vector<int>& nums, int goal) {
    return atMostK(nums, goal) - atMostK(nums, goal - 1);
}

// ===== HELPER FUNCTIONS =====

bool SlidingWindow::isAnagram(const std::unordered_map<char, int>& map1, 
                             const std::unordered_map<char, int>& map2) {
    return map1 == map2;
}

int SlidingWindow::atMostK(const std::vector<int>& nums, int k) {
    if (k < 0) return 0;
    
    int left = 0, sum = 0, count = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        while (sum > k) {
            sum -= nums[left];
            left++;
        }
        
        count += right - left + 1;
    }
    
    return count;
}

double SlidingWindow::findMedian(std::vector<int>& window) {
    int n = window.size();
    if (n % 2 == 1) {
        return window[n / 2];
    } else {
        return ((long long)window[n / 2 - 1] + window[n / 2]) / 2.0;
    }
}

} // namespace algorithms
} // namespace leetcode_study_guide