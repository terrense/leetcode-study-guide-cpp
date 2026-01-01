/**
 * @file array.cpp
 * @brief Implementation file for Array data structure
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/array.h"
#include <iostream>
#include <iomanip>

namespace leetcode_study_guide {
namespace data_structures {

// Explicit template instantiations for common types
template class Array<int>;
template class Array<double>;
template class Array<std::string>;

// Explicit instantiations for standalone functions
template int max_subarray_sum<int>(const std::vector<int>& arr);
template double max_subarray_sum<double>(const std::vector<double>& arr);

template void dutch_flag_partition<int>(std::vector<int>& arr, const int& pivot);
template void dutch_flag_partition<double>(std::vector<double>& arr, const double& pivot);

template void rotate_array<int>(std::vector<int>& arr, int k);
template void rotate_array<double>(std::vector<double>& arr, int k);
template void rotate_array<std::string>(std::vector<std::string>& arr, int k);

template std::vector<std::pair<int, int>> find_all_pairs_sum<int>(const std::vector<int>& arr, const int& target);
template std::vector<std::pair<int, int>> find_all_pairs_sum<double>(const std::vector<double>& arr, const double& target);

} // namespace data_structures
} // namespace leetcode_study_guide