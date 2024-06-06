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
    std::pair<int, int> whiteKingPos;
    std::pair<int, int> blackKingPos;



    std::vector<std::pair<std::pair<int, int>,int>> enPassantMoves; //a pair of the enpasant'able position, and an int to countdown the number of turns it has left(2 turns)
    bool isEnpassant(int srcRow, int srcCol,int destRow,int destCol) const;
public:
    Board();
    Board(const Board& other);
    void initializeBoard(const std::string& boardString);
    void printBoardTest() const;
    Piece* getPiece(int row, int col) const;
    bool setPiece(int row, int col, std::unique_ptr<Piece> piece);

    bool movePiece(int srcRow, int srcCol, int destRow, int destCol);
    Board* simulateMove(int srcRow, int srcCol, int destRow, int destCol) const;
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol) const;

    bool canCastle(char srcSymbol, int destRow, int destCol) const;

    bool isSlidingPiece(char srcSymbol) const;

    void updateEnPassantMoves();



    std::vector<std::unique_ptr<Piece>>& operator[](int row);
    const std::vector<std::unique_ptr<Piece>>& operator[](int row) const;

    std::pair<int, int> getWhiteKingPos() const { return whiteKingPos; }
    std::pair<int, int> getBlackKingPos() const { return blackKingPos; }
    void setWhiteKingPos(int row, int col) { whiteKingPos = std::make_pair(row, col); }
    void setBlackKingPos(int row, int col) { blackKingPos = std::make_pair(row, col); }


};

#endif // BOARD_H
