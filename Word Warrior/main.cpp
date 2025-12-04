#include <iostream>
#include <conio.h> 
#include <windows.h>
using namespace std;

void displayMenu() {
	// Заглавие на играта
    cout << "\\     --     //  -------   --------  ------         \\     --     //     /\       --------  --------   ---  -------  --------\n";
    cout << " \\   ----   //   ||   ||   ||    ||  |     \\        \\   ----   //     /  \      ||    ||  ||    ||    |   ||   ||  ||    ||\n";
    cout << "  \\ //  \\ //    ||   ||   ________  |     //         \\ //  \\ //     /----\     ________  ________    |   ||   ||  ________\n";
    cout << "   --      --     -------   ||    \\  ------            --      --     /      \    ||    \\  ||    \\   ___  -------  ||    \\\n";
 
}
//cout << "..     ..     ..  .......   .......  .......        ..      ..      ..     .       .......  ....... ...  .......  .......                                              \n";
//cout << " ..   ....   ..   ..   ..   .     .  .     ..        ..    ....    ..     . .      .     .  .     .  .   ..   ..  .     .                                \n";
//cout << "  .. ..  .. ..    ..   ..   .......  .     ..         .. ..    .. ..     .....     .......  .......  .   ..   ..  .......                             \n";
//cout << "   ..      ..     .......   .    .   ......            ..        ..     .     .    .    .   .    .  ...  .......  .    .                                      \n";
//

void printMenu(int selected) {
    string options[3] = { "Start Game", "Settings", "Exit" };

    for (int i = 0; i < 3; i++) {
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

    while (true) {
        system("cls"); 
        displayMenu();
        printMenu(selected);
		

        key = _getch();     

        if (key == 224) {    
            key = _getch();  
            if (key == 72) selected--; 
            if (key == 80) selected++; 

            
            if (selected < 0) selected = 2;
            if (selected > 2) selected = 0;
        }
        else if (key == 13) { 
            system("cls");
            switch (selected) {
            case 0:
                cout << "Starting game..." << endl;
                break;
            case 1:
                cout << "Opening settings..." << endl;
                break;
            case 2:
                cout << "Exiting..." << endl;
                return 0;
            }
            system("pause"); 
        }
    }
}


