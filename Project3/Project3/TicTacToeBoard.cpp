#include "TicTacToeBoard.h"
#include "GameBoard.h"
#include <array>
#include <memory>
#include <vector>
#include "BoardPosition.h"

void TicTacToeBoard::CheckForWinner() {

	// It would be most efficient if we only checked squares adjacent to the most 
   // recent move. But I'm lazy. We'll check every possible direction of three squares
   // in a row. Only the current player can be the winner, so we'll only look for those squares.
	for (auto pos : BoardPosition::GetRectangularPositions(mBoard.size(), mBoard[0].size())) {
		for (auto dir : BoardDirection::CARDINAL_DIRECTIONS) {
			// Having chosen a square and a direction, walk up to 4 steps in that direction.
			BoardPosition current = pos;
			bool threeInARow = true;

			for (int steps = 0; steps < 3; steps++) {
				if (!InBounds(current) || mCurrentPlayer != GetPlayerAtPosition(current)) {
					// We either walked out of bounds, or found a square that doesn't match current player.
					threeInARow = false;
					break;
				}
				current = current + dir;
			}

			// If we matched four in a row, set the current value to the current player, indicating
			// a winner.
			if (threeInARow) {
				mCurrentValue = static_cast<int>(mCurrentPlayer);
				return;
			}
		}
	}
}

TicTacToeBoard::TicTacToeBoard() : mBoard({ Player::EMPTY }), mCurrentPlayer(Player::X), mCurrentValue(0) {
}

std::vector<std::unique_ptr<GameMove>> TicTacToeBoard::GetPossibleMoves() const {

	std::vector<std::unique_ptr<GameMove>> moves;

	// Each column that has an empty spot at the top is a valid column.
	for (int r = 0; r < mBoard[0].size(); r++) {

		for (int c = 0; c < mBoard.size(); c++) {
		
			if (mBoard[r][c] == Player::EMPTY) {
				moves.push_back(std::make_unique<TicTacToeMove>(BoardPosition(r,c)));
			}
		}
	}

	return moves;
}


void TicTacToeBoard::ApplyMove(std::unique_ptr<GameMove> move) {

	// Borrow a downcast of the given move.
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move.get());

	mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] = mCurrentPlayer;
	CheckForWinner();

	// Push the move into the history vector, switch sides.
	mHistory.push_back(std::move(move));
	mCurrentPlayer = mCurrentPlayer == Player::X ? Player::O : Player::X;
}


void TicTacToeBoard::UndoLastMove() {

	// Borrow a downcast of the last applied move.
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(mHistory.back().get());

	mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] = Player::EMPTY;

	// Remove and delete the last move.
	mHistory.pop_back();
	mCurrentValue = 0;
	mCurrentPlayer = mCurrentPlayer == Player::X ? Player::O : Player::X;
}

bool TicTacToeBoard::IsFinished() const {
	
	// mCurrentValue will be non-zero iff there is a winner.
	return mCurrentValue != 0 || mHistory.size() == mBoard.size() * mBoard[0].size();
}

int TicTacToeBoard::GetValue() const {
	return mCurrentValue;
}

int TicTacToeBoard::GetCurrentPlayer() const {
	return mCurrentPlayer == Player::X ? 1 : -1;
}

const std::vector<std::unique_ptr<GameMove>>& TicTacToeBoard::GetMoveHistory() const {
	return mHistory;
}
