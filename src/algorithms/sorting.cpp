#include "leetcode_study_guide/algorithms/sorting.h"
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <random>
#include <sstream>

namespace leetcode_study_guide {
namespace algorithms {

// ===== BASIC SORTING ALGORITHMS =====

void Sorting::bubbleSort(std::vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Array is already sorted
    }
}

void Sorting::selectionSort(std::vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (nums[j] < nums[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(nums[i], nums[minIdx]);
        }
    }
}

void Sorting::insertionSort(std::vector<int>& nums) {
    int n = nums.size();
    for (int i = 1; i < n; i++) {
        int key = nums[i];
        int j = i - 1;
        
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}

// ===== ADVANCED SORTING ALGORITHMS =====

void Sorting::mergeSort(std::vector<int>& nums) {
    if (nums.size() <= 1) return;
    mergeSortHelper(nums, 0, nums.size() - 1);
}

void Sorting::mergeSortHelper(std::vector<int>& nums, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSortHelper(nums, left, mid);
    mergeSortHelper(nums, mid + 1, right);
    merge(nums, left, mid, right);
}

void Sorting::merge(std::vector<int>& nums, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];
        }
    }
    
    while (i <= mid) temp[k++] = nums[i++];
    while (j <= right) temp[k++] = nums[j++];
    
    for (int i = 0; i < k; i++) {
        nums[left + i] = temp[i];
    }
}

void Sorting::quickSort(std::vector<int>& nums) {
    if (nums.size() <= 1) return;
    quickSortHelper(nums, 0, nums.size() - 1);
}

void Sorting::quickSortHelper(std::vector<int>& nums, int left, int right) {
    if (left < right) {
        int pivotIndex = randomizedPartition(nums, left, right);
        quickSortHelper(nums, left, pivotIndex - 1);
        quickSortHelper(nums, pivotIndex + 1, right);
    }
}

int Sorting::partition(std::vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        if (nums[j] <= pivot) {
            i++;
            std::swap(nums[i], nums[j]);
        }
    }
    
    std::swap(nums[i + 1], nums[right]);
    return i + 1;
}

int Sorting::randomizedPartition(std::vector<int>& nums, int left, int right) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(left, right);
    
    int randomIndex = dis(gen);
    std::swap(nums[randomIndex], nums[right]);
    return partition(nums, left, right);
}

void Sorting::heapSort(std::vector<int>& nums) {
    int n = nums.size();
    
    // Build max heap
    buildMaxHeap(nums);
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        std::swap(nums[0], nums[i]);
        heapify(nums, i, 0);
    }
}

void Sorting::heapify(std::vector<int>& nums, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && nums[left] > nums[largest]) {
        largest = left;
    }
    
    if (right < n && nums[right] > nums[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        std::swap(nums[i], nums[largest]);
        heapify(nums, n, largest);
    }
}

void Sorting::buildMaxHeap(std::vector<int>& nums) {
    int n = nums.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(nums, n, i);
    }
}

// ===== NON-COMPARISON BASED SORTING =====

void Sorting::countingSort(std::vector<int>& nums) {
    if (nums.empty()) return;
    
    int minVal = *std::min_element(nums.begin(), nums.end());
    int maxVal = *std::max_element(nums.begin(), nums.end());
    
    countingSortRange(nums, minVal, maxVal);
}

void Sorting::countingSortRange(std::vector<int>& nums, int minVal, int maxVal) {
    int range = maxVal - minVal + 1;
    std::vector<int> count(range, 0);
    
    // Count occurrences
    for (int num : nums) {
        count[num - minVal]++;
    }
    
    // Reconstruct array
    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i]-- > 0) {
            nums[index++] = i + minVal;
        }
    }
}

void Sorting::radixSort(std::vector<int>& nums) {
    if (nums.empty()) return;
    
    int maxNum = getMax(nums);
    
    // Do counting sort for every digit
    for (int exp = 1; maxNum / exp > 0; exp *= 10) {
        countingSortForRadix(nums, exp);
    }
}

void Sorting::countingSortForRadix(std::vector<int>& nums, int exp) {
    int n = nums.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0);
    
    // Count occurrences of digits
    for (int i = 0; i < n; i++) {
        count[(nums[i] / exp) % 10]++;
    }
    
    // Change count[i] to actual position
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(nums[i] / exp) % 10] - 1] = nums[i];
        count[(nums[i] / exp) % 10]--;
    }
    
    // Copy output array to nums
    for (int i = 0; i < n; i++) {
        nums[i] = output[i];
    }
}

int Sorting::getMax(const std::vector<int>& nums) {
    return *std::max_element(nums.begin(), nums.end());
}

void Sorting::bucketSort(std::vector<double>& nums) {
    int n = nums.size();
    if (n <= 1) return;
    
    // Create buckets
    std::vector<std::vector<double>> buckets(n);
    
    // Put array elements in different buckets
    for (double num : nums) {
        int bucketIndex = n * num; // Assuming nums are in [0, 1)
        buckets[bucketIndex].push_back(num);
    }
    
    // Sort individual buckets
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
    }
    
    // Concatenate all buckets
    int index = 0;
    for (const auto& bucket : buckets) {
        for (double num : bucket) {
            nums[index++] = num;
        }
    }
}

// ===== LEETCODE SORTING PROBLEMS =====

void Sorting::sortColors(std::vector<int>& nums) {
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
            // Don't increment mid here as we need to check the swapped element
        }
    }
}

std::vector<Sorting::Interval> Sorting::mergeIntervals(std::vector<Interval>& intervals) {
    if (intervals.empty()) return {};
    
    std::sort(intervals.begin(), intervals.end(), 
              [](const Interval& a, const Interval& b) {
                  return a.start < b.start;
              });
    
    std::vector<Interval> merged;
    merged.push_back(intervals[0]);
    
    for (size_t i = 1; i < intervals.size(); i++) {
        if (intervals[i].start <= merged.back().end) {
            merged.back().end = std::max(merged.back().end, intervals[i].end);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}

std::string Sorting::largestNumber(std::vector<int>& nums) {
    std::vector<std::string> strs;
    for (int num : nums) {
        strs.push_back(std::to_string(num));
    }
    
    std::sort(strs.begin(), strs.end(), customCompare);
    
    // Handle edge case where all numbers are 0
    if (strs[0] == "0") return "0";
    
    std::string result;
    for (const std::string& str : strs) {
        result += str;
    }
    
    return result;
}

bool Sorting::customCompare(const std::string& a, const std::string& b) {
    return a + b > b + a;
}

int Sorting::minMeetingRooms(std::vector<Interval>& intervals) {
    if (intervals.empty()) return 0;
    
    std::vector<int> starts, ends;
    for (const auto& interval : intervals) {
        starts.push_back(interval.start);
        ends.push_back(interval.end);
    }
    
    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());
    
    int rooms = 0, maxRooms = 0;
    int i = 0, j = 0;
    
    while (i < starts.size()) {
        if (starts[i] < ends[j]) {
            rooms++;
            maxRooms = std::max(maxRooms, rooms);
            i++;
        } else {
            rooms--;
            j++;
        }
    }
    
    return maxRooms;
}

int Sorting::findKthLargest(std::vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
}

int Sorting::quickSelect(std::vector<int>& nums, int left, int right, int k) {
    if (left == right) return nums[left];
    
    int pivotIndex = randomizedPartition(nums, left, right);
    
    if (k == pivotIndex) {
        return nums[k];
    } else if (k < pivotIndex) {
        return quickSelect(nums, left, pivotIndex - 1, k);
    } else {
        return quickSelect(nums, pivotIndex + 1, right, k);
    }
}

std::vector<int> Sorting::topKFrequent(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    
    // Use min heap to keep top k frequent elements
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
                       std::greater<std::pair<int, int>>> minHeap;
    
    for (const auto& pair : freq) {
        minHeap.push({pair.second, pair.first});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    std::vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<int> Sorting::sortArrayByParity(std::vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        if (nums[left] % 2 == 1 && nums[right] % 2 == 0) {
            std::swap(nums[left], nums[right]);
        }
        
        if (nums[left] % 2 == 0) left++;
        if (nums[right] % 2 == 1) right--;
    }
    
    return nums;
}

std::vector<int> Sorting::pancakeSort(std::vector<int>& nums) {
    std::vector<int> result;
    int n = nums.size();
    
    for (int i = n; i > 1; i--) {
        int maxIdx = findMaxIndex(nums, i - 1);
        
        if (maxIdx != i - 1) {
            // Flip to bring max to front
            if (maxIdx != 0) {
                flip(nums, maxIdx);
                result.push_back(maxIdx + 1);
            }
            
            // Flip to bring max to correct position
            flip(nums, i - 1);
            result.push_back(i);
        }
    }
    
    return result;
}

void Sorting::flip(std::vector<int>& nums, int k) {
    std::reverse(nums.begin(), nums.begin() + k + 1);
}

int Sorting::findMaxIndex(const std::vector<int>& nums, int end) {
    int maxIdx = 0;
    for (int i = 1; i <= end; i++) {
        if (nums[i] > nums[maxIdx]) {
            maxIdx = i;
        }
    }
    return maxIdx;
}

void Sorting::wiggleSort(std::vector<int>& nums) {
    std::vector<int> sorted = nums;
    std::sort(sorted.begin(), sorted.end());
    
    int n = nums.size();
    int mid = (n + 1) / 2;
    
    int j = mid - 1; // End of first half
    int k = n - 1;   // End of second half
    
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            nums[i] = sorted[j--];
        } else {
            nums[i] = sorted[k--];
        }
    }
}

} // namespace algorithms
} // namespace leetcode_study_guide