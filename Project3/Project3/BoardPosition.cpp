#include "BoardPosition.h"
#include "BoardDirection.h"
#include <string>
#include "OthelloMove.h"
using namespace std;


BoardPosition::BoardPosition() : mRow(0), mCol(0) {
}

BoardPosition::BoardPosition(char row, char col) : mRow(row), mCol(col) {
}

std::ostream & operator<<(std::ostream &lhs, BoardPosition rhs) {

	lhs << static_cast<string>(rhs);
	return lhs;
}

std::istream & operator>>(std::istream & lhs, BoardPosition & rhs) {

	int row, col;
	char commaCollector, parenthesisOne, parenthesisTwo;
	cout << "Enter a row and column:";
	lhs >> parenthesisOne >> row >> commaCollector >> col >> parenthesisTwo;

	rhs.mRow = row;
	rhs.mCol = col;
	return lhs;
}

BoardPosition::operator std::string() const {

	string rowStr = std::to_string(static_cast<int>(mRow));
	string colStr = std::to_string(static_cast<int>(mCol));
	return "(" + rowStr + "," + colStr + ")";
}

bool BoardPosition::operator==(BoardPosition rhs) const{

	return (static_cast<int>(mRow) == static_cast<int>(rhs.mRow) &&
		static_cast<int>(mCol) == static_cast<int>(rhs.mCol));
}

bool BoardPosition::operator<(BoardPosition rhs) {

	if (static_cast<int>(mRow) == static_cast<int>(rhs.mRow)) {

		return static_cast<int>(mCol) < static_cast<int>(rhs.mCol);
	}
	else {

		return static_cast<int>(mRow) < static_cast<int>(rhs.mRow);
	}
}

BoardPosition BoardPosition::operator+(BoardDirection dir) {

	char rowChange = static_cast<int>(mRow) + static_cast<int>(dir.GetRowDirect());
	char colChange = static_cast<int>(mCol) + static_cast<int>(dir.GetColDirect());
	BoardPosition temp = BoardPosition{ rowChange, colChange };
	return temp;

}

bool BoardPosition::InBounds(int boardSize) {

	return (mRow >= 0 && mCol >= 0) &&
		(mRow < boardSize && mCol < boardSize);
}

bool BoardPosition::InBounds(int rows, int columns) {

	return (mRow >= 0 && mCol >= 0) &&
		(mRow < rows && mCol < columns);
}

std::vector<BoardPosition> BoardPosition::GetRectangularPositions(int rows, int columns) {

	vector<BoardPosition> boardPositions;
	char row, col;

	for (int i = 1; i <= rows; i++) {

		for (int j = 1; j <= columns; j++) {

			row = rows - i;
			col = columns - j;
			BoardPosition temp = BoardPosition{ row, col };
			boardPositions.insert(boardPositions.begin(), temp);
		}
	}
	return boardPositions;
}