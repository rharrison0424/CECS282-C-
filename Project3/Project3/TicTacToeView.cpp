#include "TicTacToeView.h"
#include "TicTacToeBoard.h"
#include <memory>
#include <iostream>
#include <string>
#include <sstream>


void TicTacToeView::PrintBoard(std::ostream & s) const {

	s << "- 0 1 2" << std::endl;   //prints out the column number
	int counter = 0;        //the counter controls how many times
							//the for loop has gone
	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			if (counter % 3 == 0) {
				//these two if statments check to see when to go to a new line for the game board
				if (i > 0) {

					s << std::endl;
				}
				std::cout << i;    //prints out the row numbers
			}

			if (mTTTBoard->mBoard[i][j] == TicTacToeBoard::Player::EMPTY) {

				s << " .";
			}
			else if (mTTTBoard->mBoard[i][j] == TicTacToeBoard::Player::X) {   //represents X

				s << " X";
			}
			else {   //represents O

				s << " O";
			}
			counter++;
		}
	}
	s << std::endl;
}

std::unique_ptr<GameMove> TicTacToeView::ParseMove(const std::string & move) const {
	//takes in a move from the user and returns a move object
	std::istringstream parser;
	parser.str(move);
	char parenthesisCollector, commaCollector;
	int row, col;
	parser >> parenthesisCollector >> row >> commaCollector >> col >> parenthesisCollector;

	BoardPosition p(row, col);
	return std::make_unique<TicTacToeMove>(p);
}

std::string TicTacToeView::GetPlayerString(int player) const {
	return player == 1 ? "X" : "O";
}

std::ostream & operator<<(std::ostream & lhs, const TicTacToeView & rhs) {
	//prints the board and who's turn it is
	rhs.PrintBoard(lhs);
	lhs << "X's Move";
	rhs.mTTTBoard->GetCurrentPlayer() ==
		1 ? lhs << "X's move:" : lhs << "O's move:";
	return lhs;
}

std::ostream & operator<<(std::ostream & lhs, const TicTacToeMove & rhs) {
	return lhs << static_cast<std::string>(rhs);
}
