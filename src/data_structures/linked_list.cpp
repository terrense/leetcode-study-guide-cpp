/**
 * @file linked_list.cpp
 * @brief Implementation file for LinkedList data structures
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include "leetcode_study_guide/data_structures/linked_list.h"
#include <iostream>

namespace leetcode_study_guide {
namespace data_structures {

// Explicit template instantiations for common types
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<std::string>;

template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<std::string>;

template class CircularLinkedList<int>;
template class CircularLinkedList<double>;
template class CircularLinkedList<std::string>;

// Explicit instantiations for standalone functions
template SinglyLinkedList<int> merge_k_sorted_lists<int>(const std::vector<SinglyLinkedList<int>>& lists);
template SinglyLinkedList<double> merge_k_sorted_lists<double>(const std::vector<SinglyLinkedList<double>>& lists);

template SinglyLinkedList<int> rotate_right<int>(const SinglyLinkedList<int>& list, int k);
template SinglyLinkedList<double> rotate_right<double>(const SinglyLinkedList<double>& list, int k);
template SinglyLinkedList<std::string> rotate_right<std::string>(const SinglyLinkedList<std::string>& list, int k);

// Implementation of add_two_numbers function
SinglyLinkedList<int> add_two_numbers(const SinglyLinkedList<int>& num1, 
                                      const SinglyLinkedList<int>& num2) {
    SinglyLinkedList<int> result;
    auto dummy = std::make_shared<ListNode<int>>(0);
    auto current = dummy;
    
    auto ptr1 = num1.head();
    auto ptr2 = num2.head();
    int carry = 0;
    
    while (ptr1 || ptr2 || carry) {
        int sum = carry;
        
        if (ptr1) {
            sum += ptr1->data;
            ptr1 = ptr1->next;
        }
        
        if (ptr2) {
            sum += ptr2->data;
            ptr2 = ptr2->next;
        }
        
        carry = sum / 10;
        current->next = std::make_shared<ListNode<int>>(sum % 10);
        current = current->next;
    }
    
    // Set up result
    result.head_ = dummy->next;
    
    // Calculate size
    auto temp = result.head_;
    while (temp) {
        result.size_++;
        temp = temp->next;
    }
    
    return result;
}

} // namespace data_structures
} // namespace leetcode_study_guide