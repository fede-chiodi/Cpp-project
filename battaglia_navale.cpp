#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void clearCampo(char battle[10][10]){
    
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            battle[i][j] = '.';
        }
    }
}


void viewCampo(char battle[10][10]){

    cout << endl;
    // cout << "    Campo da gioco" << endl;
    cout << endl;
    cout << "  0 1 2 3 4 5 6 7 8 9" << endl;

    for (int i = 0; i < 10; i++)
    {  
        cout << i << " ";
        for (int j = 0; j < 10; j++)
        {
            cout << battle[i][j] << " ";
        }
        cout <<  endl;
    }  
}


// true se la posizione è libera
// false altrimenti
bool check_pos(char battle[10][10], int x, int y) {
    return (x >= 0 && x < 10) && (y >= 0 && y < 10) && battle[x][y] == '.';
}

bool checkShip(int x, int y, int length, char verso, char battle[10][10]){

    // length--;
    switch(verso) {
        case 'N':
            for (int i = 0; i < length; i++) {
                if(!check_pos(battle, x - i, y))
                    return false;
            }
            break;
        case 'S':
            for (int i = 0; i < length; i++) {
                if(!check_pos(battle, x + i, y))
                    return false;
            }
            break;
        case 'E':
            for (int i = 0; i < length; i++) {
                if(!check_pos(battle, x, y + i))
                    return false;
            }
            break;
        case 'O':
            for (int i = 0; i < length; i++) {
                if(!check_pos(battle, x, y - i))
                    return false;
            }
            break;
    }
    return true;
}

void setShips(char battle[10][10]){
    unsigned int lung_navi[] = {2, 2, 3, 3, 4};
    int x, y, length;
    char verso;
    for (int i = 0; i < 5; i++) {
        length = lung_navi[i];
        do {
            cout << "coordinata x: ";
            cin >> x;
            cin.clear();
            cout << "coordinata y: ";
            cin >> y; 
            cin.clear();
        }while(!check_pos(battle, x, y));

        do {
            do {
                cout << "verso della nave (N-S-E-O): ";
                cin >> verso;
            } while (verso != 'N' && verso != 'S' && verso != 'E' && verso != 'O');
            if(checkShip(x, y, length, verso, battle)) {
                switch (verso) {
                // set ship verso destra
                    case 'E':
                        for (int i = 0; i < length; i++) {
                            battle[x][y + i] = '*';
                        }
                        break;
                        // set ship verso sinistra
                    case 'O':
                        for (int i = 0; i < length; i++) {
                            battle[x][y - i] = '*';
                        }
                        break;
                        // set ship verso l'alto
                    case 'N':
                        for (int i = 0; i < length; i++) {
                            battle[x - i][y] = '*';
                        }
                        break;
                            // set ship verso il basso
                    case 'S':
                        for (int i = 0; i < length; i++) {
                            battle[x + i][y] = '*';
                        }
                        break;
                    default:
                        break;
                }
                break;
            }
        }while(1);
        viewCampo(battle);
    }
}

void setShips2(char battle2[10][10]) {
    srand(time(NULL));
    unsigned int lung_navi[] = {2, 2, 3, 3, 4};
    int x, y, length;
    char verso;
    for (int i = 0; i < 5; i++) {
        length = lung_navi[i];
        do {
            x=rand()%10;
            y=rand()%10;
        }while(!check_pos(battle2, x, y));

        do {
            do {
                int azimut = rand()%4;
                if (azimut == 0)
                {
                    verso = 'N';
                }
                else if (azimut == 1)
                {
                    verso = 'S';
                }
                else if (azimut = 2)
                {
                    verso = 'E';
                }
                else if (azimut == 3)
                {
                    verso = 'O';
                }      
            } while (verso != 'N' && verso != 'S' && verso != 'E' && verso != 'O');
            if(checkShip(x, y, length, verso, battle2)) {
                switch (verso) {
                        // set ship verso destra
                    case 'E':
                        for (int i = 0; i < length; i++) {
                            battle2[x][y + i] = '*';
                        }
                        break;
                        // set ship verso sinistra
                    case 'O':
                        for (int i = 0; i < length; i++) {
                            battle2[x][y - i] = '*';
                        }
                        break;
                        // set ship verso l'alto
                    case 'N':
                        for (int i = 0; i < length; i++) {
                            battle2[x - i][y] = '*';
                        }
                        break;
                            // set ship verso il basso
                    case 'S':
                        for (int i = 0; i < length; i++) {
                            battle2[x + i][y] = '*';
                        }
                        break;
                    default:
                        break;
                }
                break;
            }
        }while(1);
    }
    ///viewCampo(battle2);
}

void game_player(char battle_opp[10][10], char battle_player_opp[10][10]){
    int x, y;
    do
    {
        cout << "inserisci coordinata d'offensiva x: ";
        cin >> x;
        cin.clear();
        cout << "inserisci coordinata d'offensiva y: ";
        cin >> y; 
        cin.clear();
    } while (!((x >= 0 && x < 10) && (y >= 0 && y < 10)));
    if (battle_opp[x][y] == '.')
    {
        // cout << "colpo in mare" << endl;
        battle_player_opp[x][y] = '/';
    }
    else {
        // cout << "nave colpita" << endl;
        battle_opp[x][y] = 'X';
        battle_player_opp[x][y] = 'X';
    }
    cout << "\n";
    cout << "CAMPO NEMICO:\n";
    viewCampo(battle_player_opp);  
}

void game_bot(char battle_opp[10][10], char battle_opp_player[10][10]){
    srand(time(NULL));
    int x, y;
    do {
        x=rand()%10;
        y=rand()%10;

    }while(battle_opp_player[x][y] == '/' || battle_opp_player[x][y] == 'X');
        // cout << "nave colpita" << endl;
    if(battle_opp[x][y] == '*') {
        battle_opp_player[x][y] = 'X';
        battle_opp[x][y] = 'X';
    }
    else {
        // cout << "colpo in mare" << endl;
        battle_opp_player[x][y] = '/';
    }
    viewCampo(battle_opp_player);
}

bool check_game(char battle[10][10]) {
    size_t count = 0;
    unsigned int ship_chunks = 2 + 2 + 3 + 3 + 4;
    for (size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 10; j++){
            if(battle[i][j] == 'X')
                count++;
        }
    }
    return count == ship_chunks;
}

int main(){
    cout << "----------------------" << endl;
    cout << "   BATTAGLIA NAVALE   " << endl;
    cout << "----------------------\n" << endl;
    char battle[10][10];
    char battle2[10][10];

    char battle_player[10][10], battle_opp[10][10];
    clearCampo(battle);
    clearCampo(battle2);
    clearCampo(battle_player);
    clearCampo(battle_opp);
    viewCampo(battle);
    setShips(battle);
    cout << "\n";
    // cout << "CAMPO DELL'AVVERSARIO:\n";
    setShips2(battle2);
    // viewCampo(battle2);

    cout << endl;
    cout << "------------------------" << endl;
    cout << "   HA INIZIO IL GIOCO   "  << endl;
    cout << "------------------------" << endl;
    cout << endl;

    bool iswin = false;
    do {
        game_player(battle2, battle_player);
        cout << "\n";
        cout << "IL TUO CAMPO:\n";
        viewCampo(battle);
        if(check_game(battle_player)) {
            iswin = true;
            cout << "\n";
            cout << "-------------------" << endl;
            cout << "     HAI VINTO     " << endl;
            cout << "-------------------" << endl;
        }
        else {
            game_bot(battle, battle_opp);
            if(check_game(battle_opp)) {
                iswin = true;
                cout << "\n";
                cout << "-------------------" << endl;
                cout << "     HAI PERSO     " << endl;
                cout << "-------------------" << endl;
            }
        }
    }while(!iswin);

return 0;
}
