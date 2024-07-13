#ifndef MOVEEVALUATOR_H
#define MOVEEVALUATOR_H

class Game; // Forward declaration
class Board; // Forward declaration

class MoveEvaluator {
public:
    MoveEvaluator(const Game& game, const Board& board);

    int evalMove(int srcRow, int srcCol, int destRow, int destCol);
private:
    const Game& game;
    const Board& board;
    int evalThreatandPos(int srcRow, int srcCol, int destRow, int destCol);
    int evalPieceValues(char piece);
    int evalTakePiece(int destRow, int destCol);
    int centerControl(int destRow, int destCol);

};

#endif // MOVEEVALUATOR_H
