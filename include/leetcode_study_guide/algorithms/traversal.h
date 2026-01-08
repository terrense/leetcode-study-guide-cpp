#ifndef LEETCODE_STUDY_GUIDE_TRAVERSAL_H
#define LEETCODE_STUDY_GUIDE_TRAVERSAL_H

#include <vector>
#include <queue>
#include <stack>
#include <functional>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Tree and Graph Traversal Algorithm Patterns
 * 
 * This module implements DFS and BFS traversal algorithms for both
 * trees and graphs, with both recursive and iterative implementations.
 */

// Forward declarations for tree structures
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Traversal {
public:
    // ===== TREE TRAVERSAL ALGORITHMS =====
    
    /**
     * Tree DFS Traversals - Recursive Implementation
     * Time Complexity: O(n)
     * Space Complexity: O(h) where h is height of tree
     */
    static std::vector<int> inorderRecursive(TreeNode* root);
    static std::vector<int> preorderRecursive(TreeNode* root);
    static std::vector<int> postorderRecursive(TreeNode* root);
    
    /**
     * Tree DFS Traversals - Iterative Implementation
     * Time Complexity: O(n)
     * Space Complexity: O(h) where h is height of tree
     */
    static std::vector<int> inorderIterative(TreeNode* root);
    static std::vector<int> preorderIterative(TreeNode* root);
    static std::vector<int> postorderIterative(TreeNode* root);
    
    /**
     * Tree BFS Traversal (Level Order)
     * Time Complexity: O(n)
     * Space Complexity: O(w) where w is maximum width of tree
     */
    static std::vector<int> levelOrder(TreeNode* root);
    static std::vector<std::vector<int>> levelOrderByLevels(TreeNode* root);
    
    /**
     * Tree BFS Variations
     */
    static std::vector<int> rightSideView(TreeNode* root);
    static std::vector<double> averageOfLevels(TreeNode* root);
    static int maxDepth(TreeNode* root);
    static int minDepth(TreeNode* root);
    
    // ===== GRAPH TRAVERSAL ALGORITHMS =====
    
    /**
     * Graph DFS - Recursive Implementation
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    static std::vector<int> dfsRecursive(const std::vector<std::vector<int>>& graph, int start);
    static void dfsRecursiveHelper(const std::vector<std::vector<int>>& graph, int node, 
                                   std::vector<bool>& visited, std::vector<int>& result);
    
    /**
     * Graph DFS - Iterative Implementation
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    static std::vector<int> dfsIterative(const std::vector<std::vector<int>>& graph, int start);
    
    /**
     * Graph BFS Implementation
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    static std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start);
    
    /**
     * Connected Components using DFS
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    static int countConnectedComponents(const std::vector<std::vector<int>>& graph);
    static std::vector<std::vector<int>> findConnectedComponents(const std::vector<std::vector<int>>& graph);
    
    /**
     * Shortest Path in Unweighted Graph using BFS
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    static std::vector<int> shortestPath(const std::vector<std::vector<int>>& graph, int start, int end);
    static int shortestDistance(const std::vector<std::vector<int>>& graph, int start, int end);
    
    /**
     * Cycle Detection
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    static bool hasCycleUndirected(const std::vector<std::vector<int>>& graph);
    static bool hasCycleDirected(const std::vector<std::vector<int>>& graph);
    
    /**
     * Topological Sort (for DAG)
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    static std::vector<int> topologicalSort(const std::vector<std::vector<int>>& graph);
    static std::vector<int> topologicalSortKahn(const std::vector<std::vector<int>>& graph);
    
    /**
     * Generic traversal with custom visitor function
     */
    static void dfsWithVisitor(const std::vector<std::vector<int>>& graph, int start,
                              std::function<void(int)> visitor);
    static void bfsWithVisitor(const std::vector<std::vector<int>>& graph, int start,
                              std::function<void(int)> visitor);

private:
    // Helper functions for tree traversals
    static void inorderHelper(TreeNode* root, std::vector<int>& result);
    static void preorderHelper(TreeNode* root, std::vector<int>& result);
    static void postorderHelper(TreeNode* root, std::vector<int>& result);
    
    // Helper functions for graph algorithms
    static void dfsComponentHelper(const std::vector<std::vector<int>>& graph, int node,
                                  std::vector<bool>& visited, std::vector<int>& component);
    static bool hasCycleUndirectedHelper(const std::vector<std::vector<int>>& graph, int node,
                                        std::vector<bool>& visited, int parent);
    static bool hasCycleDirectedHelper(const std::vector<std::vector<int>>& graph, int node,
                                      std::vector<int>& color);
    static void topologicalSortHelper(const std::vector<std::vector<int>>& graph, int node,
                                     std::vector<bool>& visited, std::stack<int>& topoStack);
};

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_TRAVERSAL_H