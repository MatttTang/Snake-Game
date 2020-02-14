#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

void PrintMenu();
void PrintGameOver();

class Snake
{
private:
	char board[12][22] = { ' ' };
	bool Alive = true;
	void UpdateGame();
	enum class direction
	{
		left, right, up, down
	};
	direction dir;
	int playerX = 5;
	int playerY = 5;
	int elapsed = 200;
	int tail = 0;
	int fruitX;
	int fruitY;
	int tailX[15] = { 0 };
	int tailY[15] = { 0 };
	int tailEndX = 0;
	int tailEndY = 0;
	


public:
	Snake();
	void PrintBoard();
	void CheckGameState();
	void Game();
	void Move();
	//void PrintDirection();
	void GenerateFruit();
	void TailLogic();
};

// This function assigns the tail of the snake with its positions on the game board
void Snake::TailLogic()
{
	if (tail > 0) {
		// When the tail is greater than one, each tail unit occupies the next tail unit's old position which simulates movement forward
		if (tail > 1) {
			for (int i = tail; i > 0; i--) {
				tailX[i] = tailX[i - 1];
				tailY[i] = tailY[i - 1];
			}
		}
		// Assign the first tail's position with the snake head's old position
		tailX[1] = playerX;
		tailY[1] = playerY;
		tailEndX = tailX[tail];
		tailEndY = tailY[tail];
		// Assign tail positions with the character '0' on the game board
		for (int i = tail; i > 0; i--) {
			board[tailX[i]][tailY[i]] = '0';
		}
	}
}

// Randomly generate a fruit onto the game board, ensure the fruit does not spawn ontop of the player
void Snake::GenerateFruit()
{
	do {
		fruitX = rand() % 10 + 1;
		fruitY = rand() % 20 + 1;
	} while (fruitX == playerX && fruitY == playerY);
	board[fruitX][fruitY] = '*';
}

/*
void Snake::PrintDirection()
{
	if (dir == direction::left) {
		cout << "left" << endl;
	}

	else if (dir == direction::right) {
		cout << "right" << endl;
	}

	else if (dir == direction::up) {
		cout << "up" << endl;
	}

	else if (dir == direction::down) {
		cout << "down" << endl;
	}
}*/

// Read in player input, set direction
void Snake::Move()
{
	// When w, a, s, d keys are input, change directions accordingly
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			// Do not allow directions to change when the opposite direction is input
			if (dir == direction::right) {
				break;
			}
			dir = direction::left;
			break;
		case 'w':
			if (dir == direction::down) {
				break;
			}
			dir = direction::up;
			break;
		case 's':
			if (dir == direction::up) {
				break;
			}
			dir = direction::down;
			break;
		case 'd':
			if (dir == direction::left) {
				break;
			}
			dir = direction::right;
			break;
		}
	}

	// Update the Game's matrix
	UpdateGame();
}

// This function runs the game
void Snake::Game()
{
	// First generate a fruit to begin the game
	GenerateFruit();

	// While the player is alive, keep the game running, first read the player input, then print the board
	while (Alive) {
		Move();
		PrintBoard();
		// Delay the loop to allow the game to get harder as more fruit are collected
		this_thread::sleep_for(chrono::milliseconds(elapsed));
	}
}

// Print the board state to the terminal for player to view
void Snake::PrintBoard()
{
	// Clear the terminal
	system("cls");
	// Print the 2d matrix
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 22; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << "Score: " << tail * 100 << endl;
}

// Check what the tile the player is interacting with
void Snake::CheckGameState()
{
	// If the player hits the boundary or hits tail, end the game
	if (board[playerX][playerY] == '#' || board[playerX][playerY] == '0') {
		Alive = false;
	}

	// If the player eats a fruit, increase the tail, and generate a new fruit
	else if (board[playerX][playerY] == '*') {
		tail++;
		elapsed = elapsed - 20;
		GenerateFruit();
	}
}

// Update the matrix 
void Snake::UpdateGame()
{
	// Change the player's old position to a blank
	board[playerX][playerY] = ' ';

	// When the tail exists, make the end of the tail's old position a blank, and assign the fruit to its coordinate
	if (tail > 0) {
		board[tailEndX][tailEndY] = ' ';
		board[fruitX][fruitY] = '*';
	}

	// Depending on direction, move the player in that direction relative to the last position
	if (dir == direction::left) {
		TailLogic();
		playerY = playerY - 1;
		CheckGameState();
		board[playerX][playerY] = 'O';
	}
	else if (dir == direction::right) {
		TailLogic();
		playerY = playerY + 1;
		CheckGameState();
		board[playerX][playerY] = 'O';
	}

	else if (dir == direction::up) {
		TailLogic();
		playerX = playerX - 1;
		CheckGameState();
		board[playerX][playerY] = 'O';
	}

	else if (dir == direction::down) {
		TailLogic();
		playerX = playerX + 1;
		CheckGameState();
		board[playerX][playerY] = 'O';
	}
}

// Construct the game board
Snake::Snake()
{
	// Initialize the player to position 4,4 on the board
	board[5][5] = 'O';

	// Create the boundary for the game board
	for (int i = 0; i < 22; i++) {
		board[0][i] = '#';
		board[11][i] = '#';
	}
	for (int i = 0; i < 12; i++) {
		board[i][0] = '#';
		board[i][21] = '#';
	}
}
