/**
 * @file learning_path.cpp
 * @brief Implementation of learning path and topic-related classes
 */

#include "leetcode_study_guide/learning_path.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>

namespace leetcode_study_guide {

// Checkpoint implementation
Checkpoint::Checkpoint(const std::string& description) : description_(description) {
    if (description.empty()) {
        throw std::invalid_argument("Checkpoint description cannot be empty");
    }
}

void Checkpoint::addRequiredProblem(const std::string& problem_id) {
    if (!problem_id.empty() && 
        std::find(required_problems_.begin(), required_problems_.end(), problem_id) == required_problems_.end()) {
        required_problems_.push_back(problem_id);
    }
}

void Checkpoint::removeRequiredProblem(const std::string& problem_id) {
    required_problems_.erase(std::remove(required_problems_.begin(), required_problems_.end(), problem_id), 
                            required_problems_.end());
}

void Checkpoint::addAssessmentCriterion(const std::string& criterion) {
    if (!criterion.empty()) {
        assessment_criteria_.push_back(criterion);
    }
}

void Checkpoint::removeAssessmentCriterion(const std::string& criterion) {
    assessment_criteria_.erase(std::remove(assessment_criteria_.begin(), assessment_criteria_.end(), criterion), 
                              assessment_criteria_.end());
}

// Topic implementation
Topic::Topic(const std::string& id, const std::string& title, const std::string& theory)
    : id_(id), title_(title), theory_(theory) {
    validateRequiredFields();
}

Topic::Topic(const Topic& other)
    : id_(other.id_), title_(other.title_), theory_(other.theory_),
      implementations_(other.implementations_), practice_problems_(other.practice_problems_),
      checkpoints_(other.checkpoints_), data_structure_(other.data_structure_),
      algorithm_pattern_(other.algorithm_pattern_) {
}

Topic& Topic::operator=(const Topic& other) {
    if (this != &other) {
        id_ = other.id_;
        title_ = other.title_;
        theory_ = other.theory_;
        implementations_ = other.implementations_;
        practice_problems_ = other.practice_problems_;
        checkpoints_ = other.checkpoints_;
        data_structure_ = other.data_structure_;
        algorithm_pattern_ = other.algorithm_pattern_;
    }
    return *this;
}

Topic::Topic(Topic&& other) noexcept
    : id_(std::move(other.id_)), title_(std::move(other.title_)),
      theory_(std::move(other.theory_)), implementations_(std::move(other.implementations_)),
      practice_problems_(std::move(other.practice_problems_)), 
      checkpoints_(std::move(other.checkpoints_)),
      data_structure_(other.data_structure_), algorithm_pattern_(other.algorithm_pattern_) {
}

Topic& Topic::operator=(Topic&& other) noexcept {
    if (this != &other) {
        id_ = std::move(other.id_);
        title_ = std::move(other.title_);
        theory_ = std::move(other.theory_);
        implementations_ = std::move(other.implementations_);
        practice_problems_ = std::move(other.practice_problems_);
        checkpoints_ = std::move(other.checkpoints_);
        data_structure_ = other.data_structure_;
        algorithm_pattern_ = other.algorithm_pattern_;
    }
    return *this;
}

void Topic::addImplementation(const CodeImplementation& implementation) {
    implementations_.push_back(implementation);
}

void Topic::removeImplementation(size_t index) {
    if (index < implementations_.size()) {
        implementations_.erase(implementations_.begin() + index);
    }
}

void Topic::addPracticeProblem(const std::string& problem_id) {
    if (!problem_id.empty() && 
        std::find(practice_problems_.begin(), practice_problems_.end(), problem_id) == practice_problems_.end()) {
        practice_problems_.push_back(problem_id);
    }
}

void Topic::removePracticeProblem(const std::string& problem_id) {
    practice_problems_.erase(std::remove(practice_problems_.begin(), practice_problems_.end(), problem_id), 
                            practice_problems_.end());
}

bool Topic::hasPracticeProblems() const {
    return !practice_problems_.empty();
}

size_t Topic::getPracticeProblemsCount() const {
    return practice_problems_.size();
}

void Topic::addCheckpoint(const Checkpoint& checkpoint) {
    checkpoints_.push_back(checkpoint);
}

void Topic::removeCheckpoint(size_t index) {
    if (index < checkpoints_.size()) {
        checkpoints_.erase(checkpoints_.begin() + index);
    }
}

bool Topic::hasCheckpoints() const {
    return !checkpoints_.empty();
}

void Topic::validate() const {
    validateRequiredFields();
}

void Topic::validateRequiredFields() const {
    if (id_.empty()) {
        throw std::invalid_argument("Topic ID is required and cannot be empty");
    }
    
    if (title_.empty()) {
        throw std::invalid_argument("Topic title is required and cannot be empty");
    }
    
    if (theory_.empty()) {
        throw std::invalid_argument("Topic theory is required and cannot be empty");
    }
}

// LearningPath implementation
LearningPath::LearningPath(const std::string& id, const std::string& title, 
                           const std::string& description, const std::string& estimated_time,
                           LearningPathDifficulty difficulty)
    : id_(id), title_(title), description_(description), 
      estimated_time_(estimated_time), difficulty_(difficulty) {
    validateRequiredFields();
}

LearningPath::LearningPath(const LearningPath& other)
    : id_(other.id_), title_(other.title_), description_(other.description_),
      estimated_time_(other.estimated_time_), difficulty_(other.difficulty_),
      prerequisites_(other.prerequisites_) {
    
    // Deep copy topics
    topics_.reserve(other.topics_.size());
    for (const auto& topic : other.topics_) {
        topics_.push_back(std::make_shared<Topic>(*topic));
    }
}

LearningPath& LearningPath::operator=(const LearningPath& other) {
    if (this != &other) {
        id_ = other.id_;
        title_ = other.title_;
        description_ = other.description_;
        estimated_time_ = other.estimated_time_;
        difficulty_ = other.difficulty_;
        prerequisites_ = other.prerequisites_;
        
        // Deep copy topics
        topics_.clear();
        topics_.reserve(other.topics_.size());
        for (const auto& topic : other.topics_) {
            topics_.push_back(std::make_shared<Topic>(*topic));
        }
    }
    return *this;
}

LearningPath::LearningPath(LearningPath&& other) noexcept
    : id_(std::move(other.id_)), title_(std::move(other.title_)),
      description_(std::move(other.description_)), estimated_time_(std::move(other.estimated_time_)),
      difficulty_(other.difficulty_), prerequisites_(std::move(other.prerequisites_)),
      topics_(std::move(other.topics_)) {
}

LearningPath& LearningPath::operator=(LearningPath&& other) noexcept {
    if (this != &other) {
        id_ = std::move(other.id_);
        title_ = std::move(other.title_);
        description_ = std::move(other.description_);
        estimated_time_ = std::move(other.estimated_time_);
        difficulty_ = other.difficulty_;
        prerequisites_ = std::move(other.prerequisites_);
        topics_ = std::move(other.topics_);
    }
    return *this;
}

void LearningPath::addPrerequisite(const std::string& prerequisite_id) {
    if (!prerequisite_id.empty() && 
        std::find(prerequisites_.begin(), prerequisites_.end(), prerequisite_id) == prerequisites_.end()) {
        prerequisites_.push_back(prerequisite_id);
    }
}

void LearningPath::removePrerequisite(const std::string& prerequisite_id) {
    prerequisites_.erase(std::remove(prerequisites_.begin(), prerequisites_.end(), prerequisite_id), 
                        prerequisites_.end());
}

bool LearningPath::hasPrerequisites() const {
    return !prerequisites_.empty();
}

void LearningPath::addTopic(std::shared_ptr<Topic> topic) {
    if (topic) {
        topics_.push_back(topic);
    }
}

void LearningPath::removeTopic(size_t index) {
    if (index < topics_.size()) {
        topics_.erase(topics_.begin() + index);
    }
}

size_t LearningPath::getTopicCount() const {
    return topics_.size();
}

std::shared_ptr<Topic> LearningPath::getTopicById(const std::string& topic_id) const {
    auto it = std::find_if(topics_.begin(), topics_.end(),
                          [&topic_id](const std::shared_ptr<Topic>& topic) {
                              return topic && topic->getId() == topic_id;
                          });
    return (it != topics_.end()) ? *it : nullptr;
}

std::vector<std::shared_ptr<Topic>> LearningPath::getTopicsByDataStructure(DataStructureCategory data_structure) const {
    std::vector<std::shared_ptr<Topic>> result;
    
    for (const auto& topic : topics_) {
        if (topic && topic->getDataStructure() && 
            topic->getDataStructure().value() == data_structure) {
            result.push_back(topic);
        }
    }
    
    return result;
}

std::vector<std::shared_ptr<Topic>> LearningPath::getTopicsByAlgorithmPattern(AlgorithmPattern pattern) const {
    std::vector<std::shared_ptr<Topic>> result;
    
    for (const auto& topic : topics_) {
        if (topic && topic->getAlgorithmPattern() && 
            topic->getAlgorithmPattern().value() == pattern) {
            result.push_back(topic);
        }
    }
    
    return result;
}

std::string LearningPath::getSummary() const {
    std::ostringstream oss;
    oss << title_ << " (";
    
    switch (difficulty_) {
        case LearningPathDifficulty::BEGINNER: oss << "Beginner"; break;
        case LearningPathDifficulty::INTERMEDIATE: oss << "Intermediate"; break;
        case LearningPathDifficulty::ADVANCED: oss << "Advanced"; break;
    }
    
    oss << ") - " << topics_.size() << " topics, " << estimated_time_;
    
    return oss.str();
}

void LearningPath::validate() const {
    validateRequiredFields();
    
    if (topics_.empty()) {
        throw std::invalid_argument("Learning path must have at least one topic");
    }
}

void LearningPath::validateRequiredFields() const {
    if (id_.empty()) {
        throw std::invalid_argument("Learning path ID is required and cannot be empty");
    }
    
    if (title_.empty()) {
        throw std::invalid_argument("Learning path title is required and cannot be empty");
    }
    
    if (description_.empty()) {
        throw std::invalid_argument("Learning path description is required and cannot be empty");
    }
    
    if (estimated_time_.empty()) {
        throw std::invalid_argument("Learning path estimated time is required and cannot be empty");
    }
}

} // namespace leetcode_study_guide