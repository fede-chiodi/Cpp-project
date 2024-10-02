#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void registrazione() {
    string username, password;
    std::string line;

    cout << "Inserisci un nome utente: ";
    cin >> username;
    cout << "Inserisci una password: ";
    cin >> password;

    bool existing = false;
    ifstream file("utenti.txt");

    if (file.is_open()) {
        while (getline(file, line)) {
            string file_username, file_password;
            std::istringstream iss(line);
            iss >> file_username;

            if (file_username == username) {
                existing = true;
                break;
            }
        }
        file.close();
    } else {
        cout << "Errore nell'aprire il file!" << endl;
        return;
    }

    if (existing) {
        cout << "Nome utente già esistente! Si prega di scegliere un altro nome." << endl;
    } else {
        ofstream file("utenti.txt", ios::app);
        if (file.is_open()) {
            file << username << " " << password << endl;
            file.close();
            cout << "Registrazione avvenuta con successo!" << endl;
        } else {
            cout << "Errore nell'aprire il file!" << endl;
        }
    }
}

void login() {
    std::string line;
    string username, password;
    bool autenticato = false;

    cout << "Nome utente: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("utenti.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            string file_username, file_password;
            std::istringstream iss(line);
            iss >> file_username >> file_password;

            if (file_username == username && file_password == password) {
                autenticato = true;
                break;
            }
        }
        file.close();

        if (autenticato) {
            cout << "Login avvenuto con successo!" << endl;
        } else {
            cout << "Nome utente o password errati!" << endl;
        }
    } else {
        cout << "Errore nell'aprire il file!" << endl;
    }
}

int main() {
    int scelta;
    
    do {
        cout << "1. Registration "<< endl;
        cout << "2. Login" << endl;
        cout << "3. Esci" << endl;
        cout << "Scegli un'opzione: ";
        cin >> scelta;

        switch (scelta) {
            case 1:
                registrazione();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "Uscita dal programma." << endl;
                break;
            default:
                cout << "Opzione non valida!" << endl;
        }
    } while (scelta != 3);

    return 0;
}
