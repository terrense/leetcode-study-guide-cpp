/**
 * @file solution.h
 * @brief Solution-related class definitions for the LeetCode Study Guide system
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_SOLUTION_H
#define LEETCODE_STUDY_GUIDE_SOLUTION_H

#include "common.h"
#include <string>
#include <vector>
#include <any>

namespace leetcode_study_guide {

/**
 * @brief Test case for validating a solution
 */
class TestCase {
public:
    /**
     * @brief Constructor for TestCase
     * @param input Input data for the test case
     * @param expected_output Expected output for the test case
     * @param description Description of what this test case validates
     */
    TestCase(const std::any& input, const std::any& expected_output, 
             const std::string& description);

    // Getters
    const std::any& getInput() const { return input_; }
    const std::any& getExpectedOutput() const { return expected_output_; }
    const std::string& getDescription() const { return description_; }

    // Setters
    void setInput(const std::any& input) { input_ = input; }
    void setExpectedOutput(const std::any& expected_output) { expected_output_ = expected_output; }
    void setDescription(const std::string& description) { description_ = description; }

private:
    std::any input_;
    std::any expected_output_;
    std::string description_;
};

/**
 * @brief Code implementation in a specific programming language
 */
class CodeImplementation {
public:
    /**
     * @brief Constructor for CodeImplementation
     * @param language Programming language used
     * @param code Complete code implementation
     */
    CodeImplementation(ProgrammingLanguage language, const std::string& code);

    // Getters
    ProgrammingLanguage getLanguage() const { return language_; }
    const std::string& getCode() const { return code_; }
    const std::vector<std::string>& getComments() const { return comments_; }

    // Setters
    void setLanguage(ProgrammingLanguage language) { language_ = language; }
    void setCode(const std::string& code) { code_ = code; }

    // Comment management
    void addComment(const std::string& comment);
    void removeComment(size_t index);
    void clearComments();

private:
    ProgrammingLanguage language_;
    std::string code_;
    std::vector<std::string> comments_;
};

/**
 * @brief Complete solution for a problem including approach, complexity, and implementation
 */
class Solution {
public:
    /**
     * @brief Constructor for Solution
     * @param approach High-level approach description
     * @param time_complexity Time complexity in Big O notation
     * @param space_complexity Space complexity in Big O notation
     * @param explanation Detailed step-by-step explanation
     */
    Solution(const std::string& approach, ComplexityNotation time_complexity,
             ComplexityNotation space_complexity, const std::string& explanation);

    /**
     * @brief Destructor
     */
    ~Solution() = default;

    // Copy constructor and assignment operator
    Solution(const Solution& other);
    Solution& operator=(const Solution& other);

    // Move constructor and assignment operator
    Solution(Solution&& other) noexcept;
    Solution& operator=(Solution&& other) noexcept;

    // Getters
    const std::string& getApproach() const { return approach_; }
    ComplexityNotation getTimeComplexity() const { return time_complexity_; }
    ComplexityNotation getSpaceComplexity() const { return space_complexity_; }
    const std::string& getExplanation() const { return explanation_; }
    const std::vector<CodeImplementation>& getCodeImplementations() const { return code_implementations_; }
    const std::vector<TestCase>& getTestCases() const { return test_cases_; }

    // Setters
    void setApproach(const std::string& approach) { approach_ = approach; }
    void setTimeComplexity(ComplexityNotation complexity) { time_complexity_ = complexity; }
    void setSpaceComplexity(ComplexityNotation complexity) { space_complexity_ = complexity; }
    void setExplanation(const std::string& explanation) { explanation_ = explanation; }

    // Code implementation management
    void addCodeImplementation(const CodeImplementation& implementation);
    void removeCodeImplementation(size_t index);
    const CodeImplementation* getCodeForLanguage(ProgrammingLanguage language) const;
    bool hasLanguageImplementation(ProgrammingLanguage language) const;
    std::vector<ProgrammingLanguage> getSupportedLanguages() const;

    // Test case management
    void addTestCase(const TestCase& test_case);
    void removeTestCase(size_t index);
    size_t getTestCaseCount() const;

    /**
     * @brief Get a summary string of the solution for display purposes
     * @return Summary string containing approach, complexities, and supported languages
     */
    std::string getSummary() const;

    /**
     * @brief Validate solution data for completeness and correctness
     * @throws std::invalid_argument if validation fails
     */
    void validate() const;

private:
    std::string approach_;
    ComplexityNotation time_complexity_;
    ComplexityNotation space_complexity_;
    std::string explanation_;
    std::vector<CodeImplementation> code_implementations_;
    std::vector<TestCase> test_cases_;

    /**
     * @brief Validate required fields
     * @throws std::invalid_argument if validation fails
     */
    void validateRequiredFields() const;
};

} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_SOLUTION_H