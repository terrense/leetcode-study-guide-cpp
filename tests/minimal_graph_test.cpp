/**
 * @file minimal_graph_test.cpp
 * @brief Minimal unit tests for Graph data structure (only basic implemented functionality)
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include <gtest/gtest.h>
#include <vector>

// Minimal Graph class for testing basic functionality
template<typename T>
class MinimalGraph {
private:
    std::vector<T> vertices_;
    std::vector<std::pair<T, T>> edges_;
    bool directed_;
    
public:
    MinimalGraph(bool directed = false) : directed_(directed) {}
    
    bool add_vertex(const T& vertex) {
        for (const T& v : vertices_) {
            if (v == vertex) return false;
        }
        vertices_.push_back(vertex);
        return true;
    }
    
    bool add_edge(const T& from, const T& to) {
        edges_.push_back({from, to});
        if (!directed_) {
            edges_.push_back({to, from});
        }
        return true;
    }
    
    bool has_vertex(const T& vertex) const {
        for (const T& v : vertices_) {
            if (v == vertex) return true;
        }
        return false;
    }
    
    bool has_edge(const T& from, const T& to) const {
        for (const auto& edge : edges_) {
            if (edge.first == from && edge.second == to) return true;
        }
        return false;
    }
    
    size_t vertex_count() const { return vertices_.size(); }
    size_t edge_count() const { return directed_ ? edges_.size() : edges_.size() / 2; }
    bool empty() const { return vertices_.empty(); }
    bool is_directed() const { return directed_; }
};

class MinimalGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create simple undirected graph: 0-1-2-3
        graph.add_vertex(0);
        graph.add_vertex(1);
        graph.add_vertex(2);
        graph.add_vertex(3);
        graph.add_edge(0, 1);
        graph.add_edge(1, 2);
        graph.add_edge(2, 3);
    }
    
    MinimalGraph<int> graph;
};

// Basic Graph Operations Tests

TEST_F(MinimalGraphTest, BasicOperations) {
    EXPECT_FALSE(graph.empty());
    EXPECT_EQ(graph.vertex_count(), 4);
    EXPECT_FALSE(graph.is_directed());
    
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

TEST_F(MinimalGraphTest, AddOperations) {
    // Add new vertex
    EXPECT_TRUE(graph.add_vertex(4));
    EXPECT_EQ(graph.vertex_count(), 5);
    EXPECT_FALSE(graph.add_vertex(4)); // Duplicate
    
    // Add new edge
    EXPECT_TRUE(graph.add_edge(0, 4));
    EXPECT_TRUE(graph.has_edge(0, 4));
    EXPECT_TRUE(graph.has_edge(4, 0)); // Undirected
}

TEST(GraphEdgeCasesTest, EmptyGraphOperations) {
    MinimalGraph<int> empty_graph;
    
    EXPECT_TRUE(empty_graph.empty());
    EXPECT_EQ(empty_graph.vertex_count(), 0);
    
    // Operations on empty graph
    EXPECT_FALSE(empty_graph.has_vertex(0));
    EXPECT_FALSE(empty_graph.has_edge(0, 1));
}

TEST(GraphEdgeCasesTest, SingleVertexGraph) {
    MinimalGraph<int> single_graph;
    single_graph.add_vertex(0);
    
    EXPECT_FALSE(single_graph.empty());
    EXPECT_EQ(single_graph.vertex_count(), 1);
}

TEST(GraphEdgeCasesTest, DirectedGraphProperties) {
    MinimalGraph<int> directed_graph(true);
    directed_graph.add_vertex(0);
    directed_graph.add_vertex(1);
    directed_graph.add_edge(0, 1);
    
    EXPECT_TRUE(directed_graph.is_directed());
    EXPECT_TRUE(directed_graph.has_edge(0, 1));
    EXPECT_FALSE(directed_graph.has_edge(1, 0)); // Directed, so only one direction
}