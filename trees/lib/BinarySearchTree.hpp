#pragma once
#include <iostream>
 
template<typename T>
class BTNode {
    public:
        T data;
        BTNode *left;
        BTNode *right;
        BTNode *parent;

        BTNode* getLeft() const { return left; }
        BTNode* getRight() const { return right; }
        T getData() const { return data; }
 
        BTNode(T _it, BTNode *_parent = nullptr) : data(_it), left(nullptr), right(nullptr), parent(_parent) {}
};
 
template<typename T>
class BinarySearchTree {
    private:
        BTNode<T> *root;
 
        void insert(BTNode<T> *&node, T key_value, BTNode<T> *parent_node) {
            if(!node) {
                node = new BTNode<T>(key_value, parent_node);
                return;
            }
            if(key_value < node->data)
                return insert(node->left, key_value, node);
            else if(key_value > node->data)
                return insert(node->right, key_value, node);
        }
 
        template<typename F>
        void in_order_traversal(F func, BTNode<T> *node) {
            if(node){
                in_order_traversal(func, node->left);
                func(node);
                in_order_traversal(func, node->right);
            }
        }
 
        template<typename F>
        void pre_order_traversal(F func, BTNode<T> *node) {
            if(node){
                func(node);
                pre_order_traversal(func, node->left);
                pre_order_traversal(func, node->right);
            }
        }
 
        template<typename F>
        void post_order_traversal(F func, BTNode<T> *node) {
            if(node){
                post_order_traversal(func, node->left);
                post_order_traversal(func, node->right);
                func(node);
            }
        }
 
        template <typename O>
        BTNode<T> *search_node(BTNode<T> *node, O key_value) {
            if(!node || node->data == key_value)
                return node;
            if(key_value < node->data)
                return search_node(node->left, key_value);
            else if(key_value > node->data)
                return search_node(node->right, key_value);
 
            return nullptr;
        }
 
        BTNode<T> *findMin(BTNode<T> *node) {
            while(node && node->left)
                node = node->left;
 
            return node;
        }
 
        BTNode<T> *findMax(BTNode<T> *node) {
            while(node && node->right)
                node = node->right;
 
            return node;
        }
 
        BTNode<T> *remove_node(BTNode<T> *node, T key_value) {
            if(!node) return nullptr;
 
            if(key_value < node->data)
                node->left = remove_node(node->left, key_value);
            else if(key_value > node->data)
                node->right = remove_node(node->right, key_value);
            else {
                if(!node->left) {
                    BTNode<T> *tmp = node->right;
                    delete node;
                    return tmp;
                } else if(!node->right) {
                    BTNode<T> *tmp = node->left;
                    delete node;
                    return tmp;
                }
 
                BTNode<T> *minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove_node(node->right, minNode->data);
            }
            return node;
        }
 
        void print_tree_helper(BTNode<T> *node, int space) {
            if (node == nullptr) {
                return;
            }
            space += 10;
            print_tree_helper(node->right, space);
            std::cout << std::endl;
 
            for (int i = 10; i < space; i++)
                std::cout << " ";
            std::cout << node->data << "\n";
 
            print_tree_helper(node->left, space);
        }

 
    public:
        void add_right(BTNode<T> *node, T key_value) {
            if(node != nullptr){
                if(node->right == nullptr)
                    node->right = new BTNode<T>(key_value);
            }
        }

        void add_left(BTNode<T> *node, T key_value) {
            if(node != nullptr){
                if(node->left == nullptr) {
                    node->left = new BTNode<T>(key_value);
                }
            }
        }
        
        BinarySearchTree() : root(nullptr) {}
 
        void insert(T key_v) {
            insert(root, key_v, nullptr);
        }
 
        template<typename F>
        void in_order_traversal(F func) {
            in_order_traversal(func, root);
            std::cout << "\n";    
        }
 
        template<typename F>
        void pre_order_traversal(F func) {
            pre_order_traversal(func, root);
            std::cout << "\n";    
        }
 
        template<typename F>
        void post_order_traversal(F func) {
            post_order_traversal(func, root);
            std::cout << "\n";    
        }
 
        template<typename O>
        BTNode<T> *search(O key_v) {
            return search_node(root, key_v);
        }
 
        T findMin() {
            BTNode<T> *min_node = findMin(root);
            return min_node ? min_node->data : T();
        }
        T findMax() {
            BTNode<T> *max_node = findMax(root);
            return max_node ? max_node->data : T();
        }
 
        void remove(T key_v) {
            root = remove_node(root, key_v);
        }
 
        void print_tree() {
            print_tree_helper(root, 0);
        }

        BTNode<T> *getRoot() { return root; }
};