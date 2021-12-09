#include "OthelloMove.h"
#include "BoardPosition.h"
#include "BoardDirection.h"
#include <array>
#include <memory>
#include <vector>
#include "OthelloBoard.h"

OthelloBoard::OthelloBoard() : mBoard{ Player::EMPTY }, mCurrentValue(0), mCurrentPlayer(Player::BLACK) {

	//initializes the four board pieces to the correct Player
	mBoard[3][3] = Player::WHITE;
	mBoard[3][4] = Player::BLACK;
	mBoard[4][3] = Player::BLACK;
	mBoard[4][4] = Player::WHITE;
}

std::vector<std::unique_ptr<GameMove>> OthelloBoard::GetPossibleMoves() const {

	std::vector<std::unique_ptr<GameMove>> moves;
	int spaceCounter = 0, samePosition = 0;

	//walks through all squares on the game board
	for (BoardPosition p : BoardPosition::GetRectangularPositions(8,8)) {

		//found a possible move
		if (GetPlayerAtPosition(p) == Player::EMPTY) {

				BoardPosition position(p), temp(p);
				
				//walks thorough all directions for a piece on the game board
				for (BoardDirection d : BoardDirection::CARDINAL_DIRECTIONS) {

					while (InBounds(position = position + d)) {

						//next piece is empty or the current player: exit loop
						if ((GetPlayerAtPosition(position) == Player::EMPTY) 
							|| (GetPlayerAtPosition(position) == mCurrentPlayer && spaceCounter == 0)) {
							
							break;
						}
						//next piece is an enemy, keep going
						if (PositionIsEnemy(position, mCurrentPlayer)) {

							spaceCounter++;
						}
						//found a possible move
						if ((GetPlayerAtPosition(position) == mCurrentPlayer) && (spaceCounter > 0 && samePosition == 0)) {

							moves.push_back(std::make_unique<OthelloMove>(temp));
							samePosition++;
						}
					}
					position = temp, spaceCounter = 0;
				}
				samePosition = 0;
		}	
	}
	//no possible moves were found, so only possible move is to pass
	if (moves.size() == 0) {

		moves.push_back(std::make_unique<OthelloMove>(BoardPosition(-1,-1)));
	}
	return moves;
}

void OthelloBoard::ApplyMove(std::unique_ptr<GameMove> move) {

	OthelloMove *m = dynamic_cast<OthelloMove*>(move.get());
	//only apply a move if it is not a pass
	if (!m->IsPass()) {

		BoardPosition position(m->mPosition), temp(m->mPosition);
		int spaceCounter = 0, row = position.GetRow(), col = position.GetCol();
		mBoard[position.GetRow()][position.GetCol()] = mCurrentPlayer;
		mCurrentValue = mCurrentPlayer == Player::BLACK ? mCurrentValue + 1 : mCurrentValue - 1;

		//walk in every direction for the position on the game board
		for (BoardDirection d : BoardDirection::CARDINAL_DIRECTIONS) {

			while (InBounds(position = position + d)) {

				//if the position is empty or the current player: break
				if ((GetPlayerAtPosition(position) == Player::EMPTY)
					|| (GetPlayerAtPosition(position) == mCurrentPlayer && spaceCounter == 0)) {

					break;
				}
				//if the position is an enemy
				if (PositionIsEnemy(position, mCurrentPlayer)) {

					spaceCounter++;
				}
				//found pieces to flip
				if ((GetPlayerAtPosition(position) == mCurrentPlayer) && (spaceCounter > 0)) {

					//flips all the enemy pieces to the current player
					for (int i = 0; i < spaceCounter; i++) {

						mBoard[row = row + d.GetRowDirect()][col = col + d.GetColDirect()] = mCurrentPlayer;
						mCurrentValue = mCurrentPlayer == Player::BLACK ? mCurrentValue + 2 : mCurrentValue - 2;
					}
					m->AddFlipSet(OthelloMove::FlipSet(spaceCounter, d));
					break;
				}
			}
			position = temp, spaceCounter = 0, row = position.GetRow(), col = position.GetCol();
		}
	}
	mHistory.push_back(std::move(move));
	mCurrentPlayer = mCurrentPlayer == Player::BLACK ? Player::WHITE : Player::BLACK;
}

void OthelloBoard::UndoLastMove() {

	OthelloMove *undoMove = dynamic_cast<OthelloMove*>(mHistory.back().get());
	BoardPosition position(undoMove->mPosition), temp(undoMove->mPosition);
	mBoard[position.GetRow()][position.GetCol()] = Player::EMPTY;
	mCurrentValue = mCurrentPlayer == Player::BLACK ? mCurrentValue + 1 : mCurrentValue - 1;

	//for all the pieces to be flipped in the move object
	for (OthelloMove::FlipSet f : undoMove->mFlips) {

		for (int i = 0; i < f.mFlipCount; i++) {

			//flips all pieces back to original player and updates board value
			position = position + f.mDirection;
			mBoard[position.GetRow()][position.GetCol()] = mCurrentPlayer;
			mCurrentValue = mCurrentPlayer == Player::BLACK ? mCurrentValue + 2 : mCurrentValue - 2;
		}
		position = temp;
	}
	mHistory.pop_back();
	mCurrentPlayer = mCurrentPlayer == Player::BLACK ? Player::WHITE : Player::BLACK;
}

bool OthelloBoard::IsFinished() const {

	return mHistory.size() == mBoard.size() * mBoard[0].size();
}
