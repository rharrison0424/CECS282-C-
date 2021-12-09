#include <iostream>
#include "OthelloGame.h"
using namespace std;

int main(int argc, char* argv[]) {

	const int BOARD_SIZE = 8;
	std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> board = { 0 };
	int r, c, lastTurn, winner, turnCounter = 0, pass = 0;
	char currentPlayer;
	bool value = false;

	//initialize the game board and display it to the users
	board[3][3] = -1;
	board[3][4] = 1;
	board[4][3] = 1;
	board[4][4] = -1;
	PrintBoard(board);

	while(!value){

		if (turnCounter % 2 == 0) {

			//keeps track of when it is black pieces turn
			currentPlayer = 1;
			cout << endl << "Black's turn. Please choose a move:" << endl;
		}
		else {

			//keeps track of when it is white pieces turn
			currentPlayer = -1;
			cout << endl << "White's turn. Please choose a move:" << endl;
		}
		//gets the desired move from the current player and validates the move
		//if it is not a valid move, it will prompt the user to enter a correct move
		//until a valid move is entered
		GetMove(r, c);
		while (!IsValidMove(board, r, c)) {
			 
			cout << "Invalid move. Please choose a move:" << endl;
			GetMove(r, c);
		}
		//finds when both players enter (-1,-1) as their move in succession which means
		//both players pass and the game ends regardless if each board space was played
		if (r == -1 && c == -1) {
			
			if (pass == 0) {

				lastTurn = turnCounter;
			}
			else {

				if (turnCounter == lastTurn + 1) {

					value = true;
				}
				else {

					lastTurn = turnCounter;
				}
			}
			pass++;
		}
		//applies the correct move and prints the board
		else {

			ApplyMove(board, r, c, currentPlayer);
			PrintBoard(board);
		}
		turnCounter++;
	}
	//finds the winner of the game 
	winner = GetValue(board);

	if (winner > 0) {

		cout << "Game Over. Black wins!" << endl;
	}
	else if (winner < 0) {

		cout << "Game Over. White wins!" << endl;
	}
	else {

		cout << "Game Over. We have a tie!" << endl;
	}
}