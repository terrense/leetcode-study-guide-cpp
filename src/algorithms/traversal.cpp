#include "leetcode_study_guide/algorithms/traversal.h"
#include <unordered_set>
#include <algorithm>

namespace leetcode_study_guide {
namespace algorithms {

// ===== TREE TRAVERSAL IMPLEMENTATIONS =====

/**
 * Recursive Tree Traversals
 * These functions use recursion to traverse binary trees in different orders.
 * The recursive approach is intuitive but uses O(h) space on the call stack,
 * where h is the height of the tree.
 */

/**
 * Inorder Traversal (Recursive): Left -> Root -> Right
 * This traversal visits nodes in sorted order for Binary Search Trees.
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - recursion stack depth equals tree height
 */
std::vector<int> Traversal::inorderRecursive(TreeNode* root) {
    // Create a vector to store the traversal results
    std::vector<int> result;
    // Call the recursive helper function to perform inorder traversal
    inorderHelper(root, result);
    return result;
}

/**
 * Preorder Traversal (Recursive): Root -> Left -> Right
 * This traversal is useful for creating a copy of the tree or prefix expressions.
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - recursion stack depth equals tree height
 */
std::vector<int> Traversal::preorderRecursive(TreeNode* root) {
    // Create a vector to store the traversal results
    std::vector<int> result;
    // Call the recursive helper function to perform preorder traversal
    preorderHelper(root, result);
    return result;
}

/**
 * Postorder Traversal (Recursive): Left -> Right -> Root
 * This traversal is useful for deleting trees or postfix expressions.
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - recursion stack depth equals tree height
 */
std::vector<int> Traversal::postorderRecursive(TreeNode* root) {
    // Create a vector to store the traversal results
    std::vector<int> result;
    // Call the recursive helper function to perform postorder traversal
    postorderHelper(root, result);
    return result;
}

/**
 * Inorder Helper Function: Implements the recursive inorder traversal logic
 * Pattern: Left subtree -> Root node -> Right subtree
 * @param root: Current node being processed
 * @param result: Reference to vector storing traversal results
 */
void Traversal::inorderHelper(TreeNode* root, std::vector<int>& result) {
    // Base case: if current node is null, return immediately
    // This handles empty trees and leaf node children
    if (!root) return;
    
    // Step 1: Recursively traverse the left subtree first
    // This ensures all left nodes are processed before the root
    inorderHelper(root->left, result);
    
    // Step 2: Process the current root node
    // Add the node's value to our result vector
    result.push_back(root->val);
    
    // Step 3: Recursively traverse the right subtree last
    // This ensures the root is processed before right nodes
    inorderHelper(root->right, result);
}

/**
 * Preorder Helper Function: Implements the recursive preorder traversal logic
 * Pattern: Root node -> Left subtree -> Right subtree
 * @param root: Current node being processed
 * @param result: Reference to vector storing traversal results
 */
void Traversal::preorderHelper(TreeNode* root, std::vector<int>& result) {
    // Base case: if current node is null, return immediately
    if (!root) return;
    
    // Step 1: Process the current root node first
    // This is the key difference from inorder - root comes first
    result.push_back(root->val);
    
    // Step 2: Recursively traverse the left subtree
    preorderHelper(root->left, result);
    
    // Step 3: Recursively traverse the right subtree
    preorderHelper(root->right, result);
}

/**
 * Postorder Helper Function: Implements the recursive postorder traversal logic
 * Pattern: Left subtree -> Right subtree -> Root node
 * @param root: Current node being processed
 * @param result: Reference to vector storing traversal results
 */
void Traversal::postorderHelper(TreeNode* root, std::vector<int>& result) {
    // Base case: if current node is null, return immediately
    if (!root) return;
    
    // Step 1: Recursively traverse the left subtree first
    postorderHelper(root->left, result);
    
    // Step 2: Recursively traverse the right subtree second
    postorderHelper(root->right, result);
    
    // Step 3: Process the current root node last
    // This is the key difference - root comes after both subtrees
    result.push_back(root->val);
}

/**
 * Iterative Tree Traversals
 * These functions use explicit stacks to simulate recursion, avoiding
 * potential stack overflow issues with very deep trees.
 * Space complexity is still O(h) but uses heap memory instead of call stack.
 */

/**
 * Inorder Traversal (Iterative): Uses explicit stack to simulate recursion
 * Algorithm: Keep going left and pushing nodes to stack, then pop and process,
 * then move to right subtree. This mimics the recursive call pattern.
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - stack can hold up to h nodes (tree height)
 */
std::vector<int> Traversal::inorderIterative(TreeNode* root) {
    // Create a vector to store the traversal results
    std::vector<int> result;
    // Use an explicit stack to simulate the recursive call stack
    std::stack<TreeNode*> stack;
    // Pointer to track the current node being processed
    TreeNode* current = root;
    
    // Continue processing while there are nodes to visit or stack has nodes
    // This condition ensures we don't miss any nodes in the tree
    while (current || !stack.empty()) {
        // Phase 1: Go as far left as possible, pushing nodes onto stack
        // This simulates the recursive calls going down the left spine
        while (current) {
            stack.push(current);        // Save current node for later processing
            current = current->left;    // Move to left child
        }
        
        // Phase 2: Process the leftmost unprocessed node
        // Pop from stack - this is the leftmost node we haven't processed yet
        current = stack.top();
        stack.pop();
        
        // Visit/process this node - add its value to results
        // This corresponds to the "visit root" step in recursive inorder
        result.push_back(current->val);
        
        // Phase 3: Move to right subtree for further processing
        // This simulates returning from left subtree and moving to right
        current = current->right;
    }
    
    return result;
}

/**
 * Preorder Traversal (Iterative): Root -> Left -> Right
 * Uses stack but processes nodes immediately when pushed (root first).
 * Key insight: Push right child first, then left, so left is processed first.
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - stack depth equals tree height
 */
std::vector<int> Traversal::preorderIterative(TreeNode* root) {
    // Create vector to store results
    std::vector<int> result;
    // Handle empty tree case
    if (!root) return result;
    
    // Use explicit stack for iterative traversal
    std::stack<TreeNode*> stack;
    // Start by pushing root onto stack
    stack.push(root);
    
    // Process nodes while stack is not empty
    while (!stack.empty()) {
        // Pop the top node from stack
        TreeNode* node = stack.top();
        stack.pop();
        
        // Process current node immediately (preorder = root first)
        result.push_back(node->val);
        
        // Push children onto stack: RIGHT FIRST, then LEFT
        // This ensures left child is processed before right child
        // because stack is LIFO (Last In, First Out)
        if (node->right) stack.push(node->right);  // Push right first
        if (node->left) stack.push(node->left);    // Push left second (processed first)
    }
    
    return result;
}

/**
 * Postorder Traversal (Iterative): Left -> Right -> Root
 * Most complex iterative traversal. We need to ensure both children are
 * processed before processing the parent. Uses lastVisited pointer to track.
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(h) - stack depth equals tree height
 */
std::vector<int> Traversal::postorderIterative(TreeNode* root) {
    // Create vector to store results
    std::vector<int> result;
    if (!root) return result;
    
    // Use explicit stack for traversal
    std::stack<TreeNode*> stack;
    // Track the last node we processed to avoid infinite loops
    TreeNode* lastVisited = nullptr;
    // Current node being examined
    TreeNode* current = root;
    
    // Continue while we have nodes to process or stack is not empty
    while (current || !stack.empty()) {
        if (current) {
            // Phase 1: Go as far left as possible, pushing nodes
            // This is similar to inorder, but we don't process nodes yet
            stack.push(current);
            current = current->left;
        } else {
            // Phase 2: Examine the top of stack without popping yet
            TreeNode* peekNode = stack.top();
            
            // Check if we can process this node:
            // - If it has no right child, OR
            // - If we just finished processing its right child
            if (peekNode->right && lastVisited != peekNode->right) {
                // This node has a right child we haven't processed yet
                // Move to right subtree to process it first
                current = peekNode->right;
            } else {
                // Both children (if any) have been processed
                // Now we can safely process this node (postorder = root last)
                result.push_back(peekNode->val);
                lastVisited = stack.top();  // Remember we processed this node
                stack.pop();                // Remove from stack
            }
        }
    }
    
    return result;
}

/**
 * Breadth-First Search (BFS) Tree Traversals
 * BFS explores nodes level by level, using a queue (FIFO) data structure.
 * This is fundamentally different from DFS which goes deep first.
 */

/**
 * Level Order Traversal: Visit all nodes level by level from left to right
 * Classic BFS implementation using queue. Useful for finding shortest paths
 * in unweighted trees and level-based processing.
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(w) - where w is maximum width of tree (max nodes in any level)
 */
std::vector<int> Traversal::levelOrder(TreeNode* root) {
    // Create vector to store results
    std::vector<int> result;
    if (!root) return result;
    
    // Use queue for BFS - FIFO (First In, First Out)
    // This ensures we process nodes in level order
    std::queue<TreeNode*> queue;
    // Start BFS from root node
    queue.push(root);
    
    // Process nodes while queue is not empty
    while (!queue.empty()) {
        // Get the front node from queue (oldest unprocessed node)
        TreeNode* node = queue.front();
        queue.pop();
        
        // Process current node - add its value to results
        result.push_back(node->val);
        
        // Add children to queue for future processing
        // Left child first, then right child (left-to-right order)
        if (node->left) queue.push(node->left);
        if (node->right) queue.push(node->right);
    }
    
    return result;
}

/**
 * Level Order Traversal by Levels: Groups nodes by their level in the tree
 * Returns a 2D vector where each inner vector contains all nodes at that level.
 * Key technique: Process entire level at once using queue size.
 * Time Complexity: O(n) - visit each node once
 * Space Complexity: O(w) - where w is maximum width of tree
 */
std::vector<std::vector<int>> Traversal::levelOrderByLevels(TreeNode* root) {
    // Create 2D vector to store results grouped by level
    std::vector<std::vector<int>> result;
    if (!root) return result;
    
    // Use queue for BFS traversal
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    // Process tree level by level
    while (!queue.empty()) {
        // Key insight: queue.size() tells us how many nodes are in current level
        int levelSize = queue.size();
        // Create vector to store current level's nodes
        std::vector<int> currentLevel;
        
        // Process all nodes in current level
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = queue.front();
            queue.pop();
            
            // Add current node's value to current level
            currentLevel.push_back(node->val);
            
            // Add children to queue - they belong to next level
            if (node->left) queue.push(node->left);
            if (node->right) queue.push(node->right);
        }
        
        // Add completed level to results
        result.push_back(currentLevel);
    }
    
    return result;
}

// BFS Variations
std::vector<int> Traversal::rightSideView(TreeNode* root) {
    std::vector<int> result;
    if (!root) return result;
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = queue.front();
            queue.pop();
            
            if (i == levelSize - 1) {
                result.push_back(node->val);
            }
            
            if (node->left) queue.push(node->left);
            if (node->right) queue.push(node->right);
        }
    }
    
    return result;
}

std::vector<double> Traversal::averageOfLevels(TreeNode* root) {
    std::vector<double> result;
    if (!root) return result;
    
    std::queue<TreeNode*> queue;
    queue.push(root);
    
    while (!queue.empty()) {
        int levelSize = queue.size();
        long long sum = 0;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = queue.front();
            queue.pop();
            sum += node->val;
            
            if (node->left) queue.push(node->left);
            if (node->right) queue.push(node->right);
        }
        
        result.push_back((double)sum / levelSize);
    }
    
    return result;
}

int Traversal::maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}

int Traversal::minDepth(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    
    int minLeft = root->left ? minDepth(root->left) : INT_MAX;
    int minRight = root->right ? minDepth(root->right) : INT_MAX;
    
    return 1 + std::min(minLeft, minRight);
}

// ===== GRAPH TRAVERSAL IMPLEMENTATIONS =====

// Graph DFS Recursive
std::vector<int> Traversal::dfsRecursive(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> result;
    std::vector<bool> visited(graph.size(), false);
    dfsRecursiveHelper(graph, start, visited, result);
    return result;
}

void Traversal::dfsRecursiveHelper(const std::vector<std::vector<int>>& graph, int node,
                                  std::vector<bool>& visited, std::vector<int>& result) {
    visited[node] = true;
    result.push_back(node);
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsRecursiveHelper(graph, neighbor, visited, result);
        }
    }
}

// Graph DFS Iterative
std::vector<int> Traversal::dfsIterative(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> result;
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> stack;
    
    stack.push(start);
    
    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        
        if (!visited[node]) {
            visited[node] = true;
            result.push_back(node);
            
            // Add neighbors in reverse order to maintain left-to-right traversal
            for (int i = graph[node].size() - 1; i >= 0; i--) {
                if (!visited[graph[node][i]]) {
                    stack.push(graph[node][i]);
                }
            }
        }
    }
    
    return result;
}

// Graph BFS
std::vector<int> Traversal::bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<int> result;
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> queue;
    
    queue.push(start);
    visited[start] = true;
    
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        result.push_back(node);
        
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }
    
    return result;
}

// Connected Components
int Traversal::countConnectedComponents(const std::vector<std::vector<int>>& graph) {
    int count = 0;
    std::vector<bool> visited(graph.size(), false);
    
    for (size_t i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            std::vector<int> component;
            dfsComponentHelper(graph, i, visited, component);
            count++;
        }
    }
    
    return count;
}

std::vector<std::vector<int>> Traversal::findConnectedComponents(const std::vector<std::vector<int>>& graph) {
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(graph.size(), false);
    
    for (size_t i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            std::vector<int> component;
            dfsComponentHelper(graph, i, visited, component);
            components.push_back(component);
        }
    }
    
    return components;
}

void Traversal::dfsComponentHelper(const std::vector<std::vector<int>>& graph, int node,
                                  std::vector<bool>& visited, std::vector<int>& component) {
    visited[node] = true;
    component.push_back(node);
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsComponentHelper(graph, neighbor, visited, component);
        }
    }
}

// Shortest Path using BFS
std::vector<int> Traversal::shortestPath(const std::vector<std::vector<int>>& graph, int start, int end) {
    std::vector<int> parent(graph.size(), -1);
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> queue;
    
    queue.push(start);
    visited[start] = true;
    
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        
        if (node == end) break;
        
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = node;
                queue.push(neighbor);
            }
        }
    }
    
    // Reconstruct path
    std::vector<int> path;
    if (parent[end] != -1 || start == end) {
        int current = end;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());
    }
    
    return path;
}

int Traversal::shortestDistance(const std::vector<std::vector<int>>& graph, int start, int end) {
    std::vector<int> distance(graph.size(), -1);
    std::queue<int> queue;
    
    queue.push(start);
    distance[start] = 0;
    
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        
        if (node == end) return distance[end];
        
        for (int neighbor : graph[node]) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[node] + 1;
                queue.push(neighbor);
            }
        }
    }
    
    return -1; // No path found
}

// Cycle Detection
bool Traversal::hasCycleUndirected(const std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(graph.size(), false);
    
    for (size_t i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            if (hasCycleUndirectedHelper(graph, i, visited, -1)) {
                return true;
            }
        }
    }
    
    return false;
}

bool Traversal::hasCycleUndirectedHelper(const std::vector<std::vector<int>>& graph, int node,
                                        std::vector<bool>& visited, int parent) {
    visited[node] = true;
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (hasCycleUndirectedHelper(graph, neighbor, visited, node)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }
    
    return false;
}

bool Traversal::hasCycleDirected(const std::vector<std::vector<int>>& graph) {
    std::vector<int> color(graph.size(), 0); // 0: white, 1: gray, 2: black
    
    for (size_t i = 0; i < graph.size(); i++) {
        if (color[i] == 0) {
            if (hasCycleDirectedHelper(graph, i, color)) {
                return true;
            }
        }
    }
    
    return false;
}

bool Traversal::hasCycleDirectedHelper(const std::vector<std::vector<int>>& graph, int node,
                                      std::vector<int>& color) {
    color[node] = 1; // Gray (visiting)
    
    for (int neighbor : graph[node]) {
        if (color[neighbor] == 1) {
            return true; // Back edge found
        }
        if (color[neighbor] == 0 && hasCycleDirectedHelper(graph, neighbor, color)) {
            return true;
        }
    }
    
    color[node] = 2; // Black (visited)
    return false;
}

// Topological Sort
std::vector<int> Traversal::topologicalSort(const std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> topoStack;
    
    for (size_t i = 0; i < graph.size(); i++) {
        if (!visited[i]) {
            topologicalSortHelper(graph, i, visited, topoStack);
        }
    }
    
    std::vector<int> result;
    while (!topoStack.empty()) {
        result.push_back(topoStack.top());
        topoStack.pop();
    }
    
    return result;
}

void Traversal::topologicalSortHelper(const std::vector<std::vector<int>>& graph, int node,
                                     std::vector<bool>& visited, std::stack<int>& topoStack) {
    visited[node] = true;
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            topologicalSortHelper(graph, neighbor, visited, topoStack);
        }
    }
    
    topoStack.push(node);
}

// Kahn's Algorithm for Topological Sort
std::vector<int> Traversal::topologicalSortKahn(const std::vector<std::vector<int>>& graph) {
    std::vector<int> indegree(graph.size(), 0);
    
    // Calculate indegrees
    for (size_t i = 0; i < graph.size(); i++) {
        for (int neighbor : graph[i]) {
            indegree[neighbor]++;
        }
    }
    
    std::queue<int> queue;
    for (size_t i = 0; i < indegree.size(); i++) {
        if (indegree[i] == 0) {
            queue.push(i);
        }
    }
    
    std::vector<int> result;
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        result.push_back(node);
        
        for (int neighbor : graph[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                queue.push(neighbor);
            }
        }
    }
    
    return result;
}

// Generic traversal with visitor
void Traversal::dfsWithVisitor(const std::vector<std::vector<int>>& graph, int start,
                               std::function<void(int)> visitor) {
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> stack;
    
    stack.push(start);
    
    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        
        if (!visited[node]) {
            visited[node] = true;
            visitor(node);
            
            for (int i = graph[node].size() - 1; i >= 0; i--) {
                if (!visited[graph[node][i]]) {
                    stack.push(graph[node][i]);
                }
            }
        }
    }
}

void Traversal::bfsWithVisitor(const std::vector<std::vector<int>>& graph, int start,
                               std::function<void(int)> visitor) {
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> queue;
    
    queue.push(start);
    visited[start] = true;
    
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        visitor(node);
        
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }
}

} // namespace algorithms
} // namespace leetcode_study_guide