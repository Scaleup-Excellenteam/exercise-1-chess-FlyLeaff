#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H

#include "Game.h"
#include "Board.h"
#include "MoveEvaluator.h"
#include "PriorityQueue.h"
#include <string>

class ChessAlgorithm {
public:
    ChessAlgorithm(const Game& game, const Board& board, int depth);
    std::string recommendBestMove();

private:
    const Game& game;
    const Board& board;
    MoveEvaluator evaluator;
    int depth;
};

#endif // CHESSALGORITHM_H
