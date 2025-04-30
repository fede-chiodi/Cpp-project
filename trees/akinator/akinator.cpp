#include "../BSTree.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <thread>
#include <chrono> 

struct Record {
    std::string key, type_d;
    int id, parent_id;

    bool operator<(const Record &other) const {
        return id < other.id;
    }

    bool operator>(const Record &other) const {
        return id > other.id;
    }

    bool operator==(const Record &other) const {
        return id == other.id;
    }
};

//output
std::ostream &operator<<(std::ostream &os, const Record &record) {
    os << "(" << record.type_d << ")" << record.key;
    return os;
}

BinarySearchTree<Record> bst_akinator;

void load_from_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Errore nell'apertura del file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::stack<BTNode<Record>*> st;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, typeStr, keyStr, p_idStr;

        std::getline(ss, idStr, ';');
        std::getline(ss, typeStr, ';');
        std::getline(ss, keyStr, ';');
        std::getline(ss, p_idStr, ';');

        int id = std::stoi(idStr);
        int p_id = std::stoi(p_idStr);

        Record new_record = {keyStr, typeStr, id, p_id};

        // se lo stack è vuoto, inseriamo il nodo root, e lo pushiamo nello stack
        if(st.empty()) {
            bst_akinator.insert(new_record);
            st.push(bst_akinator.getRoot());
        }
        // se lo stack non è vuoto significa che il nodo esaminato ha un nodo parent
        else {
            // si analizza il primo nodo parent tra lo stack di nodi parent, se il suo id non corrisponde al parent_id del record da inserire
            // si continua a cercare il nodo parent corretto e viene tolto dallo stack con st.pop()
            // e si aggiorna il puntatore n, in modo che punti al nodo parent corretto alla fine del ciclo
            BTNode<Record>* n = st.top();
            while(n->data.id != new_record.parent_id) {
                st.pop();
                n = st.top();
            } 
            // se il nodo parent è stato trovato, si inserisce il nuovo nodo figlio e si esegue il push sullo stack del nodo stesso
            // il nodo parent si trova solo se id del puntatore n (che sarebbe il parent) è uguale al parent_id del record da inserire
            if(n->data.id == new_record.parent_id) {
                // se è SI si inserisce il nuovo nodo figlio a sinistra
                // si aggiorna anche il puntatore n al nodo figlio appena inserito (quindi al nodo left)
                if(typeStr == "SI") {
                    bst_akinator.add_left(n, new_record);
                    n = n->left;
                }
                else {
                    // accade la stessa situazione del nodo aggiunta a sinistra con la differenza che si rimuove il nodo parent dallo stack
                    // si esegue la pop() perchè un nodo può avere al massimo un figlio sinistro e uno destro. Questo perchè ha gia sia il nodo
                    // figlio destro che il nodo figlio sinistro
                    bst_akinator.add_right(n, new_record);
                    n = n->right;
                    st.pop();
                }
            }
            st.push(n);
        }
    }
    file.close();
}

void save_to_file() {
    std::ofstream file("db_csv.csv");
    
    auto lambda_func = [&](BTNode<Record> *node) {
        file << node->data.id << ";"
             << node->data.type_d << ";"
             << node->data.key << ";"
             << node->data.parent_id << std::endl;
    };

    bst_akinator.pre_order_traversal(lambda_func);
    file.close();
}

void ai_coaching(std::string new_animal, std::string new_characteristic, BTNode<Record> *tmp) {
    Record animal_record = {new_animal, "SI", tmp->data.id + 1, tmp->data.id};
    Record characteristic_record = {new_characteristic, tmp->data.type_d, tmp->data.id, tmp->data.parent_id};

    Record old_record = tmp->data;
    old_record.type_d = "NO";
    old_record.parent_id = tmp->data.id;

    tmp->data = characteristic_record;
    bst_akinator.add_right(tmp, old_record);
    bst_akinator.add_left(tmp, animal_record);
    std::cout << "Thank you! I have learned something new.\n";
}

void play_akinator_game() {
    std::cout << "YOU ARE STARTING THE GAME\n";
    std::cout << "I HAVE TO GUESS WHICH ANIMAL YOU ARE THINKING OF\n";
    std::cout << "IN THE CASE I DO NOT GUESS YOU CAN TEACH ME ON SOMETHING NEW\n";

    BTNode<Record> *tmp = bst_akinator.getRoot();
    while(tmp->right != nullptr || tmp->left != nullptr) {
        std::cout << tmp->getData().key << "(y/n)?";
        char choice;
        std::cin >> choice;

        switch (choice){
            case 'y':{
                tmp = tmp->getLeft();
                break;
            }
            case 'n':{
                tmp = tmp->getRight();
                break;
            }
        }
    }

    std::cout << "Are you thinking of " << tmp->getData().key << "? (y/n)";
    char final_choice;
    std::cin >> final_choice;
    std::cin.ignore();
    if(final_choice == 'y') 
        std::cout << "I GUESS IT RIGHT!\n YOU ARE THINKING OF " << tmp->getData().key << "\n";
    else {
        std::cout << "I DO NOT GUESS IT\nWHICH ANIMAL ARE YOU THINKING OF? ";
        std::string animal;
        std::getline(std::cin, animal);
        std::cout << "WHICH DIFFERENT CHARACTERS FROM " << tmp->getData().key << " IT HAS? ";
        std::string characteristic;
        std::getline(std::cin, characteristic);
        
        ai_coaching(animal, characteristic, tmp);
    }
}

void game() {
    std::cout << "Welcome to Akinator!" << std::endl;
    size_t choice;
    do {
        std::cout << "1. Play" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "3. View Tree" << std::endl;
        std::cout << "4. Save to File" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                play_akinator_game();
                break;
            }
            case 2: {
                std::cout << "Exiting from the Akinator game";
                for (int i = 0; i < 3; ++i) { 
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "." << std::flush;
                }
                std::cout << std::endl;
                return;
            }
            case 3: {
                bst_akinator.print_tree();
                break;
            }
            case 4:{
                save_to_file();
                break;
            }
        }
    } while(choice != 0);
}

int main() {
    load_from_file("db_csv.csv");
    // bst_akinator.print_tree();
    game();
    
    return 0;
}
