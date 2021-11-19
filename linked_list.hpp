#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <typename T>
class linked_list {
 public:
    struct node {
        node* prev;
        node* next;
        T value;

        node(const T& value) : prev{nullptr}, next{nullptr}, value{value} {}
    };

    linked_list() : head{nullptr}, tail{nullptr}, the_size{0} {}

    const node* get_head() const { return this->head; }
    
    size_t size() const {
        return the_size;
    }
    
    bool empty() const { return size() == 0; }

    const T& at(size_t index) const {
        // check for out of bounds
        if (index >= size()) {
            throw std::out_of_range("index of access is out of bounds");
        }
        // traverse to index
        const node* the_node = traverse(index);
        if (the_node == nullptr) {
            throw std::runtime_error("failed to traverse to index");
        }
        // return node's value
        return the_node->value;
    }
    
    void insert(size_t index, const T& value) {
        // if index is out of bounds, throw exception
        if (index > size()) {
            throw std::out_of_range("index of insertion is out of bounds");
        }
        // make a new node
        node* the_node = new node(value);
        // if list is empty, insert at head-tail
        if (empty()) {
            head = the_node;
            tail = the_node;
        }
        // if index is 0, insert at head
        else if (index == 0) {
            // attach
            the_node->next = head;
            // reroute
            head->prev = the_node;
            // update head
            head = the_node;
        }
        // if index is size(), insert at tail
        else if (index == size()) {
            // attach
            the_node->prev = tail;
            // reroute
            tail->next = the_node;
            // update tail
            tail = the_node;
        }
        // else insert in middle
        else {
            //   traverse to index
            node* curr = traverse(index);
            //   connect
            the_node->next = curr;
            the_node->prev = curr->prev;
            //   reroute
            the_node->prev->next = the_node;
            the_node->next->prev = the_node;
        }
        the_size++;
    }
    
    void erase(size_t index) {
        // if index is out of bounds, throw exception
        if (index >= size()) {
            throw std::out_of_range("index of removal is out of bounds");
        }
        // if size is 1, delete head-tail
        if (size() == 1) {
            delete head;
            // oops.  missed these in class
            //head = nullptr;
            //tail = nullptr;
        }
        // if index is 0, delete head
        else if (index == 0) {
            // get pointer to old_head
            node* old_head = head;
            // disconnect
            old_head->next->prev = nullptr;
            // update head
            head = old_head->next;
            // delete old head
            delete old_head;
        }
        // if index is size-1, delete tail
        else if (index == size()-1) {
            node* old_tail = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete old_tail;
        }
        // else delete middle node
        else {
            //   traverse to index
            node* curr = traverse(index);
            //   reroute
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            //   delete
            delete curr;
        }
        the_size--;
    }

 private:
    node* head;
    node* tail;
    size_t the_size;

    const node* traverse(size_t index) const {
        if (index >= size()) {
            return nullptr;
        }
        node* curr = head;
        for (size_t i = 0; i < index && curr; i++, curr = curr->next) {}
        return curr;
    }

    node* traverse(size_t index) {
        if (index >= size()) {
            return nullptr;
        }
        node* curr = head;
        for (size_t i = 0; i < index && curr; i++, curr = curr->next) {}
        return curr;
    }
};

#endif  // LINKED_LIST_HPP 