/**
 * @file leetcode_study_guide.h
 * @brief Main header file for the LeetCode Study Guide system
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_H
#define LEETCODE_STUDY_GUIDE_H

// Include all public headers
#include "common.h"
#include "problem.h"
#include "solution.h"
#include "learning_path.h"

/**
 * @namespace leetcode_study_guide
 * @brief Main namespace for the LeetCode Study Guide system
 * 
 * This namespace contains all classes and functions for the comprehensive
 * LeetCode study guide system that covers data structures, algorithms,
 * and problem-solving patterns.
 */
namespace leetcode_study_guide {

/**
 * @brief Get the version of the LeetCode Study Guide library
 * @return Version string in format "major.minor.patch"
 */
std::string getVersion();

/**
 * @brief Initialize the LeetCode Study Guide system
 * @return true if initialization successful, false otherwise
 */
bool initialize();

/**
 * @brief Cleanup the LeetCode Study Guide system
 */
void cleanup();

} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_H