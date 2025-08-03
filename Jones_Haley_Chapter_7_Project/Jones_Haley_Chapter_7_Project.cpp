// Jones_Haley_Chapter_7_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

const int SIZE = 3;
const char EMPTY = '*';
const string PLAY = "PLAY";
const string TIE = "TIE";
const string X_WIN = "X_WIN";
const string O_WIN = "O_WIN";
const string WINNER = "WINNER";
const string SPACE_LEFT = "SPACE_LEFT";
const string NO_SPACE = "NO_SPACE";

// Functions
void initializeBoard(char board[SIZE][SIZE]);
void displayBoard(const char board[SIZE][SIZE]);
void placeToken(char token, char board[SIZE][SIZE]);
void getLocation(int& row, int& col, const char board[SIZE][SIZE]);
string getBoardState(char token, char board[SIZE][SIZE]);
string checkForWinner(char token, char board[SIZE][SIZE]);

int main() {
	char board[SIZE][SIZE];
	char player1_token = 'X';
	char player2_token = 'O';
	string boardState = PLAY;

	initializeBoard(board);
	displayBoard(board);

	while (boardState == PLAY) {
		placeToken(player1_token, board);
		displayBoard(board);
		boardState = getBoardState(player1_token, board);
		if (boardState != PLAY) break;

		placeToken(player2_token, board);
		displayBoard(board);
		boardState = getBoardState(player2_token, board);
	}

	if (boardState == X_WIN)
		cout << "Player 1 (X) wins!" << endl;
	else if (boardState == O_WIN)
		cout << "Player 2 (O) wins!" << endl;
	else if (boardState == TIE)
		cout << "The game is a tie." << endl;

	return 0;
}

void initializeBoard(char board[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			board[i][j] = EMPTY;
}

void displayBoard(const char board[SIZE][SIZE]) {
	cout << "\n  1 2 3\n";
	for (int i = 0; i < SIZE; ++i) {
		cout << i + 1 << "  ";
		for (int j = 0; j < SIZE; ++j)
			cout << board[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}

void placeToken(char token, char board[SIZE][SIZE]) {
	int row, col;
	getLocation(row, col, board);
	board[row][col] = token;
}

void getLocation(int& row, int& col, const char board[SIZE][SIZE]) {
	bool valid = false;

	while (!valid) {
		cout << "Enter row (1-3) and column (1-3) for your move: ";
		cin >> row >> col;

		if (cin.fail() || row < 1 || row > 3 || col < 1 || col > 3) {
			cout << "Invalid input. Please enter numbers between 1 and 3.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		row -= 1;
		col -= 1;

		if (board[row][col] != EMPTY)
			cout << "Cell already occupied. Try again.\n";
		else
			valid = true;
	}
}

string getBoardState(char token, char board[SIZE][SIZE])
{
	return string();
}

string checkForWinner(char token, char board[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; ++i) {
		if (board[i][0] == token && board[i][1] == token && board[i][2])
			return WINNER;
		if (board[0][i] == token && board[1][i] == token && board[2][0] == token)
			return WINNER;
	}

	if (board[0][0] == token && board[1][1] == token && board[2][2] == token)
		return WINNER;
	if (board[0][2] == token && board[1][1] == token && board[2][0] == token)
		return WINNER;

	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			if (board[1][j] == EMPTY)
				return SPACE_LEFT;

	return NO_SPACE;
}