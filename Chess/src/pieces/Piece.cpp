#include "Piece.h"
#include <stdexcept>

Piece::Piece(const Piece& other) : symbol(other.symbol), color(other.color) {
    movementStrategies.reserve(other.movementStrategies.size());
    for (const auto& strategy : other.movementStrategies) {
        // Since MovementStrategy is pure virtual, we can't directly copy it
        // that why the clone method exists
        if (strategy) {
            if (const auto* cloneMethod = dynamic_cast<const MovementStrategy*>(strategy.get())) {
                movementStrategies.push_back(cloneMethod->clone());
            }
            else 
            {
                throw std::runtime_error("Invalid MovementStrategy type");
            }
        }
        else {
            movementStrategies.push_back(nullptr);
        }
    }
}

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

