/**
 * @file learning_path.h
 * @brief Learning path and topic-related class definitions for the LeetCode Study Guide system
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_LEARNING_PATH_H
#define LEETCODE_STUDY_GUIDE_LEARNING_PATH_H

#include "common.h"
#include "solution.h"
#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace leetcode_study_guide {

/**
 * @brief Assessment checkpoint within a learning path
 */
class Checkpoint {
public:
    /**
     * @brief Constructor for Checkpoint
     * @param description Description of the checkpoint
     */
    explicit Checkpoint(const std::string& description);

    // Getters
    const std::string& getDescription() const { return description_; }
    const std::vector<std::string>& getRequiredProblems() const { return required_problems_; }
    const std::vector<std::string>& getAssessmentCriteria() const { return assessment_criteria_; }

    // Setters
    void setDescription(const std::string& description) { description_ = description; }

    // Required problem management
    void addRequiredProblem(const std::string& problem_id);
    void removeRequiredProblem(const std::string& problem_id);

    // Assessment criteria management
    void addAssessmentCriterion(const std::string& criterion);
    void removeAssessmentCriterion(const std::string& criterion);

private:
    std::string description_;
    std::vector<std::string> required_problems_;
    std::vector<std::string> assessment_criteria_;
};

/**
 * @brief Individual topic within a learning path
 */
class Topic {
public:
    /**
     * @brief Constructor for Topic
     * @param id Unique identifier for the topic
     * @param title Topic title
     * @param theory Theoretical explanation and concepts
     */
    Topic(const std::string& id, const std::string& title, const std::string& theory);

    /**
     * @brief Destructor
     */
    ~Topic() = default;

    // Copy constructor and assignment operator
    Topic(const Topic& other);
    Topic& operator=(const Topic& other);

    // Move constructor and assignment operator
    Topic(Topic&& other) noexcept;
    Topic& operator=(Topic&& other) noexcept;

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getTitle() const { return title_; }
    const std::string& getTheory() const { return theory_; }
    const std::vector<CodeImplementation>& getImplementations() const { return implementations_; }
    const std::vector<std::string>& getPracticeProblems() const { return practice_problems_; }
    const std::vector<Checkpoint>& getCheckpoints() const { return checkpoints_; }
    std::optional<DataStructureCategory> getDataStructure() const { return data_structure_; }
    std::optional<AlgorithmPattern> getAlgorithmPattern() const { return algorithm_pattern_; }

    // Setters
    void setTitle(const std::string& title) { title_ = title; }
    void setTheory(const std::string& theory) { theory_ = theory; }
    void setDataStructure(DataStructureCategory data_structure) { data_structure_ = data_structure; }
    void setAlgorithmPattern(AlgorithmPattern algorithm_pattern) { algorithm_pattern_ = algorithm_pattern; }

    // Implementation management
    void addImplementation(const CodeImplementation& implementation);
    void removeImplementation(size_t index);

    // Practice problem management
    void addPracticeProblem(const std::string& problem_id);
    void removePracticeProblem(const std::string& problem_id);
    bool hasPracticeProblems() const;
    size_t getPracticeProblemsCount() const;

    // Checkpoint management
    void addCheckpoint(const Checkpoint& checkpoint);
    void removeCheckpoint(size_t index);
    bool hasCheckpoints() const;

    /**
     * @brief Validate topic data for completeness and correctness
     * @throws std::invalid_argument if validation fails
     */
    void validate() const;

private:
    std::string id_;
    std::string title_;
    std::string theory_;
    std::vector<CodeImplementation> implementations_;
    std::vector<std::string> practice_problems_;
    std::vector<Checkpoint> checkpoints_;
    std::optional<DataStructureCategory> data_structure_;
    std::optional<AlgorithmPattern> algorithm_pattern_;

    /**
     * @brief Validate required fields
     * @throws std::invalid_argument if validation fails
     */
    void validateRequiredFields() const;
};

/**
 * @brief Structured learning path containing multiple topics
 */
class LearningPath {
public:
    /**
     * @brief Constructor for LearningPath
     * @param id Unique identifier for the learning path
     * @param title Learning path title
     * @param description Description of what this path covers
     * @param estimated_time Estimated time to complete this path
     * @param difficulty Difficulty level of this learning path
     */
    LearningPath(const std::string& id, const std::string& title, 
                 const std::string& description, const std::string& estimated_time,
                 LearningPathDifficulty difficulty);

    /**
     * @brief Destructor
     */
    ~LearningPath() = default;

    // Copy constructor and assignment operator
    LearningPath(const LearningPath& other);
    LearningPath& operator=(const LearningPath& other);

    // Move constructor and assignment operator
    LearningPath(LearningPath&& other) noexcept;
    LearningPath& operator=(LearningPath&& other) noexcept;

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getTitle() const { return title_; }
    const std::string& getDescription() const { return description_; }
    const std::string& getEstimatedTime() const { return estimated_time_; }
    LearningPathDifficulty getDifficulty() const { return difficulty_; }
    const std::vector<std::string>& getPrerequisites() const { return prerequisites_; }
    const std::vector<std::shared_ptr<Topic>>& getTopics() const { return topics_; }

    // Setters
    void setTitle(const std::string& title) { title_ = title; }
    void setDescription(const std::string& description) { description_ = description; }
    void setEstimatedTime(const std::string& estimated_time) { estimated_time_ = estimated_time; }
    void setDifficulty(LearningPathDifficulty difficulty) { difficulty_ = difficulty; }

    // Prerequisite management
    void addPrerequisite(const std::string& prerequisite_id);
    void removePrerequisite(const std::string& prerequisite_id);
    bool hasPrerequisites() const;

    // Topic management
    void addTopic(std::shared_ptr<Topic> topic);
    void removeTopic(size_t index);
    size_t getTopicCount() const;
    std::shared_ptr<Topic> getTopicById(const std::string& topic_id) const;
    std::vector<std::shared_ptr<Topic>> getTopicsByDataStructure(DataStructureCategory data_structure) const;
    std::vector<std::shared_ptr<Topic>> getTopicsByAlgorithmPattern(AlgorithmPattern pattern) const;

    /**
     * @brief Get a summary string of the learning path for display purposes
     * @return Summary string containing title, difficulty, topic count, and estimated time
     */
    std::string getSummary() const;

    /**
     * @brief Validate learning path data for completeness and correctness
     * @throws std::invalid_argument if validation fails
     */
    void validate() const;

private:
    std::string id_;
    std::string title_;
    std::string description_;
    std::string estimated_time_;
    LearningPathDifficulty difficulty_;
    std::vector<std::string> prerequisites_;
    std::vector<std::shared_ptr<Topic>> topics_;

    /**
     * @brief Validate required fields
     * @throws std::invalid_argument if validation fails
     */
    void validateRequiredFields() const;
};

} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_LEARNING_PATH_H