#pragma once
#include <vector>
#include <memory>
#include "MovementStrats.h"
class Piece
{
protected:
    std::vector<std::unique_ptr<MovementStrategy>> movementStrategies;
    char symbol;
    char color;

public:
    Piece(char symbol, char color) : symbol(symbol), color(color) {}
    Piece() : symbol(' '), color(' ') {}
    Piece(const Piece& other);

    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const;

    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol) const;

    inline char getSymbol() const { return symbol; }
    inline char getColor() const { return color; }
    virtual ~Piece() = default;
};
