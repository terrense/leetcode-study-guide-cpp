/**
 * @file graph.cpp
 * @brief Implementation file for Graph data structure
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/graph.h"
#include <iostream>

namespace leetcode_study_guide {
namespace data_structures {

// Explicit template instantiations for common types

// Graph instantiations
template class Graph<int, int>;
template class Graph<int, double>;
template class Graph<std::string, int>;
template class Graph<std::string, double>;
template class Graph<char, int>;

// Edge instantiations
template struct Edge<int, int>;
template struct Edge<int, double>;
template struct Edge<std::string, int>;
template struct Edge<std::string, double>;
template struct Edge<char, int>;

// Utility function instantiations
template Graph<int, int> create_complete_graph<int, int>(const std::vector<int>& vertices, bool directed, bool weighted);
template Graph<std::string, int> create_complete_graph<std::string, int>(const std::vector<std::string>& vertices, bool directed, bool weighted);

template Graph<int, int> create_cycle_graph<int, int>(const std::vector<int>& vertices, bool directed, bool weighted);
template Graph<std::string, int> create_cycle_graph<std::string, int>(const std::vector<std::string>& vertices, bool directed, bool weighted);

template Graph<int, int> create_path_graph<int, int>(const std::vector<int>& vertices, bool directed, bool weighted);
template Graph<std::string, int> create_path_graph<std::string, int>(const std::vector<std::string>& vertices, bool directed, bool weighted);

template Graph<int, int> create_star_graph<int, int>(const int& center, const std::vector<int>& leaves, bool directed, bool weighted);
template Graph<std::string, int> create_star_graph<std::string, int>(const std::string& center, const std::vector<std::string>& leaves, bool directed, bool weighted);

} // namespace data_structures
} // namespace leetcode_study_guide