#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

// ====================== CLEAR / UI =======================
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

// ====================== STRUCTS =========================
struct Player {
    string name;
    int score;
};

struct Settings {
    bool soundEffects = true;
    bool musicEnabled = true;
    int volume = 50;
    string theme = "Default";
    string difficulty = "Easy";
};

const int MAX_PLAYERS = 10;
const string FILENAME = "leaderboard.txt";
const string SETTINGS_FILE = "settings.txt";


// ====================== LEADERBOARD ======================
void loadLeaderboard(Player leaderboard[], int& count) {
    ifstream file(FILENAME);
    count = 0;

    if (file.is_open()) {
        while (count < MAX_PLAYERS &&
            file >> leaderboard[count].name >> leaderboard[count].score) {
            count++;
        }
        file.close();
    }
}

void saveLeaderboard(Player leaderboard[], int count) {
    ofstream file(FILENAME);
    for (int i = 0; i < count; i++) {
        file << leaderboard[i].name << " " << leaderboard[i].score << endl;
    }
}

// ====================== SETTINGS SAVE/LOAD ================
void loadSettings(Settings& s) {
    ifstream file(SETTINGS_FILE);
    if (file.is_open()) {
        file >> s.soundEffects >> s.musicEnabled >> s.volume;
        file.ignore();
        getline(file, s.theme);
        getline(file, s.difficulty);
        file.close();
    }
}

void saveSettings(const Settings& s) {
    ofstream file(SETTINGS_FILE);
    file << s.soundEffects << " "
        << s.musicEnabled << " "
        << s.volume << endl;
    file << s.theme << endl;
    file << s.difficulty << endl;
}

// ====================== SORT ===============================
void sortLeaderboard(Player leaderboard[], int count) {
    sort(leaderboard, leaderboard + count,
        [](const Player& a, const Player& b) {
            return a.score > b.score;
        }
    );
}

// ====================== DISPLAY LEADERBOARD ===============
void displayLeaderboard(Player leaderboard[], int count) {
    clearScreen();
    cout << "=================================\n";
    cout << "         LEADERBOARD\n";
    cout << "=================================\n\n";

    if (count == 0) {
        cout << "No scores yet.\n\n";
    }
    else {
        sortLeaderboard(leaderboard, count);
        cout << "Rank\tName\t\tScore\n";
        cout << "---------------------------------\n";

        for (int i = 0; i < count; i++)
            cout << i + 1 << "\t" << leaderboard[i].name << "\t\t" << leaderboard[i].score << endl;
    }

    cout << "\nPress ENTER to return...";
    cin.get();
}

// ====================== ADD SCORE =========================
void addScore(Player leaderboard[], int& count) {
    if (count >= MAX_PLAYERS) {
        cout << "Leaderboard is full.\n";
        cin.get();
        return;
    }

    string name;
    int score;

    cout << "Enter player name: ";
    cin >> name;

    cout << "Enter score: ";
    while (!(cin >> score)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid score: ";
    }

    cin.ignore();

    leaderboard[count] = { name, score };
    count++;

    cout << "\nScore added!\nPress ENTER...";
    cin.get();
}

// ====================== SETTINGS MENU ======================
void settingsMenu(Settings& s) {
    while (true) {
        clearScreen();
        cout << "=================================\n";
        cout << "           SETTINGS\n";
        cout << "=================================\n\n";

        cout << "1. Sound Effects: " << (s.soundEffects ? "ON" : "OFF") << endl;
        cout << "2. Music: " << (s.musicEnabled ? "ON" : "OFF") << endl;
        cout << "3. Volume: " << s.volume << "%" << endl;
        cout << "4. Theme: " << s.theme << endl;
        cout << "5. Difficulty: " << s.difficulty << endl;
        cout << "6. Reset to Default\n";
        cout << "7. Back\n\n";

        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            s.soundEffects = !s.soundEffects;
        }
        else if (choice == 2) {
            s.musicEnabled = !s.musicEnabled;
        }
        else if (choice == 3) {
            cout << "Enter volume (0-100): ";
            cin >> s.volume;
            cin.ignore();
            if (s.volume < 0) s.volume = 0;
            if (s.volume > 100) s.volume = 100;
        }
        else if (choice == 4) {
            clearScreen();
            cout << "Select Theme:\n";
            cout << "1. Default\n2. Dark\n3. Light\n4. Ocean\n5. Forest\n";

            int t;
            cin >> t;
            cin.ignore();

            if (t == 1) s.theme = "Default";
            if (t == 2) s.theme = "Dark";
            if (t == 3) s.theme = "Light";
            if (t == 4) s.theme = "Ocean";
            if (t == 5) s.theme = "Forest";
        }
        else if (choice == 5) {
            clearScreen();
            cout << "Select Difficulty:\n1. Easy\n2. Medium\n3. Hard\n";

            int d;
            cin >> d;
            cin.ignore();

            if (d == 1) s.difficulty = "Easy";
            if (d == 2) s.difficulty = "Medium";
            if (d == 3) s.difficulty = "Hard";
        }
        else if (choice == 6) {
            s.soundEffects = true;
            s.musicEnabled = true;
            s.volume = 50;
            s.theme = "Default";
            s.difficulty = "Easy";
        }
        else if (choice == 7) {
            saveSettings(s);
            return;
        }
    }
}

// ====================== START GAME =========================
void startGame(Player leaderboard[], int& count, Settings s) {
    clearScreen();
    cout << "==== STARTING GAME ====\n\n";
    cout << "Difficulty: " << s.difficulty << endl;
    cout << "Sound: " << (s.soundEffects ? "ON" : "OFF") << endl;
    cout << "Music: " << (s.musicEnabled ? "ON" : "OFF") << endl;
    cout << "Volume: " << s.volume << "%\n";

    cout << "\n(Simulation) Press ENTER...";
    cin.get();

    addScore(leaderboard, count);
    saveLeaderboard(leaderboard, count);
}

// ====================== PRINT MENU ==========================
void printMenu(int sel) {
    string items[4] = { "Start Game", "Leaderboard", "Settings", "Exit" };

    for (int i = 0; i < 4; i++) {
        if (i == sel)
            cout << ">> **" << items[i] << "** <<\n";
        else
            cout << "   " << items[i] << "\n";
    }
}

// ====================== MAIN ================================
int main() {
    Player leaderboard[MAX_PLAYERS];
    int playerCount = 0;
    Settings settings;

    loadLeaderboard(leaderboard, playerCount);
    loadSettings(settings);

    while (true) {
        clearScreen();
        displayMenu();
        printMenu(0);

        cout << "\nEnter option (1-4): ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) startGame(leaderboard, playerCount, settings);
        else if (choice == 2) displayLeaderboard(leaderboard, playerCount);
        else if (choice == 3) settingsMenu(settings);
        else if (choice == 4) {
            saveSettings(settings);
            return 0;
        }
    }
}
