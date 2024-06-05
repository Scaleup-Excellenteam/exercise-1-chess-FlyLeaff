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

public:
    Game();
    void initialize(const std::string& boardString);
    void switchTurn();
    bool movePiece(int srcRow, int srcCol, int destRow, int destCol);
    bool isWhiteTurn() const { return whiteTurn; }
    bool isGameOver() const;
    bool isLegalMove(int srcRow, int srcCol, int destRow, int destCol) const;
    bool doesMoveCauseSelfCheck(int srcRow, int srcCol, int destRow, int destCol) const;

    bool isCheck(char color) const;

    bool isWhitePiece(char pieceSymbol) const;
    char getCurrentPlayerColor() const;

    // Static function to parse chess notation
    static std::pair<std::pair<int, int>, std::pair<int, int>> parseMove(const std::string& move);

};

#endif // GAME_H
