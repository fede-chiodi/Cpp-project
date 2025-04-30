#pragma once
#include <iostream>

template<typename T>
class BinaryTreeNode {
  private:
   T data;
   BinaryTreeNode<T> *right;
   BinaryTreeNode<T> *left;
   BinaryTreeNode<T> *parent;
    
  public:
   BinaryTreeNode(T init_data) : data(init_data), left(nullptr), right(nullptr), parent(nullptr) {}
   BinaryTreeNode() = default;

   T get_data() { return data; }
   BinaryTreeNode<T> *get_left() { return left; }
   BinaryTreeNode<T> *get_right() { return right; }
   BinaryTreeNode<T> *get_parent() { return parent; }

   BinaryTreeNode<T> *search(T target_v) {
     if(this->data == target_v) return this;

     if(left) {
       BinaryTreeNode<T> *found = left->search(target_v);
       if(found != nullptr) return found;
     }
     if(right) {
       BinaryTreeNode<T> *found = right->search(target_v);
       if(found != nullptr) return found;
     }

     return nullptr;
   }

   void insert_l(T l_value) {
     if(left == nullptr) {
       left = new BinaryTreeNode<T>(l_value);
       left->parent = this;
     }
   }

   void insert_r(T r_value) {
    if(right == nullptr) {
      right = new BinaryTreeNode<T>(r_value);
      right->parent = this;
    }
   }

   void insert(T p_value, T c_value) {
     BinaryTreeNode<T> *p_node = search(p_value);
     if(p_node){
       if(p_node->left == nullptr)
         p_node->insert_l(c_value);
       else if(p_node->right == nullptr)
         p_node->insert_r(c_value);
     }
   }

   template<typename F>
   void pre_order(F func) {
     func(this);
     if(left) left->pre_order(func);
     if(right) right->pre_order(func);
   }

   template<typename F>
   void in_order(F func) {
     if(left) left->in_order(func);
     func(this);
     if(right) right->in_order(func);
   }

   template<typename F>
   void post_order(F func) {
     if(left) left->post_order(func);
     if(right) right->post_order(func);
     func(this);
   }

   void remove_left() {
     if(left) {
       delete left;
       left = nullptr;
     }
   }

   void remove_right() {
     if(right) {
       delete right;
       right = nullptr;
     }
   }

   void remove(T target_t) {
    BinaryTreeNode<T> *node = search(target_t);
    if(node){
      if(node->left)
        node->remove_left();
      if(node->right)
        node->remove_right();

      if(node->parent) {
        if(node->parent->left == node)
          node->parent->left = nullptr;
        else if(node->parent->right == node)
          node->parent->right = nullptr;
      }

      delete node;
    }
   }

   void print(size_t depth = 0) {
     for(size_t i = 0; i < depth; i++)
       std::cout << "\t";
     std::cout << data << std::endl;
     if(left) left->print(depth + 1);
     if(right) right->print(depth + 1);
   }
};
