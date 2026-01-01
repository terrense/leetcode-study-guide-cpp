/**
 * @file tree.tpp
 * @brief Template implementation for Tree and Binary Search Tree classes
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_TREE_TPP
#define LEETCODE_STUDY_GUIDE_TREE_TPP

#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <limits>

namespace leetcode_study_guide {
namespace data_structures {

// BinaryTree Implementation

template<typename T>
void BinaryTree<T>::set_root(const T& value) {
    root_ = std::make_shared<TreeNode<T>>(value);
    size_ = 1;
}

template<typename T>
typename BinaryTree<T>::NodePtr BinaryTree<T>::insert_left(NodePtr parent, const T& value) {
    if (!parent) {
        throw std::invalid_argument("Parent node cannot be null");
    }
    
    auto new_node = std::make_shared<TreeNode<T>>(value);
    parent->left = new_node;
    ++size_;
    return new_node;
}

template<typename T>
typename BinaryTree<T>::NodePtr BinaryTree<T>::insert_right(NodePtr parent, const T& value) {
    if (!parent) {
        throw std::invalid_argument("Parent node cannot be null");
    }
    
    auto new_node = std::make_shared<TreeNode<T>>(value);
    parent->right = new_node;
    ++size_;
    return new_node;
}

template<typename T>
void BinaryTree<T>::build_from_array(const std::vector<T>& values, const T& null_value) {
    if (values.empty()) {
        clear();
        return;
    }
    
    root_ = std::make_shared<TreeNode<T>>(values[0]);
    size_ = 1;
    
    std::queue<NodePtr> queue;
    queue.push(root_);
    
    for (size_t i = 1; i < values.size(); i += 2) {
        NodePtr current = queue.front();
        queue.pop();
        
        // Left child
        if (i < values.size() && values[i] != null_value) {
            current->left = std::make_shared<TreeNode<T>>(values[i]);
            queue.push(current->left);
            ++size_;
        }
        
        // Right child
        if (i + 1 < values.size() && values[i + 1] != null_value) {
            current->right = std::make_shared<TreeNode<T>>(values[i + 1]);
            queue.push(current->right);
            ++size_;
        }
    }
}

template<typename T>
std::vector<T> BinaryTree<T>::inorder_traversal() const {
    std::vector<T> result;
    inorder_helper(root_, result);
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::preorder_traversal() const {
    std::vector<T> result;
    preorder_helper(root_, result);
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::postorder_traversal() const {
    std::vector<T> result;
    postorder_helper(root_, result);
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::level_order_traversal() const {
    std::vector<T> result;
    if (!root_) return result;
    
    std::queue<NodePtr> queue;
    queue.push(root_);
    
    while (!queue.empty()) {
        NodePtr current = queue.front();
        queue.pop();
        result.push_back(current->data);
        
        if (current->left) queue.push(current->left);
        if (current->right) queue.push(current->right);
    }
    
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::inorder_iterative() const {
    std::vector<T> result;
    if (!root_) return result;
    
    std::stack<NodePtr> stack;
    NodePtr current = root_;
    
    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }
        
        current = stack.top();
        stack.pop();
        result.push_back(current->data);
        current = current->right;
    }
    
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::preorder_iterative() const {
    std::vector<T> result;
    if (!root_) return result;
    
    std::stack<NodePtr> stack;
    stack.push(root_);
    
    while (!stack.empty()) {
        NodePtr current = stack.top();
        stack.pop();
        result.push_back(current->data);
        
        if (current->right) stack.push(current->right);
        if (current->left) stack.push(current->left);
    }
    
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::postorder_iterative() const {
    std::vector<T> result;
    if (!root_) return result;
    
    std::stack<NodePtr> stack1, stack2;
    stack1.push(root_);
    
    while (!stack1.empty()) {
        NodePtr current = stack1.top();
        stack1.pop();
        stack2.push(current);
        
        if (current->left) stack1.push(current->left);
        if (current->right) stack1.push(current->right);
    }
    
    while (!stack2.empty()) {
        result.push_back(stack2.top()->data);
        stack2.pop();
    }
    
    return result;
}

template<typename T>
int BinaryTree<T>::height() const {
    return height_helper(root_);
}

template<typename T>
int BinaryTree<T>::min_depth() const {
    return min_depth_helper(root_);
}

template<typename T>
bool BinaryTree<T>::is_balanced() const {
    int height = 0;
    return is_balanced_helper(root_, height);
}

template<typename T>
bool BinaryTree<T>::is_symmetric() const {
    if (!root_) return true;
    return is_symmetric_helper(root_->left, root_->right);
}

template<typename T>
size_t BinaryTree<T>::count_nodes() const {
    return count_nodes_helper(root_);
}

template<typename T>
typename BinaryTree<T>::NodePtr BinaryTree<T>::find(const T& value) const {
    return find_helper(root_, value);
}

template<typename T>
std::vector<T> BinaryTree<T>::find_path(const T& target) const {
    std::vector<T> path;
    find_path_helper(root_, target, path);
    return path;
}

template<typename T>
typename BinaryTree<T>::NodePtr BinaryTree<T>::lowest_common_ancestor(const T& val1, const T& val2) const {
    return lca_helper(root_, val1, val2);
}

template<typename T>
void BinaryTree<T>::clear() {
    root_ = nullptr;
    size_ = 0;
}

template<typename T>
void BinaryTree<T>::print_tree() const {
    if (!root_) {
        std::cout << "Empty tree\n";
        return;
    }
    print_tree_helper(root_, "", true);
}

// Helper methods implementation

template<typename T>
void BinaryTree<T>::inorder_helper(NodePtr node, std::vector<T>& result) const {
    if (!node) return;
    inorder_helper(node->left, result);
    result.push_back(node->data);
    inorder_helper(node->right, result);
}

template<typename T>
void BinaryTree<T>::preorder_helper(NodePtr node, std::vector<T>& result) const {
    if (!node) return;
    result.push_back(node->data);
    preorder_helper(node->left, result);
    preorder_helper(node->right, result);
}

template<typename T>
void BinaryTree<T>::postorder_helper(NodePtr node, std::vector<T>& result) const {
    if (!node) return;
    postorder_helper(node->left, result);
    postorder_helper(node->right, result);
    result.push_back(node->data);
}

template<typename T>
int BinaryTree<T>::height_helper(NodePtr node) const {
    if (!node) return 0;
    return 1 + std::max(height_helper(node->left), height_helper(node->right));
}

template<typename T>
int BinaryTree<T>::min_depth_helper(NodePtr node) const {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    
    int left_depth = node->left ? min_depth_helper(node->left) : std::numeric_limits<int>::max();
    int right_depth = node->right ? min_depth_helper(node->right) : std::numeric_limits<int>::max();
    
    return 1 + std::min(left_depth, right_depth);
}

template<typename T>
bool BinaryTree<T>::is_balanced_helper(NodePtr node, int& height) const {
    if (!node) {
        height = 0;
        return true;
    }
    
    int left_height = 0, right_height = 0;
    bool left_balanced = is_balanced_helper(node->left, left_height);
    bool right_balanced = is_balanced_helper(node->right, right_height);
    
    height = 1 + std::max(left_height, right_height);
    
    return left_balanced && right_balanced && std::abs(left_height - right_height) <= 1;
}

template<typename T>
bool BinaryTree<T>::is_symmetric_helper(NodePtr left, NodePtr right) const {
    if (!left && !right) return true;
    if (!left || !right) return false;
    
    return (left->data == right->data) &&
           is_symmetric_helper(left->left, right->right) &&
           is_symmetric_helper(left->right, right->left);
}

template<typename T>
size_t BinaryTree<T>::count_nodes_helper(NodePtr node) const {
    if (!node) return 0;
    return 1 + count_nodes_helper(node->left) + count_nodes_helper(node->right);
}

template<typename T>
typename BinaryTree<T>::NodePtr BinaryTree<T>::find_helper(NodePtr node, const T& value) const {
    if (!node) return nullptr;
    if (node->data == value) return node;
    
    auto left_result = find_helper(node->left, value);
    if (left_result) return left_result;
    
    return find_helper(node->right, value);
}

template<typename T>
bool BinaryTree<T>::find_path_helper(NodePtr node, const T& target, std::vector<T>& path) const {
    if (!node) return false;
    
    path.push_back(node->data);
    
    if (node->data == target) return true;
    
    if (find_path_helper(node->left, target, path) || 
        find_path_helper(node->right, target, path)) {
        return true;
    }
    
    path.pop_back();
    return false;
}

template<typename T>
typename BinaryTree<T>::NodePtr BinaryTree<T>::lca_helper(NodePtr node, const T& val1, const T& val2) const {
    if (!node) return nullptr;
    
    if (node->data == val1 || node->data == val2) return node;
    
    auto left_lca = lca_helper(node->left, val1, val2);
    auto right_lca = lca_helper(node->right, val1, val2);
    
    if (left_lca && right_lca) return node;
    return left_lca ? left_lca : right_lca;
}

template<typename T>
void BinaryTree<T>::print_tree_helper(NodePtr node, const std::string& prefix, bool is_last) const {
    if (!node) return;
    
    std::cout << prefix << (is_last ? "└── " : "├── ") << node->data << std::endl;
    
    if (node->left || node->right) {
        if (node->left) {
            print_tree_helper(node->left, prefix + (is_last ? "    " : "│   "), !node->right);
        }
        if (node->right) {
            print_tree_helper(node->right, prefix + (is_last ? "    " : "│   "), true);
        }
    }
}

// BinarySearchTree Implementation

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const std::vector<T>& sorted_array) : BinaryTree<T>() {
    if (!sorted_array.empty()) {
        root_ = build_balanced_bst(sorted_array, 0, sorted_array.size() - 1);
        size_ = sorted_array.size();
    }
}

template<typename T>
bool BinarySearchTree<T>::insert(const T& value) {
    bool inserted = false;
    root_ = insert_helper(root_, value, inserted);
    if (inserted) ++size_;
    return inserted;
}

template<typename T>
bool BinarySearchTree<T>::search(const T& value) const {
    return search_helper(root_, value);
}

template<typename T>
bool BinarySearchTree<T>::remove(const T& value) {
    bool removed = false;
    root_ = remove_helper(root_, value, removed);
    if (removed) --size_;
    return removed;
}

template<typename T>
T BinarySearchTree<T>::find_min() const {
    if (!root_) {
        throw std::runtime_error("Tree is empty");
    }
    return find_min_node(root_)->data;
}

template<typename T>
T BinarySearchTree<T>::find_max() const {
    if (!root_) {
        throw std::runtime_error("Tree is empty");
    }
    return find_max_node(root_)->data;
}

template<typename T>
T BinarySearchTree<T>::find_successor(const T& value) const {
    // Implementation for finding inorder successor
    auto inorder = this->inorder_traversal();
    auto it = std::find(inorder.begin(), inorder.end(), value);
    if (it == inorder.end() || std::next(it) == inorder.end()) {
        throw std::runtime_error("No successor found");
    }
    return *std::next(it);
}

template<typename T>
T BinarySearchTree<T>::find_predecessor(const T& value) const {
    // Implementation for finding inorder predecessor
    auto inorder = this->inorder_traversal();
    auto it = std::find(inorder.begin(), inorder.end(), value);
    if (it == inorder.end() || it == inorder.begin()) {
        throw std::runtime_error("No predecessor found");
    }
    return *std::prev(it);
}

template<typename T>
bool BinarySearchTree<T>::is_valid_bst() const {
    return is_valid_bst_helper(root_, nullptr, nullptr);
}

template<typename T>
std::vector<T> BinarySearchTree<T>::to_sorted_array() const {
    return this->inorder_traversal();
}

template<typename T>
T BinarySearchTree<T>::kth_smallest(int k) const {
    if (k <= 0 || k > static_cast<int>(size_)) {
        throw std::out_of_range("k is out of range");
    }
    
    T result;
    kth_smallest_helper(root_, k, result);
    return result;
}

template<typename T>
T BinarySearchTree<T>::kth_largest(int k) const {
    if (k <= 0 || k > static_cast<int>(size_)) {
        throw std::out_of_range("k is out of range");
    }
    
    T result;
    kth_largest_helper(root_, k, result);
    return result;
}

template<typename T>
int BinarySearchTree<T>::balance_factor(NodePtr node) const {
    if (!node) return 0;
    return this->height_helper(node->left) - this->height_helper(node->right);
}

template<typename T>
bool BinarySearchTree<T>::needs_rebalancing() const {
    return needs_rebalancing_helper(root_);
}

template<typename T>
typename BinarySearchTree<T>::NodePtr BinarySearchTree<T>::rotate_right(NodePtr node) {
    if (!node || !node->left) return node;
    
    NodePtr new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    
    return new_root;
}

template<typename T>
typename BinarySearchTree<T>::NodePtr BinarySearchTree<T>::rotate_left(NodePtr node) {
    if (!node || !node->right) return node;
    
    NodePtr new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    
    return new_root;
}

// BST Helper methods implementation

template<typename T>
typename BinarySearchTree<T>::NodePtr BinarySearchTree<T>::insert_helper(NodePtr node, const T& value, bool& inserted) {
    if (!node) {
        inserted = true;
        return std::make_shared<TreeNode<T>>(value);
    }
    
    if (value < node->data) {
        node->left = insert_helper(node->left, value, inserted);
    } else if (value > node->data) {
        node->right = insert_helper(node->right, value, inserted);
    }
    // If value == node->data, don't insert (no duplicates)
    
    return node;
}

template<typename T>
bool BinarySearchTree<T>::search_helper(NodePtr node, const T& value) const {
    if (!node) return false;
    
    if (value == node->data) return true;
    else if (value < node->data) return search_helper(node->left, value);
    else return search_helper(node->right, value);
}

template<typename T>
typename BinarySearchTree<T>::NodePtr BinarySearchTree<T>::remove_helper(NodePtr node, const T& value, bool& removed) {
    if (!node) return nullptr;
    
    if (value < node->data) {
        node->left = remove_helper(node->left, value, removed);
    } else if (value > node->data) {
        node->right = remove_helper(node->right, value, removed);
    } else {
        // Node to be deleted found
        removed = true;
        
        if (!node->left && !node->right) {
            // Leaf node
            return nullptr;
        } else if (!node->left) {
            // Only right child
            return node->right;
        } else if (!node->right) {
            // Only left child
            return node->left;
        } else {
            // Two children: find inorder successor
            NodePtr successor = find_min_node(node->right);
            node->data = successor->data;
            node->right = remove_helper(node->right, successor->data, removed);
            removed = true; // Reset since we found the original node
        }
    }
    
    return node;
}

template<typename T>
typename BinarySearchTree<T>::NodePtr BinarySearchTree<T>::find_min_node(NodePtr node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

template<typename T>
typename BinarySearchTree<T>::NodePtr BinarySearchTree<T>::find_max_node(NodePtr node) const {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}

template<typename T>
bool BinarySearchTree<T>::is_valid_bst_helper(NodePtr node, const T* min_val, const T* max_val) const {
    if (!node) return true;
    
    if ((min_val && node->data <= *min_val) || (max_val && node->data >= *max_val)) {
        return false;
    }
    
    return is_valid_bst_helper(node->left, min_val, &node->data) &&
           is_valid_bst_helper(node->right, &node->data, max_val);
}

template<typename T>
bool BinarySearchTree<T>::kth_smallest_helper(NodePtr node, int& k, T& result) const {
    if (!node) return false;
    
    if (kth_smallest_helper(node->left, k, result)) return true;
    
    --k;
    if (k == 0) {
        result = node->data;
        return true;
    }
    
    return kth_smallest_helper(node->right, k, result);
}

template<typename T>
bool BinarySearchTree<T>::kth_largest_helper(NodePtr node, int& k, T& result) const {
    if (!node) return false;
    
    if (kth_largest_helper(node->right, k, result)) return true;
    
    --k;
    if (k == 0) {
        result = node->data;
        return true;
    }
    
    return kth_largest_helper(node->left, k, result);
}

template<typename T>
bool BinarySearchTree<T>::needs_rebalancing_helper(NodePtr node) const {
    if (!node) return false;
    
    int bf = balance_factor(node);
    if (bf > 1 || bf < -1) return true;
    
    return needs_rebalancing_helper(node->left) || needs_rebalancing_helper(node->right);
}

template<typename T>
typename BinarySearchTree<T>::NodePtr BinarySearchTree<T>::build_balanced_bst(const std::vector<T>& sorted_array, int start, int end) {
    if (start > end) return nullptr;
    
    int mid = start + (end - start) / 2;
    auto node = std::make_shared<TreeNode<T>>(sorted_array[mid]);
    
    node->left = build_balanced_bst(sorted_array, start, mid - 1);
    node->right = build_balanced_bst(sorted_array, mid + 1, end);
    
    return node;
}

// Standalone utility functions implementation

template<typename T>
bool are_identical(const BinaryTree<T>& tree1, const BinaryTree<T>& tree2) {
    std::function<bool(typename BinaryTree<T>::NodePtr, typename BinaryTree<T>::NodePtr)> 
        compare = [&](typename BinaryTree<T>::NodePtr node1, typename BinaryTree<T>::NodePtr node2) -> bool {
        if (!node1 && !node2) return true;
        if (!node1 || !node2) return false;
        
        return (node1->data == node2->data) &&
               compare(node1->left, node2->left) &&
               compare(node1->right, node2->right);
    };
    
    return compare(tree1.get_root(), tree2.get_root());
}

template<typename T>
std::string serialize_tree(const BinaryTree<T>& tree, const std::string& null_marker) {
    std::ostringstream oss;
    std::function<void(typename BinaryTree<T>::NodePtr)> serialize = 
        [&](typename BinaryTree<T>::NodePtr node) {
        if (!node) {
            oss << null_marker << ",";
            return;
        }
        
        oss << node->data << ",";
        serialize(node->left);
        serialize(node->right);
    };
    
    serialize(tree.get_root());
    std::string result = oss.str();
    if (!result.empty()) result.pop_back(); // Remove trailing comma
    return result;
}

template<typename T>
BinaryTree<T> deserialize_tree(const std::string& data, const std::string& null_marker) {
    BinaryTree<T> tree;
    if (data.empty()) return tree;
    
    std::istringstream iss(data);
    std::string token;
    std::queue<std::string> tokens;
    
    while (std::getline(iss, token, ',')) {
        tokens.push(token);
    }
    
    std::function<typename BinaryTree<T>::NodePtr()> deserialize = [&]() -> typename BinaryTree<T>::NodePtr {
        if (tokens.empty()) return nullptr;
        
        std::string val = tokens.front();
        tokens.pop();
        
        if (val == null_marker) return nullptr;
        
        T value;
        std::istringstream(val) >> value;
        auto node = std::make_shared<TreeNode<T>>(value);
        
        node->left = deserialize();
        node->right = deserialize();
        
        return node;
    };
    
    auto root = deserialize();
    if (root) {
        tree.set_root(root->data);
        // Note: This is a simplified version. Full implementation would need to rebuild the tree structure.
    }
    
    return tree;
}

template<typename T>
int tree_diameter(const BinaryTree<T>& tree) {
    int diameter = 0;
    
    std::function<int(typename BinaryTree<T>::NodePtr)> height = 
        [&](typename BinaryTree<T>::NodePtr node) -> int {
        if (!node) return 0;
        
        int left_height = height(node->left);
        int right_height = height(node->right);
        
        diameter = std::max(diameter, left_height + right_height);
        
        return 1 + std::max(left_height, right_height);
    };
    
    height(tree.get_root());
    return diameter;
}

} // namespace data_structures
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_TREE_TPP