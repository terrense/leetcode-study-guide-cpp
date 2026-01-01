/**
 * @file common.cpp
 * @brief Implementation of common utility functions
 */

#include "leetcode_study_guide/common.h"
#include <stdexcept>
#include <unordered_map>

namespace leetcode_study_guide {

std::string difficultyLevelToString(DifficultyLevel level) {
    switch (level) {
        case DifficultyLevel::EASY: return "Easy";
        case DifficultyLevel::MEDIUM: return "Medium";
        case DifficultyLevel::HARD: return "Hard";
        default: throw std::invalid_argument("Invalid difficulty level");
    }
}

DifficultyLevel stringToDifficultyLevel(const std::string& str) {
    static const std::unordered_map<std::string, DifficultyLevel> map = {
        {"Easy", DifficultyLevel::EASY},
        {"Medium", DifficultyLevel::MEDIUM},
        {"Hard", DifficultyLevel::HARD}
    };
    
    auto it = map.find(str);
    if (it != map.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid difficulty level string: " + str);
}

std::string programmingLanguageToString(ProgrammingLanguage lang) {
    switch (lang) {
        case ProgrammingLanguage::CPP: return "C++";
        case ProgrammingLanguage::PYTHON: return "Python";
        case ProgrammingLanguage::JAVA: return "Java";
        case ProgrammingLanguage::JAVASCRIPT: return "JavaScript";
        case ProgrammingLanguage::TYPESCRIPT: return "TypeScript";
        case ProgrammingLanguage::GO: return "Go";
        case ProgrammingLanguage::RUST: return "Rust";
        default: throw std::invalid_argument("Invalid programming language");
    }
}

ProgrammingLanguage stringToProgrammingLanguage(const std::string& str) {
    static const std::unordered_map<std::string, ProgrammingLanguage> map = {
        {"C++", ProgrammingLanguage::CPP},
        {"Python", ProgrammingLanguage::PYTHON},
        {"Java", ProgrammingLanguage::JAVA},
        {"JavaScript", ProgrammingLanguage::JAVASCRIPT},
        {"TypeScript", ProgrammingLanguage::TYPESCRIPT},
        {"Go", ProgrammingLanguage::GO},
        {"Rust", ProgrammingLanguage::RUST}
    };
    
    auto it = map.find(str);
    if (it != map.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid programming language string: " + str);
}

std::string complexityNotationToString(ComplexityNotation complexity) {
    switch (complexity) {
        case ComplexityNotation::O_1: return "O(1)";
        case ComplexityNotation::O_LOG_N: return "O(log n)";
        case ComplexityNotation::O_N: return "O(n)";
        case ComplexityNotation::O_N_LOG_N: return "O(n log n)";
        case ComplexityNotation::O_N_SQUARED: return "O(n²)";
        case ComplexityNotation::O_N_CUBED: return "O(n³)";
        case ComplexityNotation::O_2_POWER_N: return "O(2^n)";
        case ComplexityNotation::O_N_FACTORIAL: return "O(n!)";
        default: throw std::invalid_argument("Invalid complexity notation");
    }
}

ComplexityNotation stringToComplexityNotation(const std::string& str) {
    static const std::unordered_map<std::string, ComplexityNotation> map = {
        {"O(1)", ComplexityNotation::O_1},
        {"O(log n)", ComplexityNotation::O_LOG_N},
        {"O(n)", ComplexityNotation::O_N},
        {"O(n log n)", ComplexityNotation::O_N_LOG_N},
        {"O(n²)", ComplexityNotation::O_N_SQUARED},
        {"O(n³)", ComplexityNotation::O_N_CUBED},
        {"O(2^n)", ComplexityNotation::O_2_POWER_N},
        {"O(n!)", ComplexityNotation::O_N_FACTORIAL}
    };
    
    auto it = map.find(str);
    if (it != map.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid complexity notation string: " + str);
}

std::string dataStructureCategoryToString(DataStructureCategory category) {
    switch (category) {
        case DataStructureCategory::ARRAY: return "Array";
        case DataStructureCategory::LINKED_LIST: return "LinkedList";
        case DataStructureCategory::STACK: return "Stack";
        case DataStructureCategory::QUEUE: return "Queue";
        case DataStructureCategory::TREE: return "Tree";
        case DataStructureCategory::GRAPH: return "Graph";
        case DataStructureCategory::HASH: return "Hash";
        case DataStructureCategory::HEAP: return "Heap";
        case DataStructureCategory::TRIE: return "Trie";
        default: throw std::invalid_argument("Invalid data structure category");
    }
}

DataStructureCategory stringToDataStructureCategory(const std::string& str) {
    static const std::unordered_map<std::string, DataStructureCategory> map = {
        {"Array", DataStructureCategory::ARRAY},
        {"LinkedList", DataStructureCategory::LINKED_LIST},
        {"Stack", DataStructureCategory::STACK},
        {"Queue", DataStructureCategory::QUEUE},
        {"Tree", DataStructureCategory::TREE},
        {"Graph", DataStructureCategory::GRAPH},
        {"Hash", DataStructureCategory::HASH},
        {"Heap", DataStructureCategory::HEAP},
        {"Trie", DataStructureCategory::TRIE}
    };
    
    auto it = map.find(str);
    if (it != map.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid data structure category string: " + str);
}

std::string algorithmPatternToString(AlgorithmPattern pattern) {
    switch (pattern) {
        case AlgorithmPattern::TWO_POINTERS: return "Two Pointers";
        case AlgorithmPattern::SLIDING_WINDOW: return "Sliding Window";
        case AlgorithmPattern::BINARY_SEARCH: return "Binary Search";
        case AlgorithmPattern::DFS: return "DFS";
        case AlgorithmPattern::BFS: return "BFS";
        case AlgorithmPattern::DYNAMIC_PROGRAMMING: return "Dynamic Programming";
        case AlgorithmPattern::GREEDY: return "Greedy";
        case AlgorithmPattern::BACKTRACKING: return "Backtracking";
        case AlgorithmPattern::DIVIDE_AND_CONQUER: return "Divide and Conquer";
        case AlgorithmPattern::SORTING: return "Sorting";
        default: throw std::invalid_argument("Invalid algorithm pattern");
    }
}

AlgorithmPattern stringToAlgorithmPattern(const std::string& str) {
    static const std::unordered_map<std::string, AlgorithmPattern> map = {
        {"Two Pointers", AlgorithmPattern::TWO_POINTERS},
        {"Sliding Window", AlgorithmPattern::SLIDING_WINDOW},
        {"Binary Search", AlgorithmPattern::BINARY_SEARCH},
        {"DFS", AlgorithmPattern::DFS},
        {"BFS", AlgorithmPattern::BFS},
        {"Dynamic Programming", AlgorithmPattern::DYNAMIC_PROGRAMMING},
        {"Greedy", AlgorithmPattern::GREEDY},
        {"Backtracking", AlgorithmPattern::BACKTRACKING},
        {"Divide and Conquer", AlgorithmPattern::DIVIDE_AND_CONQUER},
        {"Sorting", AlgorithmPattern::SORTING}
    };
    
    auto it = map.find(str);
    if (it != map.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid algorithm pattern string: " + str);
}

} // namespace leetcode_study_guide