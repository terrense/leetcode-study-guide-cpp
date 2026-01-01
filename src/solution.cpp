/**
 * @file solution.cpp
 * @brief Implementation of solution-related classes
 */

#include "leetcode_study_guide/solution.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>

namespace leetcode_study_guide {

// TestCase implementation
TestCase::TestCase(const std::any& input, const std::any& expected_output, 
                   const std::string& description)
    : input_(input), expected_output_(expected_output), description_(description) {
    if (description.empty()) {
        throw std::invalid_argument("Test case description cannot be empty");
    }
}

// CodeImplementation implementation
CodeImplementation::CodeImplementation(ProgrammingLanguage language, const std::string& code)
    : language_(language), code_(code) {
    if (code.empty()) {
        throw std::invalid_argument("Code implementation cannot be empty");
    }
}

void CodeImplementation::addComment(const std::string& comment) {
    if (!comment.empty()) {
        comments_.push_back(comment);
    }
}

void CodeImplementation::removeComment(size_t index) {
    if (index < comments_.size()) {
        comments_.erase(comments_.begin() + index);
    }
}

void CodeImplementation::clearComments() {
    comments_.clear();
}

// Solution implementation
Solution::Solution(const std::string& approach, ComplexityNotation time_complexity,
                   ComplexityNotation space_complexity, const std::string& explanation)
    : approach_(approach), time_complexity_(time_complexity), 
      space_complexity_(space_complexity), explanation_(explanation) {
    validateRequiredFields();
}

Solution::Solution(const Solution& other)
    : approach_(other.approach_), time_complexity_(other.time_complexity_),
      space_complexity_(other.space_complexity_), explanation_(other.explanation_),
      code_implementations_(other.code_implementations_), test_cases_(other.test_cases_) {
}

Solution& Solution::operator=(const Solution& other) {
    if (this != &other) {
        approach_ = other.approach_;
        time_complexity_ = other.time_complexity_;
        space_complexity_ = other.space_complexity_;
        explanation_ = other.explanation_;
        code_implementations_ = other.code_implementations_;
        test_cases_ = other.test_cases_;
    }
    return *this;
}

Solution::Solution(Solution&& other) noexcept
    : approach_(std::move(other.approach_)), time_complexity_(other.time_complexity_),
      space_complexity_(other.space_complexity_), explanation_(std::move(other.explanation_)),
      code_implementations_(std::move(other.code_implementations_)), 
      test_cases_(std::move(other.test_cases_)) {
}

Solution& Solution::operator=(Solution&& other) noexcept {
    if (this != &other) {
        approach_ = std::move(other.approach_);
        time_complexity_ = other.time_complexity_;
        space_complexity_ = other.space_complexity_;
        explanation_ = std::move(other.explanation_);
        code_implementations_ = std::move(other.code_implementations_);
        test_cases_ = std::move(other.test_cases_);
    }
    return *this;
}

void Solution::addCodeImplementation(const CodeImplementation& implementation) {
    // Check if language already exists
    for (const auto& existing : code_implementations_) {
        if (existing.getLanguage() == implementation.getLanguage()) {
            throw std::invalid_argument("Code implementation for this language already exists");
        }
    }
    code_implementations_.push_back(implementation);
}

void Solution::removeCodeImplementation(size_t index) {
    if (index < code_implementations_.size()) {
        code_implementations_.erase(code_implementations_.begin() + index);
    }
}

const CodeImplementation* Solution::getCodeForLanguage(ProgrammingLanguage language) const {
    auto it = std::find_if(code_implementations_.begin(), code_implementations_.end(),
                          [language](const CodeImplementation& impl) {
                              return impl.getLanguage() == language;
                          });
    return (it != code_implementations_.end()) ? &(*it) : nullptr;
}

bool Solution::hasLanguageImplementation(ProgrammingLanguage language) const {
    return getCodeForLanguage(language) != nullptr;
}

std::vector<ProgrammingLanguage> Solution::getSupportedLanguages() const {
    std::vector<ProgrammingLanguage> languages;
    languages.reserve(code_implementations_.size());
    
    for (const auto& impl : code_implementations_) {
        languages.push_back(impl.getLanguage());
    }
    
    return languages;
}

void Solution::addTestCase(const TestCase& test_case) {
    test_cases_.push_back(test_case);
}

void Solution::removeTestCase(size_t index) {
    if (index < test_cases_.size()) {
        test_cases_.erase(test_cases_.begin() + index);
    }
}

size_t Solution::getTestCaseCount() const {
    return test_cases_.size();
}

std::string Solution::getSummary() const {
    std::ostringstream oss;
    oss << approach_ << " - Time: " << complexityNotationToString(time_complexity_)
        << ", Space: " << complexityNotationToString(space_complexity_);
    
    if (!code_implementations_.empty()) {
        oss << " (";
        for (size_t i = 0; i < code_implementations_.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << programmingLanguageToString(code_implementations_[i].getLanguage());
        }
        oss << ")";
    }
    
    return oss.str();
}

void Solution::validate() const {
    validateRequiredFields();
    
    if (code_implementations_.empty()) {
        throw std::invalid_argument("Solution must have at least one code implementation");
    }
    
    if (test_cases_.empty()) {
        throw std::invalid_argument("Solution must have at least one test case");
    }
}

void Solution::validateRequiredFields() const {
    if (approach_.empty()) {
        throw std::invalid_argument("Solution approach is required and cannot be empty");
    }
    
    if (explanation_.empty()) {
        throw std::invalid_argument("Solution explanation is required and cannot be empty");
    }
}

} // namespace leetcode_study_guide