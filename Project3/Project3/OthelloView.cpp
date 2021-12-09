#include "OthelloView.h"
#include "OthelloBoard.h"
#include <memory>
#include <iostream>
#include <string>
#include <sstream>

std::ostream & operator<<(std::ostream & lhs, const OthelloView & rhs) {
	
	//prints the board and who's turn it is
	rhs.PrintBoard(lhs);
    rhs.mOthelloBoard->GetCurrentPlayer() == 
		1 ? lhs << "Black's move:" : lhs << "White's move:";
	return lhs;
}

std::ostream & operator<<(std::ostream & lhs, const OthelloMove & rhs) {
	
	//prints out the move
	return lhs << static_cast<std::string>(rhs);
}

void OthelloView::PrintBoard(std::ostream & s) const {

	s << "- 0 1 2 3 4 5 6 7";
	int counter = 0;

	//prints out the game board along with player pieces
	for (int row = 0; row < 8; row++) {

		for (int col = 0; col < 8; col++) {

			if (counter % 8 == 0) {

				s << std::endl << row;
			}
			if (mOthelloBoard->mBoard[row][col] == OthelloBoard::Player::EMPTY) {

				s << " .";
			}
			else if (mOthelloBoard->mBoard[row][col] == OthelloBoard::Player::BLACK) {

				s << " B";
			}
			else if (mOthelloBoard->mBoard[row][col] == OthelloBoard::Player::WHITE) {

				s << " W";
			}
			counter++;
		}
	}
	s << std::endl;
}

std::unique_ptr<GameMove> OthelloView::ParseMove(const std::string & strFormat) const {

	//takes in a move from the user and returns a move object
	std::istringstream parser;
	parser.str(strFormat);
	char parenthesisCollector, commaCollector;
	int row, col;
	parser >> parenthesisCollector >> row >> commaCollector >> col >> parenthesisCollector;

	BoardPosition p(row, col);
	return std::make_unique<OthelloMove>(p);
}

std::string OthelloView::GetPlayerString(int player) const {
	return player == 1 ? "Black" : "White";
}
