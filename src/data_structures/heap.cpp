/**
 * @file heap.cpp
 * @brief Implementation file for Heap and Trie data structures
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/heap.h"
#include <iostream>
#include <algorithm>

namespace leetcode_study_guide {
namespace data_structures {

// Trie Implementation

Trie::Trie() : root_(std::make_unique<TrieNode>()), total_words_(0) {}

void Trie::insert(const std::string& word) {
    TrieNode* current = root_.get();
    
    for (char c : word) {
        int index = c - 'a';
        if (index < 0 || index >= 26) {
            continue; // Skip non-lowercase letters
        }
        
        if (!current->children[index]) {
            current->children[index] = std::make_unique<TrieNode>();
        }
        
        current = current->children[index].get();
        current->prefix_count++;
    }
    
    if (!current->is_end_of_word) {
        current->is_end_of_word = true;
        total_words_++;
    }
    current->word_count++;
}

bool Trie::search(const std::string& word) const {
    TrieNode* node = find_node(word);
    return node && node->is_end_of_word;
}

bool Trie::starts_with(const std::string& prefix) const {
    return find_node(prefix) != nullptr;
}

bool Trie::remove(const std::string& word) {
    if (!search(word)) {
        return false;
    }
    
    remove_helper(root_.get(), word, 0);
    total_words_--;
    return true;
}

std::vector<std::string> Trie::get_words_with_prefix(const std::string& prefix) const {
    std::vector<std::string> words;
    TrieNode* prefix_node = find_node(prefix);
    
    if (prefix_node) {
        collect_words(prefix_node, prefix, words);
    }
    
    return words;
}

std::vector<std::string> Trie::get_all_words() const {
    std::vector<std::string> words;
    collect_words(root_.get(), "", words);
    return words;
}

int Trie::count_words_with_prefix(const std::string& prefix) const {
    TrieNode* node = find_node(prefix);
    return node ? node->prefix_count : 0;
}

std::string Trie::longest_common_prefix() const {
    std::string lcp;
    TrieNode* current = root_.get();
    
    while (current) {
        int child_count = 0;
        int child_index = -1;
        
        for (int i = 0; i < 26; ++i) {
            if (current->children[i]) {
                child_count++;
                child_index = i;
            }
        }
        
        // Stop if we have multiple children or reached end of word
        if (child_count != 1 || current->is_end_of_word) {
            break;
        }
        
        lcp += static_cast<char>('a' + child_index);
        current = current->children[child_index].get();
    }
    
    return lcp;
}

std::vector<std::string> Trie::auto_complete(const std::string& prefix, int max_suggestions) const {
    std::vector<std::string> suggestions;
    TrieNode* prefix_node = find_node(prefix);
    
    if (prefix_node) {
        int count = 0;
        collect_words_limited(prefix_node, prefix, suggestions, count, max_suggestions);
    }
    
    return suggestions;
}

std::vector<std::string> Trie::shortest_unique_prefixes(const std::vector<std::string>& words) {
    Trie trie;
    
    // Insert all words
    for (const std::string& word : words) {
        trie.insert(word);
    }
    
    std::vector<std::string> prefixes;
    
    for (const std::string& word : words) {
        std::string prefix;
        TrieNode* current = trie.root_.get();
        
        for (char c : word) {
            int index = c - 'a';
            if (index < 0 || index >= 26) continue;
            
            prefix += c;
            current = current->children[index].get();
            
            // If this is the only word with this prefix, we found the shortest unique prefix
            if (current && current->prefix_count == 1) {
                break;
            }
        }
        
        prefixes.push_back(prefix);
    }
    
    return prefixes;
}

bool Trie::empty() const {
    return total_words_ == 0;
}

int Trie::size() const {
    return total_words_;
}

void Trie::clear() {
    root_ = std::make_unique<TrieNode>();
    total_words_ = 0;
}

void Trie::print_words() const {
    std::cout << "Trie contains " << total_words_ << " words:\n";
    print_words_helper(root_.get(), "");
}

// Trie Helper Methods

Trie::TrieNode* Trie::find_node(const std::string& prefix) const {
    TrieNode* current = root_.get();
    
    for (char c : prefix) {
        int index = c - 'a';
        if (index < 0 || index >= 26 || !current->children[index]) {
            return nullptr;
        }
        current = current->children[index].get();
    }
    
    return current;
}

void Trie::collect_words(TrieNode* node, const std::string& prefix, std::vector<std::string>& words) const {
    if (!node) return;
    
    if (node->is_end_of_word) {
        words.push_back(prefix);
    }
    
    for (int i = 0; i < 26; ++i) {
        if (node->children[i]) {
            char next_char = static_cast<char>('a' + i);
            collect_words(node->children[i].get(), prefix + next_char, words);
        }
    }
}

void Trie::collect_words_limited(TrieNode* node, const std::string& prefix, 
                                std::vector<std::string>& words, int& count, int limit) const {
    if (!node || count >= limit) return;
    
    if (node->is_end_of_word) {
        words.push_back(prefix);
        count++;
        if (count >= limit) return;
    }
    
    for (int i = 0; i < 26; ++i) {
        if (node->children[i] && count < limit) {
            char next_char = static_cast<char>('a' + i);
            collect_words_limited(node->children[i].get(), prefix + next_char, words, count, limit);
        }
    }
}

bool Trie::remove_helper(TrieNode* node, const std::string& word, int index) {
    if (index == static_cast<int>(word.length())) {
        if (!node->is_end_of_word) {
            return false;
        }
        
        node->is_end_of_word = false;
        node->word_count--;
        
        // Check if node has any children
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                return false; // Don't delete this node, it has children
            }
        }
        
        return true; // Delete this node if it has no children and no words end here
    }
    
    int char_index = word[index] - 'a';
    if (char_index < 0 || char_index >= 26 || !node->children[char_index]) {
        return false;
    }
    
    TrieNode* child = node->children[char_index].get();
    bool should_delete_child = remove_helper(child, word, index + 1);
    
    if (should_delete_child) {
        node->children[char_index].reset();
        
        // Check if current node should be deleted
        if (!node->is_end_of_word) {
            for (int i = 0; i < 26; ++i) {
                if (node->children[i]) {
                    return false; // Don't delete this node, it has other children
                }
            }
            return true; // Delete this node if it has no children and no words end here
        }
    }
    
    return false;
}

void Trie::print_words_helper(TrieNode* node, const std::string& prefix) const {
    if (!node) return;
    
    if (node->is_end_of_word) {
        std::cout << "  " << prefix << "\n";
    }
    
    for (int i = 0; i < 26; ++i) {
        if (node->children[i]) {
            char next_char = static_cast<char>('a' + i);
            print_words_helper(node->children[i].get(), prefix + next_char);
        }
    }
}

// Explicit template instantiations for common types

// Heap instantiations
template class Heap<int, std::less<int>>;
template class Heap<int, std::greater<int>>;
template class Heap<double, std::less<double>>;
template class Heap<double, std::greater<double>>;
template class Heap<std::string, std::less<std::string>>;
template class Heap<std::string, std::greater<std::string>>;

// Utility function instantiations
template bool is_heap_array<int>(const std::vector<int>& arr, const std::less<int>& comp);
template bool is_heap_array<int>(const std::vector<int>& arr, const std::greater<int>& comp);
template bool is_heap_array<double>(const std::vector<double>& arr, const std::less<double>& comp);
template bool is_heap_array<double>(const std::vector<double>& arr, const std::greater<double>& comp);

template void heapify_array<int>(std::vector<int>& arr, const std::less<int>& comp);
template void heapify_array<int>(std::vector<int>& arr, const std::greater<int>& comp);
template void heapify_array<double>(std::vector<double>& arr, const std::less<double>& comp);
template void heapify_array<double>(std::vector<double>& arr, const std::greater<double>& comp);

template int find_kth_largest<int>(const std::vector<int>& arr, int k);
template double find_kth_largest<double>(const std::vector<double>& arr, int k);

template int find_kth_smallest<int>(const std::vector<int>& arr, int k);
template double find_kth_smallest<double>(const std::vector<double>& arr, int k);

template std::vector<int> merge_k_sorted_arrays<int>(const std::vector<std::vector<int>>& arrays);
template std::vector<double> merge_k_sorted_arrays<double>(const std::vector<std::vector<double>>& arrays);
template std::vector<std::string> merge_k_sorted_arrays<std::string>(const std::vector<std::vector<std::string>>& arrays);

} // namespace data_structures
} // namespace leetcode_study_guide