#pragma once

#include "Game.h"
#include "Board.h"
#include "MoveEvaluator.h"
#include "PriorityQueue.h"

class ChessAlgorithm {
public:
    ChessAlgorithm(const Game& game, int depth);
    std::string recommendBestMove();

private:
    const Game& game;
    MoveEvaluator evaluator;
    int depth;

    int minimax(Board& board, int depth, int alpha, int beta, bool isMaximizingPlayer, char currentPlayer);
};
