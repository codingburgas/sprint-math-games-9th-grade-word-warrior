#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm> 

using namespace std;


void clearScreen() {
    system("cls");
}

void displayMenu() {
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
const string FILENAME = "leaderboard.txt";


void loadLeaderboard(Player leaderboard[], int& playerCount) {
    ifstream file(FILENAME);
    playerCount = 0;

    if (file.is_open()) {
        while (playerCount < MAX_PLAYERS && file >> leaderboard[playerCount].name >> leaderboard[playerCount].score) {
            playerCount++;
        }
        file.close();
    }
}

void saveLeaderboard(Player leaderboard[], int playerCount) {
    ofstream file(FILENAME);

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
    clearScreen();
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

    cout << "Press ENTER to return to menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void addScore(Player leaderboard[], int& playerCount) {
    if (playerCount >= MAX_PLAYERS) {
        cout << "Leaderboard is full! Cannot add more scores.\n";
        cout << "Press ENTER to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    string name;
    int score;

    cout << "Enter player name: ";
    cin >> name;

    cout << "Enter score: ";
    while (!(cin >> score)) {
        cout << "Invalid input. Please enter an integer for the score: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    leaderboard[playerCount].name = name;
    leaderboard[playerCount].score = score;
    playerCount++;

    cout << "\nScore added successfully!\n";
    cout << "Press ENTER to continue...";
    cin.get();
}

void startGame(Player leaderboard[], int& playerCount) {
    clearScreen();
    cout << "=================================\n";
    cout << "         SELECT DIFFICULTY\n";
    cout << "=================================\n\n";

    cout << "1. Easy\n";
    cout << "2. Normal\n";
    cout << "3. Hard\n";
    cout << "4. Back to Menu\n";

    int choice;
    cout << "\nEnter choice (1-4): ";

    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << "Invalid choice. Enter a number from 1 to 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 4) {
        return;
    }

    string difficulty;
    switch (choice) {
    case 1: difficulty = "Easy"; break;
    case 2: difficulty = "Normal"; break;
    case 3: difficulty = "Hard"; break;
    }

    clearScreen();
    cout << "Starting game on **" << difficulty << "** difficulty..." << endl;
    cout << "\n[Game simulation - adding a score]\n\n";

    addScore(leaderboard, playerCount);
    saveLeaderboard(leaderboard, playerCount);
}

void printMenu(int selected) {
    string options[4] = { "1. Start Game", "2. Leaderboard", "3. Settings", "4. Exit" };
    for (int i = 0; i < 4; i++) {
        if (i == selected) {
            cout << ">> " << "**" << options[i] << "**" << " << \n";
        }
        else {
            cout << "   " << options[i] << " \n";
        }
    }
}

int main() {
    int selected = 0;
    int choice;
    Player leaderboard[MAX_PLAYERS];
    int playerCount = 0;

    loadLeaderboard(leaderboard, playerCount);

    while (true) {
        clearScreen();
        displayMenu();
        printMenu(selected);

        cout << "\nEnter option number (1-4) and press ENTER: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        selected = choice - 1;

        if (selected >= 0 && selected <= 3) {
            clearScreen();
            switch (selected) {
            case 0:
                startGame(leaderboard, playerCount);
                break;
            case 1:
                displayLeaderboard(leaderboard, playerCount);
                break;
            case 2:
                cout << "Opening settings..." << endl;
                cout << "Press ENTER to return...";
                cin.get();
                break;
            case 3:
                cout << "Exiting..." << endl;
                saveLeaderboard(leaderboard, playerCount);
                return 0;
            }
        }
        else {
            cout << "\nInvalid choice. Please enter a number from 1 to 4.\n";
            cout << "Press ENTER to try again...";
            cin.get();
        }
    }
}