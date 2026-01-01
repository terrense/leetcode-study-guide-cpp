/**
 * @file simple_graph_test.cpp
 * @brief Simplified unit tests for Graph data structure (basic functionality only)
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/graph.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace leetcode_study_guide::data_structures;

class SimpleGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create simple undirected graph: 0-1-2-3
        graph = Graph<int>(false, false); // undirected, unweighted
        graph.add_vertex(0);
        graph.add_vertex(1);
        graph.add_vertex(2);
        graph.add_vertex(3);
        graph.add_edge(0, 1);
        graph.add_edge(1, 2);
        graph.add_edge(2, 3);
    }
    
    Graph<int> graph;
};

// Basic Graph Operations Tests

TEST_F(SimpleGraphTest, BasicOperations) {
    EXPECT_FALSE(graph.empty());
    EXPECT_EQ(graph.vertex_count(), 4);
    EXPECT_FALSE(graph.is_directed());
    EXPECT_FALSE(graph.is_weighted());
    
    // Test vertex operations
    EXPECT_TRUE(graph.has_vertex(0));
    EXPECT_TRUE(graph.has_vertex(3));
    EXPECT_FALSE(graph.has_vertex(4));
    
    // Test edge operations
    EXPECT_TRUE(graph.has_edge(0, 1));
    EXPECT_TRUE(graph.has_edge(1, 0)); // Undirected, so both directions
    EXPECT_TRUE(graph.has_edge(1, 2));
    EXPECT_FALSE(graph.has_edge(0, 3));
}

TEST_F(SimpleGraphTest, AddRemoveOperations) {
    // Add new vertex
    EXPECT_TRUE(graph.add_vertex(4));
    EXPECT_EQ(graph.vertex_count(), 5);
    EXPECT_FALSE(graph.add_vertex(4)); // Duplicate
    
    // Add new edge
    EXPECT_TRUE(graph.add_edge(0, 4));
    EXPECT_TRUE(graph.has_edge(0, 4));
    EXPECT_TRUE(graph.has_edge(4, 0)); // Undirected
    
    // Remove edge
    EXPECT_TRUE(graph.remove_edge(0, 1));
    EXPECT_FALSE(graph.has_edge(0, 1));
    EXPECT_FALSE(graph.has_edge(1, 0));
    
    // Remove vertex
    EXPECT_TRUE(graph.remove_vertex(4));
    EXPECT_FALSE(graph.has_vertex(4));
    EXPECT_EQ(graph.vertex_count(), 4);
}

// Graph Traversal Tests (if implemented)

TEST_F(SimpleGraphTest, DepthFirstSearch) {
    std::vector<int> dfs_result = graph.dfs(0);
    
    EXPECT_EQ(dfs_result.size(), 4);
    EXPECT_EQ(dfs_result[0], 0); // Should start with 0
    
    // All vertices should be visited
    std::sort(dfs_result.begin(), dfs_result.end());
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(dfs_result, expected);
}

TEST_F(SimpleGraphTest, BreadthFirstSearch) {
    std::vector<int> bfs_result = graph.bfs(0);
    
    EXPECT_EQ(bfs_result.size(), 4);
    EXPECT_EQ(bfs_result[0], 0); // Should start with 0
    
    // All vertices should be visited
    std::sort(bfs_result.begin(), bfs_result.end());
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(bfs_result, expected);
}

// Utility Methods Tests

TEST_F(SimpleGraphTest, UtilityMethods) {
    // Test get vertices
    std::vector<int> vertices = graph.get_vertices();
    EXPECT_EQ(vertices.size(), 4);
    std::sort(vertices.begin(), vertices.end());
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(vertices, expected);
    
    // Test get neighbors
    std::vector<int> neighbors_1 = graph.get_neighbors(1);
    EXPECT_EQ(neighbors_1.size(), 2); // Connected to 0, 2
}

// Edge Cases and Error Handling

TEST(GraphEdgeCasesTest, EmptyGraphOperations) {
    Graph<int> empty_graph;
    
    EXPECT_TRUE(empty_graph.empty());
    EXPECT_EQ(empty_graph.vertex_count(), 0);
    
    // Operations on empty graph
    EXPECT_FALSE(empty_graph.has_vertex(0));
    EXPECT_FALSE(empty_graph.has_edge(0, 1));
    
    std::vector<int> dfs_empty = empty_graph.dfs(0);
    EXPECT_TRUE(dfs_empty.empty());
}

TEST(GraphEdgeCasesTest, SingleVertexGraph) {
    Graph<int> single_graph;
    single_graph.add_vertex(0);
    
    EXPECT_FALSE(single_graph.empty());
    EXPECT_EQ(single_graph.vertex_count(), 1);
    
    std::vector<int> dfs_single = single_graph.dfs(0);
    EXPECT_EQ(dfs_single.size(), 1);
    EXPECT_EQ(dfs_single[0], 0);
}