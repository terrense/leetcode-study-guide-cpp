/**
 * @file graph.h
 * @brief Graph data structure implementations for the LeetCode Study Guide
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#ifndef LEETCODE_STUDY_GUIDE_GRAPH_H
#define LEETCODE_STUDY_GUIDE_GRAPH_H

#include "../common.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <limits>
#include <functional>
#include <algorithm>

namespace leetcode_study_guide {
namespace data_structures {

/**
 * @brief Edge structure for weighted graphs
 */
template<typename T, typename WeightType = int>
struct Edge {
    T from;
    T to;
    WeightType weight;
    
    /**
     * @brief Constructor for unweighted edge
     */
    Edge(const T& f, const T& t) : from(f), to(t), weight(WeightType{}) {}
    
    /**
     * @brief Constructor for weighted edge
     */
    Edge(const T& f, const T& t, const WeightType& w) : from(f), to(t), weight(w) {}
    
    /**
     * @brief Equality operator
     */
    bool operator==(const Edge& other) const {
        return from == other.from && to == other.to && weight == other.weight;
    }
    
    /**
     * @brief Less than operator (for sorting by weight)
     */
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

/**
 * @brief Graph class with adjacency list and matrix representations
 * 
 * This class provides a comprehensive implementation of graph operations
 * commonly used in LeetCode problems, including DFS, BFS, shortest path
 * algorithms, and graph analysis functions.
 */
template<typename T, typename WeightType = int>
class Graph {
public:
    using EdgeType = Edge<T, WeightType>;
    using AdjacencyList = std::unordered_map<T, std::vector<std::pair<T, WeightType>>>;
    using AdjacencyMatrix = std::vector<std::vector<WeightType>>;
    using VertexMap = std::unordered_map<T, int>;
    
    /**
     * @brief Default constructor (creates empty graph)
     */
    Graph(bool directed = false, bool weighted = false);
    
    /**
     * @brief Constructor with vertex list
     * @param vertices List of vertices to initialize
     * @param directed Whether graph is directed
     * @param weighted Whether graph is weighted
     */
    Graph(const std::vector<T>& vertices, bool directed = false, bool weighted = false);
    
    /**
     * @brief Constructor from edge list
     * @param edges List of edges to build graph from
     * @param directed Whether graph is directed
     * @param weighted Whether graph is weighted
     */
    Graph(const std::vector<EdgeType>& edges, bool directed = false, bool weighted = false);
    
    // Graph Construction and Modification
    
    /**
     * @brief Add vertex to graph
     * @param vertex Vertex to add
     * @return True if vertex was added, false if already exists
     * Time Complexity: O(1) average
     * Space Complexity: O(1)
     */
    bool add_vertex(const T& vertex);
    
    /**
     * @brief Remove vertex from graph
     * @param vertex Vertex to remove
     * @return True if vertex was removed, false if not found
     * Time Complexity: O(V + E) where V is vertices, E is edges
     * Space Complexity: O(1)
     */
    bool remove_vertex(const T& vertex);
    
    /**
     * @brief Add edge to graph
     * @param from Source vertex
     * @param to Destination vertex
     * @param weight Edge weight (default 1)
     * @return True if edge was added
     * Time Complexity: O(1) average
     * Space Complexity: O(1)
     */
    bool add_edge(const T& from, const T& to, const WeightType& weight = WeightType{1});
    
    /**
     * @brief Remove edge from graph
     * @param from Source vertex
     * @param to Destination vertex
     * @return True if edge was removed
     * Time Complexity: O(degree(from))
     * Space Complexity: O(1)
     */
    bool remove_edge(const T& from, const T& to);
    
    /**
     * @brief Check if vertex exists
     * @param vertex Vertex to check
     * @return True if vertex exists
     * Time Complexity: O(1) average
     * Space Complexity: O(1)
     */
    bool has_vertex(const T& vertex) const;
    
    /**
     * @brief Check if edge exists
     * @param from Source vertex
     * @param to Destination vertex
     * @return True if edge exists
     * Time Complexity: O(degree(from))
     * Space Complexity: O(1)
     */
    bool has_edge(const T& from, const T& to) const;
    
    /**
     * @brief Get edge weight
     * @param from Source vertex
     * @param to Destination vertex
     * @return Edge weight, or infinity if edge doesn't exist
     * Time Complexity: O(degree(from))
     * Space Complexity: O(1)
     */
    WeightType get_edge_weight(const T& from, const T& to) const;
    
    // Graph Traversal Algorithms
    
    /**
     * @brief Depth-First Search traversal
     * @param start Starting vertex
     * @return Vector of vertices in DFS order
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    std::vector<T> dfs(const T& start) const;
    
    /**
     * @brief DFS with custom visit function
     * @param start Starting vertex
     * @param visit_func Function to call for each vertex
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    void dfs(const T& start, std::function<void(const T&)> visit_func) const;
    
    /**
     * @brief Breadth-First Search traversal
     * @param start Starting vertex
     * @return Vector of vertices in BFS order
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    std::vector<T> bfs(const T& start) const;
    
    /**
     * @brief BFS with custom visit function
     * @param start Starting vertex
     * @param visit_func Function to call for each vertex
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    void bfs(const T& start, std::function<void(const T&)> visit_func) const;
    
    /**
     * @brief Find path between two vertices using DFS
     * @param start Starting vertex
     * @param end Target vertex
     * @return Path from start to end, empty if no path exists
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    std::vector<T> find_path_dfs(const T& start, const T& end) const;
    
    /**
     * @brief Find shortest path between two vertices using BFS (unweighted)
     * @param start Starting vertex
     * @param end Target vertex
     * @return Shortest path from start to end, empty if no path exists
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    std::vector<T> find_shortest_path_bfs(const T& start, const T& end) const;
    
    // Graph Analysis and Properties
    
    /**
     * @brief Check if graph is connected (undirected) or strongly connected (directed)
     * @return True if graph is connected
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    bool is_connected() const;
    
    /**
     * @brief Find connected components (undirected graph)
     * @return Vector of connected components, each component is a vector of vertices
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    std::vector<std::vector<T>> find_connected_components() const;
    
    /**
     * @brief Check if graph has cycle
     * @return True if graph contains a cycle
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    bool has_cycle() const;
    
    /**
     * @brief Topological sort (for DAG)
     * @return Topologically sorted vertices, empty if graph has cycle
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    std::vector<T> topological_sort() const;
    
    /**
     * @brief Check if graph is bipartite
     * @return True if graph is bipartite
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    bool is_bipartite() const;
    
    /**
     * @brief Get bipartite coloring if graph is bipartite
     * @return Map of vertex to color (0 or 1), empty if not bipartite
     * Time Complexity: O(V + E)
     * Space Complexity: O(V)
     */
    std::unordered_map<T, int> get_bipartite_coloring() const;
    
    // Shortest Path Algorithms (for weighted graphs)
    
    /**
     * @brief Dijkstra's shortest path algorithm
     * @param start Starting vertex
     * @return Map of vertex to shortest distance from start
     * Time Complexity: O((V + E) log V)
     * Space Complexity: O(V)
     */
    std::unordered_map<T, WeightType> dijkstra(const T& start) const;
    
    /**
     * @brief Dijkstra's shortest path to specific target
     * @param start Starting vertex
     * @param end Target vertex
     * @return Pair of (distance, path), distance is infinity if no path
     * Time Complexity: O((V + E) log V)
     * Space Complexity: O(V)
     */
    std::pair<WeightType, std::vector<T>> dijkstra_path(const T& start, const T& end) const;
    
    /**
     * @brief Bellman-Ford algorithm (handles negative weights)
     * @param start Starting vertex
     * @return Pair of (distances map, has_negative_cycle)
     * Time Complexity: O(VE)
     * Space Complexity: O(V)
     */
    std::pair<std::unordered_map<T, WeightType>, bool> bellman_ford(const T& start) const;
    
    /**
     * @brief Floyd-Warshall all-pairs shortest path
     * @return Matrix of shortest distances between all pairs
     * Time Complexity: O(V³)
     * Space Complexity: O(V²)
     */
    std::vector<std::vector<WeightType>> floyd_warshall() const;
    
    // Minimum Spanning Tree (for weighted undirected graphs)
    
    /**
     * @brief Kruskal's MST algorithm
     * @return Vector of edges in MST
     * Time Complexity: O(E log E)
     * Space Complexity: O(V)
     */
    std::vector<EdgeType> kruskal_mst() const;
    
    /**
     * @brief Prim's MST algorithm
     * @param start Starting vertex (optional)
     * @return Vector of edges in MST
     * Time Complexity: O((V + E) log V)
     * Space Complexity: O(V)
     */
    std::vector<EdgeType> prim_mst(const T& start = T{}) const;
    
    // Graph Representations
    
    /**
     * @brief Get adjacency list representation
     * @return Adjacency list
     */
    const AdjacencyList& get_adjacency_list() const { return adj_list_; }
    
    /**
     * @brief Get adjacency matrix representation
     * @return Adjacency matrix
     * Time Complexity: O(V²)
     * Space Complexity: O(V²)
     */
    AdjacencyMatrix get_adjacency_matrix() const;
    
    /**
     * @brief Get edge list
     * @return Vector of all edges
     * Time Complexity: O(E)
     * Space Complexity: O(E)
     */
    std::vector<EdgeType> get_edge_list() const;
    
    // Utility Methods
    
    /**
     * @brief Get all vertices
     * @return Vector of all vertices
     */
    std::vector<T> get_vertices() const;
    
    /**
     * @brief Get neighbors of a vertex
     * @param vertex Vertex to get neighbors for
     * @return Vector of neighboring vertices
     */
    std::vector<T> get_neighbors(const T& vertex) const;
    
    /**
     * @brief Get degree of a vertex
     * @param vertex Vertex to get degree for
     * @return Degree of vertex (in-degree + out-degree for directed graphs)
     */
    int get_degree(const T& vertex) const;
    
    /**
     * @brief Get in-degree of a vertex (for directed graphs)
     * @param vertex Vertex to get in-degree for
     * @return In-degree of vertex
     */
    int get_in_degree(const T& vertex) const;
    
    /**
     * @brief Get out-degree of a vertex (for directed graphs)
     * @param vertex Vertex to get out-degree for
     * @return Out-degree of vertex
     */
    int get_out_degree(const T& vertex) const;
    
    /**
     * @brief Get number of vertices
     * @return Number of vertices
     */
    size_t vertex_count() const { return adj_list_.size(); }
    
    /**
     * @brief Get number of edges
     * @return Number of edges
     */
    size_t edge_count() const;
    
    /**
     * @brief Check if graph is directed
     * @return True if graph is directed
     */
    bool is_directed() const { return directed_; }
    
    /**
     * @brief Check if graph is weighted
     * @return True if graph is weighted
     */
    bool is_weighted() const { return weighted_; }
    
    /**
     * @brief Check if graph is empty
     * @return True if graph has no vertices
     */
    bool empty() const { return adj_list_.empty(); }
    
    /**
     * @brief Clear all vertices and edges
     */
    void clear();
    
    /**
     * @brief Print graph structure (for debugging)
     */
    void print_graph() const;

private:
    AdjacencyList adj_list_;
    bool directed_;
    bool weighted_;
    
    // Helper methods
    void dfs_helper(const T& vertex, std::unordered_set<T>& visited, 
                   std::vector<T>& result) const;
    void dfs_helper(const T& vertex, std::unordered_set<T>& visited, 
                   std::function<void(const T&)> visit_func) const;
    bool find_path_dfs_helper(const T& current, const T& target, 
                             std::unordered_set<T>& visited, 
                             std::vector<T>& path) const;
    bool has_cycle_directed() const;
    bool has_cycle_undirected() const;
    bool has_cycle_directed_helper(const T& vertex, std::unordered_set<T>& visited, 
                                  std::unordered_set<T>& rec_stack) const;
    bool has_cycle_undirected_helper(const T& vertex, const T& parent, 
                                    std::unordered_set<T>& visited) const;
    void topological_sort_helper(const T& vertex, std::unordered_set<T>& visited, 
                                std::stack<T>& topo_stack) const;
    bool is_bipartite_helper(const T& start, std::unordered_map<T, int>& colors) const;
    
    // Union-Find for Kruskal's algorithm
    class UnionFind {
    public:
        explicit UnionFind(const std::vector<T>& vertices);
        T find(const T& x);
        bool unite(const T& x, const T& y);
        
    private:
        std::unordered_map<T, T> parent_;
        std::unordered_map<T, int> rank_;
    };
    
    static constexpr WeightType INFINITY = std::numeric_limits<WeightType>::max();
};

// Standalone Graph Utility Functions

/**
 * @brief Create complete graph (all vertices connected to all others)
 * @param vertices List of vertices
 * @param directed Whether graph should be directed
 * @param weighted Whether graph should be weighted
 * @return Complete graph
 */
template<typename T, typename WeightType = int>
Graph<T, WeightType> create_complete_graph(const std::vector<T>& vertices, 
                                          bool directed = false, bool weighted = false);

/**
 * @brief Create cycle graph (vertices connected in a cycle)
 * @param vertices List of vertices in cycle order
 * @param directed Whether graph should be directed
 * @param weighted Whether graph should be weighted
 * @return Cycle graph
 */
template<typename T, typename WeightType = int>
Graph<T, WeightType> create_cycle_graph(const std::vector<T>& vertices, 
                                       bool directed = false, bool weighted = false);

/**
 * @brief Create path graph (vertices connected in a line)
 * @param vertices List of vertices in path order
 * @param directed Whether graph should be directed
 * @param weighted Whether graph should be weighted
 * @return Path graph
 */
template<typename T, typename WeightType = int>
Graph<T, WeightType> create_path_graph(const std::vector<T>& vertices, 
                                      bool directed = false, bool weighted = false);

/**
 * @brief Create star graph (one central vertex connected to all others)
 * @param center Central vertex
 * @param leaves Leaf vertices
 * @param directed Whether graph should be directed
 * @param weighted Whether graph should be weighted
 * @return Star graph
 */
template<typename T, typename WeightType = int>
Graph<T, WeightType> create_star_graph(const T& center, const std::vector<T>& leaves, 
                                      bool directed = false, bool weighted = false);

/**
 * @brief Check if two graphs are isomorphic
 * @param g1 First graph
 * @param g2 Second graph
 * @return True if graphs are isomorphic
 */
template<typename T, typename WeightType = int>
bool are_isomorphic(const Graph<T, WeightType>& g1, const Graph<T, WeightType>& g2);

} // namespace data_structures
} // namespace leetcode_study_guide

// Include template implementation
#include "graph.tpp"

#endif // LEETCODE_STUDY_GUIDE_GRAPH_H