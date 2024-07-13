#include "ChessAlgorithm.h"
#include "Game.h"
#include "Board.h"
#include "Movecomparator.h"

ChessAlgorithm::ChessAlgorithm(const Game& game, const Board& board, int depth)
    : game(game), board(board), evaluator(game, board), depth(depth) {}

std::string ChessAlgorithm::recommendBestMove() {
    PriorityQueue<std::pair<int, std::string>, MoveComparator> pq;

    for(int row = 0; row < 8; row++)
		for(int col = 0; col < 8; col++)
		{
			if (board.getPiece(row, col) && board.getPiece(row, col)->getColor() == game.getCurrentPlayerColor())
			{
				auto moves = game.getAllPossibleMovesFrom(row, col,&game.getBoard());
				for (auto move : moves)
				{
					std::string moveStr = Game::formatMove(row, col, move.first, move.second);
					int moveValue = evaluator.evalMove(row, col, move.first, move.second);
					pq.push({ moveValue, moveStr });
				}
			}
				
		}

    return "asd";
}
