#ifndef LEETCODE_STUDY_GUIDE_ALGORITHMS_H
#define LEETCODE_STUDY_GUIDE_ALGORITHMS_H

/**
 * LeetCode Study Guide - Algorithm Patterns Module
 * 
 * This header provides access to all algorithm pattern implementations
 * commonly used in LeetCode problems. Each module contains both the
 * algorithmic implementations and related problem solutions.
 * 
 * Modules included:
 * - Binary Search: Various binary search patterns and scenarios
 * - Dynamic Programming: Memoization and tabulation approaches
 * - Greedy Algorithms: Optimization problems with greedy strategies
 * - Traversal: DFS and BFS for trees and graphs
 * - Backtracking: Combinatorial and constraint satisfaction problems
 * - Divide and Conquer: Recursive problem-solving strategies
 * - Sorting: Various sorting algorithms and related problems
 * - Two Pointers: Opposite and same direction pointer techniques
 * - Sliding Window: Fixed and variable size window problems
 */

// Search and Optimization Patterns
#include "algorithms/binary_search.h"
#include "algorithms/dynamic_programming.h"
#include "algorithms/greedy.h"

// Traversal and Backtracking Patterns
#include "algorithms/traversal.h"
#include "algorithms/backtracking.h"
#include "algorithms/divide_conquer.h"

// Sorting and Pointer Technique Patterns
#include "algorithms/sorting.h"
#include "algorithms/two_pointers.h"
#include "algorithms/sliding_window.h"

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Algorithm Pattern Categories
 * 
 * This enumeration helps categorize different algorithm patterns
 * for educational and organizational purposes.
 */
enum class PatternCategory {
    SEARCH_OPTIMIZATION,    // Binary Search, DP, Greedy
    TRAVERSAL_BACKTRACKING, // DFS, BFS, Backtracking, Divide & Conquer
    SORTING_POINTERS        // Sorting, Two Pointers, Sliding Window
};

/**
 * Algorithm Complexity Information
 * 
 * Structure to store time and space complexity information
 * for educational purposes.
 */
struct ComplexityInfo {
    std::string timeComplexity;
    std::string spaceComplexity;
    std::string description;
    
    ComplexityInfo(const std::string& time, const std::string& space, const std::string& desc)
        : timeComplexity(time), spaceComplexity(space), description(desc) {}
};

/**
 * Algorithm Pattern Registry
 * 
 * Provides metadata about implemented algorithm patterns
 * for documentation and learning purposes.
 */
class PatternRegistry {
public:
    /**
     * Get complexity information for a specific algorithm pattern
     */
    static ComplexityInfo getBinarySearchComplexity() {
        return ComplexityInfo("O(log n)", "O(1)", "Logarithmic search in sorted data");
    }
    
    static ComplexityInfo getDynamicProgrammingComplexity() {
        return ComplexityInfo("O(n*m)", "O(n*m)", "Optimization with overlapping subproblems");
    }
    
    static ComplexityInfo getGreedyComplexity() {
        return ComplexityInfo("O(n log n)", "O(1)", "Local optimal choices for global optimum");
    }
    
    static ComplexityInfo getTraversalComplexity() {
        return ComplexityInfo("O(V + E)", "O(V)", "Visit all vertices and edges once");
    }
    
    static ComplexityInfo getBacktrackingComplexity() {
        return ComplexityInfo("O(b^d)", "O(d)", "Explore solution space with pruning");
    }
    
    static ComplexityInfo getDivideConquerComplexity() {
        return ComplexityInfo("O(n log n)", "O(log n)", "Recursive divide and combine");
    }
    
    static ComplexityInfo getSortingComplexity() {
        return ComplexityInfo("O(n log n)", "O(1)", "Arrange elements in order");
    }
    
    static ComplexityInfo getTwoPointersComplexity() {
        return ComplexityInfo("O(n)", "O(1)", "Two pointers moving through data");
    }
    
    static ComplexityInfo getSlidingWindowComplexity() {
        return ComplexityInfo("O(n)", "O(k)", "Fixed or variable size window optimization");
    }
    
    /**
     * Get pattern category for educational grouping
     */
    static PatternCategory getPatternCategory(const std::string& patternName) {
        if (patternName == "binary_search" || patternName == "dynamic_programming" || 
            patternName == "greedy") {
            return PatternCategory::SEARCH_OPTIMIZATION;
        } else if (patternName == "traversal" || patternName == "backtracking" || 
                   patternName == "divide_conquer") {
            return PatternCategory::TRAVERSAL_BACKTRACKING;
        } else {
            return PatternCategory::SORTING_POINTERS;
        }
    }
};

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_ALGORITHMS_H