#include "leetcode_study_guide/algorithms/divide_conquer.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <unordered_map>

namespace leetcode_study_guide {
namespace algorithms {

// ===== MERGE SORT =====

void DivideConquer::mergeSort(std::vector<int>& nums) {
    if (nums.size() <= 1) return;
    mergeSortRange(nums, 0, nums.size() - 1);
}

void DivideConquer::mergeSortRange(std::vector<int>& nums, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSortRange(nums, left, mid);
    mergeSortRange(nums, mid + 1, right);
    merge(nums, left, mid, right);
}

void DivideConquer::merge(std::vector<int>& nums, int left, int mid, int right) {
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

// ===== QUICK SORT =====

void DivideConquer::quickSort(std::vector<int>& nums) {
    if (nums.size() <= 1) return;
    quickSortRange(nums, 0, nums.size() - 1);
}

void DivideConquer::quickSortRange(std::vector<int>& nums, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(nums, left, right);
        quickSortRange(nums, left, pivotIndex - 1);
        quickSortRange(nums, pivotIndex + 1, right);
    }
}

int DivideConquer::partition(std::vector<int>& nums, int left, int right) {
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

// ===== MAXIMUM SUBARRAY =====

int DivideConquer::maxSubArray(const std::vector<int>& nums) {
    if (nums.empty()) return 0;
    return maxSubArrayHelper(nums, 0, nums.size() - 1);
}

int DivideConquer::maxSubArrayHelper(const std::vector<int>& nums, int left, int right) {
    if (left == right) return nums[left];
    
    int mid = left + (right - left) / 2;
    
    int leftMax = maxSubArrayHelper(nums, left, mid);
    int rightMax = maxSubArrayHelper(nums, mid + 1, right);
    int crossMax = maxCrossingSum(nums, left, mid, right);
    
    return std::max({leftMax, rightMax, crossMax});
}

int DivideConquer::maxCrossingSum(const std::vector<int>& nums, int left, int mid, int right) {
    int leftSum = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= left; i--) {
        sum += nums[i];
        leftSum = std::max(leftSum, sum);
    }
    
    int rightSum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        sum += nums[i];
        rightSum = std::max(rightSum, sum);
    }
    
    return leftSum + rightSum;
}

// ===== CLOSEST PAIR OF POINTS =====

double DivideConquer::closestPair(std::vector<Point>& points) {
    std::vector<Point> pointsX = points;
    std::vector<Point> pointsY = points;
    
    std::sort(pointsX.begin(), pointsX.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    
    std::sort(pointsY.begin(), pointsY.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });
    
    return closestPairHelper(pointsX, pointsY);
}

double DivideConquer::closestPairHelper(std::vector<Point>& pointsX, std::vector<Point>& pointsY) {
    int n = pointsX.size();
    
    // Base case: brute force for small arrays
    if (n <= 3) {
        double minDist = std::numeric_limits<double>::max();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                minDist = std::min(minDist, distance(pointsX[i], pointsX[j]));
            }
        }
        return minDist;
    }
    
    // Divide
    int mid = n / 2;
    Point midPoint = pointsX[mid];
    
    std::vector<Point> leftY, rightY;
    for (const Point& p : pointsY) {
        if (p.x <= midPoint.x) {
            leftY.push_back(p);
        } else {
            rightY.push_back(p);
        }
    }
    
    std::vector<Point> leftX(pointsX.begin(), pointsX.begin() + mid);
    std::vector<Point> rightX(pointsX.begin() + mid, pointsX.end());
    
    double leftMin = closestPairHelper(leftX, leftY);
    double rightMin = closestPairHelper(rightX, rightY);
    
    double minDist = std::min(leftMin, rightMin);
    
    // Find closest points across the divide
    std::vector<Point> strip;
    for (const Point& p : pointsY) {
        if (std::abs(p.x - midPoint.x) < minDist) {
            strip.push_back(p);
        }
    }
    
    return std::min(minDist, stripClosest(strip, minDist));
}

double DivideConquer::distance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double DivideConquer::stripClosest(std::vector<Point>& strip, double minDist) {
    double min = minDist;
    
    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min; j++) {
            min = std::min(min, distance(strip[i], strip[j]));
        }
    }
    
    return min;
}

// ===== MATRIX MULTIPLICATION =====

std::vector<std::vector<int>> DivideConquer::matrixMultiply(const std::vector<std::vector<int>>& A,
                                                           const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}

std::vector<std::vector<int>> DivideConquer::strassenMultiply(const std::vector<std::vector<int>>& A,
                                                             const std::vector<std::vector<int>>& B) {
    int n = A.size();
    
    // Base case
    if (n <= 2) {
        return matrixMultiply(A, B);
    }
    
    int half = n / 2;
    
    // Divide matrices into quadrants
    auto A11 = getSubMatrix(A, 0, 0, half);
    auto A12 = getSubMatrix(A, 0, half, half);
    auto A21 = getSubMatrix(A, half, 0, half);
    auto A22 = getSubMatrix(A, half, half, half);
    
    auto B11 = getSubMatrix(B, 0, 0, half);
    auto B12 = getSubMatrix(B, 0, half, half);
    auto B21 = getSubMatrix(B, half, 0, half);
    auto B22 = getSubMatrix(B, half, half, half);
    
    // Compute Strassen's 7 products
    auto M1 = strassenMultiply(addMatrices(A11, A22), addMatrices(B11, B22));
    auto M2 = strassenMultiply(addMatrices(A21, A22), B11);
    auto M3 = strassenMultiply(A11, subtractMatrices(B12, B22));
    auto M4 = strassenMultiply(A22, subtractMatrices(B21, B11));
    auto M5 = strassenMultiply(addMatrices(A11, A12), B22);
    auto M6 = strassenMultiply(subtractMatrices(A21, A11), addMatrices(B11, B12));
    auto M7 = strassenMultiply(subtractMatrices(A12, A22), addMatrices(B21, B22));
    
    // Compute result quadrants
    auto C11 = addMatrices(subtractMatrices(addMatrices(M1, M4), M5), M7);
    auto C12 = addMatrices(M3, M5);
    auto C21 = addMatrices(M2, M4);
    auto C22 = addMatrices(subtractMatrices(addMatrices(M1, M3), M2), M6);
    
    // Combine quadrants
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    setSubMatrix(C, C11, 0, 0);
    setSubMatrix(C, C12, 0, half);
    setSubMatrix(C, C21, half, 0);
    setSubMatrix(C, C22, half, half);
    
    return C;
}

// ===== COUNT INVERSIONS =====

int DivideConquer::countInversions(std::vector<int>& nums) {
    return countInversionsHelper(nums, 0, nums.size() - 1);
}

int DivideConquer::countInversionsHelper(std::vector<int>& nums, int left, int right) {
    if (left >= right) return 0;
    
    int mid = left + (right - left) / 2;
    
    int leftInv = countInversionsHelper(nums, left, mid);
    int rightInv = countInversionsHelper(nums, mid + 1, right);
    int splitInv = mergeAndCount(nums, left, mid, right);
    
    return leftInv + rightInv + splitInv;
}

int DivideConquer::mergeAndCount(std::vector<int>& nums, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    int invCount = 0;
    
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];
            invCount += (mid - i + 1); // All elements from i to mid are greater than nums[j]
        }
    }
    
    while (i <= mid) temp[k++] = nums[i++];
    while (j <= right) temp[k++] = nums[j++];
    
    for (int i = 0; i < k; i++) {
        nums[left + i] = temp[i];
    }
    
    return invCount;
}

// ===== MAJORITY ELEMENT =====

int DivideConquer::majorityElement(const std::vector<int>& nums) {
    return majorityElementHelper(nums, 0, nums.size() - 1);
}

int DivideConquer::majorityElementHelper(const std::vector<int>& nums, int left, int right) {
    if (left == right) return nums[left];
    
    int mid = left + (right - left) / 2;
    
    int leftMajority = majorityElementHelper(nums, left, mid);
    int rightMajority = majorityElementHelper(nums, mid + 1, right);
    
    if (leftMajority == rightMajority) return leftMajority;
    
    int leftCount = countInRange(nums, leftMajority, left, right);
    int rightCount = countInRange(nums, rightMajority, left, right);
    
    return leftCount > rightCount ? leftMajority : rightMajority;
}

int DivideConquer::countInRange(const std::vector<int>& nums, int target, int left, int right) {
    int count = 0;
    for (int i = left; i <= right; i++) {
        if (nums[i] == target) count++;
    }
    return count;
}

// ===== FAST EXPONENTIATION =====

double DivideConquer::myPow(double x, int n) {
    long long longN = n;
    if (longN < 0) {
        x = 1 / x;
        longN = -longN;
    }
    return powHelper(x, longN);
}

double DivideConquer::powHelper(double x, long long n) {
    if (n == 0) return 1.0;
    
    double half = powHelper(x, n / 2);
    
    if (n % 2 == 0) {
        return half * half;
    } else {
        return half * half * x;
    }
}

// ===== KTH LARGEST ELEMENT =====

int DivideConquer::findKthLargest(std::vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
}

int DivideConquer::quickSelect(std::vector<int>& nums, int left, int right, int k) {
    if (left == right) return nums[left];
    
    int pivotIndex = partition(nums, left, right);
    
    if (k == pivotIndex) {
        return nums[k];
    } else if (k < pivotIndex) {
        return quickSelect(nums, left, pivotIndex - 1, k);
    } else {
        return quickSelect(nums, pivotIndex + 1, right, k);
    }
}

// ===== DIFFERENT WAYS TO ADD PARENTHESES =====

std::vector<int> DivideConquer::diffWaysToCompute(const std::string& expression) {
    return computeHelper(expression, 0, expression.length() - 1);
}

std::vector<int> DivideConquer::computeHelper(const std::string& expression, int start, int end) {
    std::vector<int> result;
    
    // Base case: single number
    bool hasOperator = false;
    for (int i = start; i <= end; i++) {
        if (isOperator(expression[i])) {
            hasOperator = true;
            break;
        }
    }
    
    if (!hasOperator) {
        result.push_back(std::stoi(expression.substr(start, end - start + 1)));
        return result;
    }
    
    // Divide at each operator
    for (int i = start; i <= end; i++) {
        if (isOperator(expression[i])) {
            std::vector<int> left = computeHelper(expression, start, i - 1);
            std::vector<int> right = computeHelper(expression, i + 1, end);
            
            for (int l : left) {
                for (int r : right) {
                    result.push_back(compute(l, r, expression[i]));
                }
            }
        }
    }
    
    return result;
}

bool DivideConquer::isOperator(char c) {
    return c == '+' || c == '-' || c == '*';
}

int DivideConquer::compute(int left, int right, char op) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        default: return 0;
    }
}

// ===== UNIQUE BINARY SEARCH TREES II =====

std::vector<DivideConquer::TreeNode*> DivideConquer::generateTrees(int n) {
    if (n == 0) return {};
    return generateTreesHelper(1, n);
}

std::vector<DivideConquer::TreeNode*> DivideConquer::generateTreesHelper(int start, int end) {
    std::vector<TreeNode*> result;
    
    if (start > end) {
        result.push_back(nullptr);
        return result;
    }
    
    for (int i = start; i <= end; i++) {
        std::vector<TreeNode*> leftTrees = generateTreesHelper(start, i - 1);
        std::vector<TreeNode*> rightTrees = generateTreesHelper(i + 1, end);
        
        for (TreeNode* left : leftTrees) {
            for (TreeNode* right : rightTrees) {
                TreeNode* root = new TreeNode(i);
                root->left = left;
                root->right = right;
                result.push_back(root);
            }
        }
    }
    
    return result;
}

// ===== MEDIAN OF TWO SORTED ARRAYS =====

double DivideConquer::findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }
    
    int m = nums1.size(), n = nums2.size();
    int left = 0, right = m;
    
    while (left <= right) {
        int partitionX = (left + right) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;
        
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];
        
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];
        
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((m + n) % 2 == 0) {
                return (std::max(maxLeftX, maxLeftY) + std::min(minRightX, minRightY)) / 2.0;
            } else {
                return std::max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            right = partitionX - 1;
        } else {
            left = partitionX + 1;
        }
    }
    
    return 0.0;
}

// ===== HELPER FUNCTIONS FOR MATRIX OPERATIONS =====

std::vector<std::vector<int>> DivideConquer::addMatrices(const std::vector<std::vector<int>>& A,
                                                        const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    
    return C;
}

std::vector<std::vector<int>> DivideConquer::subtractMatrices(const std::vector<std::vector<int>>& A,
                                                             const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    
    return C;
}

std::vector<std::vector<int>> DivideConquer::getSubMatrix(const std::vector<std::vector<int>>& matrix,
                                                         int row, int col, int size) {
    std::vector<std::vector<int>> subMatrix(size, std::vector<int>(size));
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            subMatrix[i][j] = matrix[row + i][col + j];
        }
    }
    
    return subMatrix;
}

void DivideConquer::setSubMatrix(std::vector<std::vector<int>>& matrix,
                                const std::vector<std::vector<int>>& subMatrix,
                                int row, int col) {
    int size = subMatrix.size();
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[row + i][col + j] = subMatrix[i][j];
        }
    }
}

} // namespace algorithms
} // namespace leetcode_study_guide