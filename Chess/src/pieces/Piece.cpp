#include "Piece.h"

Piece::Piece(const Piece& other) : symbol(other.symbol), color(other.color) {
    // Allocate new memory for the vector of movement strategies
    movementStrategies.reserve(other.movementStrategies.size());
    for (const auto& strategy : other.movementStrategies) {
        // Since MovementStrategy is pure virtual, we can't directly copy it
        // Use a custom clone() method if MovementStrategy has one
        if (strategy) {
            // Check if MovementStrategy provides a clone() method
            if (const auto* cloneMethod = dynamic_cast<const MovementStrategy*>(strategy.get())) {
                movementStrategies.push_back(cloneMethod->clone());
            }
            else {
                // Handle the case where clone() is not available (error or alternative logic)
                // You might throw an exception or implement alternative copying logic here
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

