#pragma once
#include <iostream>
#include <list>

template<typename T>
class GenericTreeNode {
  private:
    T data;
    std::list<GenericTreeNode<T>*> children;
    GenericTreeNode<T> *parent = nullptr;
  public:

    GenericTreeNode(T init_data) : data(init_data) {}
    GenericTreeNode() = default;

    T get_data() { return data; }
    std::list<GenericTreeNode<T>*> get_children() { return children; }
    GenericTreeNode<T> *get_parent() { return parent; }

    GenericTreeNode<T> *search(T target_v) {
      if(this->data == target_v) return this;
      
      for(auto child : children) {
        GenericTreeNode<T> *found = child->search(target_v);
        if(found != nullptr) return found;
      }

      return nullptr;
    }

    void insert(T value) {
      GenericTreeNode<T> *node = new GenericTreeNode<T>(value);
      node->parent = this;
      children.push_back(node);
    }

    void insert(T p_value, T c_value) {
      GenericTreeNode<T> *p_node = search(p_value);
      if(p_node)
        p_node->insert(c_value);
    }

    void remove(T target) {
      GenericTreeNode<T> *node = nullptr;
      for(auto child : children) {
        if(child->data == target) {
          node = child;
          break;
        }
      }

      if(node) {
        children.remove_if([=](auto child) { return child == node; });
        for(auto child : node->children)
          node->remove(child->data);
        delete node;
      }
    }

    template<typename F>
    void for_each(F func) {
      func(this->data);
      for(auto child : children)
        child->for_each(func);
      // func(this->data)
    }

    // example
    // auto lambda_func = [](GenericTreeNode<T> *node) { std::cout << node->data << " "; }
  
    void print(size_t depth = 0){
      for(size_t i = 0; i < depth; i++)
        std::cout << "\t";
      std::cout << data << std::endl;
      for(auto child : children) {
        child->print(depth + 1);
      }
    }
};