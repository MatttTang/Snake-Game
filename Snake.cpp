// Author: Matthew Tang
//
// Date: 12/19/2019
//
// Program: Create a snake game to be played in the command terminal

#include "snakey.h"


int main()
{
    // Randomize the seed for random generation
    srand(time(0));

    // Print game opening menu, and initialize game
    PrintMenu();
    Snake snake;
    snake.PrintBoard();

    // Begin the game
    snake.Game();
    PrintGameOver();
    return 0;
}

void PrintGameOver()
{
    cout << "Thanks for playing." << endl;
}

void PrintMenu()
{
    char input = ' ';
    while (input != '1' && input != '2') {
        cout << "Snake Game" << endl;
        cout << "1. Begin Game" << endl;
        cout << "2. Exit " << endl;
        cin >> input;
    }

    if (input == '2')
        exit(EXIT_SUCCESS);
    
    system("cls");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
