#pragma once
#include <iostream>

template<typename T>
class BinarySearchTreeNode {
  private:
    T data;
    BinarySearchTreeNode<T> *left;
    BinarySearchTreeNode<T> *right;
    BinarySearchTreeNode<T> *parent;

    void insert_l(T l_value) {
      if(left == nullptr) {
        left = new BinarySearchTreeNode<T>(l_value);
        left->parent = this;
      }
    }

    void insert_r(T r_value) {
      if(right == nullptr) {
        right = new BinarySearchTreeNode<T>(r_value);
        right->parent = this;
      }
    }

  public:
    BinarySearchTreeNode(T init_data) : data(init_data), left(nullptr), right(nullptr), parent(nullptr) {}
    BinarySearchTreeNode() = default;

    T get_data() { return data; }
    BinarySearchTreeNode<T> *get_left() { return left; }
    BinarySearchTreeNode<T> *get_right() { return right; }
    BinarySearchTreeNode<T> *get_parent() { return parent; }

    template<typename F>
    void traversal_pre_order(F func) {
      func(this);
      if(left) left->traversal_pre_order(func);
      if(right) right->traversal_pre_order(func);
    }
    
    template<typename F>
    void traversal_in_order(F func) {
      if(left) left->traversal_in_order(func);
      func(this);
      if(right) right->traversal_in_order(func);
    }

    template<typename F>
    void traversal_post_order(F func) {
      if(left) left->traversal_post_order(func);
      if(right) right->traversal_post_order(func);
      func(this);
    }

    void insert(T value) {
      if(this->data > value && left == nullptr)
        return insert_l(value);
      if(this->data <= value && right == nullptr)
        return insert_r(value);

      return (this->data > value) ? left->insert(value) : right->insert(value);
    }

    BinarySearchTreeNode<T> *search(T target) {
      if(this->data == target) return this;
      if(this->data > target){
        if(left)
           return left->search(target);
        else
          return nullptr;
      } else if(this->data <= target) {
        if(right)
          return right->search(target);
        else
          return nullptr;
      }

      return nullptr;
    }

    bool is_leaf() {
      return right == nullptr && left == nullptr;
    }

    void print(size_t depth = 0){
      if(right) right->print(depth + 1);
      for(size_t i = 0; i < depth; i++)
        std::cout << "\t";
      std::cout << data << std::endl;
      if(left) left->print(depth + 1);
    }
};