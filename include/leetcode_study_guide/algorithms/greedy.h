#ifndef LEETCODE_STUDY_GUIDE_GREEDY_H
#define LEETCODE_STUDY_GUIDE_GREEDY_H

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

namespace leetcode_study_guide {
namespace algorithms {

/**
 * Greedy Algorithm Patterns
 * 
 * This module implements common greedy algorithm patterns for
 * optimization problems where local optimal choices lead to
 * global optimal solutions.
 */
class Greedy {
public:
    /**
     * Activity Selection Problem
     * Select maximum number of non-overlapping activities
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     */
    struct Activity {
        int start, end;
        Activity(int s, int e) : start(s), end(e) {}
    };
    
    static int activitySelection(std::vector<Activity>& activities);
    
    /**
     * Fractional Knapsack Problem
     * Maximize value with fractional items allowed
     * Time Complexity: O(n log n)
     * Space Complexity: O(1)
     */
    struct Item {
        int value, weight;
        Item(int v, int w) : value(v), weight(w) {}
        double valuePerWeight() const { return (double)value / weight; }
    };
    
    static double fractionalKnapsack(std::vector<Item>& items, int capacity);
    
    /**
     * Job Scheduling with Deadlines
     * Maximize profit by scheduling jobs within deadlines
     * Time Complexity: O(n^2)
     * Space Complexity: O(n)
     */
    struct Job {
        int id, deadline, profit;
        Job(int i, int d, int p) : id(i), deadline(d), profit(p) {}
    };
    
    static std::vector<int> jobScheduling(std::vector<Job>& jobs);
    
    /**
     * Huffman Coding
     * Generate optimal prefix codes for data compression
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    struct HuffmanNode {
        char ch;
        int freq;
        HuffmanNode* left;
        HuffmanNode* right;
        
        HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
        HuffmanNode(int f) : ch('\0'), freq(f), left(nullptr), right(nullptr) {}
    };
    
    static std::unordered_map<char, std::string> huffmanCoding(const std::string& text);
    
    /**
     * Minimum Spanning Tree - Kruskal's Algorithm
     * Find minimum cost to connect all vertices
     * Time Complexity: O(E log E)
     * Space Complexity: O(V)
     */
    struct Edge {
        int src, dest, weight;
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    };
    
    static std::vector<Edge> kruskalMST(int vertices, std::vector<Edge>& edges);
    
    /**
     * Minimum Spanning Tree - Prim's Algorithm
     * Find minimum cost to connect all vertices
     * Time Complexity: O(V^2) or O(E log V) with priority queue
     * Space Complexity: O(V)
     */
    static std::vector<Edge> primMST(int vertices, const std::vector<std::vector<std::pair<int, int>>>& graph);
    
    /**
     * Coin Change - Minimum Coins (Greedy approach for specific coin systems)
     * Find minimum number of coins for given amount
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     * Note: Only works for canonical coin systems
     */
    static int coinChangeGreedy(const std::vector<int>& coins, int amount);
    
    /**
     * Gas Station Problem
     * Find starting gas station to complete circular tour
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int canCompleteCircuit(const std::vector<int>& gas, const std::vector<int>& cost);
    
    /**
     * Jump Game
     * Determine if you can reach the last index
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static bool canJump(const std::vector<int>& nums);
    
    /**
     * Jump Game II
     * Find minimum number of jumps to reach the end
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int jump(const std::vector<int>& nums);

private:
    // Union-Find data structure for Kruskal's algorithm
    class UnionFind {
    public:
        std::vector<int> parent, rank;
        
        UnionFind(int n);
        int find(int x);
        bool unite(int x, int y);
    };
    
    // Helper functions
    static void generateCodes(HuffmanNode* root, const std::string& code, 
                             std::unordered_map<char, std::string>& codes);
};

} // namespace algorithms
} // namespace leetcode_study_guide

#endif // LEETCODE_STUDY_GUIDE_GREEDY_H