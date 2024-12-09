#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class Queue {
  protected:
      struct Node {
        T data;
        Node *next;

        Node(T d) : data(d), next(nullptr) {}
      };  

      Node *head, *tail;
  public:
      
      Queue();
      ~Queue();

      bool is_empty();
      void enqueue(T data);
      T dequeue();
      T peek();

      size_t get_size() const;

      template<typename F>
      void for_each(F func);
      void print_queue();
};

// construct
template<typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr) {}

//deconstructor, frees memory from queue
template<typename T>
Queue<T>::~Queue() {
  while(!is_empty()) {
    dequeue();
  }
}

template<typename T>
bool Queue<T>::is_empty() {
  return head == nullptr;
}

template<typename T>
void Queue<T>::enqueue(T data) {
  Node *new_node = new Node(data);

  if(is_empty())
     head = tail = new_node;
  else {
    tail->next = new_node;
    tail = new_node;
  }
}

template<typename T>
T Queue<T>::dequeue() {
  if(is_empty())
    throw std::underflow_error("Queue is empty!");

  Node *node_to_delete = head;
  T head_data = head->data;
  head = head->next;

  if(head == nullptr)
    tail = nullptr;

  delete node_to_delete;
  return head_data; 
}

template<typename T>
T Queue<T>::peek() {
  if(is_empty())
    throw std::underflow_error("Queue is empty!");

  return head->data;
}

template<typename T>
size_t Queue<T>::get_size() const {
  size_t size = 0;
  Node *current = head;
  while(current != nullptr) {
    size++;
    current = current->next;
  }

  return size;
}

template<typename T>
template<typename F>
void Queue<T>::for_each(F func) {
  if(is_empty()){
    std::cout << "Queue is empty!" << std::endl;
    return;
  }

  Node *_tmp = head;
  while(_tmp != NULL) {
      func(_tmp->data);
      _tmp = _tmp->next;
  }
}

template<typename T>
void Queue<T>::print_queue(){
  if(is_empty()) {
    throw std::underflow_error("Queue is empty!");
    return;
  }
  else {
    for_each([] (T data){
      std::cout << data << " -> ";
    });
    std::cout << " nullptr" << std::endl;
  }
}