#pragma once
#include <iostream>

template<typename T> 
class Stack {
    protected:
        struct Node{
            T data;
            Node* next;

            Node(T d, Node *n = nullptr) : data(d), next(n) {}
        };

        Node *head;
    
    public:
        Stack() : head(nullptr) {}

        size_t count();
        bool isEmpty();
        void push(T x);

        T pop();
        T top();
};

template<typename T>
size_t Stack<T>::count() {
    size_t counter = 0;
    Node *current = head;
    while(current != NULL) {
        counter++;
        current = current->next;
    }

    return counter;
}

template<typename T>
bool Stack<T>::isEmpty() {
  return head == NULL;
}

template<typename T>
void Stack<T>::push(T x) {
  head = new Node(x, head);
}

template<typename T>
T Stack<T>::pop() {
    if(isEmpty()) 
          throw std::underflow_error("Stack is empty");

    Node *_tmp = head;
    T _value = _tmp->data;
    head = head->next;
    
    delete _tmp;
    return _value;
}

template<typename T>
T Stack<T>::top() {
    if(isEmpty())
          throw std::underflow_error("Stack is empty");

    return head->data;
}
