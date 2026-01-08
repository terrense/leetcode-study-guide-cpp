/**
 * @file linked_list.tpp
 * @brief Template implementation for LinkedList classes
 * @author LeetCode Study Guide Team
 * @version 1.0.0
 */

#include <stdexcept>
#include <iostream>
#include <queue>

namespace leetcode_study_guide {
namespace data_structures {

// SinglyLinkedList Implementation

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(std::initializer_list<T> init_list) 
    : head_(nullptr), size_(0) {
    for (const auto& value : init_list) {
        push_back(value);
    }
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const std::vector<T>& values) 
    : head_(nullptr), size_(0) {
    for (const auto& value : values) {
        push_back(value);
    }
}

template<typename T>
void SinglyLinkedList<T>::push_front(const T& value) {
    auto new_node = std::make_shared<ListNode<T>>(value, head_);
    head_ = new_node;
    size_++;
}

template<typename T>
void SinglyLinkedList<T>::push_back(const T& value) {
    auto new_node = std::make_shared<ListNode<T>>(value);
    
    if (!head_) {
        head_ = new_node;
    } else {
        auto current = head_;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    size_++;
}

template<typename T>
void SinglyLinkedList<T>::insert(size_t position, const T& value) {
    if (position > size_) {
        throw std::out_of_range("Position out of range");
    }
    
    if (position == 0) {
        push_front(value);
        return;
    }
    
    auto prev = get_node_at(position - 1);
    auto new_node = std::make_shared<ListNode<T>>(value, prev->next);
    prev->next = new_node;
    size_++;
}

template<typename T>
void SinglyLinkedList<T>::pop_front() {
    if (!head_) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    
    head_ = head_->next;
    size_--;
}

template<typename T>
void SinglyLinkedList<T>::pop_back() {
    if (!head_) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    
    if (size_ == 1) {
        head_ = nullptr;
        size_--;
        return;
    }
    
    auto current = head_;
    while (current->next && current->next->next) {
        current = current->next;
    }
    current->next = nullptr;
    size_--;
}

template<typename T>
void SinglyLinkedList<T>::erase(size_t position) {
    if (position >= size_) {
        throw std::out_of_range("Position out of range");
    }
    
    if (position == 0) {
        pop_front();
        return;
    }
    
    auto prev = get_node_at(position - 1);
    prev->next = prev->next->next;
    size_--;
}

template<typename T>
void SinglyLinkedList<T>::remove(const T& value) {
    while (head_ && head_->data == value) {
        pop_front();
    }
    
    if (!head_) return;
    
    auto current = head_;
    while (current->next) {
        if (current->next->data == value) {
            current->next = current->next->next;
            size_--;
        } else {
            current = current->next;
        }
    }
}

template<typename T>
int SinglyLinkedList<T>::find(const T& value) const {
    auto current = head_;
    int position = 0;
    
    while (current) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    
    return -1;
}

template<typename T>
T& SinglyLinkedList<T>::at(size_t position) {
    if (position >= size_) {
        throw std::out_of_range("Position out of range");
    }
    return get_node_at(position)->data;
}

template<typename T>
const T& SinglyLinkedList<T>::at(size_t position) const {
    if (position >= size_) {
        throw std::out_of_range("Position out of range");
    }
    return get_node_at(position)->data;
}

template<typename T>
void SinglyLinkedList<T>::reverse() {
    NodePtr prev = nullptr;
    NodePtr current = head_;
    NodePtr next = nullptr;
    
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    head_ = prev;
}

template<typename T>
void SinglyLinkedList<T>::reverse_recursive() {
    head_ = reverse_recursive_helper(head_);
}

template<typename T>
typename SinglyLinkedList<T>::NodePtr 
SinglyLinkedList<T>::reverse_recursive_helper(NodePtr node) {
    if (!node || !node->next) {
        return node;
    }
    
    NodePtr new_head = reverse_recursive_helper(node->next);
    node->next->next = node;
    node->next = nullptr;
    
    return new_head;
}

template<typename T>
bool SinglyLinkedList<T>::has_cycle() const {
    if (!head_ || !head_->next) return false;
    
    auto slow = head_;
    auto fast = head_;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true;
        }
    }
    
    return false;
}

template<typename T>
typename SinglyLinkedList<T>::NodePtr 
SinglyLinkedList<T>::find_cycle_start() const {
    if (!has_cycle()) return nullptr;
    
    auto slow = head_;
    auto fast = head_;
    
    // Find meeting point
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    // Find start of cycle
    slow = head_;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}

template<typename T>
typename SinglyLinkedList<T>::NodePtr 
SinglyLinkedList<T>::find_middle() const {
    if (!head_) return nullptr;
    
    auto slow = head_;
    auto fast = head_;
    
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

template<typename T>
void SinglyLinkedList<T>::remove_nth_from_end(size_t n) {
    if (n == 0 || n > size_) return;
    
    auto dummy = std::make_shared<ListNode<T>>(T{});
    dummy->next = head_;
    
    auto first = dummy;
    auto second = dummy;
    
    // Move first pointer n+1 steps ahead
    for (size_t i = 0; i <= n; ++i) {
        first = first->next;
    }
    
    // Move both pointers until first reaches end
    while (first) {
        first = first->next;
        second = second->next;
    }
    
    // Remove the nth node from end
    second->next = second->next->next;
    head_ = dummy->next;
    size_--;
}

template<typename T>
SinglyLinkedList<T> SinglyLinkedList<T>::merge_sorted(const SinglyLinkedList<T>& other) const {
    SinglyLinkedList<T> result;
    auto dummy = std::make_shared<ListNode<T>>(T{});
    auto current = dummy;
    
    auto ptr1 = head_;
    auto ptr2 = other.head_;
    
    while (ptr1 && ptr2) {
        if (ptr1->data <= ptr2->data) {
            current->next = std::make_shared<ListNode<T>>(ptr1->data);
            ptr1 = ptr1->next;
        } else {
            current->next = std::make_shared<ListNode<T>>(ptr2->data);
            ptr2 = ptr2->next;
        }
        current = current->next;
        result.size_++;
    }
    
    while (ptr1) {
        current->next = std::make_shared<ListNode<T>>(ptr1->data);
        ptr1 = ptr1->next;
        current = current->next;
        result.size_++;
    }
    
    while (ptr2) {
        current->next = std::make_shared<ListNode<T>>(ptr2->data);
        ptr2 = ptr2->next;
        current = current->next;
        result.size_++;
    }
    
    result.head_ = dummy->next;
    return result;
}

template<typename T>
bool SinglyLinkedList<T>::is_palindrome() const {
    if (size_ <= 1) return true;
    
    // Find middle
    auto middle = find_middle();
    
    // Reverse second half
    auto second_half = middle->next;
    middle->next = nullptr;
    
    NodePtr prev = nullptr;
    auto current = second_half;
    while (current) {
        auto next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    // Compare first and second half
    auto first = head_;
    auto second = prev;
    bool is_palindrome = true;
    
    while (second) {
        if (first->data != second->data) {
            is_palindrome = false;
            break;
        }
        first = first->next;
        second = second->next;
    }
    
    // Restore original list (reverse second half back)
    current = prev;
    prev = nullptr;
    while (current) {
        auto next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    middle->next = prev;
    
    return is_palindrome;
}

template<typename T>
void SinglyLinkedList<T>::clear() {
    head_ = nullptr;
    size_ = 0;
}

template<typename T>
std::vector<T> SinglyLinkedList<T>::to_vector() const {
    std::vector<T> result;
    result.reserve(size_);
    
    auto current = head_;
    while (current) {
        result.push_back(current->data);
        current = current->next;
    }
    
    return result;
}

template<typename T>
void SinglyLinkedList<T>::print() const {
    auto current = head_;
    while (current) {
        std::cout << current->data;
        if (current->next) std::cout << " -> ";
        current = current->next;
    }
    std::cout << " -> nullptr" << std::endl;
}

template<typename T>
typename SinglyLinkedList<T>::NodePtr 
SinglyLinkedList<T>::get_node_at(size_t position) const {
    if (position >= size_) {
        throw std::out_of_range("Position out of range");
    }
    
    auto current = head_;
    for (size_t i = 0; i < position; ++i) {
        current = current->next;
    }
    
    return current;
}

// DoublyLinkedList Implementation

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> init_list) 
    : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto& value : init_list) {
        push_back(value);
    }
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const std::vector<T>& values) 
    : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto& value : values) {
        push_back(value);
    }
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    auto new_node = std::make_shared<DoublyListNode<T>>(value);
    
    if (!head_) {
        head_ = tail_ = new_node;
    } else {
        new_node->next = head_;
        head_->prev = new_node;
        head_ = new_node;
    }
    size_++;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    auto new_node = std::make_shared<DoublyListNode<T>>(value);
    
    if (!tail_) {
        head_ = tail_ = new_node;
    } else {
        tail_->next = new_node;
        new_node->prev = tail_;
        tail_ = new_node;
    }
    size_++;
}

template<typename T>
void DoublyLinkedList<T>::insert(size_t position, const T& value) {
    if (position > size_) {
        throw std::out_of_range("Position out of range");
    }
    
    if (position == 0) {
        push_front(value);
        return;
    }
    
    if (position == size_) {
        push_back(value);
        return;
    }
    
    auto new_node = std::make_shared<DoublyListNode<T>>(value);
    auto current = get_node_at(position);
    
    new_node->next = current;
    new_node->prev = current->prev.lock();
    
    if (auto prev_node = current->prev.lock()) {
        prev_node->next = new_node;
    }
    current->prev = new_node;
    
    size_++;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (!head_) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    
    if (size_ == 1) {
        head_ = tail_ = nullptr;
    } else {
        head_ = head_->next;
        head_->prev.reset();
    }
    size_--;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (!tail_) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    
    if (size_ == 1) {
        head_ = tail_ = nullptr;
    } else {
        tail_ = tail_->prev.lock();
        tail_->next = nullptr;
    }
    size_--;
}

template<typename T>
void DoublyLinkedList<T>::erase(size_t position) {
    if (position >= size_) {
        throw std::out_of_range("Position out of range");
    }
    
    if (position == 0) {
        pop_front();
        return;
    }
    
    if (position == size_ - 1) {
        pop_back();
        return;
    }
    
    auto current = get_node_at(position);
    auto prev_node = current->prev.lock();
    auto next_node = current->next;
    
    if (prev_node) {
        prev_node->next = next_node;
    }
    if (next_node) {
        next_node->prev = prev_node;
    }
    
    size_--;
}

template<typename T>
int DoublyLinkedList<T>::find(const T& value) const {
    auto current = head_;
    int position = 0;
    
    while (current) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    
    return -1;
}

template<typename T>
T& DoublyLinkedList<T>::at(size_t position) {
    if (position >= size_) {
        throw std::out_of_range("Position out of range");
    }
    return get_node_at(position)->data;
}

template<typename T>
const T& DoublyLinkedList<T>::at(size_t position) const {
    if (position >= size_) {
        throw std::out_of_range("Position out of range");
    }
    return get_node_at(position)->data;
}

template<typename T>
void DoublyLinkedList<T>::reverse() {
    auto current = head_;
    
    while (current) {
        // Swap next and prev pointers
        auto temp = current->next;
        current->next = current->prev.lock();
        current->prev = temp;
        
        // Move to next node (which is now in prev)
        current = temp;
    }
    
    // Swap head and tail
    std::swap(head_, tail_);
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    head_ = tail_ = nullptr;
    size_ = 0;
}

template<typename T>
std::vector<T> DoublyLinkedList<T>::to_vector() const {
    std::vector<T> result;
    result.reserve(size_);
    
    auto current = head_;
    while (current) {
        result.push_back(current->data);
        current = current->next;
    }
    
    return result;
}

template<typename T>
void DoublyLinkedList<T>::print_forward() const {
    auto current = head_;
    std::cout << "Forward: ";
    while (current) {
        std::cout << current->data;
        if (current->next) std::cout << " <-> ";
        current = current->next;
    }
    std::cout << " <-> nullptr" << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::print_backward() const {
    auto current = tail_;
    std::cout << "Backward: ";
    while (current) {
        std::cout << current->data;
        if (auto prev = current->prev.lock()) std::cout << " <-> ";
        current = current->prev.lock();
    }
    std::cout << " <-> nullptr" << std::endl;
}

template<typename T>
typename DoublyLinkedList<T>::NodePtr 
DoublyLinkedList<T>::get_node_at(size_t position) const {
    if (position >= size_) {
        throw std::out_of_range("Position out of range");
    }
    
    // Optimize by choosing direction based on position
    if (position < size_ / 2) {
        // Start from head
        auto current = head_;
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        return current;
    } else {
        // Start from tail
        auto current = tail_;
        for (size_t i = size_ - 1; i > position; --i) {
            current = current->prev.lock();
        }
        return current;
    }
}

// CircularLinkedList Implementation

template<typename T>
CircularLinkedList<T>::CircularLinkedList(std::initializer_list<T> init_list) 
    : head_(nullptr), size_(0) {
    for (const auto& value : init_list) {
        push_back(value);
    }
}

template<typename T>
void CircularLinkedList<T>::push_front(const T& value) {
    auto new_node = std::make_shared<ListNode<T>>(value);
    
    if (!head_) {
        head_ = new_node;
        new_node->next = new_node;  // Point to itself
    } else {
        // Find last node
        auto last = head_;
        while (last->next != head_) {
            last = last->next;
        }
        
        new_node->next = head_;
        last->next = new_node;
        head_ = new_node;
    }
    size_++;
}

template<typename T>
void CircularLinkedList<T>::push_back(const T& value) {
    auto new_node = std::make_shared<ListNode<T>>(value);
    
    if (!head_) {
        head_ = new_node;
        new_node->next = new_node;  // Point to itself
    } else {
        // Find last node
        auto last = head_;
        while (last->next != head_) {
            last = last->next;
        }
        
        last->next = new_node;
        new_node->next = head_;
    }
    size_++;
}

template<typename T>
void CircularLinkedList<T>::pop_front() {
    if (!head_) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    
    if (size_ == 1) {
        head_ = nullptr;
    } else {
        // Find last node
        auto last = head_;
        while (last->next != head_) {
            last = last->next;
        }
        
        last->next = head_->next;
        head_ = head_->next;
    }
    size_--;
}

template<typename T>
void CircularLinkedList<T>::pop_back() {
    if (!head_) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    
    if (size_ == 1) {
        head_ = nullptr;
    } else {
        // Find second-to-last node
        auto current = head_;
        while (current->next->next != head_) {
            current = current->next;
        }
        
        current->next = head_;
    }
    size_--;
}

template<typename T>
void CircularLinkedList<T>::clear() {
    if (head_) {
        // Break the circular link first
        auto last = head_;
        while (last->next != head_) {
            last = last->next;
        }
        last->next = nullptr;
    }
    
    head_ = nullptr;
    size_ = 0;
}

template<typename T>
std::vector<T> CircularLinkedList<T>::to_vector() const {
    std::vector<T> result;
    if (!head_) return result;
    
    result.reserve(size_);
    auto current = head_;
    
    do {
        result.push_back(current->data);
        current = current->next;
    } while (current != head_);
    
    return result;
}

template<typename T>
void CircularLinkedList<T>::print() const {
    if (!head_) {
        std::cout << "Empty circular list" << std::endl;
        return;
    }
    
    auto current = head_;
    do {
        std::cout << current->data;
        current = current->next;
        if (current != head_) std::cout << " -> ";
    } while (current != head_);
    std::cout << " -> (back to " << head_->data << ")" << std::endl;
}

// Standalone Algorithm Functions

template<typename T>
SinglyLinkedList<T> merge_k_sorted_lists(const std::vector<SinglyLinkedList<T>>& lists) {
    if (lists.empty()) return SinglyLinkedList<T>();
    
    auto compare = [](const std::shared_ptr<ListNode<T>>& a, 
                     const std::shared_ptr<ListNode<T>>& b) {
        return a->data > b->data;  // Min heap
    };
    
    std::priority_queue<std::shared_ptr<ListNode<T>>, 
                       std::vector<std::shared_ptr<ListNode<T>>>, 
                       decltype(compare)> pq(compare);
    
    // Add first node of each list to priority queue
    for (const auto& list : lists) {
        if (list.head()) {
            pq.push(list.head());
        }
    }
    
    SinglyLinkedList<T> result;
    auto dummy = std::make_shared<ListNode<T>>(T{});
    auto current = dummy;
    
    while (!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        
        current->next = std::make_shared<ListNode<T>>(node->data);
        current = current->next;
        
        if (node->next) {
            pq.push(node->next);
        }
    }
    
    result.head_ = dummy->next;
    
    // Calculate size
    auto temp = result.head_;
    while (temp) {
        result.size_++;
        temp = temp->next;
    }
    
    return result;
}

template<typename T>
SinglyLinkedList<T> rotate_right(const SinglyLinkedList<T>& list, int k) {
    if (list.empty() || k == 0) return list;
    
    SinglyLinkedList<T> result = list;  // Copy constructor needed
    int n = static_cast<int>(result.size());
    k = k % n;
    
    if (k == 0) return result;
    
    // Find the new tail (n-k-1 from start)
    auto new_tail = result.head();
    for (int i = 0; i < n - k - 1; ++i) {
        new_tail = new_tail->next;
    }
    
    // New head is next of new tail
    auto new_head = new_tail->next;
    
    // Break the connection
    new_tail->next = nullptr;
    
    // Find the end of the new head part and connect to old head
    auto current = new_head;
    while (current->next) {
        current = current->next;
    }
    current->next = result.head();
    
    result.head_ = new_head;
    return result;
}

} // namespace data_structures
} // namespace leetcode_study_guide