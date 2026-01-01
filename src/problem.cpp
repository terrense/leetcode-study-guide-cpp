/**
 * @file problem.cpp
 * @brief Implementation of problem-related classes
 */

#include "leetcode_study_guide/problem.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>

namespace leetcode_study_guide {

// Example implementation
Example::Example(const std::string& input, const std::string& output, 
                 const std::string& explanation)
    : input_(input), output_(output), explanation_(explanation) {
    if (input.empty()) {
        throw std::invalid_argument("Example input cannot be empty");
    }
    if (output.empty()) {
        throw std::invalid_argument("Example output cannot be empty");
    }
}

// Problem implementation
Problem::Problem(const std::string& id, const std::string& title, 
                 DifficultyLevel difficulty, const std::string& description)
    : id_(id), title_(title), difficulty_(difficulty), description_(description) {
    validateRequiredFields();
}

Problem::Problem(const Problem& other)
    : id_(other.id_), title_(other.title_), difficulty_(other.difficulty_),
      description_(other.description_), categories_(other.categories_),
      tags_(other.tags_), constraints_(other.constraints_),
      examples_(other.examples_), related_problems_(other.related_problems_) {
    
    // Deep copy solutions
    solutions_.reserve(other.solutions_.size());
    for (const auto& solution : other.solutions_) {
        solutions_.push_back(std::make_shared<Solution>(*solution));
    }
}

Problem& Problem::operator=(const Problem& other) {
    if (this != &other) {
        id_ = other.id_;
        title_ = other.title_;
        difficulty_ = other.difficulty_;
        description_ = other.description_;
        categories_ = other.categories_;
        tags_ = other.tags_;
        constraints_ = other.constraints_;
        examples_ = other.examples_;
        related_problems_ = other.related_problems_;
        
        // Deep copy solutions
        solutions_.clear();
        solutions_.reserve(other.solutions_.size());
        for (const auto& solution : other.solutions_) {
            solutions_.push_back(std::make_shared<Solution>(*solution));
        }
    }
    return *this;
}

Problem::Problem(Problem&& other) noexcept
    : id_(std::move(other.id_)), title_(std::move(other.title_)),
      difficulty_(other.difficulty_), description_(std::move(other.description_)),
      categories_(std::move(other.categories_)), tags_(std::move(other.tags_)),
      constraints_(std::move(other.constraints_)), examples_(std::move(other.examples_)),
      solutions_(std::move(other.solutions_)), 
      related_problems_(std::move(other.related_problems_)) {
}

Problem& Problem::operator=(Problem&& other) noexcept {
    if (this != &other) {
        id_ = std::move(other.id_);
        title_ = std::move(other.title_);
        difficulty_ = other.difficulty_;
        description_ = std::move(other.description_);
        categories_ = std::move(other.categories_);
        tags_ = std::move(other.tags_);
        constraints_ = std::move(other.constraints_);
        examples_ = std::move(other.examples_);
        solutions_ = std::move(other.solutions_);
        related_problems_ = std::move(other.related_problems_);
    }
    return *this;
}

void Problem::addCategory(DataStructureCategory category) {
    if (std::find(categories_.begin(), categories_.end(), category) == categories_.end()) {
        categories_.push_back(category);
    }
}

void Problem::removeCategory(DataStructureCategory category) {
    categories_.erase(std::remove(categories_.begin(), categories_.end(), category), 
                     categories_.end());
}

bool Problem::hasCategory(DataStructureCategory category) const {
    return std::find(categories_.begin(), categories_.end(), category) != categories_.end();
}

void Problem::addTag(AlgorithmPattern tag) {
    if (std::find(tags_.begin(), tags_.end(), tag) == tags_.end()) {
        tags_.push_back(tag);
    }
}

void Problem::removeTag(AlgorithmPattern tag) {
    tags_.erase(std::remove(tags_.begin(), tags_.end(), tag), tags_.end());
}

bool Problem::hasTag(AlgorithmPattern tag) const {
    return std::find(tags_.begin(), tags_.end(), tag) != tags_.end();
}

void Problem::addConstraint(const std::string& constraint) {
    if (!constraint.empty()) {
        constraints_.push_back(constraint);
    }
}

void Problem::removeConstraint(const std::string& constraint) {
    constraints_.erase(std::remove(constraints_.begin(), constraints_.end(), constraint), 
                      constraints_.end());
}

void Problem::addExample(const Example& example) {
    examples_.push_back(example);
}

void Problem::removeExample(size_t index) {
    if (index < examples_.size()) {
        examples_.erase(examples_.begin() + index);
    }
}

void Problem::addSolution(std::shared_ptr<Solution> solution) {
    if (solution) {
        solutions_.push_back(solution);
    }
}

void Problem::removeSolution(size_t index) {
    if (index < solutions_.size()) {
        solutions_.erase(solutions_.begin() + index);
    }
}

size_t Problem::getSolutionCount() const {
    return solutions_.size();
}

void Problem::addRelatedProblem(const std::string& problem_id) {
    if (!problem_id.empty() && 
        std::find(related_problems_.begin(), related_problems_.end(), problem_id) == related_problems_.end()) {
        related_problems_.push_back(problem_id);
    }
}

void Problem::removeRelatedProblem(const std::string& problem_id) {
    related_problems_.erase(std::remove(related_problems_.begin(), related_problems_.end(), problem_id), 
                           related_problems_.end());
}

bool Problem::hasRelatedProblems() const {
    return !related_problems_.empty();
}

std::string Problem::getSummary() const {
    std::ostringstream oss;
    oss << id_ << ": " << title_ << " (" << difficultyLevelToString(difficulty_) << ")";
    
    if (!categories_.empty()) {
        oss << " - ";
        for (size_t i = 0; i < categories_.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << dataStructureCategoryToString(categories_[i]);
        }
    }
    
    return oss.str();
}

void Problem::validate() const {
    validateRequiredFields();
    
    if (categories_.empty()) {
        throw std::invalid_argument("Problem must have at least one category");
    }
    
    if (examples_.empty()) {
        throw std::invalid_argument("Problem must have at least one example");
    }
}

void Problem::validateRequiredFields() const {
    if (id_.empty()) {
        throw std::invalid_argument("Problem ID is required and cannot be empty");
    }
    
    if (title_.empty()) {
        throw std::invalid_argument("Problem title is required and cannot be empty");
    }
    
    if (description_.empty()) {
        throw std::invalid_argument("Problem description is required and cannot be empty");
    }
}

} // namespace leetcode_study_guide