/**
 * @file main.cpp
 * @brief Main entry point for LeetCode Study Guide
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/array.h"
#include <iostream>

using namespace leetcode_study_guide::data_structures;

int main() {
    std::cout << "LeetCode Study Guide - C++ Implementation" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    try {
        // Test basic array operations
        Array<int> arr{1, 2, 3, 4, 5};
        
        std::cout << "Created array with elements: ";
        for (size_t i = 0; i < arr.size(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        
        // Test search
        int search_val = 3;
        int index = arr.linear_search(search_val);
        std::cout << "Found " << search_val << " at index: " << index << std::endl;
        
        // Test two pointers
        auto result = arr.two_sum_sorted(7);
        if (result.first != -1) {
            std::cout << "Two sum result: indices " << result.first 
                      << " and " << result.second << std::endl;
        }
        
        // Test sorting
        Array<int> unsorted{5, 2, 8, 1, 9};
        std::cout << "Before sorting: ";
        for (size_t i = 0; i < unsorted.size(); ++i) {
            std::cout << unsorted[i] << " ";
        }
        std::cout << std::endl;
        
        unsorted.merge_sort();
        std::cout << "After merge sort: ";
        for (size_t i = 0; i < unsorted.size(); ++i) {
            std::cout << unsorted[i] << " ";
        }
        std::cout << std::endl;
        
        std::cout << "\nArray module implementation completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}