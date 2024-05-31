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
    bool movePiece(int srcRow, int srcCol, int destRow, int destCol);

};

#endif // BOARD_H
