#pragma once

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "ChessExceptions.h"

class Game
{
private:

    mutable Board board;
    bool whiteTurn;
    bool innerIsCheck(Board& tempBoard, char color) const;
    inline void switchTurn();
    bool doesMoveCauseSelfCheck(int srcRow, int srcCol, int destRow, int destCol) const;
    inline char getOpponentColor() const;
    inline bool isWhitePiece(char pieceSymbol) const;

    inline bool isWhiteTurn() const { return whiteTurn; }
 
    bool didWhiteCastleLastTurn;
    bool didBlackCastleLastTurn;

public:
    Game();
    void initialize(const std::string& boardString);
    bool movePiece(int srcRow, int srcCol, int destRow, int destCol);
    inline bool isGameOver() const;
    bool isLegalMove(int srcRow, int srcCol, int destRow, int destCol) const;

    std::string lastCastleMove() const;

    bool isCheck(char color) const;
    //TODO: Implement checkmate

    inline char getCurrentPlayerColor() const;

    // Static function to parse chess notation
    static std::pair<std::pair<int, int>, std::pair<int, int>> parseMove(const std::string& move);

};

#endif // GAME_H
