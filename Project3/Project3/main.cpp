#include "GameView.h"
#include "GameBoard.h"
#include "GameMove.h"
#include "TicTacToeBoard.h"
#include "TicTacToeView.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "ConnectFourBoard.h"
#include "ConnectFourView.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

int main(int argc, char* argv[]) {

	// Initialization
	string gameChoice, userInput; // a string to hold the user's command choice
	shared_ptr<GameBoard> board;
	unique_ptr<GameView> v;

	do {

		cout << "What game do you want to play?  1) Othello; 2) Tic Tac Toe; 3) Connect Four; 4) Exit";
		cin >> gameChoice;

		if (gameChoice == "1") {

			auto oBoard = make_shared<OthelloBoard>();
			v = make_unique<OthelloView>(oBoard);
			board = oBoard;

		}
		else if (gameChoice == "2") {

			auto TTTBoard = make_shared<TicTacToeBoard>();
			v = make_unique<TicTacToeView>(TTTBoard);
			board = TTTBoard;
		}
		else if (gameChoice == "3") {

			auto CFBoard = make_shared<ConnectFourBoard>();
			v = make_unique<ConnectFourView>(CFBoard);
			board = CFBoard;
		}
		else if  (gameChoice == "4") {

			break;
		}
		// Main loop
		do {
			// Print the game board using the GameView object
			 cout << endl << *v;
			 cout << v->GetPlayerString(board->GetCurrentPlayer()) << "'s move:" << endl;

			// Print all possible moves
			cout << "Possible moves:" << endl;
			const std::vector<std::unique_ptr<GameMove>> &possibleMoves = board->GetPossibleMoves();
			for (int i = 0; i < possibleMoves.size(); i++) {

				cout << (string) *possibleMoves[i] << " ";
			}
			bool validCommand = false;
			do {
				// Ask to input a command
				cout << endl << "Enter a command:" << endl;
				cin >> userInput;

				// Command loop:
			 // move (r,c)
				if (userInput == "move") {

					bool found = false;
					string move;
					cin >> move;

					//creates a move object 
					unique_ptr<GameMove> m{ v->ParseMove(move) };
		
					for (int i = 0; i < possibleMoves.size(); i++) {

						//if the user enters a possible move, that move will be applied to the game board
						if (*possibleMoves[i] == *m) {

							board->ApplyMove(std::move(m));
							validCommand = true;
							found = true;
							break;
						}
					}
					//if user enters an invalid move
					if (!found) {

						cout << endl << "Not a valid move" << endl << endl;
					}
				}
				// undo n
				else if (userInput == "undo") {

					int n;
					cin >> n;
					validCommand = true;

					//if user undos more moves than has already been played
					if (n > board->GetMoveHistory().size()) {

						cout << endl << "Going back to starting baord" << endl << endl;
						n = board->GetMoveHistory().size();
					}
					for (int i = 0; i < n; i++) {

						board->UndoLastMove();
					}
				}
				// showValue
				else if (userInput == "showValue") {

					cout << endl << "Board Value: " << board->GetValue() << endl << endl;
				}
				// showHistory
				else if (userInput == "showHistory") {

					int count = 0;
				    string otherPlayer = v->GetPlayerString(-1 * board->GetCurrentPlayer());
					string currentPlayer = v->GetPlayerString(board->GetCurrentPlayer());
			
					const std::vector<std::unique_ptr<GameMove>> &moveHistory = board->GetMoveHistory();
					cout << endl;

					//walks through moveHistory vector backwards
					for (vector<unique_ptr<GameMove>>::const_reverse_iterator rItr = moveHistory.rbegin();
						rItr != moveHistory.rend(); rItr++) {

						if (count % 2 == 0) {

							cout << otherPlayer << ":" << (string)(**rItr) << endl;
						}
						else {

							cout << currentPlayer << ":" << (string)(**rItr) << endl;
						}
						count++;
					}
				}
				// quit
				else if (userInput == "quit") {

					break;
				}

			} while (!validCommand);

		} while (!board->IsFinished() && userInput != "quit"); // you may want to change the condition
		//prints out a winner based on the value of the board
		if (board->GetValue() > 0) {

			cout << endl << v->GetPlayerString(1) << " Wins!" << endl;
		}
		else if (board->GetValue() < 0) {

			cout << endl << v->GetPlayerString(-1) << " Wins!" << endl;
		}
		else {

			cout << endl << "Tie!" << endl;
		}
	}while (gameChoice != "4");	
}
