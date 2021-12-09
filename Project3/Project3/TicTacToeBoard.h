#pragma once
#include "TicTacToeMove.h"
#include "BoardPosition.h"
#include "GameBoard.h"
#include <array>
#include <memory>
#include <vector>
#include <string>

class TicTacToeBoard : public GameBoard {

public:

	static const int BOARD_SIZE = 3;

	TicTacToeBoard();

	// Inherited via GameBoard
	std::vector<std::unique_ptr<GameMove>> GetPossibleMoves() const override;
	void ApplyMove(std::unique_ptr<GameMove> move) override;
	void UndoLastMove() override;
	bool IsFinished() const override;
	int GetValue() const override;
	int GetCurrentPlayer() const override;
	const std::vector<std::unique_ptr<GameMove>>& GetMoveHistory() const override;

private:
	enum class Player { EMPTY = 0, X = 1, O = -1 };
	std::array<std::array<Player, BOARD_SIZE>, BOARD_SIZE> mBoard;
	std::vector<std::unique_ptr<GameMove>> mHistory;

	Player mCurrentPlayer;
	int mCurrentValue;

	friend class TicTacToeView;

	void CheckForWinner();

	bool InBounds(BoardPosition p) {
		return p.InBounds(BOARD_SIZE);
	}
	// Returns true if the given position contains the enemy of the given player.
	inline bool PositionIsEnemy(BoardPosition position, Player p) const {
		Player atPosition = GetPlayerAtPosition(position);
		return atPosition != Player::EMPTY && atPosition != p;
	}
	inline Player GetPlayerAtPosition(BoardPosition position) const {
		return mBoard[position.GetRow()][position.GetCol()];
	}
};