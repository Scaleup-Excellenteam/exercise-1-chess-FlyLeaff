#include "MovementStrats.h"
#include "ConstUtils.h"

std::vector<std::pair<int, int>> HorizontalVerticalMovement::getValidMoves(int srcRow, int srcCol) const
{
    std::vector<std::pair<int, int>> moves;

    // Horizontal moves
    for (int col = 0; col < 8; ++col)
    {
        if (col != srcCol)  // Exclude the source column
            moves.emplace_back(srcRow, col);
    }

    // Vertical moves
    for (int row = 0; row < 8; ++row)
    {
        if (row != srcRow)  // Exclude the source row
            moves.emplace_back(row, srcCol);
    }

    return moves;
}

std::unique_ptr<MovementStrategy> HorizontalVerticalMovement::clone() const
{
    return std::make_unique<HorizontalVerticalMovement>(*this);
}


std::vector<std::pair<int, int>> DiagonalMovement::getValidMoves(int srcRow, int srcCol) const
{
    std::vector<std::pair<int, int>> moves;
    for (int i = 1; i < 8; ++i)
    {
        if (srcRow + i < 8 && srcCol + i < 8) moves.emplace_back(srcRow + i, srcCol + i);
        if (srcRow - i >= 0 && srcCol + i < 8) moves.emplace_back(srcRow - i, srcCol + i);
        if (srcRow + i < 8 && srcCol - i >= 0) moves.emplace_back(srcRow + i, srcCol - i);
        if (srcRow - i >= 0 && srcCol - i >= 0) moves.emplace_back(srcRow - i, srcCol - i);
    }
    return moves;
}

std::unique_ptr<MovementStrategy> DiagonalMovement::clone() const
{
    return std::make_unique<DiagonalMovement>(*this);
}

std::vector<std::pair<int, int>> KingMovement::getValidMoves(int srcRow, int srcCol) const
{
    std::vector<std::pair<int, int>> moves;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
            {
                int newRow = srcRow + i;
                int newCol = srcCol + j;
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
                    moves.emplace_back(newRow, newCol);
            }
    return moves;
}

std::unique_ptr<MovementStrategy> KingMovement::clone() const
{
    return std::make_unique<KingMovement>(*this);
}

std::vector<std::pair<int, int>> KnightMovement::getValidMoves(int srcRow, int srcCol) const
{
    std::vector<std::pair<int, int>> moves;
    int possibleMoves[8][2] =
    {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    for (const auto& move : possibleMoves)
    {
        int newRow = srcRow + move[0];
        int newCol = srcCol + move[1];
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8)
            moves.emplace_back(newRow, newCol);
    }
    return moves;
}

std::unique_ptr<MovementStrategy> KnightMovement::clone() const
{
    return std::make_unique<KnightMovement>(*this);
}

std::vector<std::pair<int, int>> PawnMovement::getValidMoves(int srcRow, int srcCol) const
{
    std::vector<std::pair<int, int>> moves;
    int direction = isWhite ? 1 : -1; // White pawns move down (+1), black pawns move up (-1)

    // Move forward one square
    if (isWithinBounds(srcRow + direction, srcCol))
    {
        moves.emplace_back(srcRow + direction, srcCol);

        // Move forward two squares from the starting position
        if ((isWhite && srcRow == 1) || (!isWhite && srcRow == 6))
        {
            if (isWithinBounds(srcRow + 2 * direction, srcCol))
            {
                moves.emplace_back(srcRow + 2 * direction, srcCol);
            }
        }
    }

    // Capture left
    if (isWithinBounds(srcRow + direction, srcCol - 1))
    {
        moves.emplace_back(srcRow + direction, srcCol - 1);
    }

    // Capture right
    if (isWithinBounds(srcRow + direction, srcCol + 1))
    {
        moves.emplace_back(srcRow + direction, srcCol + 1);
    }

    return moves;
}
std::unique_ptr<MovementStrategy> PawnMovement::clone() const
{
    return std::make_unique<PawnMovement>(*this);
}
