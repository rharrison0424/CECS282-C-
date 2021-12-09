#pragma once
#include "GameView.h"
#include "TicTacToeBoard.h"
#include <memory>
#include <iostream>

class TicTacToeView : public GameView {

private:
	std::shared_ptr<TicTacToeBoard> mTTTBoard;

	// Prints JUST the board (including row/column headers) to the given ostream object.
	void PrintBoard(std::ostream &s) const override;

public:

	TicTacToeView(std::shared_ptr<TicTacToeBoard> b) : mTTTBoard(b) {
	}

	std::unique_ptr<GameMove> ParseMove(const std::string & move) const override;
	std::string GetPlayerString(int player) const override;

	friend std::ostream& operator<< (std::ostream &lhs, const TicTacToeView &rhs);

};
std::ostream& operator<<(std::ostream &lhs, const TicTacToeMove &rhs);