/**
 * @file tree.h
 * @brief Tree and Binary Search Tree implementations for the LeetCode Study Guide
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_TREE_H
#define LEETCODE_STUDY_GUIDE_TREE_H

#include "../common.h"
#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <iostream>

namespace leetcode_study_guide {
namespace data_structures {

/**
 * @brief Binary Tree Node structure
 */
template<typename T>
struct TreeNode {
    T data;
    std::shared_ptr<TreeNode<T>> left;
    std::shared_ptr<TreeNode<T>> right;
    
    /**
     * @brief Constructor for TreeNode
     * @param value Value to store in the node
     */
    explicit TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
    
    /**
     * @brief Constructor with child nodes
     * @param value Value to store in the node
     * @param left_child Left child node
     * @param right_child Right child node
     */
    TreeNode(const T& value, 
             std::shared_ptr<TreeNode<T>> left_child, 
             std::shared_ptr<TreeNode<T>> right_child)
        : data(value), left(left_child), right(right_child) {}
};

/**
 * @brief Binary Tree implementation with traversal algorithms
 * 
 * This class provides a comprehensive implementation of binary tree operations
 * commonly used in LeetCode problems, including all traversal methods and
 * tree manipulation algorithms.
 */
template<typename T>
class BinaryTree {
public:
    using NodePtr = std::shared_ptr<TreeNode<T>>;
    
    /**
     * @brief Default constructor
     */
    BinaryTree() : root_(nullptr), size_(0) {}
    
    /**
     * @brief Constructor with root value
     * @param root_value Value for the root node
     */
    explicit BinaryTree(const T& root_value) 
        : root_(std::make_shared<TreeNode<T>>(root_value)), size_(1) {}
    
    /**
     * @brief Destructor
     */
    virtual ~BinaryTree() = default;
    
    // Tree Construction and Modification
    
    /**
     * @brief Set the root of the tree
     * @param value Value for the root node
     */
    void set_root(const T& value);
    
    /**
     * @brief Insert node as left child of given node
     * @param parent Parent node
     * @param value Value for new node
     * @return Pointer to newly created node
     */
    NodePtr insert_left(NodePtr parent, const T& value);
    
    /**
     * @brief Insert node as right child of given node
     * @param parent Parent node
     * @param value Value for new node
     * @return Pointer to newly created node
     */
    NodePtr insert_right(NodePtr parent, const T& value);
    
    /**
     * @brief Build tree from level-order array (LeetCode format)
     * @param values Vector of values in level-order, nullptr represented as default T{}
     * @param null_value Value representing null nodes
     */
    void build_from_array(const std::vector<T>& values, const T& null_value);
    
    // Tree Traversal Algorithms
    
    /**
     * @brief Inorder traversal (Left, Root, Right)
     * @return Vector of values in inorder sequence
     * Time Complexity: O(n)
     * Space Complexity: O(h) where h is height
     */
    std::vector<T> inorder_traversal() const;
    
    /**
     * @brief Preorder traversal (Root, Left, Right)
     * @return Vector of values in preorder sequence
     * Time Complexity: O(n)
     * Space Complexity: O(h) where h is height
     */
    std::vector<T> preorder_traversal() const;
    
    /**
     * @brief Postorder traversal (Left, Right, Root)
     * @return Vector of values in postorder sequence
     * Time Complexity: O(n)
     * Space Complexity: O(h) where h is height
     */
    std::vector<T> postorder_traversal() const;
    
    /**
     * @brief Level-order traversal (BFS)
     * @return Vector of values in level-order sequence
     * Time Complexity: O(n)
     * Space Complexity: O(w) where w is maximum width
     */
    std::vector<T> level_order_traversal() const;
    
    /**
     * @brief Iterative inorder traversal
     * @return Vector of values in inorder sequence
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> inorder_iterative() const;
    
    /**
     * @brief Iterative preorder traversal
     * @return Vector of values in preorder sequence
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> preorder_iterative() const;
    
    /**
     * @brief Iterative postorder traversal
     * @return Vector of values in postorder sequence
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> postorder_iterative() const;
    
    // Tree Properties and Analysis
    
    /**
     * @brief Calculate height of the tree
     * @return Height of the tree (0 for empty tree)
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    int height() const;
    
    /**
     * @brief Calculate maximum depth of the tree
     * @return Maximum depth (same as height)
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    int max_depth() const { return height(); }
    
    /**
     * @brief Calculate minimum depth of the tree
     * @return Minimum depth to a leaf node
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    int min_depth() const;
    
    /**
     * @brief Check if tree is balanced
     * @return True if tree is height-balanced
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    bool is_balanced() const;
    
    /**
     * @brief Check if tree is symmetric
     * @return True if tree is symmetric around its center
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    bool is_symmetric() const;
    
    /**
     * @brief Count total number of nodes
     * @return Number of nodes in the tree
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    size_t count_nodes() const;
    
    // Tree Search and Path Operations
    
    /**
     * @brief Find node with given value
     * @param value Value to search for
     * @return Pointer to node if found, nullptr otherwise
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    NodePtr find(const T& value) const;
    
    /**
     * @brief Find path from root to target value
     * @param target Target value
     * @return Vector representing path from root to target
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    std::vector<T> find_path(const T& target) const;
    
    /**
     * @brief Find lowest common ancestor of two values
     * @param val1 First value
     * @param val2 Second value
     * @return Pointer to LCA node, nullptr if not found
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    NodePtr lowest_common_ancestor(const T& val1, const T& val2) const;
    
    // Utility Methods
    
    /**
     * @brief Get root node
     * @return Pointer to root node
     */
    NodePtr get_root() const { return root_; }
    
    /**
     * @brief Check if tree is empty
     * @return True if tree is empty
     */
    bool empty() const { return root_ == nullptr; }
    
    /**
     * @brief Get size of tree
     * @return Number of nodes in tree
     */
    size_t size() const { return size_; }
    
    /**
     * @brief Clear the tree
     */
    void clear();
    
    /**
     * @brief Print tree structure (for debugging)
     */
    void print_tree() const;

protected:
    NodePtr root_;
    size_t size_;
    
    // Helper methods for recursive operations
    void inorder_helper(NodePtr node, std::vector<T>& result) const;
    void preorder_helper(NodePtr node, std::vector<T>& result) const;
    void postorder_helper(NodePtr node, std::vector<T>& result) const;
    int height_helper(NodePtr node) const;
    int min_depth_helper(NodePtr node) const;
    bool is_balanced_helper(NodePtr node, int& height) const;
    bool is_symmetric_helper(NodePtr left, NodePtr right) const;
    size_t count_nodes_helper(NodePtr node) const;
    NodePtr find_helper(NodePtr node, const T& value) const;
    bool find_path_helper(NodePtr node, const T& target, std::vector<T>& path) const;
    NodePtr lca_helper(NodePtr node, const T& val1, const T& val2) const;
    void print_tree_helper(NodePtr node, const std::string& prefix, bool is_last) const;
};

/**
 * @brief Binary Search Tree implementation
 * 
 * This class extends BinaryTree with BST-specific operations including
 * search, insert, delete, and validation. Maintains BST property where
 * left subtree values < root < right subtree values.
 */
template<typename T>
class BinarySearchTree : public BinaryTree<T> {
public:
    using NodePtr = std::shared_ptr<TreeNode<T>>;
    using BinaryTree<T>::root_;
    using BinaryTree<T>::size_;
    
    /**
     * @brief Default constructor
     */
    BinarySearchTree() : BinaryTree<T>() {}
    
    /**
     * @brief Constructor with root value
     * @param root_value Value for the root node
     */
    explicit BinarySearchTree(const T& root_value) : BinaryTree<T>(root_value) {}
    
    /**
     * @brief Constructor from sorted array
     * @param sorted_array Sorted array to build BST from
     */
    explicit BinarySearchTree(const std::vector<T>& sorted_array);
    
    // BST Operations
    
    /**
     * @brief Insert value into BST
     * @param value Value to insert
     * @return True if inserted, false if already exists
     * Time Complexity: O(h) where h is height
     * Space Complexity: O(h) for recursion
     */
    bool insert(const T& value);
    
    /**
     * @brief Search for value in BST
     * @param value Value to search for
     * @return True if found, false otherwise
     * Time Complexity: O(h) where h is height
     * Space Complexity: O(h) for recursion
     */
    bool search(const T& value) const;
    
    /**
     * @brief Delete value from BST
     * @param value Value to delete
     * @return True if deleted, false if not found
     * Time Complexity: O(h) where h is height
     * Space Complexity: O(h) for recursion
     */
    bool remove(const T& value);
    
    /**
     * @brief Find minimum value in BST
     * @return Minimum value
     * @throws std::runtime_error if tree is empty
     * Time Complexity: O(h)
     * Space Complexity: O(1)
     */
    T find_min() const;
    
    /**
     * @brief Find maximum value in BST
     * @return Maximum value
     * @throws std::runtime_error if tree is empty
     * Time Complexity: O(h)
     * Space Complexity: O(1)
     */
    T find_max() const;
    
    /**
     * @brief Find inorder successor of given value
     * @param value Value to find successor for
     * @return Successor value
     * @throws std::runtime_error if no successor exists
     * Time Complexity: O(h)
     * Space Complexity: O(h)
     */
    T find_successor(const T& value) const;
    
    /**
     * @brief Find inorder predecessor of given value
     * @param value Value to find predecessor for
     * @return Predecessor value
     * @throws std::runtime_error if no predecessor exists
     * Time Complexity: O(h)
     * Space Complexity: O(h)
     */
    T find_predecessor(const T& value) const;
    
    // BST Validation and Properties
    
    /**
     * @brief Validate if tree maintains BST property
     * @return True if valid BST, false otherwise
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    bool is_valid_bst() const;
    
    /**
     * @brief Get sorted array from BST (inorder traversal)
     * @return Sorted vector of all values
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    std::vector<T> to_sorted_array() const;
    
    /**
     * @brief Find kth smallest element (1-indexed)
     * @param k Position (1-indexed)
     * @return kth smallest element
     * @throws std::out_of_range if k is invalid
     * Time Complexity: O(h + k)
     * Space Complexity: O(h)
     */
    T kth_smallest(int k) const;
    
    /**
     * @brief Find kth largest element (1-indexed)
     * @param k Position (1-indexed)
     * @return kth largest element
     * @throws std::out_of_range if k is invalid
     * Time Complexity: O(h + k)
     * Space Complexity: O(h)
     */
    T kth_largest(int k) const;
    
    // Tree Balancing (Basic AVL concepts)
    
    /**
     * @brief Calculate balance factor of a node
     * @param node Node to calculate balance factor for
     * @return Balance factor (height of left - height of right)
     * Time Complexity: O(h)
     * Space Complexity: O(h)
     */
    int balance_factor(NodePtr node) const;
    
    /**
     * @brief Check if tree needs rebalancing (AVL property)
     * @return True if any node has balance factor > 1 or < -1
     * Time Complexity: O(n)
     * Space Complexity: O(h)
     */
    bool needs_rebalancing() const;
    
    /**
     * @brief Perform right rotation (for AVL balancing)
     * @param node Root of subtree to rotate
     * @return New root after rotation
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    NodePtr rotate_right(NodePtr node);
    
    /**
     * @brief Perform left rotation (for AVL balancing)
     * @param node Root of subtree to rotate
     * @return New root after rotation
     * Time Complexity: O(1)
     * Space Complexity: O(1)
     */
    NodePtr rotate_left(NodePtr node);

private:
    // Helper methods for BST operations
    NodePtr insert_helper(NodePtr node, const T& value, bool& inserted);
    bool search_helper(NodePtr node, const T& value) const;
    NodePtr remove_helper(NodePtr node, const T& value, bool& removed);
    NodePtr find_min_node(NodePtr node) const;
    NodePtr find_max_node(NodePtr node) const;
    bool is_valid_bst_helper(NodePtr node, const T* min_val, const T* max_val) const;
    bool kth_smallest_helper(NodePtr node, int& k, T& result) const;
    bool kth_largest_helper(NodePtr node, int& k, T& result) const;
    int balance_factor_helper(NodePtr node) const;
    bool needs_rebalancing_helper(NodePtr node) const;
    NodePtr build_balanced_bst(const std::vector<T>& sorted_array, int start, int end);
};

// Standalone Tree Utility Functions

/**
 * @brief Check if two trees are identical
 * @param tree1 First tree
 * @param tree2 Second tree
 * @return True if trees are structurally identical with same values
 * Time Complexity: O(min(n1, n2))
 * Space Complexity: O(min(h1, h2))
 */
template<typename T>
bool are_identical(const BinaryTree<T>& tree1, const BinaryTree<T>& tree2);

/**
 * @brief Serialize tree to string (preorder with null markers)
 * @param tree Tree to serialize
 * @param null_marker String to represent null nodes
 * @return Serialized string representation
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
template<typename T>
std::string serialize_tree(const BinaryTree<T>& tree, const std::string& null_marker = "null");

/**
 * @brief Deserialize string to tree
 * @param data Serialized string data
 * @param null_marker String representing null nodes
 * @return Reconstructed tree
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
template<typename T>
BinaryTree<T> deserialize_tree(const std::string& data, const std::string& null_marker = "null");

/**
 * @brief Find diameter of binary tree (longest path between any two nodes)
 * @param tree Tree to analyze
 * @return Length of diameter
 * Time Complexity: O(n)
 * Space Complexity: O(h)
 */
template<typename T>
int tree_diameter(const BinaryTree<T>& tree);

} // namespace data_structures
} // namespace leetcode_study_guide

// Include template implementation
#include "tree.tpp"

#endif // LEETCODE_STUDY_GUIDE_TREE_H