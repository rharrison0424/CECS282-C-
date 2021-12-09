#include "BoardPosition.h"
#include "BoardDirection.h"
#include <string>
#include "TicTacToeMove.h"
using namespace std;

bool TicTacToeMove::operator==(const GameMove & rhs) const {
	const TicTacToeMove &m = dynamic_cast<const TicTacToeMove&>(rhs);
	return (mPosition == m.mPosition);
}

TicTacToeMove::operator std::string() const {

	string rowStr = std::to_string(static_cast<int>(mPosition.GetRow()));
	string colStr = std::to_string(static_cast<int>(mPosition.GetCol()));
	return "(" + rowStr + "," + colStr + ")";
}
