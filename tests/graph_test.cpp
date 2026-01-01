/**
 * @file graph_test.cpp
 * @brief Unit tests for Graph data structure
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/graph.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace leetcode_study_guide::data_structures;

class UndirectedGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create undirected graph: 0-1-2-3 with additional edge 1-3
        graph = Graph<int>(false, false); // undirected, unweighted
        graph.add_vertex(0);
        graph.add_vertex(1);
        graph.add_vertex(2);
        graph.add_vertex(3);
        graph.add_edge(0, 1);
        graph.add_edge(1, 2);
        graph.add_edge(2, 3);
        graph.add_edge(1, 3);
    }
    
    Graph<int> graph;
};

class DirectedGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create directed graph: 0->1->2->3 with additional edge 1->3
        directed_graph = Graph<int>(true, false); // directed, unweighted
        directed_graph.add_vertex(0);
        directed_graph.add_vertex(1);
        directed_graph.add_vertex(2);
        directed_graph.add_vertex(3);
        directed_graph.add_edge(0, 1);
        directed_graph.add_edge(1, 2);
        directed_graph.add_edge(2, 3);
        directed_graph.add_edge(1, 3);
    }
    
    Graph<int> directed_graph;
};

class WeightedGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create weighted undirected graph
        weighted_graph = Graph<int, int>(false, true); // undirected, weighted
        weighted_graph.add_vertex(0);
        weighted_graph.add_vertex(1);
        weighted_graph.add_vertex(2);
        weighted_graph.add_vertex(3);
        weighted_graph.add_edge(0, 1, 4);
        weighted_graph.add_edge(0, 2, 2);
        weighted_graph.add_edge(1, 2, 1);
        weighted_graph.add_edge(1, 3, 5);
        weighted_graph.add_edge(2, 3, 3);
    }
    
    Graph<int, int> weighted_graph;
};

// Basic Graph Operations Tests

TEST_F(UndirectedGraphTest, BasicOperations) {
    EXPECT_FALSE(graph.empty());
    EXPECT_EQ(graph.vertex_count(), 4);
    EXPECT_EQ(graph.edge_count(), 4);
    EXPECT_FALSE(graph.is_directed());
    EXPECT_FALSE(graph.is_weighted());
    
    // Test vertex operations
    EXPECT_TRUE(graph.has_vertex(0));
    EXPECT_TRUE(graph.has_vertex(3));
    EXPECT_FALSE(graph.has_vertex(4));
    
    // Test edge operations
    EXPECT_TRUE(graph.has_edge(0, 1));
    EXPECT_TRUE(graph.has_edge(1, 0)); // Undirected, so both directions
    EXPECT_TRUE(graph.has_edge(1, 3));
    EXPECT_FALSE(graph.has_edge(0, 3));
}

TEST_F(UndirectedGraphTest, AddRemoveOperations) {
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

TEST_F(DirectedGraphTest, DirectedGraphProperties) {
    EXPECT_TRUE(directed_graph.is_directed());
    EXPECT_FALSE(directed_graph.is_weighted());
    
    // Test directed edges
    EXPECT_TRUE(directed_graph.has_edge(0, 1));
    EXPECT_FALSE(directed_graph.has_edge(1, 0)); // Directed, so only one direction
    
    // Test degrees
    EXPECT_EQ(directed_graph.get_out_degree(1), 2); // 1->2, 1->3
    EXPECT_EQ(directed_graph.get_in_degree(1), 1);  // 0->1
    EXPECT_EQ(directed_graph.get_in_degree(3), 2);  // 1->3, 2->3
}

TEST_F(WeightedGraphTest, WeightedGraphProperties) {
    EXPECT_FALSE(weighted_graph.is_directed());
    EXPECT_TRUE(weighted_graph.is_weighted());
    
    // Test edge weights
    EXPECT_EQ(weighted_graph.get_edge_weight(0, 1), 4);
    EXPECT_EQ(weighted_graph.get_edge_weight(1, 2), 1);
    EXPECT_EQ(weighted_graph.get_edge_weight(2, 3), 3);
    
    // Non-existent edge should return infinity
    auto infinity = std::numeric_limits<int>::max();
    EXPECT_EQ(weighted_graph.get_edge_weight(0, 3), infinity);
}

// Graph Traversal Tests

TEST_F(UndirectedGraphTest, DepthFirstSearch) {
    std::vector<int> dfs_result = graph.dfs(0);
    
    EXPECT_EQ(dfs_result.size(), 4);
    EXPECT_EQ(dfs_result[0], 0); // Should start with 0
    
    // All vertices should be visited
    std::sort(dfs_result.begin(), dfs_result.end());
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(dfs_result, expected);
}

TEST_F(UndirectedGraphTest, BreadthFirstSearch) {
    std::vector<int> bfs_result = graph.bfs(0);
    
    EXPECT_EQ(bfs_result.size(), 4);
    EXPECT_EQ(bfs_result[0], 0); // Should start with 0
    
    // All vertices should be visited
    std::sort(bfs_result.begin(), bfs_result.end());
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(bfs_result, expected);
}

TEST_F(UndirectedGraphTest, PathFinding) {
    // Test DFS path finding
    std::vector<int> dfs_path = graph.find_path_dfs(0, 3);
    EXPECT_FALSE(dfs_path.empty());
    EXPECT_EQ(dfs_path.front(), 0);
    EXPECT_EQ(dfs_path.back(), 3);
    
    // Test BFS shortest path
    std::vector<int> bfs_path = graph.find_shortest_path_bfs(0, 3);
    EXPECT_FALSE(bfs_path.empty());
    EXPECT_EQ(bfs_path.front(), 0);
    EXPECT_EQ(bfs_path.back(), 3);
    EXPECT_EQ(bfs_path.size(), 3); // 0->1->3 (shortest path)
    
    // Test path to non-existent vertex
    std::vector<int> no_path = graph.find_path_dfs(0, 5);
    EXPECT_TRUE(no_path.empty());
}

// Graph Analysis Tests

TEST_F(UndirectedGraphTest, ConnectivityAnalysis) {
    EXPECT_TRUE(graph.is_connected());
    
    // Test connected components
    std::vector<std::vector<int>> components = graph.find_connected_components();
    EXPECT_EQ(components.size(), 1); // All vertices in one component
    EXPECT_EQ(components[0].size(), 4);
    
    // Add disconnected vertex
    graph.add_vertex(4);
    EXPECT_FALSE(graph.is_connected());
    
    components = graph.find_connected_components();
    EXPECT_EQ(components.size(), 2); // Two components now
}

TEST_F(UndirectedGraphTest, CycleDetection) {
    EXPECT_TRUE(graph.has_cycle()); // 1-2-3-1 forms a cycle
    
    // Create acyclic graph (tree)
    Graph<int> tree(false, false);
    tree.add_edge(0, 1);
    tree.add_edge(1, 2);
    tree.add_edge(1, 3);
    EXPECT_FALSE(tree.has_cycle());
}

TEST_F(DirectedGraphTest, DirectedGraphAnalysis) {
    EXPECT_FALSE(directed_graph.has_cycle()); // No cycle in this DAG
    
    // Test topological sort
    std::vector<int> topo_sort = directed_graph.topological_sort();
    EXPECT_EQ(topo_sort.size(), 4);
    EXPECT_EQ(topo_sort[0], 0); // 0 should come first (no incoming edges)
    
    // Add cycle and test
    directed_graph.add_edge(3, 0); // Creates cycle
    EXPECT_TRUE(directed_graph.has_cycle());
    
    std::vector<int> topo_with_cycle = directed_graph.topological_sort();
    EXPECT_TRUE(topo_with_cycle.empty()); // Cannot sort graph with cycle
}

TEST_F(UndirectedGraphTest, BipartiteTest) {
    // Create bipartite graph
    Graph<int> bipartite(false, false);
    bipartite.add_edge(0, 1);
    bipartite.add_edge(0, 3);
    bipartite.add_edge(2, 1);
    bipartite.add_edge(2, 3);
    
    EXPECT_TRUE(bipartite.is_bipartite());
    
    auto coloring = bipartite.get_bipartite_coloring();
    EXPECT_FALSE(coloring.empty());
    
    // Verify coloring is valid
    for (int v : {0, 1, 2, 3}) {
        for (int neighbor : bipartite.get_neighbors(v)) {
            EXPECT_NE(coloring[v], coloring[neighbor]);
        }
    }
    
    // Test non-bipartite graph (triangle)
    Graph<int> triangle(false, false);
    triangle.add_edge(0, 1);
    triangle.add_edge(1, 2);
    triangle.add_edge(2, 0);
    
    EXPECT_FALSE(triangle.is_bipartite());
}

// Shortest Path Algorithm Tests

TEST_F(WeightedGraphTest, DijkstraAlgorithm) {
    auto distances = weighted_graph.dijkstra(0);
    
    EXPECT_EQ(distances[0], 0); // Distance to self
    EXPECT_EQ(distances[1], 3); // 0->2->1 (cost: 2+1=3)
    EXPECT_EQ(distances[2], 2); // 0->2 (cost: 2)
    EXPECT_EQ(distances[3], 5); // 0->2->3 (cost: 2+3=5)
    
    // Test path finding
    auto [distance, path] = weighted_graph.dijkstra_path(0, 3);
    EXPECT_EQ(distance, 5);
    EXPECT_EQ(path.size(), 3); // 0->2->3
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 2);
    EXPECT_EQ(path[2], 3);
}

TEST_F(WeightedGraphTest, BellmanFordAlgorithm) {
    auto [distances, has_negative_cycle] = weighted_graph.bellman_ford(0);
    
    EXPECT_FALSE(has_negative_cycle);
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 3);
    EXPECT_EQ(distances[2], 2);
    EXPECT_EQ(distances[3], 5);
    
    // Test with negative edge (but no negative cycle)
    Graph<int, int> negative_graph(true, true);
    negative_graph.add_edge(0, 1, 1);
    negative_graph.add_edge(1, 2, -3);
    negative_graph.add_edge(0, 2, 4);
    
    auto [neg_distances, neg_cycle] = negative_graph.bellman_ford(0);
    EXPECT_FALSE(neg_cycle);
    EXPECT_EQ(neg_distances[2], -2); // 0->1->2 (cost: 1+(-3)=-2)
}

TEST_F(WeightedGraphTest, FloydWarshallAlgorithm) {
    auto all_distances = weighted_graph.floyd_warshall();
    
    EXPECT_EQ(all_distances.size(), 4);
    for (const auto& row : all_distances) {
        EXPECT_EQ(row.size(), 4);
    }
    
    // Check some known distances
    EXPECT_EQ(all_distances[0][0], 0); // Distance to self
    EXPECT_EQ(all_distances[0][2], 2); // Direct edge 0->2
    EXPECT_EQ(all_distances[0][3], 5); // 0->2->3
}

// Graph Representations Tests

TEST_F(UndirectedGraphTest, GraphRepresentations) {
    // Test adjacency list
    const auto& adj_list = graph.get_adjacency_list();
    EXPECT_EQ(adj_list.size(), 4);
    
    // Test adjacency matrix
    auto adj_matrix = graph.get_adjacency_matrix();
    EXPECT_EQ(adj_matrix.size(), 4);
    for (const auto& row : adj_matrix) {
        EXPECT_EQ(row.size(), 4);
    }
    
    // Test edge list
    auto edge_list = graph.get_edge_list();
    EXPECT_EQ(edge_list.size(), 4); // 4 edges in undirected graph
}

TEST_F(UndirectedGraphTest, UtilityMethods) {
    // Test get vertices
    std::vector<int> vertices = graph.get_vertices();
    EXPECT_EQ(vertices.size(), 4);
    std::sort(vertices.begin(), vertices.end());
    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(vertices, expected);
    
    // Test get neighbors
    std::vector<int> neighbors_1 = graph.get_neighbors(1);
    EXPECT_EQ(neighbors_1.size(), 3); // Connected to 0, 2, 3
    
    // Test degrees
    EXPECT_EQ(graph.get_degree(1), 3); // Connected to 0, 2, 3
    EXPECT_EQ(graph.get_degree(0), 1); // Connected to 1 only
}

// Standalone Utility Function Tests

TEST(GraphUtilityTest, CreateCompleteGraph) {
    std::vector<int> vertices = {0, 1, 2, 3};
    auto complete = create_complete_graph<int>(vertices, false, false);
    
    EXPECT_EQ(complete.vertex_count(), 4);
    EXPECT_EQ(complete.edge_count(), 6); // n(n-1)/2 for undirected complete graph
    
    // Every vertex should be connected to every other vertex
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            EXPECT_TRUE(complete.has_edge(i, j));
        }
    }
}

TEST(GraphUtilityTest, CreateCycleGraph) {
    std::vector<int> vertices = {0, 1, 2, 3};
    auto cycle = create_cycle_graph<int>(vertices, false, false);
    
    EXPECT_EQ(cycle.vertex_count(), 4);
    EXPECT_EQ(cycle.edge_count(), 4);
    
    // Should form a cycle: 0-1-2-3-0
    EXPECT_TRUE(cycle.has_edge(0, 1));
    EXPECT_TRUE(cycle.has_edge(1, 2));
    EXPECT_TRUE(cycle.has_edge(2, 3));
    EXPECT_TRUE(cycle.has_edge(3, 0));
}

TEST(GraphUtilityTest, CreatePathGraph) {
    std::vector<int> vertices = {0, 1, 2, 3};
    auto path = create_path_graph<int>(vertices, false, false);
    
    EXPECT_EQ(path.vertex_count(), 4);
    EXPECT_EQ(path.edge_count(), 3);
    
    // Should form a path: 0-1-2-3
    EXPECT_TRUE(path.has_edge(0, 1));
    EXPECT_TRUE(path.has_edge(1, 2));
    EXPECT_TRUE(path.has_edge(2, 3));
    EXPECT_FALSE(path.has_edge(0, 3));
}

TEST(GraphUtilityTest, CreateStarGraph) {
    std::vector<int> leaves = {1, 2, 3, 4};
    auto star = create_star_graph<int>(0, leaves, false, false);
    
    EXPECT_EQ(star.vertex_count(), 5);
    EXPECT_EQ(star.edge_count(), 4);
    
    // Center should be connected to all leaves
    for (int leaf : leaves) {
        EXPECT_TRUE(star.has_edge(0, leaf));
    }
    
    // Leaves should not be connected to each other
    EXPECT_FALSE(star.has_edge(1, 2));
    EXPECT_FALSE(star.has_edge(2, 3));
}

// Edge Cases and Error Handling

TEST(GraphEdgeCasesTest, EmptyGraphOperations) {
    Graph<int> empty_graph;
    
    EXPECT_TRUE(empty_graph.empty());
    EXPECT_EQ(empty_graph.vertex_count(), 0);
    EXPECT_EQ(empty_graph.edge_count(), 0);
    
    // Operations on empty graph
    EXPECT_FALSE(empty_graph.has_vertex(0));
    EXPECT_FALSE(empty_graph.has_edge(0, 1));
    EXPECT_TRUE(empty_graph.is_connected()); // Empty graph is considered connected
    
    std::vector<int> dfs_empty = empty_graph.dfs(0);
    EXPECT_TRUE(dfs_empty.empty());
}

TEST(GraphEdgeCasesTest, SingleVertexGraph) {
    Graph<int> single_graph;
    single_graph.add_vertex(0);
    
    EXPECT_FALSE(single_graph.empty());
    EXPECT_EQ(single_graph.vertex_count(), 1);
    EXPECT_EQ(single_graph.edge_count(), 0);
    EXPECT_TRUE(single_graph.is_connected());
    EXPECT_FALSE(single_graph.has_cycle());
    
    std::vector<int> dfs_single = single_graph.dfs(0);
    EXPECT_EQ(dfs_single.size(), 1);
    EXPECT_EQ(dfs_single[0], 0);
}

TEST(GraphEdgeCasesTest, DisconnectedGraph) {
    Graph<int> disconnected;
    disconnected.add_vertex(0);
    disconnected.add_vertex(1);
    disconnected.add_vertex(2);
    disconnected.add_vertex(3);
    disconnected.add_edge(0, 1);
    disconnected.add_edge(2, 3);
    
    EXPECT_FALSE(disconnected.is_connected());
    
    auto components = disconnected.find_connected_components();
    EXPECT_EQ(components.size(), 2);
    
    // DFS from 0 should only reach 0 and 1
    std::vector<int> dfs_partial = disconnected.dfs(0);
    EXPECT_EQ(dfs_partial.size(), 2);
}

TEST(GraphEdgeCasesTest, SelfLoops) {
    Graph<int> self_loop_graph;
    self_loop_graph.add_vertex(0);
    self_loop_graph.add_edge(0, 0); // Self loop
    
    EXPECT_TRUE(self_loop_graph.has_edge(0, 0));
    EXPECT_EQ(self_loop_graph.get_degree(0), 1);
    
    // Self loop should create cycle in undirected graph
    EXPECT_TRUE(self_loop_graph.has_cycle());
}

TEST(GraphEdgeCasesTest, InvalidOperations) {
    Graph<int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    
    // Remove non-existent vertex
    EXPECT_FALSE(graph.remove_vertex(5));
    
    // Remove non-existent edge
    EXPECT_FALSE(graph.remove_edge(0, 5));
    EXPECT_FALSE(graph.remove_edge(5, 0));
    
    // Operations on non-existent vertices
    EXPECT_TRUE(graph.get_neighbors(5).empty());
    EXPECT_EQ(graph.get_degree(5), 0);
}