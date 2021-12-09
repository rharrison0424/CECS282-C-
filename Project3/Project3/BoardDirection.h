#pragma once
#include<array>

class BoardDirection {

private:
	char mRowChange, mColChange;

public:
	BoardDirection();
	BoardDirection(char rowChange, char colChange);

	inline char GetRowDirect() const { return mRowChange; }
	inline char GetColDirect() const { return mColChange; }

	static std::array<BoardDirection, 8> CARDINAL_DIRECTIONS;
};
