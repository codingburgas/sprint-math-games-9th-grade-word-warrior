#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

void displayMenu() {
    // Game title
    cout << R"TITLE(
 __          __           _  __          __             _            
 \ \        / /          | | \ \        / /            (_)           
  \ \  /\  / /__  _ __ __| |  \ \  /\  / /_ _ _ __ _ __ _  ___  _ __ 
   \ \/  \/ / _ \| '__/ _` |   \ \/  \/ / _` | '__| '__| |/ _ \| '__|
    \  /\  / (_) | | | (_| |    \  /\  / (_| | |  | |  | | (_) | |   
     \/  \/ \___/|_|  \__,_|     \/  \/ \__,_|_|  |_|  |_|\___/|_|   
                                                                      
)TITLE";
    cout << "\n";
    cout << "=========================================\n\n";
}
struct Player {
    string name;
    int score;
};

const int MAX_PLAYERS = 10;

void loadLeaderboard(Player leaderboard[], int& playerCount, const string& filename) {
    ifstream file(filename);
    playerCount = 0;

    if (file.is_open()) {
        while (playerCount < MAX_PLAYERS && file >> leaderboard[playerCount].name >> leaderboard[playerCount].score) {
            playerCount++;
        }
        file.close();
    }
}

void saveLeaderboard(Player leaderboard[], int playerCount, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (int i = 0; i < playerCount; i++) {
            file << leaderboard[i].name << " " << leaderboard[i].score << endl;
        }
        file.close();
    }
}

void sortLeaderboard(Player leaderboard[], int playerCount) {
    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = 0; j < playerCount - i - 1; j++) {
            if (leaderboard[j].score < leaderboard[j + 1].score) {
                Player temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}

void displayLeaderboard(Player leaderboard[], int playerCount) {
    system("cls");
    cout << "=================================\n";
    cout << "         LEADERBOARD\n";
    cout << "=================================\n\n";

    if (playerCount == 0) {
        cout << "No scores yet! Play a game to add your score.\n\n";
    }
    else {
        sortLeaderboard(leaderboard, playerCount);

        cout << "Rank\tName\t\tScore\n";
        cout << "---------------------------------\n";
        for (int i = 0; i < playerCount; i++) {
            cout << i + 1 << "\t" << leaderboard[i].name << "\t\t" << leaderboard[i].score << endl;
        }
        cout << "\n";
    }

    cout << "Press any key to return to menu...";
    _getch();
}

void addScore(Player leaderboard[], int& playerCount) {
    if (playerCount >= MAX_PLAYERS) {
        cout << "Leaderboard is full! Cannot add more scores.\n";
        cout << "Press any key to continue...";
        _getch();
        return;
    }

    string name;
    int score;

    cout << "Enter player name: ";
    cin >> name;
    cout << "Enter score: ";
    cin >> score;

    leaderboard[playerCount].name = name;
    leaderboard[playerCount].score = score;
    playerCount++;

    cout << "\nScore added successfully!\n";
    cout << "Press any key to continue...";
    _getch();
}

void printMenu(int selected) {
    string options[4] = { "Start Game", "Leaderboard", "Settings", "Exit" };
    for (int i = 0; i < 4; i++) {
        if (i == selected) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << "> " << options[i] << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else {
            cout << "  " << options[i] << endl;
        }
    }
}

int main() {
    int selected = 0;
    int key;
    Player leaderboard[MAX_PLAYERS];
    int playerCount = 0;
    const string filename = "leaderboard.txt";

    loadLeaderboard(leaderboard, playerCount, filename);

    while (true) {
        system("cls");
        displayMenu();
        printMenu(selected);

        key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) selected--;
            if (key == 80) selected++; 

            if (selected < 0) selected = 3;
            if (selected > 3) selected = 0;
        }
        else if (key == 13) {
            system("cls");
            switch (selected) {
            case 0:
                cout << "Starting game..." << endl;
                cout << "\n[Game simulation - adding a score]\n\n";
                addScore(leaderboard, playerCount);
                saveLeaderboard(leaderboard, playerCount, filename);
                break;
            case 1:  
                displayLeaderboard(leaderboard, playerCount);
                break;
            case 2:  
                cout << "Opening settings..." << endl;
                system("pause");
                break;
            case 3: 
                cout << "Exiting..." << endl;
                saveLeaderboard(leaderboard, playerCount, filename);
                return 0;
            }
        }
    }
}