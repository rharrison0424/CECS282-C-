#include "BoardPosition.h"
#include "BoardDirection.h"
#include <string>
#include "OthelloMove.h"
using namespace std;


bool OthelloMove::operator==(const GameMove & rhs) const {

	const OthelloMove &m = dynamic_cast<const OthelloMove&>(rhs);
	return (mPosition == m.mPosition);
}

OthelloMove::operator std::string() const {

	//returns move as a pass or as a position in form of (r,c)
	if (IsPass()) {

		return "pass";
	}
	string rowStr = std::to_string(static_cast<int>(mPosition.GetRow()));
	string colStr = std::to_string(static_cast<int>(mPosition.GetCol()));
	return "(" + rowStr + "," + colStr + ")";
}