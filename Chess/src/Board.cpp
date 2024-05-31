#include "Board.h"
#include "Pieces/Rook.h"
#include <stdexcept>
#include <iostream>
// Include other piece headers as needed

Board::Board()
{
    // Initialize the board with null pointers
    board.resize(8);
    for (auto& row : board)
    {
        row.resize(8);
    }
}

void Board::initializeBoard(const std::string& boardString)
{
    if (boardString.size() != 64)
    {
        throw std::invalid_argument("Invalid board string length");
    }

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            char pieceChar = boardString[row * 8 + col];
            switch (pieceChar)
            {
            case 'R':
                board[row][col] = std::make_unique<Rook>('R');
                break;
            case 'r':
                board[row][col] = std::make_unique<Rook>('r');
                break;
                // Add cases for other pieces
            case '#':
                board[row][col] = nullptr;
                break;
            default:
                board[row][col] = nullptr;
                break;
            }
        }
    }
}

Piece* Board::getPiece(int row, int col) const
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
    {
        return nullptr;
    }
    return board[row][col].get();

}
bool Board::movePiece(int srcRow, int srcCol, int destRow, int destCol)
{
    if (srcRow < 0 || srcRow >= 8 || srcCol < 0 || srcCol >= 8 ||
        destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8)
    {
        return false;
    }

    Piece* piece = getPiece(srcRow, srcCol);
    if (!piece || !piece->isValidMove(srcRow, srcCol, destRow, destCol))
    {
        return false;
    }

    board[destRow][destCol] = std::move(board[srcRow][srcCol]);
    board[srcRow][srcCol].reset();
    return true;
}


