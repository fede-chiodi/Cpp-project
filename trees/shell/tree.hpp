#pragma once
#include <iostream>
#include <list>
#include <cstring>
#include <fstream>

template <typename T>
class TreeNode {
    private:
        T data;
        std::list<TreeNode<T>*> children;
        TreeNode<T> *parent = nullptr;
        char attribute;
    public:
        TreeNode(T init_data) { this->data = init_data; }
        TreeNode() = default;
        T get_data() const { return data; }
        
        TreeNode<T>* get_parent() {
            return parent;
        } 

        char getAttribute() { return attribute; }
        
        void add_child(T new_data, char attribute_child = 'd') {
            TreeNode<T> *new_child = new TreeNode<T>(new_data);
            new_child->parent = this;
            new_child->attribute = attribute_child;
            children.push_back(new_child);
        }

        TreeNode<T> *search(T target) {
            if(this->data == target) return this;

            for(auto &child : children) {
                TreeNode<T> *found_child = child->search(target);
                if(found_child != nullptr) 
                    return found_child;
            }
            return nullptr;
        }
        
        void add_child(T parent_data, T child_data) {
            TreeNode<T> *parent = search(parent_data);
            if(parent != nullptr)
                parent->add_child(child_data);
        }

        void print_tree(size_t depth = 0, std::string prefix = "") {
            std::string connector = (depth > 0 ? "└── " : "");
            std::cout << prefix << connector << data << std::endl;
            prefix += (depth > 0 ? "    " : "");

            for (auto &child : children) {
                child->print_tree(depth + 1, prefix);
            }
        }

        bool is_descendant(TreeNode<T>* node) {
            if (this == node) return true;
            for (auto& child : children) {
                if (child->is_descendant(node)) return true;
            }
            return false;
        }

        void get_path(TreeNode<T> *curr) {
            std::cout << "\033[36m";
            if(this == curr) {
                std::cout << this->data;
                std::cout << "\033[0m";
                return;
            }

            for(auto &child : children) {
                if(child->is_descendant(curr)) {
                    if(this->data != "/")
                        std::cout << this->data << "/";
                    child->get_path(curr);
                    std::cout << "\033[0m";
                    return;
                }
            }
        }
        
        void list_dir() {
            std::cout << "\n\033[32m";
            for(auto& child : children) 
                std::cout << child->data << " ";
            std::cout << "\n\033[0m" << std::endl;
        }

        TreeNode<T>* find_direct_child(T target) {
            for (auto& child : children) {
                if (child->data == target) 
                    return child;
            }
            return nullptr;
        }

        void remove_child(T child_to_remove_data, std::string command = "") {
            TreeNode<T> *node = nullptr;

            for(auto child : children) {
                if(child->data == child_to_remove_data) {
                    node = child;
                    break;
                }
            }

            if(!node) {
                std::cerr << "Error, file or directory not found." << std::endl;
                return;
            }

            if(command == "rmdir" && node->attribute == 'd') {
                if(!node->children.empty())
                    std::cout << "all the files and directory inside will be removed\n";
                
                children.remove(node);
                delete node;
                std::cout << "Directory " << child_to_remove_data << " removed." << std::endl;

            } else if(command == "rm" && node->attribute == 'f') {
                children.remove(node);
                delete node;
                std::cout << "File " << child_to_remove_data << " removed." << std::endl;
            } else if (command == "rm" && node->attribute == 'd')
                std::cout << "cannot remove " << child_to_remove_data << " with " << command << " command\n";
            else if (command == "rmdir" && node->attribute == 'f')
                std::cout << "cannot remove " << child_to_remove_data << " with " << command << " command\n";
        }
  
        void serialize(std::ofstream& save_file) {
            if(!this) return;

            save_file << (parent ? parent->data : "") << ";" << this->data << ";" << this->attribute << "\n";

            for(TreeNode *child : children) {
               child->serialize(save_file);
            }
        }

        TreeNode<T>* deserialize(std::ifstream& load_file) {
            std::string file_line; 
            T parentData, childData;
            std::string node_attribute;
            while(std::getline(load_file, file_line)) {
                std::istringstream ss(file_line);
                std::getline(ss, parentData, ';');
                std::getline(ss, childData, ';');
                std::getline(ss, node_attribute, ';');
                
                if(parentData == "") {
                    this->parent = nullptr;
                    this->data = childData;
                    this->attribute = node_attribute[0];
                } else {
                    TreeNode<T> *parent_node = this->search(parentData);
                    if(parent_node) {
                        parent_node->add_child(childData, node_attribute[0]);
                    }
                }
            }

            return this;
        }
};
