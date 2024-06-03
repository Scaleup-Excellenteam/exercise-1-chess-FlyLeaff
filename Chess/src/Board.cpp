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
        throw std::invalid_argument("Invalid board string length");


    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col)
        {
            char pieceChar = boardString[row * 8 + col];
            switch (pieceChar)
            {
            case 'R':
                board[row][col] = std::make_unique<Rook>('w');
                break;
            case 'r':
                board[row][col] = std::make_unique<Rook>('b');
                break;
                // TODO Add cases for other pieces
            case '#':
                board[row][col] = nullptr;
                break;
            default:
                board[row][col] = nullptr;
                break;
            }
        }
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (board[row][col])
                std::cout << board[row][col]->getSymbol() << ' ';
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
    
}

Piece* Board::getPiece(int row, int col) const
{
    if (!isWithinBounds(row, col))
        return nullptr;
    
    return board[row][col].get();

}
bool Board::movePiece(int srcRow, int srcCol, int destRow, int destCol)
{

    // this function simply moves the piece from src to dest, it doesnt check if the move is valid
    if (!isWithinBounds(srcRow, srcCol) || !isWithinBounds(destRow, destCol))   
		return false;
	

    Piece* piece = getPiece(srcRow, srcCol);
    if (!piece)
        return false;


    board[destRow][destCol] = std::move(board[srcRow][srcCol]);
    board[srcRow][srcCol].reset();
    return true;
}

bool Board::isWithinBounds(int row, int col) 
{
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}
