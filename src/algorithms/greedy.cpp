#include "leetcode_study_guide/algorithms/greedy.h"
#include <algorithm>
#include <queue>
#include <numeric>

namespace leetcode_study_guide {
namespace algorithms {

// Activity Selection Problem
int Greedy::activitySelection(std::vector<Activity>& activities) {
    if (activities.empty()) return 0;
    
    // Sort by end time
    std::sort(activities.begin(), activities.end(), 
              [](const Activity& a, const Activity& b) {
                  return a.end < b.end;
              });
    
    int count = 1;
    int lastEnd = activities[0].end;
    
    for (size_t i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastEnd) {
            count++;
            lastEnd = activities[i].end;
        }
    }
    
    return count;
}

// Fractional Knapsack
double Greedy::fractionalKnapsack(std::vector<Item>& items, int capacity) {
    // Sort by value per weight ratio in descending order
    std::sort(items.begin(), items.end(), 
              [](const Item& a, const Item& b) {
                  return a.valuePerWeight() > b.valuePerWeight();
              });
    
    double totalValue = 0.0;
    int remainingCapacity = capacity;
    
    for (const auto& item : items) {
        if (remainingCapacity >= item.weight) {
            // Take the whole item
            totalValue += item.value;
            remainingCapacity -= item.weight;
        } else {
            // Take fraction of the item
            totalValue += item.value * ((double)remainingCapacity / item.weight);
            break;
        }
    }
    
    return totalValue;
}

// Job Scheduling with Deadlines
std::vector<int> Greedy::jobScheduling(std::vector<Job>& jobs) {
    // Sort jobs by profit in descending order
    std::sort(jobs.begin(), jobs.end(), 
              [](const Job& a, const Job& b) {
                  return a.profit > b.profit;
              });
    
    // Find maximum deadline
    int maxDeadline = 0;
    for (const auto& job : jobs) {
        maxDeadline = std::max(maxDeadline, job.deadline);
    }
    
    std::vector<int> schedule(maxDeadline + 1, -1);
    std::vector<int> selectedJobs;
    
    for (const auto& job : jobs) {
        // Find a free slot for this job (from deadline to 1)
        for (int slot = job.deadline; slot >= 1; slot--) {
            if (schedule[slot] == -1) {
                schedule[slot] = job.id;
                selectedJobs.push_back(job.id);
                break;
            }
        }
    }
    
    return selectedJobs;
}

// Huffman Coding
std::unordered_map<char, std::string> Greedy::huffmanCoding(const std::string& text) {
    // Count frequency of each character
    std::unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }
    
    // Create priority queue (min-heap) of nodes
    auto compare = [](HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    };
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, decltype(compare)> pq(compare);
    
    for (const auto& pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // Build Huffman tree
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        HuffmanNode* merged = new HuffmanNode(left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        
        pq.push(merged);
    }
    
    HuffmanNode* root = pq.top();
    
    // Generate codes
    std::unordered_map<char, std::string> codes;
    if (freq.size() == 1) {
        // Special case: only one character
        codes[root->ch] = "0";
    } else {
        generateCodes(root, "", codes);
    }
    
    return codes;
}

void Greedy::generateCodes(HuffmanNode* root, const std::string& code, 
                          std::unordered_map<char, std::string>& codes) {
    if (!root) return;
    
    if (root->ch != '\0') {
        // Leaf node
        codes[root->ch] = code;
        return;
    }
    
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Union-Find implementation
Greedy::UnionFind::UnionFind(int n) : parent(n), rank(n, 0) {
    std::iota(parent.begin(), parent.end(), 0);
}

int Greedy::UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

bool Greedy::UnionFind::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    
    if (rootX == rootY) return false;
    
    // Union by rank
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    
    return true;
}

// Kruskal's MST
std::vector<Greedy::Edge> Greedy::kruskalMST(int vertices, std::vector<Edge>& edges) {
    // Sort edges by weight
    std::sort(edges.begin(), edges.end(), 
              [](const Edge& a, const Edge& b) {
                  return a.weight < b.weight;
              });
    
    UnionFind uf(vertices);
    std::vector<Edge> mst;
    
    for (const auto& edge : edges) {
        if (uf.unite(edge.src, edge.dest)) {
            mst.push_back(edge);
            if (mst.size() == vertices - 1) break;
        }
    }
    
    return mst;
}

// Prim's MST
std::vector<Greedy::Edge> Greedy::primMST(int vertices, const std::vector<std::vector<std::pair<int, int>>>& graph) {
    std::vector<bool> inMST(vertices, false);
    std::vector<Edge> mst;
    
    // Priority queue: {weight, {vertex, parent}}
    std::priority_queue<std::pair<int, std::pair<int, int>>, 
                       std::vector<std::pair<int, std::pair<int, int>>>,
                       std::greater<>> pq;
    
    // Start from vertex 0
    inMST[0] = true;
    for (const auto& edge : graph[0]) {
        pq.push({edge.second, {edge.first, 0}});
    }
    
    while (!pq.empty() && mst.size() < vertices - 1) {
        auto [weight, vertexParent] = pq.top();
        pq.pop();
        
        int vertex = vertexParent.first;
        int parent = vertexParent.second;
        
        if (inMST[vertex]) continue;
        
        inMST[vertex] = true;
        mst.emplace_back(parent, vertex, weight);
        
        // Add all edges from this vertex
        for (const auto& edge : graph[vertex]) {
            if (!inMST[edge.first]) {
                pq.push({edge.second, {edge.first, vertex}});
            }
        }
    }
    
    return mst;
}

// Coin Change Greedy (works only for canonical coin systems)
int Greedy::coinChangeGreedy(const std::vector<int>& coins, int amount) {
    int count = 0;
    
    // Assume coins are sorted in descending order
    for (int coin : coins) {
        while (amount >= coin) {
            amount -= coin;
            count++;
        }
    }
    
    return amount == 0 ? count : -1;
}

// Gas Station Problem
int Greedy::canCompleteCircuit(const std::vector<int>& gas, const std::vector<int>& cost) {
    int totalGas = 0, totalCost = 0;
    int currentGas = 0, start = 0;
    
    for (size_t i = 0; i < gas.size(); i++) {
        totalGas += gas[i];
        totalCost += cost[i];
        currentGas += gas[i] - cost[i];
        
        if (currentGas < 0) {
            start = i + 1;
            currentGas = 0;
        }
    }
    
    return totalGas >= totalCost ? start : -1;
}

// Jump Game
bool Greedy::canJump(const std::vector<int>& nums) {
    int maxReach = 0;
    
    for (size_t i = 0; i < nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = std::max(maxReach, (int)i + nums[i]);
        if (maxReach >= nums.size() - 1) return true;
    }
    
    return true;
}

// Jump Game II
int Greedy::jump(const std::vector<int>& nums) {
    if (nums.size() <= 1) return 0;
    
    int jumps = 0;
    int currentEnd = 0;
    int farthest = 0;
    
    for (size_t i = 0; i < nums.size() - 1; i++) {
        farthest = std::max(farthest, (int)i + nums[i]);
        
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
    }
    
    return jumps;
}

} // namespace algorithms
} // namespace leetcode_study_guide