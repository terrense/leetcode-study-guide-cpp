/**
 * @file tree.cpp
 * @brief Implementation file for Tree and Binary Search Tree data structures
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/tree.h"
#include <iostream>
#include <iomanip>

namespace leetcode_study_guide {
namespace data_structures {

// Explicit template instantiations for common types

// BinaryTree instantiations
template class BinaryTree<int>;
template class BinaryTree<double>;
template class BinaryTree<std::string>;
template class BinaryTree<char>;

// BinarySearchTree instantiations
template class BinarySearchTree<int>;
template class BinarySearchTree<double>;
template class BinarySearchTree<std::string>;
template class BinarySearchTree<char>;

// TreeNode instantiations
template struct TreeNode<int>;
template struct TreeNode<double>;
template struct TreeNode<std::string>;
template struct TreeNode<char>;

// Standalone utility function instantiations
template bool are_identical<int>(const BinaryTree<int>& tree1, const BinaryTree<int>& tree2);
template bool are_identical<double>(const BinaryTree<double>& tree1, const BinaryTree<double>& tree2);
template bool are_identical<std::string>(const BinaryTree<std::string>& tree1, const BinaryTree<std::string>& tree2);

template std::string serialize_tree<int>(const BinaryTree<int>& tree, const std::string& null_marker);
template std::string serialize_tree<double>(const BinaryTree<double>& tree, const std::string& null_marker);
template std::string serialize_tree<std::string>(const BinaryTree<std::string>& tree, const std::string& null_marker);

template BinaryTree<int> deserialize_tree<int>(const std::string& data, const std::string& null_marker);
template BinaryTree<double> deserialize_tree<double>(const std::string& data, const std::string& null_marker);
template BinaryTree<std::string> deserialize_tree<std::string>(const std::string& data, const std::string& null_marker);

template int tree_diameter<int>(const BinaryTree<int>& tree);
template int tree_diameter<double>(const BinaryTree<double>& tree);
template int tree_diameter<std::string>(const BinaryTree<std::string>& tree);

} // namespace data_structures
} // namespace leetcode_study_guide