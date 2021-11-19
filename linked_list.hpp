#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <initializer_list>

template <typename T>
class linked_list {
 public:
    struct node {
        node* prev;
        node* next;
        T value;
    };

    const node* get_head() const { return this->head; }
    
    size_t size() const { /* TODO */ return 0; }
    
    const T& at(size_t index) const {
        /* TODO */
        return *(new T);
    }
    
    void insert(size_t index, const T& value) {
        /* TODO */
    }
    
    void erase(size_t index) {
        /* TODO */
    }

 private:
    node* head;
};

#endif  // LINKED_LIST_HPP 