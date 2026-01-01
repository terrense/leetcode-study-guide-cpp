/**
 * @file common.h
 * @brief Common types and enums used throughout the LeetCode Study Guide system
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_COMMON_H
#define LEETCODE_STUDY_GUIDE_COMMON_H

#include <string>
#include <vector>

namespace leetcode_study_guide {

/**
 * @brief Difficulty levels for problems and learning paths
 */
enum class DifficultyLevel {
    EASY,
    MEDIUM,
    HARD
};

/**
 * @brief Learning path difficulty levels
 */
enum class LearningPathDifficulty {
    BEGINNER,
    INTERMEDIATE,
    ADVANCED
};

/**
 * @brief Supported programming languages for code implementations
 */
enum class ProgrammingLanguage {
    CPP,
    PYTHON,
    JAVA,
    JAVASCRIPT,
    TYPESCRIPT,
    GO,
    RUST
};

/**
 * @brief Big O complexity notation for time and space analysis
 */
enum class ComplexityNotation {
    O_1,        // O(1)
    O_LOG_N,    // O(log n)
    O_N,        // O(n)
    O_N_LOG_N,  // O(n log n)
    O_N_SQUARED,// O(n²)
    O_N_CUBED,  // O(n³)
    O_2_POWER_N,// O(2^n)
    O_N_FACTORIAL // O(n!)
};

/**
 * @brief Major data structure categories
 */
enum class DataStructureCategory {
    ARRAY,
    LINKED_LIST,
    STACK,
    QUEUE,
    TREE,
    GRAPH,
    HASH,
    HEAP,
    TRIE
};

/**
 * @brief Algorithm pattern categories
 */
enum class AlgorithmPattern {
    TWO_POINTERS,
    SLIDING_WINDOW,
    BINARY_SEARCH,
    DFS,
    BFS,
    DYNAMIC_PROGRAMMING,
    GREEDY,
    BACKTRACKING,
    DIVIDE_AND_CONQUER,
    SORTING
};

/**
 * @brief Convert DifficultyLevel enum to string
 */
std::string difficultyLevelToString(DifficultyLevel level);

/**
 * @brief Convert string to DifficultyLevel enum
 */
DifficultyLevel stringToDifficultyLevel(const std::string& str);

/**
 * @brief Convert ProgrammingLanguage enum to string
 */
std::string programmingLanguageToString(ProgrammingLanguage lang);

/**
 * @brief Convert string to ProgrammingLanguage enum
 */
ProgrammingLanguage stringToProgrammingLanguage(const std::string& str);

/**
 * @brief Convert ComplexityNotation enum to string
 */
std::string complexityNotationToString(ComplexityNotation complexity);

/**
 * @brief Convert string to ComplexityNotation enum
 */
ComplexityNotation stringToComplexityNotation(const std::string& str);

/**
 * @brief Convert DataStructureCategory enum to string
 */
std::string dataStructureCategoryToString(DataStructureCategory category);

/**
 * @brief Convert string to DataStructureCategory enum
 */
DataStructureCategory stringToDataStructureCategory(const std::string& str);

/**
 * @brief Convert AlgorithmPattern enum to string
 */
std::string algorithmPatternToString(AlgorithmPattern pattern);

/**
 * @brief Convert string to AlgorithmPattern enum
 */
AlgorithmPattern stringToAlgorithmPattern(const std::string& str);

} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_COMMON_H