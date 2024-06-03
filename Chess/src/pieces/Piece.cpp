#include "Piece.h"

std::vector<std::pair<int, int>> Piece::getValidMoves(int srcRow, int srcCol) const
{
    std::vector<std::pair<int, int>> moves;
    for (const auto& strategy : movementStrategies)
    {
        auto strategyMoves = strategy->getValidMoves(srcRow, srcCol);
        moves.insert(moves.end(), strategyMoves.begin(), strategyMoves.end());
    }
    return moves;
}

bool Piece::isValidMove(int srcRow, int srcCol, int destRow, int destCol) const
{
    auto validMoves = getValidMoves(srcRow, srcCol);
    for (const auto& move : validMoves)
    {
        if (move.first == destRow && move.second == destCol)
        {
            return true;
        }
    }
    return false;
}

