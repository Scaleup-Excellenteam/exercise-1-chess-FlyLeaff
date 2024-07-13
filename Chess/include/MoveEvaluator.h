#pragma once

#include "Game.h"
#include "Board.h"

class MoveEvaluator {
public:
    MoveEvaluator(const Game& game, int depth);
    int evalMove(Board& board, char player);

private:
    const Game& game;
    int depth;

    int evalThreatandPos(Board& board, char player);
    int evalPieceValues(char piece);
    int centerControl(int destRow, int destCol);
};
