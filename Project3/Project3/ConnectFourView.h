#pragma once
#include "GameView.h"
#include "ConnectFourBoard.h"
#include "ConnectFourMove.h"
#include <memory>

class ConnectFourView : public GameView {
private:
	std::shared_ptr<ConnectFourBoard> mCFBoard;


	// Inherited via GameView
	void PrintBoard(std::ostream &s) const override;

public:
	ConnectFourView(std::shared_ptr<ConnectFourBoard> board);

	//Inherited via GameView
	std::unique_ptr<GameMove> ParseMove(const std::string & move) const override;
	std::string GetPlayerString(int player) const override;

	friend std::ostream& operator<< (std::ostream &lhs, const ConnectFourView &rhs);
};
std::ostream& operator<<(std::ostream &lhs, const ConnectFourMove &rhs);

