#include "MovementStrats.h"

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

std::vector<std::pair<int, int>> PawnMovement::getValidMoves(int srcRow, int srcCol) const
{
    std::vector<std::pair<int, int>> moves;
    int direction = 1; // Assuming white pieces move upwards
    if (srcRow + direction < 8)
    {
        moves.emplace_back(srcRow + direction, srcCol); // Move forward
        if (srcRow == 1 && srcRow + 2 * direction < 8)
            moves.emplace_back(srcRow + 2 * direction, srcCol); // Double move forward
        if (srcCol > 0)
            moves.emplace_back(srcRow + direction, srcCol - 1); // Capture left
        if (srcCol < 7)
            moves.emplace_back(srcRow + direction, srcCol + 1); // Capture right
    }
    return moves;
}
