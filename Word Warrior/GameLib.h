#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {
    string name;
    int score;
};

struct Settings {
    bool soundEnabled;
    bool musicEnabled;
    int volume;
    string theme;
};

const int MAX_PLAYERS = 10;
const string FILENAME = "leaderboard.txt";
const string SETTINGS_FILE = "settings.txt";



//Изчиства екрана
inline void clearScreen() {
    system("cls");
}

//Изчиства буфера на входа
inline void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


//Зарежда списъка с играчи и резултати от файл
inline void loadLeaderboard(Player leaderboard[], int& playerCount) {
    ifstream file(FILENAME);
    playerCount = 0;
    if (file.is_open()) {
        while (playerCount < MAX_PLAYERS && file >> leaderboard[playerCount].name >> leaderboard[playerCount].score) {
            playerCount++;
        }
        file.close();
    }
}

//Сортира таблицата
inline void sortLeaderboard(Player leaderboard[], int playerCount) {
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


//Зарежда настройките от файл
inline void loadSettings(Settings& settings) {
    ifstream file(SETTINGS_FILE);
    settings.soundEnabled = true;
    settings.musicEnabled = true;
    settings.volume = 50;
    settings.theme = "Default";

    if (file.is_open()) {
        file >> settings.soundEnabled >> settings.musicEnabled >> settings.volume;
        file.ignore();
        getline(file, settings.theme);
        file.close();
    }с
}

//Запазва настройки във файлa
inline void saveSettings(const Settings& settings) {
    ofstream file(SETTINGS_FILE);
    if (file.is_open()) {
        file << settings.soundEnabled << " " << settings.musicEnabled << " " << settings.volume << endl;
        file << settings.theme << endl;
        file.close();
    }
}

//Лесен режим, дума от 3 букви и 3 опита
inline void playEasyMode(Player leaderboard[], int& playerCount, const string& playerName) {
    vector<string> wordList = { "CAT", "DOG", "SUN", "CAR", "BUS", "SKY", "FOX", "BOX", "HAT", "CUP" };
    string HIDDEN_WORD = wordList[rand() % wordList.size()];

    const int MAX_TRIES = 3;
    string guess;
    vector<bool> used_hidden(3, false);
    int finalScore = 0;

    clearScreen();
    cout << "=================================\n";
    cout << "   EASY MODE (3 Letters)\n";
    cout << "=================================\n";
    cout << "Attempts: " << MAX_TRIES << "\n";
    cout << "Clues: [+] Correct, [*] Wrong place\n\n";

    for (int attempt = 1; attempt <= MAX_TRIES; ++attempt) {
        cout << "Attempt " << attempt << "/" << MAX_TRIES << ": ";
        if (!(cin >> guess)) { clearInputBuffer(); attempt--; continue; }

        transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

        if (guess.length() != 3) {
            cout << "Invalid length! Use 3 letters.\n";
            attempt--; continue;
        }

        string clue = "   ";
        fill(used_hidden.begin(), used_hidden.end(), false);

        for (int i = 0; i < 3; ++i) {
            if (guess[i] == HIDDEN_WORD[i]) { clue[i] = '+'; used_hidden[i] = true; }
        }
        for (int i = 0; i < 3; ++i) {
            if (clue[i] == ' ') {
                for (int j = 0; j < 3; ++j) {
                    if (guess[i] == HIDDEN_WORD[j] && !used_hidden[j]) {
                        clue[i] = '*'; used_hidden[j] = true; break;
                    }
                }
            }
        }
        cout << "Result: " << clue << "\n\n";

        if (guess == HIDDEN_WORD) {
            finalScore = 300 - (attempt - 1) * 50;
            cout << "WINNER! Score: " << finalScore << "\n";
            break;
        }
    }
    if (guess != HIDDEN_WORD) cout << "GAME OVER. Word was: " << HIDDEN_WORD << "\n";
    cout << "Press ENTER..."; clearInputBuffer(); cin.get();
}

//Нормален режим, дума от 5 букви и 5 опита
inline void playNormalMode(Player leaderboard[], int& playerCount, const string& playerName) {
    vector<string> wordList = {
        "APPLE", "TABLE", "CHAIR", "HOUSE", "MOUSE",
        "GHOST", "SMILE", "BRAIN", "PLANT", "WATER",
        "TIGER", "EAGLE", "PIZZA", "WORLD", "SPACE"
    };
    string HIDDEN_WORD = wordList[rand() % wordList.size()];

    const int MAX_TRIES = 5;
    string guess;
    vector<bool> used_hidden(5, false);
    int finalScore = 0;

    clearScreen();
    cout << "=================================\n";
    cout << "   NORMAL MODE (5 Letters)\n";
    cout << "=================================\n";
    cout << "Attempts: " << MAX_TRIES << "\n";
    cout << "Clues: [+] Correct, [*] Wrong place\n\n";

    for (int attempt = 1; attempt <= MAX_TRIES; ++attempt) {
        cout << "Attempt " << attempt << "/" << MAX_TRIES << ": ";
        if (!(cin >> guess)) { clearInputBuffer(); attempt--; continue; }

        transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

        if (guess.length() != 5) {
            cout << "Invalid length! Use 5 letters.\n";
            attempt--; continue;
        }

        string clue = "     ";
        fill(used_hidden.begin(), used_hidden.end(), false);

        for (int i = 0; i < 5; ++i) {
            if (guess[i] == HIDDEN_WORD[i]) {
                clue[i] = '+';
                used_hidden[i] = true;
            }
        }

        for (int i = 0; i < 5; ++i) {
            if (clue[i] == ' ') {
                for (int j = 0; j < 5; ++j) {
                    if (guess[i] == HIDDEN_WORD[j] && !used_hidden[j]) {
                        clue[i] = '*';
                        used_hidden[j] = true;
                        break;
                    }
                }
            }
        }
        cout << "Result: " << clue << "\n\n";

        if (guess == HIDDEN_WORD) {
            finalScore = 500 - (attempt - 1) * 50;
            cout << "WINNER! Score: " << finalScore << "\n";
            break;
        }
    }
    if (guess != HIDDEN_WORD) cout << "GAME OVER. Word was: " << HIDDEN_WORD << "\n";
    cout << "Press ENTER..."; clearInputBuffer(); cin.get();
}

//Сложен режим, дума от 7 букви и 5 опита
inline void playHardMode(Player leaderboard[], int& playerCount, const string& playerName) {
    vector<string> wordList = {
        "JUPITER", "PROJECT", "LIBRARY", "MYSTERY", "KINGDOM",
        "FREEDOM", "MONSTER", "CAPTAIN", "PICTURE", "MORNING",
        "STATION", "NATURAL", "COMPLEX", "ELEMENT", "VERSION"
    };
    string HIDDEN_WORD = wordList[rand() % wordList.size()];

    const int MAX_TRIES = 5;
    string guess;
    vector<bool> used_hidden(7, false);
    int finalScore = 0;

    clearScreen();
    cout << "=================================\n";
    cout << "   HARD MODE (7 Letters)\n";
    cout << "=================================\n";
    cout << "Attempts: " << MAX_TRIES << "\n";
    cout << "Clues: [+] Correct, [*] Wrong place\n\n";

    for (int attempt = 1; attempt <= MAX_TRIES; ++attempt) {
        cout << "Attempt " << attempt << "/" << MAX_TRIES << ": ";
        if (!(cin >> guess)) { clearInputBuffer(); attempt--; continue; }

        transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

        if (guess.length() != 7) {
            cout << "Invalid length! Use 7 letters.\n";
            attempt--; continue;
        }

        string clue = "       ";
        fill(used_hidden.begin(), used_hidden.end(), false);

        for (int i = 0; i < 7; ++i) {
            if (guess[i] == HIDDEN_WORD[i]) {
                clue[i] = '+';
                used_hidden[i] = true;
            }
        }

        for (int i = 0; i < 7; ++i) {
            if (clue[i] == ' ') {
                for (int j = 0; j < 7; ++j) {
                    if (guess[i] == HIDDEN_WORD[j] && !used_hidden[j]) {
                        clue[i] = '*';
                        used_hidden[j] = true;
                        break;
                    }
                }
            }
        }
        cout << "Result: " << clue << "\n\n";

        if (guess == HIDDEN_WORD) {
            finalScore = 700 - (attempt - 1) * 50;
            cout << "WINNER! Score: " << finalScore << "\n";
            break;
        }
    }
    if (guess != HIDDEN_WORD) cout << "GAME OVER. Word was: " << HIDDEN_WORD << "\n";
    cout << "Press ENTER..."; clearInputBuffer(); cin.get();
}