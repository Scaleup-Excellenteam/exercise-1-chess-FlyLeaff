#ifndef MOVEEVALUATOR_H
#define MOVEEVALUATOR_H

class Game; // Forward declaration
class Board; // Forward declaration

class MoveEvaluator {
public:
    MoveEvaluator(const Game& game, const Board& board, int depth);

    int evalMove(int srcRow, int srcCol, int destRow, int destCol,char player);
private:
    const Game& game;
    const Board& board;
    int evalThreatandPos(int srcRow, int srcCol, int destRow, int destCol, char player,Board* simBoard);
    int evalPieceValues(char piece);
    int evalTakePiece(int destRow, int destCol);
    int centerControl(int destRow, int destCol);
    int depth;
};

#endif // MOVEEVALUATOR_H
