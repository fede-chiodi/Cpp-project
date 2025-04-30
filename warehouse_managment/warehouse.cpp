#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <string>
#include <string.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class Date {
    private:
        std::string day, month, year;
    public:
        Date(std::string day, std::string month, std::string year) : day(day), month(month), year(year) {}
        Date() = default;

        std::string get_data() const {
            return day + "/" + month + "/" + year;
        }

        bool operator<(const Date& other) const {
            if(year < other.year) 
                return year < other.year;
            if (month != other.month)
                return month < other.month;
            return day < other.day;
        }
};

Date split_date(std::string date_input) {
    std::istringstream ss(date_input);
    std::string day, month, year;

    std::getline(ss, day, '/');
    std::getline(ss, month, '/');
    std::getline(ss, year, '/');

    return Date(day, month, year);
}

struct Article {
    std::string code;
    std::string description;
    size_t stock;
    std::string um;

    Article(std::string code_i = "", std::string description_i = "", size_t stock_i = 0, std::string um_i = "") : code(code_i), description(description_i), stock(stock_i), um(um_i) {}
};

struct Record {
    Date date;
    std::string description;
    char type; 
    unsigned int quantity;
    double loading_price;
    std::string code;

    Record(Date date_i, std::string description_i, char type_i, unsigned int quantity_i, double loading_price_i, std::string code_i) : date(date_i), description(description_i), type(type_i), quantity(quantity_i), loading_price(loading_price_i), code(code_i) {}
    Record() = default;
};

class Warehouse {
    private:
        std::vector<Record> records;    
        std::unordered_map<std::string, Article> articles; 

    public:

        template<typename F, typename Container>
        void visit(Container &container, F func) {
            for(const auto &item : container)
                func(item);
        }

        void add_article() {
            Article article;
            std::string code;
            std::cout << CYAN << ">>> Inserisci il codice dell'articolo: " << RESET;
            std::cin >> code;

            if(code.length() != 3) {
                std::cout << RED << "Il codice deve essere di 3 caratteri." << RESET << std::endl;
                return;
            }

            if(articles.find(code) != articles.end()) {
                std::cout << YELLOW << "L'articolo esiste gia' nel database." << RESET << std::endl;
                return;
            }

            article.code = code;
            std::cout << CYAN << ">>> Inserisci la descrizione dell'articolo: " << RESET;
            std::cin.ignore();
            std::getline(std::cin, article.description);
            std::cout << CYAN << ">>> Inserisci unità di misura: " << RESET;
            std::getline(std::cin, article.um);
            article.stock = 0;

            articles[code] = article;
            std::cout << GREEN << "✅ ARTICOLO AGGIUNTO CORRETTAMENTE" << RESET << std::endl;  
            
            save_articles();
        }

        void remove_article() {
            std::string code_to_remove;
            std::cout << CYAN << ">>> Inserisci il codice dell'articolo da eliminare: " << RESET;
            std::cin >> code_to_remove;

            if(articles.find(code_to_remove) == articles.end()) {
                std::cout << RED << "L'articolo non esiste nel database." << RESET << std::endl;
                return;
            }

            articles.erase(code_to_remove);
            std::cout << GREEN << "✅ ARTICOLO ELIMINATO CORRETTAMENTE "<< RESET << std::endl;

            save_articles();
        }

        void articles_list() {
            if (articles.empty()) {
                std::cout << YELLOW << "⚠️  Nessun articolo presente nel magazzino." << RESET << std::endl;
                return;
            }
            std::cout << BOLD << "\n=== ELENCO ARTICOLI ===\n\n" << RESET;
            for(const auto& [code, article] : articles) {
                std::cout << CYAN << "Codice: " << RESET << code << "\n"
                        << CYAN << "Descrizione: " << RESET << article.description << "\n"
                        << CYAN << "Stock attuale: " << RESET << article.stock << " " << article.um << "\n"
                        << "--------------------------\n";
            }
        }

        void insert_movement() {
            Record record;
            std::cout << BOLD << "\n\n=========== PIANO DEI MOVIMENTI ===========\n\n" << RESET;
            std::cout << CYAN << ">>> Inserisci la data del movimento (gg/mm/aaaa): " << RESET;
            std::string date;
            std::cin >> date;
            record.date = split_date(date);

            std::cout << BOLD << "EFFETTUA UNA TIPOLOGIA DI MOVIMENTO (C, S)" << RESET << std::endl;

            std::cout << CYAN << "  C: carico di merci\n" << RESET;
            std::cout << CYAN << "  S: scarico di merci\n" << RESET;
            char movement_type;
            std::cout << CYAN << ">>> MOVIMENTO: " << RESET;
            std::cin >> movement_type;
            record.type = movement_type;
            do {
                if(movement_type == 'C') {
                    std::cout << std::string(20, '=') << " CARICO " << std::string(20, '=') << std::endl;
                    do {
                        std::cout << CYAN << ">>> Codice articolo: " << RESET;
                        std::cin >> record.code;
                    } while (record.code.length() != 3);

                    if(articles.find(record.code) == articles.end()) {
                        std::cout << YELLOW << "⚠️ NESSUN ARTICOLO PRESENTE NEL MAGAZZINO CON QUESTO CODICE.\nSARAI REINDIRIZZATO AL MENU DI AGGIUNTA DEGLI ARTICOLI.\n";
                        add_article();
                    }
                    
                    std::string ddt = "DDT-";
                    while(true) {
                        std::cout << CYAN << ">>> Descrizione del movimento (DDT-): " << RESET;
                        std::cin >> record.description;
                        record.description = ddt + record.description;

                        bool description_exists = false;
                        for(const auto &item : records) {
                            if(item.description == record.description) {
                                description_exists = true;
                                break;
                            }
                        }

                        if(description_exists)
                            std::cout << RED << BOLD << "Documento di descrizione già inserito per un altro articolo.\n" << RESET;
                        else 
                            break;
                    }
                    std::cout << CYAN << ">>> Quantità di articoli: " << RESET;
                    std::cin >> record.quantity;
                    articles[record.code].stock += record.quantity;
                    std::cout << CYAN << ">>> Prezzo unitario: " << RESET;
                    std::cin >> record.loading_price;

                    records.push_back(record);
                } else if (movement_type == 'S') {  
                    std::cout << std::string(20, '=') << " SCARICO " << std::string(20, '=') << std::endl;
                    record.loading_price = 0;
                    do {
                        std::cout << CYAN << ">>> Codice articolo: " << RESET;
                        std::cin >> record.code;
                    } while (record.code.length() != 3);

                    if(articles.find(record.code) == articles.end()) {
                        std::cout << YELLOW << "⚠️ NESSUN ARTICOLO PRESENTE NEL MAGAZZINO CON QUESTO CODICE.\nSARAI REINDIRIZZATO AL MENU DI AGGIUNTA DEGLI ARTICOLI.\n";
                    } else {
                        auto it = articles.find(record.code);
                        if(it != articles.end()) {
                            std::cout << CYAN << ">>> Quantità di merci da scaricare: " << RESET;
                            std::cin >> record.quantity;
                            if(it->second.stock < record.quantity) {
                                std::cout << RED << BOLD << "quantità di articoli insufficiente" << RESET;
                            } else {
                                it->second.stock -= record.quantity;
                                std::string ddt = "DDT-";
                                while(true) {
                                    std::cout << CYAN << ">>> Descrizione del movimento (DDT-): " << RESET;
                                    std::cin >> record.description;
                                    record.description = ddt + record.description;
            
                                    bool description_exists = false;
                                    for(const auto &item : records) {
                                        if(item.description == record.description) {
                                            description_exists = true;
                                            break;
                                        }
                                    }
            
                                    if(description_exists)
                                        std::cout << RED << BOLD << "Documento di descrizione già inserito per un altro articolo.\n" << RESET;
                                    else 
                                        break;
                                }
                                records.push_back(record);
                            }
                        }
                    }
                }
                save_movements();
                save_articles();
            } while (movement_type != 'C' && movement_type != 'S');
        }

        void movement_list() {
            std::cout << BOLD << "\n\n" << std::string(25, '=') << " ELENCO MOVIMENTI " << std::string(25, '=') << "\n\n" << RESET;
            std::string art_code;
            do {
                std::cout << CYAN << ">>> CODICE ARTICOLO DI CUI OSSERVARE I MOVIMENTI: " << RESET;
                std::cin >> art_code;
            } while (art_code.length() != 3);
            std::cout << "\n\n" << BOLD << CYAN;
            std::cout << std::left
              << std::setw(12) << "DATA"
              << std::setw(8) << "TIPO"
              << std::setw(15) << "DESCRIZIONE"
              << std::setw(15) << "QUANTITÀ"
              << std::setw(10) << "PREZZO" << "\n";

            bool found = false;
            std::cout << std::string(60, '-') << "\n";
            std::sort(records.begin(), records.end(), [](const Record &a, const Record &b) {
                return a.date < b.date;
            });
            for(const auto &record : records) {
                if(art_code == std::string(record.code)) {
                    found = true;
                    std::cout << std::left
                      << std::setw(12) << record.date.get_data()
                      << std::setw(8) << (record.type == 'C' ? "Carico" : "Scarico")
                      << std::setw(15) << record.description
                      << std::setw(15) << record.quantity
                      << std::fixed << std::setprecision(2)
                      << std::setw(10) << (record.type == 'C' ? record.loading_price : 0.0)
                      << "\n";
                }
            }
            std::cout << RESET;

            if(!found)
                std::cout << YELLOW << "⚠️ Nessun movimento trovato per l'articolo con codice: " << art_code << RESET << std::endl;
        }

        void save_articles() {
            std::ofstream file("articles.csv");
            visit(articles, [&file](const std::pair<std::string, Article> &article_rec) {
                file << article_rec.first << ";"
                     << article_rec.second.description << ";"
                     << article_rec.second.stock << ";"
                     << article_rec.second.um << "\n";
            });
            file.close();
            std::cout << GREEN << "✅ Articoli salvati correttamente sul database" << RESET << std::endl;
        }

        void save_movements() {
            std::sort(records.begin(), records.end(), [](const Record &a, const Record &b) {
                return a.date < b.date;
            });
            std::ofstream file("movements.csv");
            visit(records, [&file](const Record &record) {
                file << record.date.get_data() << ";"
                     << record.type << ";"
                     << record.code << ";"
                     << record.description << ";"
                     << record.quantity << ";"
                     << record.loading_price << "\n";
            });
            file.close();
            std::cout << GREEN << "✅ Movimenti salvati correttamente sul database" << RESET << std::endl;
        }

        void upload_datas() {
            std::ifstream articles_file("articles.csv");
            std::string line;
            while(std::getline(articles_file, line)) {
                std::istringstream ss(line);
                std::string code, description, stock, um;
                std::getline(ss, code, ';');
                std::getline(ss, description, ';');
                std::getline(ss, stock, ';');
                std::getline(ss, um, ';');
                articles[code] = Article(code, description, std::stoi(stock), um);
            }
            articles_file.close();

            std::ifstream movement_file("movements.csv");
            std::string _line;
            while(std::getline(movement_file, _line)) {
                std::istringstream ss(_line);
                std::cout << _line << std::endl;
                std::string date, type_str, code, description, quantity, loading_price;
                std::getline(ss, date, ';');
                Date d = split_date(date);
                std::getline(ss, type_str, ';');
                char type = type_str[0];
                std::getline(ss, code, ';');
                std::getline(ss, description, ';');
                std::getline(ss, quantity, ';');
                std::getline(ss, loading_price, ';');
                records.push_back(Record(d, description, type, std::stoi(quantity), std::stod(loading_price), code));
            }
            movement_file.close();
        }

        void enhancment_CMP() {
            std::string code;
            std::cout << CYAN << ">>> Codice articolo di cui effettuare la valorizzazione CMP: " << RESET;
            std::cin >> code;

            double tot_v = 0;
            int tot_q = 0;
            double tot_p = 0;
            double total = 0;

            std::vector<Record> movements_code;
            for(auto it = records.begin(); it != records.end(); ++it) {
                if(it->code == code) {
                    movements_code.push_back(*it);
                }
            }

            std::sort(movements_code.begin(), movements_code.end(), [](const Record &a, const Record &b) {
                return a.date < b.date;
            });

            double cmp = 0;
            for(auto it = movements_code.begin(); it != movements_code.end(); ++it) {
                if(it->type == 'C') {
                    double value = it->quantity * it->loading_price;
                    total += value;
                    tot_q += it->quantity;
                    cmp = total / tot_q;
                } else if(it->type == 'S') {
                    int q_unload = it->quantity;
                    if(q_unload <= tot_q) {
                        tot_q -= q_unload;
                        total -= q_unload * cmp;
                    } else {
                        std::cout << RED << "⚠️ Quantità da scaricare superiore alla quantità di merce in magazzino" << RESET << std::endl;
                        return;
                    }
                }
            }

            std::cout << GREEN << BOLD << "✅ Valorizzazione totale (CMP) - merci in magazzino (VALORE GIACENZA): " << total << RESET << std::endl;
        }

        void enhancment_LIFO() {
            std::string code;
            std::cout << CYAN << ">>> Codice articolo di cui effettuare la valorizzazione LIFO: " << RESET;
            std::cin >> code;

            std::stack<std::pair<int, double>> stack;
            std::vector<Record> movements_code;

            for(auto it = records.begin(); it != records.end(); ++it) {
                if(it->code == code) {
                    movements_code.push_back(*it);
                }
            }

            std::sort(movements_code.begin(), movements_code.end(), [](const Record &a, const Record &b) {
                return a.date < b.date;
            });

            for(auto it = movements_code.begin(); it != movements_code.end(); ++it) {
                if(it->type == 'C') {
                    stack.push({it->quantity, it->loading_price});
                } else if(it->type == 'S') {
                    int q_unloaded = it->quantity;
                    
                    while(!stack.empty() && q_unloaded > 0) {
                        std::pair<int, double> pair_v = stack.top();
                        stack.pop();
                        if(pair_v.first <= q_unloaded) {
                            q_unloaded -= pair_v.first;
                        } else {
                            pair_v.first -= q_unloaded;
                            stack.push(pair_v);
                            q_unloaded = 0;
                        }
                    }
                }
            }

            double sum = 0;
            while(!stack.empty()) {
                sum += stack.top().first * stack.top().second;
                stack.pop();
            }

            std::cout << GREEN << BOLD << "✅ Valorizzazione totale (LIFO) - merci in magazzino (VALORE GIACENZA): " << sum << RESET << std::endl;
        }

        void enhancment_FIFO() {
            std::string code;
            std::cout << CYAN << ">>> Codice articolo di cui effettuare la valorizzazione FIFO: " << RESET;
            std::cin >> code;

            std::queue<std::pair<int, double>> queue;
            std::vector<Record> movements_code;

            for(auto it = records.begin(); it != records.end(); ++it) {
                if(it->code == code) {
                    movements_code.push_back(*it);
                }
            }

            std::sort(movements_code.begin(), movements_code.end(), [](const Record &a, const Record &b) {
                return a.date < b.date;
            });

            for(auto it = movements_code.begin(); it != movements_code.end(); ++it) {
                if(it->type == 'C')
                    queue.push({it->quantity, it->loading_price});
                else if(it->type == 'S') {
                    int q_unloaded = it->quantity;
                    while(!queue.empty() && q_unloaded > 0) {
                        std::pair<int, double> pair_v = queue.front();
                        queue.pop();
                        if(pair_v.first <= q_unloaded){
                            q_unloaded -= pair_v.first;
                        } else {
                            pair_v.first -= q_unloaded;
                            queue.push(pair_v);
                            q_unloaded = 0;
                        }
                    }
                }
            }

            double sum = 0;
            while(!queue.empty()) {
                sum += queue.front().first * queue.front().second;
                queue.pop();
            }

            std::cout << GREEN << BOLD << "✅ Valorizzazione totale (FIFO) - merci in magazzino (VALORE GIACENZA): " << sum << RESET << std::endl;
        }   
};

void print_menu() {
    std::cout << BOLD << "\n" << std::string(56, '=') << "\n" << RESET;
    std::cout << CYAN << BOLD << "        GESTIONE MAGAZZINO - MENU PRINCIPALE\n" << RESET;
    std::cout << BOLD << std::string(56, '=') << RESET << "\n";
    std::cout << YELLOW << " 1. " << RESET << "Aggiunta articolo\n";
    std::cout << YELLOW << " 2. " << RESET << "Eliminazione articolo\n";
    std::cout << YELLOW << " 3. " << RESET << "Elenco articoli\n";
    std::cout << YELLOW << " 4. " << RESET << "Inserimento movimento di carico/scarico\n";
    std::cout << YELLOW << " 5. " << RESET << "Elenco movimenti di un singolo articolo\n";
    std::cout << YELLOW << " 6. " << RESET << "Valorizzazione di un articolo (metodo CMP)\n";
    std::cout << YELLOW << " 7. " << RESET << "Valorizzazione di un articolo (metodo LIFO)\n";
    std::cout << YELLOW << " 8. " << RESET << "Valorizzazione di un articolo (metodo FIFO)\n";
    std::cout << YELLOW << " 0. " << RESET << "ESCI\n";
    std::cout << BOLD << std::string(56, '=') << "\n" << RESET;
    std::cout << CYAN << ">>> Scegli un'opzione: " << RESET;
}

int main(void) {
    Warehouse warehouse;
    size_t choice = 0;

    warehouse.upload_datas();

    do {
        print_menu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                warehouse.add_article();
                break;
            case 2:
                warehouse.remove_article();
                break;
            case 3:
                warehouse.articles_list();
                break;
            case 4:
                warehouse.insert_movement();
                break;
            case 5:
                warehouse.movement_list();
                break;
            case 6:
                warehouse.enhancment_CMP();
                break;
            case 7:
                warehouse.enhancment_LIFO();
                break;
            case 8:
                warehouse.enhancment_FIFO();
                break;
            case 0:
                std::cout << GREEN << "\nUscita dal programma. Arrivederci!\n" << RESET;
                break;
            default:
                std::cout << RED << "Opzione non valida. Riprova." << RESET << std::endl;
        }

    } while(choice != 0);

    return 0;
}