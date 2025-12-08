#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm> 

using namespace std;

// ====================== CLEAR SCREEN ======================
void clearScreen() {
    system("cls");
}

// ====================== MENU HEADER ======================
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

// ====================== PLAYER STRUCT ======================
struct Player {
    string name;
    int score;
};

<<<<<<< HEAD
// ====================== SETTINGS STRUCT ======================
struct Settings {
    bool soundOn = true;
    string difficulty = "Easy";
=======
struct Settings {
    bool soundEnabled;
    bool musicEnabled;
    int volume;
    string theme;
>>>>>>> 2cf8772cf944e03febbfb3e93d854f9e1b51e320
};

const int MAX_PLAYERS = 10;
const string FILENAME = "leaderboard.txt";
<<<<<<< HEAD

// ====================== LOAD LEADERBOARD ======================
=======
const string SETTINGS_FILE = "settings.txt";

>>>>>>> 2cf8772cf944e03febbfb3e93d854f9e1b51e320
void loadLeaderboard(Player leaderboard[], int& playerCount) {
    ifstream file(FILENAME);
    playerCount = 0;

    if (file.is_open()) {
        while (playerCount < MAX_PLAYERS &&
            file >> leaderboard[playerCount].name >> leaderboard[playerCount].score) {
            playerCount++;
        }
        file.close();
    }
}

// ====================== SAVE LEADERBOARD ======================
void saveLeaderboard(Player leaderboard[], int playerCount) {
    ofstream file(FILENAME);

    if (file.is_open()) {
        for (int i = 0; i < playerCount; i++) {
            file << leaderboard[i].name << " " << leaderboard[i].score << endl;
        }
        file.close();
    }
}

<<<<<<< HEAD
// ====================== SORT ======================
=======
void loadSettings(Settings& settings) {
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
    }
}

void saveSettings(const Settings& settings) {
    ofstream file(SETTINGS_FILE);

    if (file.is_open()) {
        file << settings.soundEnabled << " " << settings.musicEnabled << " "
            << settings.volume << endl;
        file << settings.theme << endl;
        file.close();
    }
}

>>>>>>> 2cf8772cf944e03febbfb3e93d854f9e1b51e320
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

// ====================== DISPLAY LEADERBOARD ======================
void displayLeaderboard(Player leaderboard[], int playerCount) {
    while (true) {
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

        cout << "1. Back to Main Menu\n";

        int choice;
        cout << "\nEnter choice: ";

        while (!(cin >> choice) || choice != 1) {
            cout << "Invalid choice. Enter 1 to return: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            return;
        }
    }
}

// ====================== ADD SCORE ======================
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
        cout << "Invalid input. Please enter an integer: ";
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

// ====================== SETTINGS MENU ======================
void settingsMenu(Settings& settings) {
    while (true) {
        clearScreen();
        cout << "=================================\n";
        cout << "            SETTINGS\n";
        cout << "=================================\n\n";

        cout << "1. Sound: " << (settings.soundOn ? "ON" : "OFF") << endl;
        cout << "2. Difficulty: " << settings.difficulty << endl;
        cout << "3. Back to Main Menu\n";

        cout << "\nEnter choice (1-3): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            settings.soundOn = !settings.soundOn;
            break;

        case 2:
            clearScreen();
            cout << "Select Difficulty:\n";
            cout << "1. Easy\n";
            cout << "2. Medium\n";
            cout << "3. Hard\n";

            int diff;
            cout << "\nEnter choice (1-3): ";
            while (!(cin >> diff) || diff < 1 || diff > 3) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Enter 1-3: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (diff == 1) settings.difficulty = "Easy";
            if (diff == 2) settings.difficulty = "Medium";
            if (diff == 3) settings.difficulty = "Hard";

            break;

        case 3:
            return;

        default:
            cout << "Invalid input. Press ENTER...";
            cin.get();
        }
    }
}

// ====================== START GAME ======================
void startGame(Player leaderboard[], int& playerCount, Settings settings) {
    clearScreen();
    cout << "=================================\n";
    cout << "         SELECT DIFFICULTY\n";
    cout << "=================================\n\n";

    cout << "Difficulty (current): " << settings.difficulty << endl;
    cout << "Sound: " << (settings.soundOn ? "ON" : "OFF") << "\n\n";

    cout << "[Simulation] Starting game...\n";
    cout << "Press ENTER to continue...";
    cin.get();

    addScore(leaderboard, playerCount);
    saveLeaderboard(leaderboard, playerCount);
}

<<<<<<< HEAD
// ====================== PRINT MENU ======================
=======
void displaySettings(Settings& settings) {
    while (true) {
        clearScreen();
        cout << "=================================\n";
        cout << "           SETTINGS\n";
        cout << "=================================\n\n";

        cout << "1. Sound Effects: " << (settings.soundEnabled ? "ON" : "OFF") << endl;
        cout << "2. Background Music: " << (settings.musicEnabled ? "ON" : "OFF") << endl;
        cout << "3. Volume: " << settings.volume << "%" << endl;
        cout << "4. Theme: " << settings.theme << endl;
        cout << "5. Reset to Defaults\n";
        cout << "6. Back to Menu\n";

        int choice;
        cout << "\nEnter choice (1-6): ";

        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << "Invalid choice. Enter a number from 1 to 6: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            settings.soundEnabled = !settings.soundEnabled;
            cout << "\nSound Effects " << (settings.soundEnabled ? "enabled" : "disabled") << "!\n";
            saveSettings(settings);
            cout << "Press ENTER to continue...";
            cin.get();
            break;

        case 2:
            settings.musicEnabled = !settings.musicEnabled;
            cout << "\nBackground Music " << (settings.musicEnabled ? "enabled" : "disabled") << "!\n";
            saveSettings(settings);
            cout << "Press ENTER to continue...";
            cin.get();
            break;

        case 3: {
            int newVolume;
            cout << "\nEnter volume (0-100): ";
            while (!(cin >> newVolume) || newVolume < 0 || newVolume > 100) {
                cout << "Invalid input. Enter a number between 0 and 100: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            settings.volume = newVolume;
            cout << "\nVolume set to " << settings.volume << "%!\n";
            saveSettings(settings);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }

        case 4:
            clearScreen();
            cout << "=================================\n";
            cout << "         SELECT THEME\n";
            cout << "=================================\n\n";
            cout << "1. Default\n";
            cout << "2. Dark\n";
            cout << "3. Light\n";
            cout << "4. Ocean\n";
            cout << "5. Forest\n";

            int themeChoice;
            cout << "\nEnter choice (1-5): ";
            while (!(cin >> themeChoice) || themeChoice < 1 || themeChoice > 5) {
                cout << "Invalid choice. Enter a number from 1 to 5: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (themeChoice) {
            case 1: settings.theme = "Default"; break;
            case 2: settings.theme = "Dark"; break;
            case 3: settings.theme = "Light"; break;
            case 4: settings.theme = "Ocean"; break;
            case 5: settings.theme = "Forest"; break;
            }

            cout << "\nTheme changed to " << settings.theme << "!\n";
            saveSettings(settings);
            cout << "Press ENTER to continue...";
            cin.get();
            break;

        case 5:
            settings.soundEnabled = true;
            settings.musicEnabled = true;
            settings.volume = 50;
            settings.theme = "Default";
            saveSettings(settings);
            cout << "\nSettings reset to defaults!\n";
            cout << "Press ENTER to continue...";
            cin.get();
            break;

        case 6:
            return;
        }
    }
}

>>>>>>> 2cf8772cf944e03febbfb3e93d854f9e1b51e320
void printMenu(int selected) {
    string options[4] = { "1. Start Game", "2. Leaderboard", "3. Settings", "4. Exit" };
    for (int i = 0; i < 4; i++) {
        if (i == selected)
            cout << ">> **" << options[i] << "** <<\n";
        else
            cout << "   " << options[i] << "\n";
    }
}

// ====================== MAIN ======================
int main() {
    int selected = 0;
    int choice;

    Player leaderboard[MAX_PLAYERS];
    int playerCount = 0;
    Settings settings;

    Settings settings; // Our real settings

    loadLeaderboard(leaderboard, playerCount);
    loadSettings(settings);

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
                startGame(leaderboard, playerCount, settings);
                break;

            case 1:
                displayLeaderboard(leaderboard, playerCount);
                break;

            case 2:
<<<<<<< HEAD
                settingsMenu(settings);
=======
                displaySettings(settings);
>>>>>>> 2cf8772cf944e03febbfb3e93d854f9e1b51e320
                break;

            case 3:
                cout << "Exiting..." << endl;
                saveLeaderboard(leaderboard, playerCount);
                saveSettings(settings);
                return 0;
            }
        }
        else {
            cout << "\nInvalid choice. Press ENTER...";
            cin.get();
        }
    }
}
