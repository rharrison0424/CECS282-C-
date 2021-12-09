#include <iostream>
#include "OthelloGame.h"
using namespace std;

void PrintBoard(const OthelloMatrix &board) {

	cout << "- 0 1 2 3 4 5 6 7";  //print out column numbers
	int counter = 0;

	for (int row = 0; row < 8; row++) {

		for (int col = 0; col < 8; col++) {
			
			if (counter % 8 == 0) {

				cout << endl << row;   //print out the row numbers
			}

			if (board[row][col] == 0) {

				cout << " .";   //print empty space on game board
			}
			else if (board[row][col] == 1) {

				cout << " B";     //print Black piece on game board
			}
			else {

				cout << " W";    //print White piece on game board
			}
			counter++;
		}
	}
}

bool InBounds(int row, int col) {

	//returns true if the row and col are greater than or equal
	//to zero and if the row and col are less than eight
	return (row >= 0 && row < 8) && (col >= 0 && col < 8);
}

bool IsValidMove(const OthelloMatrix &board, int row, int col) {

	//returns true if the row and col are in bounds and that space on the board equals
	//zero, which means it is an empty space or if the user enters (-1,-1), which
	//means they would like to pass
	return ((InBounds(row, col) && board[row][col] == 0) || (row == -1 && col == -1));
}

void GetMove(int &row, int &col) {

	//variable to take in comma from user input
	char commaCollector, parenthesisOne, parenthesisTwo;   

	//takes in row, comma, and column in that order from user
	cin >> parenthesisOne >> row >> commaCollector >> col >> parenthesisTwo;   
}

void ApplyMove(OthelloMatrix &board, int row, int col,
	char currentPlayer) {

	//set the board space to the current player and find the otherplayer
	board[row][col] = currentPlayer;
	char otherPlayer = -currentPlayer;
	//save the starting row and col since it will change once you move
	//along the game board
	int spaceCounter = 0, startingRow = row, startingCol = col;

	for (int rd = -1; rd <= 1; rd++) {

		for (int cd = -1; cd <= 1; cd++) {

			while (board[row][col] != 0) {
				
				//the while loop will break if the for loop variables equal zero
				//because that would not move in any direction of the game board
				//it will also break if the row and col are not in bounds of the
				//game board
				//if the loop does not break, move in the determined direction
				row = row + rd;
				col = col + cd;
				if ((rd == 0 && cd == 0) || !InBounds(row,col)) {
					
					break;
			    }
				//if the loop does not break, move in the determined direction


				//the loop will also break if the next space contains the game piece of
				//the current player
				if (board[row][col] == currentPlayer) {
					
					break;
			    }
				//if the board space is the other player, increment spaceCounter by 1 to
				//keep track how far we have moved in the determined direction
			    else if (board[row][col] == otherPlayer) {
					
					spaceCounter++;
			    }
			}
			//if we have moved in a direction at least once or more and the current
			//board space is the current player's piece, move backwards and flip 
			//all the of the other player's pieces to the current player's pieces
			if (board[row][col] == currentPlayer && spaceCounter > 0) {

				for (int i = 0; i < spaceCounter; i++) {

					board[row = row - rd][col = col - cd] = currentPlayer;
				}
			}
			//reset the space counter to zero and the row and col back to the 
			//initial row and col
			spaceCounter = 0;
			row = startingRow;
			col = startingCol;
		}
	}
}


int GetValue(const OthelloMatrix &board) {

	int sum = 0;

	//find the current value of the game board by adding up all the spaces and 
	//their value
	for (int row = 0; row < 8; row++) {

		for (int col = 0; col < 8; col++) {

			sum += board[row][col];
		}
	}
	return sum;
}