#include<iostream>
#include<vector>
#include<tuple>
#include<sstream>
#include<fstream>
#include"tree.hpp"

bool verify_extension_in_file_name(const std::string &str, const std::vector<std::string> &valid_extension) {
    for(auto &extension : valid_extension) {
        size_t pos = str.rfind(extension);
        if(pos != std::string::npos && pos == str.length() - extension.length()) {
            std::string str_no_extension = str.substr(0, pos);

            for(auto &other_extensioni : valid_extension) {
                if(str_no_extension.find(other_extensioni) != std::string::npos)
                    return false;
            }
            return true;
        }
    }
    return false;
}

std::tuple<std::string, std::string> parseInput(const std::string& input) {
    size_t pos = input.find(" ");
    if(pos != std::string::npos) {
        return {input.substr(0, pos), input.substr(pos + 1)};
    } else {
        return {input, ""};
    }
}

struct Commands {
    std::string command;
    std::string description;
};

std::vector<Commands> commands_list = {
    {"cd", "Change directory"},
    {"ls", "List files and directories"},
    {"mkdir", "Make a new directory"},
    {"touch", "Create a new file"},
    {"rm", "Remove a file"},
    {"rmdir", "Remove a directory"},
    {"pwd", "Print working directory"},
    {"tree", "Print the directory tree"},
};

int main() {
    // TreeNode<std::string> *fs = new TreeNode<std::string>("/");
    // fs->add_child("/", "home");
    // fs->add_child("home", "user");
    // fs->add_child("home", "user1");
    // fs->add_child("home", "user2");
    // fs->add_child("user", "Documents");
    // fs->add_child("user", "Downloads");
    // fs->add_child("user", "Desktop");
    // fs->add_child("user1", "Documents");
    // fs->add_child("user1", "Downloads");
    // fs->add_child("user1", "Desktop");
    // fs->add_child("user2", "Documents");
    // fs->add_child("user2", "Downloads");
    // fs->add_child("user2", "Desktop");
    std::ifstream file("tree.txt");
    TreeNode<std::string> *fs = new TreeNode<std::string>("/");
    fs->deserialize(file);
    file.close();
    
    std::cout << "\n--- BASE TREE OF THE FILE SYSTEM ---\n" << std::endl;
    fs->print_tree();

    std::cout << "\n---   USO YUOR LINUX SHELL SIMULATION   ---\n" << std::endl;
    std::cout << "\n---         COMMANDS         ---\n" << std::endl;
    for(auto &command : commands_list) {
        std::cout << command.command << "   -->     " << command.description << std::endl;
    }


    TreeNode<std::string> *current_dir = fs;
    std::string input;
    std::string command, arg;
    
    do {
        fs->get_path(current_dir);
        std::cout << " > ";
        std::getline(std::cin, input);

        std::tie(command, arg) = parseInput(input);

        if(command == "cd") {
            //nel caso in cui arg sia vuoto riporta alla root
            if(arg.empty()) {
                current_dir = fs;
            }

            // nel casio in cui arg inizi con '/' si tratta di un percorso assoluto e quindi si imposta la current_dir alla root, rappresentata dalla variabile fs
            if(!arg.empty() && arg[0] == '/') {
                current_dir = fs;
                arg = arg.substr(1); // elimina il primo carattere ---> '/'
            }

            std::istringstream path_stream(arg); //trasforma arg in un flusso di input per estrarre ogni directory
            std::string dir; // contenitore per le sub_directory

            /*
                FUNZIONAMENTO:
                utilizzando std::getline() si legge il flusso di input path_stream e ogni volta che si trova il carattere '/' (delimitatore) si memorizza ciò che è stato letto nella stringa
                fino ad ora in dir e la funzione std::getline() ritorna true. Quando non sono più presenti sottostringhe la funzione std::getline() ritorna false e si interrompe il ciclo.
            */

            while(std::getline(path_stream, dir, '/')) {
                std::cout << "Path part: " << dir << "\n";
                if(dir == "..") {
                    if(current_dir->get_parent() != nullptr)
                        current_dir = current_dir->get_parent();
                    else 
                        std::cout << "cannot go up from root" << std::endl;
                        break;
                } else if (dir != ".") {
                    TreeNode<std::string>* target_node = current_dir->find_direct_child(dir);
                    if(target_node != nullptr) {
                        if(target_node->getAttribute() == 'd') 
                            current_dir = target_node;
                        else 
                            std::cout << "Cannot reach a file\n";
                    } else {
                        std::cout << "directory not found" << std::endl;
                    }
                }
            }
        } else if(command == "pwd") {
            std::cout << "Your current path: ";
            fs->get_path(current_dir);
            std::cout << std::endl;
        } else if(command == "ls") {
            if(!arg.empty()) {
                TreeNode<std::string> *target_node = current_dir->find_direct_child(arg);
                if (target_node != nullptr) {
                    if (target_node->getAttribute() == 'd') {
                        target_node->list_dir();
                    } else
                        std::cout << arg << " is a file, not a directory." << std::endl;
                } else
                    std::cout << "argument not valid" << std::endl;
            } else
                current_dir->list_dir();
        } else if(command == "mkdir") {
            std::string new_dir = arg;
            char attribute_dir = 'd';
            current_dir->add_child(new_dir, attribute_dir);
        } else if(command == "tree") {
            current_dir->print_tree();
        } else if(command == "touch") {
            std::string new_file = arg;
            char attribute_file = 'f';
            std::vector<std::string> valid_extensions = {".txt", ".cpp", ".py", ".js", ".tsx", ".jpg", ".hpp", ".pdf", ".html", ".css", ".c", ".tsx", ".sql", ".apk"};
            if(verify_extension_in_file_name(new_file, valid_extensions)) {
                current_dir->add_child(new_file, attribute_file);
                std::cout << "File added" << std::endl;
            } else {
                std::cout << "File extension accepted: \n";
                for(auto extenison : valid_extensions) 
                    std::cout << "- " << extenison << "\n";
            }
        } else if(command == "rm") {
            std::string file_to_remove = arg;
            current_dir->remove_child(file_to_remove, command);
        } else if(command == "rmdir"){
            std::string dir_to_remove = arg;
            current_dir->remove_child(dir_to_remove, command);
        } else if(command == "exit") {
            std::cout << "exiting from the SHELL" << std::endl;
            std::ofstream save_file("tree.txt");
            fs->serialize(save_file);
            save_file.close();
        }
        else 
            std::cout << "Command not found" << std::endl;

    } while(command != "exit");

    return 0;   
}