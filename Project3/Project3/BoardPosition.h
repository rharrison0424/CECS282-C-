#pragma once
#include "BoardDirection.h"
#include <string>
#include <iostream>
#include <vector>

class BoardPosition {

private:
	char mRow, mCol;

public:
	BoardPosition();
	BoardPosition(char row, char col);

	inline char GetRow() const { return mRow; }
	inline char GetCol() const { return mCol; }

	operator std::string() const;

	friend std::istream& operator>>(std::istream &lhs, BoardPosition& rhs);

	bool operator==(BoardPosition rhs) const;
	bool operator<(BoardPosition rhs);

	BoardPosition operator+(BoardDirection dir);

	bool InBounds(int boardSize);
	bool InBounds(int rows, int columns);

	static std::vector<BoardPosition> GetRectangularPositions(
		int rows, int columns);

};

std::ostream& operator<<(std::ostream &lhs, BoardPosition rhs);
