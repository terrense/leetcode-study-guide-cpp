/**
 * @file problem.h
 * @brief Problem-related class definitions for the LeetCode Study Guide system
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_PROBLEM_H
#define LEETCODE_STUDY_GUIDE_PROBLEM_H

#include "common.h"
#include "solution.h"
#include <string>
#include <vector>
#include <memory>

namespace leetcode_study_guide {

/**
 * @brief Example input/output for a problem
 */
class Example {
public:
    /**
     * @brief Constructor for Example
     * @param input Input data for the example
     * @param output Expected output for the example
     * @param explanation Optional explanation of the example
     */
    Example(const std::string& input, const std::string& output, 
            const std::string& explanation = "");

    // Getters
    const std::string& getInput() const { return input_; }
    const std::string& getOutput() const { return output_; }
    const std::string& getExplanation() const { return explanation_; }

    // Setters
    void setInput(const std::string& input) { input_ = input; }
    void setOutput(const std::string& output) { output_ = output; }
    void setExplanation(const std::string& explanation) { explanation_ = explanation; }

private:
    std::string input_;
    std::string output_;
    std::string explanation_;
};

/**
 * @brief Core problem class representing a LeetCode-style problem
 */
class Problem {
public:
    /**
     * @brief Constructor for Problem
     * @param id Unique identifier for the problem
     * @param title Problem title
     * @param difficulty Difficulty level (Easy, Medium, Hard)
     * @param description Detailed problem description
     */
    Problem(const std::string& id, const std::string& title, 
            DifficultyLevel difficulty, const std::string& description);

    /**
     * @brief Destructor
     */
    ~Problem() = default;

    // Copy constructor and assignment operator
    Problem(const Problem& other);
    Problem& operator=(const Problem& other);

    // Move constructor and assignment operator
    Problem(Problem&& other) noexcept;
    Problem& operator=(Problem&& other) noexcept;

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getTitle() const { return title_; }
    DifficultyLevel getDifficulty() const { return difficulty_; }
    const std::string& getDescription() const { return description_; }
    const std::vector<DataStructureCategory>& getCategories() const { return categories_; }
    const std::vector<AlgorithmPattern>& getTags() const { return tags_; }
    const std::vector<std::string>& getConstraints() const { return constraints_; }
    const std::vector<Example>& getExamples() const { return examples_; }
    const std::vector<std::shared_ptr<Solution>>& getSolutions() const { return solutions_; }
    const std::vector<std::string>& getRelatedProblems() const { return related_problems_; }

    // Category management
    void addCategory(DataStructureCategory category);
    void removeCategory(DataStructureCategory category);
    bool hasCategory(DataStructureCategory category) const;

    // Tag management
    void addTag(AlgorithmPattern tag);
    void removeTag(AlgorithmPattern tag);
    bool hasTag(AlgorithmPattern tag) const;

    // Constraint management
    void addConstraint(const std::string& constraint);
    void removeConstraint(const std::string& constraint);

    // Example management
    void addExample(const Example& example);
    void removeExample(size_t index);

    // Solution management
    void addSolution(std::shared_ptr<Solution> solution);
    void removeSolution(size_t index);
    size_t getSolutionCount() const;

    // Related problem management
    void addRelatedProblem(const std::string& problem_id);
    void removeRelatedProblem(const std::string& problem_id);
    bool hasRelatedProblems() const;

    /**
     * @brief Get a summary string of the problem for display purposes
     * @return Summary string containing ID, title, difficulty, and categories
     */
    std::string getSummary() const;

    /**
     * @brief Validate problem data for completeness and correctness
     * @throws std::invalid_argument if validation fails
     */
    void validate() const;

private:
    std::string id_;
    std::string title_;
    DifficultyLevel difficulty_;
    std::string description_;
    std::vector<DataStructureCategory> categories_;
    std::vector<AlgorithmPattern> tags_;
    std::vector<std::string> constraints_;
    std::vector<Example> examples_;
    std::vector<std::shared_ptr<Solution>> solutions_;
    std::vector<std::string> related_problems_;

    /**
     * @brief Validate required fields
     * @throws std::invalid_argument if validation fails
     */
    void validateRequiredFields() const;
};

} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_PROBLEM_H