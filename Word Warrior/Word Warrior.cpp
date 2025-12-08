#include <iostream>
#include <ctime>
#include "GameLib.h" 

using namespace std;

void displayLeaderboard(Player leaderboard[], int playerCount) {
    while (true) {
        clearScreen();
        cout << "=================================\n";
        cout << "         LEADERBOARD\n";
        cout << "=================================\n\n";

        if (playerCount == 0) {
            cout << "No scores loaded.\n\n";
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
            clearInputBuffer();
        }
        clearInputBuffer();
        if (choice == 1) return;
    }
}

void displaySettingsMenu(Settings& settings) {
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
            clearInputBuffer();
        }
        clearInputBuffer();

        switch (choice) {
        case 1: settings.soundEnabled = !settings.soundEnabled; saveSettings(settings); break;
        case 2: settings.musicEnabled = !settings.musicEnabled; saveSettings(settings); break;
        case 3: {
            int newVolume;
            cout << "\nEnter volume (0-100): ";
            while (!(cin >> newVolume) || newVolume < 0 || newVolume > 100) { clearInputBuffer(); }
            clearInputBuffer();
            settings.volume = newVolume;
            saveSettings(settings);
            break;
        }
        case 4: {
            clearScreen();
            cout << "--- SELECT THEME ---\n1. Default\n2. Dark\n3. Light\n4. Ocean\n5. Forest\nSelect: ";
            int t;
            if (cin >> t && t >= 1 && t <= 5) {
                string themes[] = { "Default", "Default", "Dark", "Light", "Ocean", "Forest" };
                settings.theme = themes[t];
                saveSettings(settings);
            }
            clearInputBuffer();
            break;
        }
        case 5:
            settings.soundEnabled = true; settings.musicEnabled = true;
            settings.volume = 50; settings.theme = "Default";
            saveSettings(settings);
            cout << "Reset complete.\n"; cin.get();
            break;
        case 6: return;
        }
    }
}

void startGame(Player leaderboard[], int& playerCount, const string& playerName) {
    while (true) {
        clearScreen();
        cout << "=================================\n";
        cout << "         SELECT DIFFICULTY\n";
        cout << "=================================\n\n";
        cout << "1. Easy   (3 Letters, 3 Tries)\n";
        cout << "2. Normal (5 Letters, 5 Tries)\n";
        cout << "3. Hard   (Soon)\n";
        cout << "4. Back\n";
        cout << "\nSelect: ";

        int choice;
        if (!(cin >> choice)) { clearInputBuffer(); continue; }

        if (choice == 1) {
            playEasyMode(leaderboard, playerCount, playerName);
            return;
        }
        else if (choice == 2) {
            playNormalMode(leaderboard, playerCount, playerName);
            return;
        }
        else if (choice == 4) return;
        else {
            cout << "Not available yet.\n";
            clearInputBuffer(); cin.get();
        }
    }
}

void showLogo() {
    cout << R"TITLE(
 __          __           _  __          __             _            
 \ \        / /          | | \ \        / /            (_)           
  \ \  /\  / /__  _ __ __| |  \ \  /\  / /_ _ _ __ _ __ _  ___  _ __ 
   \ \/  \/ / _ \| '__/ _` |   \ \/  \/ / _` | '__| '__| |/ _ \| '__|
    \  /\  / (_) | | | (_| |    \  /\  / (_| | |  | |  | | (_) | |   
     \/  \/ \___/|_|  \__,_|     \/  \/ \__,_|_|  |_|  |_|\___/|_|   
)TITLE";
    cout << "\n=========================================\n\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Player leaderboard[MAX_PLAYERS];
    int playerCount = 0;
    Settings settings;
    string name;

    loadLeaderboard(leaderboard, playerCount);
    loadSettings(settings);

    clearScreen();
    showLogo();
    cout << "Enter your name: ";
    cin >> name;
    clearInputBuffer();

    while (true) {
        clearScreen();
        showLogo();
        cout << "Welcome, " << name << "!\n";
        cout << "Current Theme: " << settings.theme << "\n\n";

        cout << "1. Start Game\n";
        cout << "2. Leaderboard\n";
        cout << "3. Settings\n";
        cout << "4. Exit\n";
        cout << "\nOption: ";

        int choice;
        if (!(cin >> choice)) { clearInputBuffer(); continue; }
        clearInputBuffer();

        switch (choice) {
        case 1: startGame(leaderboard, playerCount, name); break;
        case 2: displayLeaderboard(leaderboard, playerCount); break;
        case 3: displaySettingsMenu(settings); break;
        case 4:
            cout << "Exiting...\n";
            saveSettings(settings);
            return 0;
        default:
            cout << "Invalid choice.\n"; cin.get();
        }
    }
}