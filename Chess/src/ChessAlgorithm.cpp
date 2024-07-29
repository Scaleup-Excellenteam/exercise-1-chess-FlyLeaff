#include "ChessAlgorithm.h"
#include "MoveComparator.h"
#include <algorithm>
#include <limits.h>

ChessAlgorithm::ChessAlgorithm(const Game& game, int depth)
    : game(game), evaluator(game, depth), depth(depth) {}

std::string ChessAlgorithm::recommendBestMove() {
    PriorityQueue<std::pair<int, std::string>, MoveComparator> pq;
    Board board = game.getBoard(); // Get the current board state

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board.getPiece(row, col) && board.getPiece(row, col)->getColor() == game.getCurrentPlayerColor()) {
                auto moves = game.getAllPossibleMovesFrom(row, col, &board);
                for (auto move : moves) {
                    std::string moveStr = Game::formatMove(row, col, move.first, move.second);
                    Board simulatedBoard = board; // Create a copy of the board for simulation
                    simulatedBoard.simulateMove(row, col, move.first, move.second); // Simulate the move
                    int moveValue = minimax(simulatedBoard, depth - 1, INT_MIN, INT_MAX, false, game.getOpponentColor());
                    pq.push({ moveValue, moveStr });
                }
            }
        }
    }

    return pq.pull().second;
}

int ChessAlgorithm::minimax(Board& board, int depth, int alpha, int beta, bool isMaximizingPlayer, char currentPlayer) {
    if (depth == 0) {
        return evaluator.evalMove(board, currentPlayer);
    }

    int bestScore = isMaximizingPlayer ? INT_MIN : INT_MAX;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board.getPiece(row, col) && board.getPiece(row, col)->getColor() == currentPlayer) {
                auto moves = game.getAllPossibleMovesFrom(row, col, &board);
                for (auto move : moves) {
                    Board simulatedBoard = board; // Create a copy of the board for simulation
                    simulatedBoard.simulateMove(row, col, move.first, move.second); // Simulate the move
                    int eval = minimax(simulatedBoard, depth - 1, alpha, beta, !isMaximizingPlayer, isMaximizingPlayer ? game.getOpponentColor() : game.getCurrentPlayerColor());
                    if (isMaximizingPlayer) {
                        bestScore = std::max(bestScore, eval);
                        alpha = std::max(alpha, eval);
                    }
                    else {
                        bestScore = std::min(bestScore, eval);
                        beta = std::min(beta, eval);
                    }
                    if (beta <= alpha) {
                        return bestScore;
                    }
                }
            }
        }
    }

    return bestScore;
}
