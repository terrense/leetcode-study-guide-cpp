/**
 * @file tree_test.cpp
 * @brief Unit tests for Tree and Binary Search Tree data structures
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/tree.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace leetcode_study_guide::data_structures;

class BinaryTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a test tree:
        //       1
        //      / \
        //     2   3
        //    / \
        //   4   5
        tree.set_root(1);
        auto root = tree.get_root();
        auto left = tree.insert_left(root, 2);
        auto right = tree.insert_right(root, 3);
        tree.insert_left(left, 4);
        tree.insert_right(left, 5);
    }
    
    BinaryTree<int> tree;
};

class BinarySearchTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a BST with values: 5, 3, 7, 2, 4, 6, 8
        bst.insert(5);
        bst.insert(3);
        bst.insert(7);
        bst.insert(2);
        bst.insert(4);
        bst.insert(6);
        bst.insert(8);
    }
    
    BinarySearchTree<int> bst;
};

// Binary Tree Tests

TEST_F(BinaryTreeTest, BasicProperties) {
    EXPECT_FALSE(tree.empty());
    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.min_depth(), 2);
    EXPECT_EQ(tree.count_nodes(), 5);
}

TEST_F(BinaryTreeTest, TraversalAlgorithms) {
    // Test inorder traversal: 4, 2, 5, 1, 3
    std::vector<int> inorder = tree.inorder_traversal();
    std::vector<int> expected_inorder = {4, 2, 5, 1, 3};
    EXPECT_EQ(inorder, expected_inorder);
    
    // Test preorder traversal: 1, 2, 4, 5, 3
    std::vector<int> preorder = tree.preorder_traversal();
    std::vector<int> expected_preorder = {1, 2, 4, 5, 3};
    EXPECT_EQ(preorder, expected_preorder);
    
    // Test postorder traversal: 4, 5, 2, 3, 1
    std::vector<int> postorder = tree.postorder_traversal();
    std::vector<int> expected_postorder = {4, 5, 2, 3, 1};
    EXPECT_EQ(postorder, expected_postorder);
    
    // Test level-order traversal: 1, 2, 3, 4, 5
    std::vector<int> level_order = tree.level_order_traversal();
    std::vector<int> expected_level_order = {1, 2, 3, 4, 5};
    EXPECT_EQ(level_order, expected_level_order);
}

TEST_F(BinaryTreeTest, IterativeTraversals) {
    // Test iterative inorder
    std::vector<int> inorder_iter = tree.inorder_iterative();
    std::vector<int> inorder_rec = tree.inorder_traversal();
    EXPECT_EQ(inorder_iter, inorder_rec);
    
    // Test iterative preorder
    std::vector<int> preorder_iter = tree.preorder_iterative();
    std::vector<int> preorder_rec = tree.preorder_traversal();
    EXPECT_EQ(preorder_iter, preorder_rec);
    
    // Test iterative postorder
    std::vector<int> postorder_iter = tree.postorder_iterative();
    std::vector<int> postorder_rec = tree.postorder_traversal();
    EXPECT_EQ(postorder_iter, postorder_rec);
}

TEST_F(BinaryTreeTest, TreeProperties) {
    // Test balanced check
    EXPECT_TRUE(tree.is_balanced());
    
    // Test symmetric check (this tree is not symmetric)
    EXPECT_FALSE(tree.is_symmetric());
    
    // Create symmetric tree
    BinaryTree<int> symmetric_tree;
    symmetric_tree.set_root(1);
    auto root = symmetric_tree.get_root();
    auto left = symmetric_tree.insert_left(root, 2);
    auto right = symmetric_tree.insert_right(root, 2);
    symmetric_tree.insert_left(left, 3);
    symmetric_tree.insert_right(left, 4);
    symmetric_tree.insert_left(right, 4);
    symmetric_tree.insert_right(right, 3);
    
    EXPECT_TRUE(symmetric_tree.is_symmetric());
}

TEST_F(BinaryTreeTest, SearchAndPath) {
    // Test find
    auto node = tree.find(4);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->data, 4);
    
    auto not_found = tree.find(10);
    EXPECT_EQ(not_found, nullptr);
    
    // Test find path
    std::vector<int> path = tree.find_path(5);
    std::vector<int> expected_path = {1, 2, 5};
    EXPECT_EQ(path, expected_path);
    
    // Test LCA
    auto lca = tree.lowest_common_ancestor(4, 5);
    EXPECT_NE(lca, nullptr);
    EXPECT_EQ(lca->data, 2);
}

TEST_F(BinaryTreeTest, BuildFromArray) {
    BinaryTree<int> array_tree;
    std::vector<int> values = {1, 2, 3, -1, -1, 4, 5}; // -1 represents null
    array_tree.build_from_array(values, -1);
    
    EXPECT_FALSE(array_tree.empty());
    EXPECT_EQ(array_tree.get_root()->data, 1);
}

// Binary Search Tree Tests

TEST_F(BinarySearchTreeTest, BasicOperations) {
    EXPECT_FALSE(bst.empty());
    EXPECT_EQ(bst.size(), 7);
    
    // Test search
    EXPECT_TRUE(bst.search(5));
    EXPECT_TRUE(bst.search(3));
    EXPECT_TRUE(bst.search(7));
    EXPECT_FALSE(bst.search(10));
    
    // Test insert duplicate
    EXPECT_FALSE(bst.insert(5)); // Should not insert duplicate
    EXPECT_EQ(bst.size(), 7);
}

TEST_F(BinarySearchTreeTest, MinMaxOperations) {
    EXPECT_EQ(bst.find_min(), 2);
    EXPECT_EQ(bst.find_max(), 8);
    
    // Test on empty tree
    BinarySearchTree<int> empty_bst;
    EXPECT_THROW(empty_bst.find_min(), std::runtime_error);
    EXPECT_THROW(empty_bst.find_max(), std::runtime_error);
}

TEST_F(BinarySearchTreeTest, SuccessorPredecessor) {
    EXPECT_EQ(bst.find_successor(3), 4);
    EXPECT_EQ(bst.find_successor(5), 6);
    EXPECT_THROW(bst.find_successor(8), std::runtime_error); // No successor for max
    
    EXPECT_EQ(bst.find_predecessor(4), 3);
    EXPECT_EQ(bst.find_predecessor(6), 5);
    EXPECT_THROW(bst.find_predecessor(2), std::runtime_error); // No predecessor for min
}

TEST_F(BinarySearchTreeTest, RemoveOperations) {
    // Remove leaf node
    EXPECT_TRUE(bst.remove(2));
    EXPECT_FALSE(bst.search(2));
    EXPECT_EQ(bst.size(), 6);
    
    // Remove node with one child
    EXPECT_TRUE(bst.remove(3));
    EXPECT_FALSE(bst.search(3));
    EXPECT_EQ(bst.size(), 5);
    
    // Remove node with two children
    EXPECT_TRUE(bst.remove(5));
    EXPECT_FALSE(bst.search(5));
    EXPECT_EQ(bst.size(), 4);
    
    // Try to remove non-existent node
    EXPECT_FALSE(bst.remove(10));
    EXPECT_EQ(bst.size(), 4);
}

TEST_F(BinarySearchTreeTest, ValidationAndProperties) {
    EXPECT_TRUE(bst.is_valid_bst());
    
    // Test sorted array conversion
    std::vector<int> sorted = bst.to_sorted_array();
    std::vector<int> expected = {2, 3, 4, 5, 6, 7, 8};
    EXPECT_EQ(sorted, expected);
    
    // Test kth smallest/largest
    EXPECT_EQ(bst.kth_smallest(1), 2);
    EXPECT_EQ(bst.kth_smallest(4), 5);
    EXPECT_EQ(bst.kth_largest(1), 8);
    EXPECT_EQ(bst.kth_largest(3), 6);
    
    EXPECT_THROW(bst.kth_smallest(0), std::out_of_range);
    EXPECT_THROW(bst.kth_smallest(10), std::out_of_range);
}

TEST_F(BinarySearchTreeTest, BalancingConcepts) {
    // Test balance factor calculation
    auto root = bst.get_root();
    int bf = bst.balance_factor(root);
    EXPECT_GE(bf, -1);
    EXPECT_LE(bf, 1);
    
    // Test rotation operations
    auto rotated_right = bst.rotate_right(root);
    EXPECT_NE(rotated_right, nullptr);
    
    auto rotated_left = bst.rotate_left(root);
    EXPECT_NE(rotated_left, nullptr);
}

TEST_F(BinarySearchTreeTest, ConstructFromSortedArray) {
    std::vector<int> sorted_array = {1, 2, 3, 4, 5, 6, 7};
    BinarySearchTree<int> balanced_bst(sorted_array);
    
    EXPECT_EQ(balanced_bst.size(), 7);
    EXPECT_TRUE(balanced_bst.is_valid_bst());
    EXPECT_TRUE(balanced_bst.is_balanced());
    
    // Root should be middle element for balanced tree
    EXPECT_EQ(balanced_bst.get_root()->data, 4);
}

// Standalone Utility Function Tests

TEST(TreeUtilityTest, IdenticalTrees) {
    BinaryTree<int> tree1, tree2;
    
    // Both empty
    EXPECT_TRUE(are_identical(tree1, tree2));
    
    // Same structure and values
    tree1.set_root(1);
    tree2.set_root(1);
    auto root1 = tree1.get_root();
    auto root2 = tree2.get_root();
    tree1.insert_left(root1, 2);
    tree2.insert_left(root2, 2);
    tree1.insert_right(root1, 3);
    tree2.insert_right(root2, 3);
    
    EXPECT_TRUE(are_identical(tree1, tree2));
    
    // Different values
    BinaryTree<int> tree3;
    tree3.set_root(1);
    auto root3 = tree3.get_root();
    tree3.insert_left(root3, 2);
    tree3.insert_right(root3, 4); // Different value
    
    EXPECT_FALSE(are_identical(tree1, tree3));
}

TEST(TreeUtilityTest, TreeDiameter) {
    BinaryTree<int> tree;
    tree.set_root(1);
    auto root = tree.get_root();
    auto left = tree.insert_left(root, 2);
    auto right = tree.insert_right(root, 3);
    tree.insert_left(left, 4);
    tree.insert_right(left, 5);
    
    int diameter = tree_diameter(tree);
    EXPECT_EQ(diameter, 3); // Path: 4 -> 2 -> 1 -> 3 or 5 -> 2 -> 1 -> 3
}

TEST(TreeUtilityTest, SerializationDeserialization) {
    BinaryTree<int> original;
    original.set_root(1);
    auto root = original.get_root();
    original.insert_left(root, 2);
    original.insert_right(root, 3);
    
    std::string serialized = serialize_tree(original);
    EXPECT_FALSE(serialized.empty());
    
    // Note: Full deserialization test would require more complex implementation
    // This is a basic test to ensure the function doesn't crash
    BinaryTree<int> deserialized = deserialize_tree<int>(serialized);
    // Basic check that deserialization doesn't crash
}

// Edge Cases and Error Handling

TEST(TreeEdgeCasesTest, EmptyTreeOperations) {
    BinaryTree<int> empty_tree;
    
    EXPECT_TRUE(empty_tree.empty());
    EXPECT_EQ(empty_tree.size(), 0);
    EXPECT_EQ(empty_tree.height(), 0);
    EXPECT_EQ(empty_tree.count_nodes(), 0);
    
    // Traversals on empty tree
    EXPECT_TRUE(empty_tree.inorder_traversal().empty());
    EXPECT_TRUE(empty_tree.preorder_traversal().empty());
    EXPECT_TRUE(empty_tree.postorder_traversal().empty());
    EXPECT_TRUE(empty_tree.level_order_traversal().empty());
}

TEST(TreeEdgeCasesTest, SingleNodeTree) {
    BinaryTree<int> single_tree;
    single_tree.set_root(42);
    
    EXPECT_FALSE(single_tree.empty());
    EXPECT_EQ(single_tree.size(), 1);
    EXPECT_EQ(single_tree.height(), 1);
    EXPECT_EQ(single_tree.count_nodes(), 1);
    
    // All traversals should return single element
    std::vector<int> expected = {42};
    EXPECT_EQ(single_tree.inorder_traversal(), expected);
    EXPECT_EQ(single_tree.preorder_traversal(), expected);
    EXPECT_EQ(single_tree.postorder_traversal(), expected);
    EXPECT_EQ(single_tree.level_order_traversal(), expected);
}

TEST(BSTEdgeCasesTest, InvalidOperations) {
    BinarySearchTree<int> bst;
    
    // Operations on empty BST
    EXPECT_FALSE(bst.search(5));
    EXPECT_FALSE(bst.remove(5));
    EXPECT_THROW(bst.find_min(), std::runtime_error);
    EXPECT_THROW(bst.find_max(), std::runtime_error);
    
    // Insert and test single element
    EXPECT_TRUE(bst.insert(5));
    EXPECT_EQ(bst.find_min(), 5);
    EXPECT_EQ(bst.find_max(), 5);
    EXPECT_THROW(bst.find_successor(5), std::runtime_error);
    EXPECT_THROW(bst.find_predecessor(5), std::runtime_error);
}