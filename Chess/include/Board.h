#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <string>
#include "Piece.h"

class Board
{
private:
    std::vector<std::vector<std::unique_ptr<Piece>>> board;

public:
    Board();
    void initializeBoard(const std::string& boardString);
    Piece* getPiece(int row, int col) const;
    bool setPiece(int row, int col, std::unique_ptr<Piece> piece);
    bool movePiece(int srcRow, int srcCol, int destRow, int destCol);
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol) const;

    static bool isWithinBounds(int row, int col);

    std::vector<std::unique_ptr<Piece>>& operator[](int row);
    const std::vector<std::unique_ptr<Piece>>& operator[](int row) const;

    static const char white = 'w';
    static const char black = 'b';
};

#endif // BOARD_H
