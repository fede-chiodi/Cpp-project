#pragma once
#include <iostream>

template<typename T>
class LinkedList {
    private:
        struct Node{
            T data;
            Node *next;

            Node(T x) : data(x), next(nullptr) {}
        };

        Node *head, *tail;
    public:
        LinkedList();
        ~LinkedList();

        bool is_empty();
        void push_at_head(T data);
        void push_at_tail(T data);
        void push_at_position(size_t position, T data);
        void pop();
        void top();
        void delete_at_tail();
        void delete_at_position(size_t position);
        
        template<typename F>
        void for_each(F func);

        void print_list();

        template<typename F>
        T search_and_return(F func);

        template<typename F>
        T at(F func);

        template<typename F>
        bool search(F func);

        template<typename F>
        LinkedList<T> map(F func);

        template<typename F>
        LinkedList<T> filter(F func);

        template<typename F>
        T find(F func);

        void reverse();
        size_t list_size();
        void unique();
};

//constructor
template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

//deconstructor
template<typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        pop();
    }
}

//verify if the list is empty
template<typename T>
bool LinkedList<T>::is_empty() {
    return head == nullptr;
}

//push a Node at head of the list
template<typename T>
void LinkedList<T>::push_at_head(T data) {
    Node *new_node = new Node(data);
    new_node->next = head;
    head = new_node;
}

//push a Node at tail of the list
template <typename T>
void LinkedList<T>::push_at_tail(T data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode; //push the new node ath the end of the list
    }
}

//push a Node in a x position
template<typename T>
void LinkedList<T>::push_at_position(size_t position, T data) {
    if (position == 0) {
        push_at_head(data);
        return;
    }

    Node *new_node = new Node(data);
    Node *_tmp = head;
    size_t current_pos = 0;

    while (_tmp != nullptr && current_pos < position - 1) {
        _tmp = _tmp->next;
        current_pos++;
    }

    if (_tmp == nullptr) {
        std::cout << "Position out of range" << std::endl;
        delete new_node; 
        return;
    }

    new_node->next = _tmp->next;
    _tmp->next = new_node;
}

template<typename T>
void LinkedList<T>::pop() {
    if(LinkedList::is_empty()) 
        return;

    Node *_tmp = head;
    head = head->next;
    delete _tmp;
}

template<typename T>
void LinkedList<T>::top() {
    if(LinkedList::is_empty())
        return;

    return head->data;
}

template<typename T>
void LinkedList<T>::delete_at_tail() {
    if(LinkedList::is_empty())
        return;
    
    //if the list is made by only one Node
    if(head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node *_tmp = head;
    while(_tmp->next != nullptr && _tmp->next->next != nullptr) { //finde the second last Node
        _tmp = _tmp->next;
    }

    delete _tmp->next;
    _tmp->next = nullptr; // Set the second last Node like the last Node
}

template<typename T>
void LinkedList<T>::delete_at_position(size_t position) {
    if(position < 0 || LinkedList::is_empty())
        return;
    
    if(position == 0){
        pop();
        return;
    }

    Node *_tmp = head;
    size_t curr_pos = 0;

    while (_tmp != nullptr && curr_pos < position - 1) {
        _tmp = _tmp->next;
        curr_pos++;
    }

    if(_tmp == nullptr || _tmp->next == nullptr) {
        std::cout << "Position out of range" << std::endl;
        return;
    }

    Node *_node_to_delete = _tmp->next;
    _tmp->next = _tmp->next->next;

    delete _node_to_delete;
}

template<typename T>
template<typename F>
void LinkedList<T>::for_each(F func) {
    Node *_tmp = head;
    while(_tmp != NULL) {
        func(_tmp->data);
        _tmp = _tmp->next;
    }
}

template<typename T>
void LinkedList<T>::print_list() {
    for_each([](T data) {
        std::cout << data << " -> ";
    });
    std::cout << "nullptr" << std::endl;
}

template<typename T>
template<typename F>
T LinkedList<T>::search_and_return(F func) {
    Node *_tmp = head;
    while (_tmp != nullptr){
        if(func(_tmp->data)) {
            return _tmp->data;
        }
        _tmp = _tmp->next;
    }

    return T(); //return a an empty object of type T
}

template<typename T>
template<typename F>
T LinkedList<T>::at(F func) {
    Node *_tmp = head;
    size_t index = 0;
    while(_tmp != nullptr){
        if(index == func()) {
            return _tmp->data;
        }
        _tmp = _tmp->next;
        index++;
    }

    return T();
}

template<typename T>
template<typename F>
bool LinkedList<T>::search(F func) {
    Node *_tmp = head;
    while(_tmp != nullptr) {
        if(func(_tmp->data)) {
            return true;
        }
        _tmp = _tmp->next;
    }

    return false;
}


//THis map function return a new Linked List with the result of the function applied to each element
template<typename T>
template<typename F>
LinkedList<T> LinkedList<T>::map(F func) {
    LinkedList<T> new_list;

    Node *_tmp = head;
    while(_tmp != nullptr) {
        new_list.push_at_tail(func(_tmp->data));
        _tmp = _tmp->next;
    }

    return new_list;
}

//This lambda function add to all the elemento of the list a condition and create a new list with the only element who satisfy the condition
template<typename T>
template<typename F>
LinkedList<T> LinkedList<T>::filter(F func) {
    LinkedList<T> new_list;
    Node* _tmp = head;

    while (_tmp != nullptr) {
        if (func(_tmp->data)) {
            new_list.push_at_tail(_tmp->data);
        }
        _tmp = _tmp->next;
    }

    return new_list;
}


//return the first element of the list who satisfy the condition
template<typename T>
template<typename F>
T LinkedList<T>::find(F func) {
    Node *_tmp = head;
    while(_tmp != nullptr) {
        if(func(_tmp->data)) {
            return _tmp->data;
        }
        _tmp = _tmp->next;
    }
    return T();
}

//this function reverse the list
template<typename T>
void LinkedList<T>::reverse() {
    Node *prev = nullptr;
    Node *curr = head;
    Node *next = nullptr;

    while(curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    head = prev;
}

template<typename T>
size_t LinkedList<T>::list_size() {
    size_t count = 0;
    Node* _tmp = head;
    while (_tmp != nullptr) {
        count++;
        _tmp = _tmp->next;
    }
    return count;
}


//this function remove the duplicate Nodes
template<typename T>
void LinkedList<T>::unique() {
    if (LinkedList::is_empty()) return;

    Node *curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        Node *runner = curr;
        while (runner->next != nullptr) {
            if (runner->next->data == curr->data) {
                Node *_tmp = runner->next;
                runner->next = _tmp->next;
                delete _tmp; //delete the duplicate Node
            } else {
                runner = runner->next;
            }
        }
        curr = curr->next;
    }
}
