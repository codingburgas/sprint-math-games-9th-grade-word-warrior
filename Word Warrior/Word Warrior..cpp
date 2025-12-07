#include <iostream>
#include <conio.h> 
#include <windows.h>
#include "leaderboard.h"
using namespace std;

void displayMenu() {
    // Заглавие на играта
    cout << "\\     --     //  -------   --------  ------         \\     --     //     /\\       --------  --------   ---  -------  --------\n";
    cout << " \\   ----   //   ||   ||   ||    ||  |     \\        \\   ----   //     /  \\      ||    ||  ||    ||    |   ||   ||  ||    ||\n";
    cout << "  \\ //  \\ //    ||   ||   ________  |     //         \\ //  \\ //     /----\\     ________  ________    |   ||   ||  ________\n";
    cout << "   --      --     -------   ||    \\  ------            --      --     /      \\    ||    \\  ||    \\   ___  -------  ||    \\\n";
    cout << "\n";
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