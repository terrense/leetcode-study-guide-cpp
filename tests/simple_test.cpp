/**
 * @file simple_test.cpp
 * @brief Simple test runner without external dependencies
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/problem.h"
#include "leetcode_study_guide/solution.h"
#include "leetcode_study_guide/learning_path.h"
#include "leetcode_study_guide/common.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace leetcode_study_guide;

// Simple test framework
class SimpleTest {
public:
    static int tests_run;
    static int tests_passed;
    
    static void assert_equal(const std::string& expected, const std::string& actual, const std::string& test_name) {
        tests_run++;
        if (expected == actual) {
            tests_passed++;
            std::cout << "[PASS] " << test_name << std::endl;
        } else {
            std::cout << "[FAIL] " << test_name << " - Expected: '" << expected << "', Got: '" << actual << "'" << std::endl;
        }
    }
    
    static void assert_true(bool condition, const std::string& test_name) {
        tests_run++;
        if (condition) {
            tests_passed++;
            std::cout << "[PASS] " << test_name << std::endl;
        } else {
            std::cout << "[FAIL] " << test_name << " - Expected true, got false" << std::endl;
        }
    }
    
    static void print_summary() {
        std::cout << "\nTest Summary: " << tests_passed << "/" << tests_run << " tests passed" << std::endl;
        if (tests_passed == tests_run) {
            std::cout << "All tests passed!" << std::endl;
        }
    }
};

int SimpleTest::tests_run = 0;
int SimpleTest::tests_passed = 0;

// Test core data models
void test_problem_creation() {
    try {
        Problem problem("1", "Two Sum", DifficultyLevel::EASY, "Find two numbers that add up to target");
        SimpleTest::assert_equal("1", problem.getId(), "Problem ID");
        SimpleTest::assert_equal("Two Sum", problem.getTitle(), "Problem Title");
        SimpleTest::assert_true(problem.getDifficulty() == DifficultyLevel::EASY, "Problem Difficulty");
    } catch (const std::exception& e) {
        std::cout << "[FAIL] Problem creation test - Exception: " << e.what() << std::endl;
        SimpleTest::tests_run++;
    }
}

void test_solution_creation() {
    try {
        Solution solution("Hash Map", ComplexityNotation::O_N, ComplexityNotation::O_N, "Use hash map for O(1) lookup");
        SimpleTest::assert_equal("Hash Map", solution.getApproach(), "Solution Approach");
        SimpleTest::assert_true(solution.getTimeComplexity() == ComplexityNotation::O_N, "Time Complexity");
        SimpleTest::assert_true(solution.getSpaceComplexity() == ComplexityNotation::O_N, "Space Complexity");
    } catch (const std::exception& e) {
        std::cout << "[FAIL] Solution creation test - Exception: " << e.what() << std::endl;
        SimpleTest::tests_run++;
    }
}

void test_learning_path_creation() {
    try {
        LearningPath path("arrays", "Array Fundamentals", "Learn array operations", "2 weeks", LearningPathDifficulty::BEGINNER);
        SimpleTest::assert_equal("arrays", path.getId(), "Learning Path ID");
        SimpleTest::assert_equal("Array Fundamentals", path.getTitle(), "Learning Path Title");
        SimpleTest::assert_true(path.getDifficulty() == LearningPathDifficulty::BEGINNER, "Learning Path Difficulty");
    } catch (const std::exception& e) {
        std::cout << "[FAIL] Learning path creation test - Exception: " << e.what() << std::endl;
        SimpleTest::tests_run++;
    }
}

void test_topic_creation() {
    try {
        Topic topic("arrays-basic", "Basic Array Operations", "Arrays are contiguous memory structures");
        SimpleTest::assert_equal("arrays-basic", topic.getId(), "Topic ID");
        SimpleTest::assert_equal("Basic Array Operations", topic.getTitle(), "Topic Title");
        SimpleTest::assert_true(!topic.getTheory().empty(), "Topic Theory");
    } catch (const std::exception& e) {
        std::cout << "[FAIL] Topic creation test - Exception: " << e.what() << std::endl;
        SimpleTest::tests_run++;
    }
}

void test_enum_conversions() {
    // Test difficulty level conversions
    SimpleTest::assert_equal("Easy", difficultyLevelToString(DifficultyLevel::EASY), "Difficulty to String");
    SimpleTest::assert_true(stringToDifficultyLevel("Medium") == DifficultyLevel::MEDIUM, "String to Difficulty");
    
    // Test complexity notation conversions
    SimpleTest::assert_equal("O(n)", complexityNotationToString(ComplexityNotation::O_N), "Complexity to String");
    SimpleTest::assert_true(stringToComplexityNotation("O(log n)") == ComplexityNotation::O_LOG_N, "String to Complexity");
    
    // Test data structure category conversions
    SimpleTest::assert_equal("Array", dataStructureCategoryToString(DataStructureCategory::ARRAY), "DataStructure to String");
    SimpleTest::assert_true(stringToDataStructureCategory("Tree") == DataStructureCategory::TREE, "String to DataStructure");
    
    // Test algorithm pattern conversions
    SimpleTest::assert_equal("Two Pointers", algorithmPatternToString(AlgorithmPattern::TWO_POINTERS), "Algorithm to String");
    SimpleTest::assert_true(stringToAlgorithmPattern("Binary Search") == AlgorithmPattern::BINARY_SEARCH, "String to Algorithm");
}

int main() {
    std::cout << "Running LeetCode Study Guide Core Tests..." << std::endl;
    std::cout << "===========================================" << std::endl;
    
    test_problem_creation();
    test_solution_creation();
    test_learning_path_creation();
    test_topic_creation();
    test_enum_conversions();
    
    SimpleTest::print_summary();
    
    return (SimpleTest::tests_passed == SimpleTest::tests_run) ? 0 : 1;
}