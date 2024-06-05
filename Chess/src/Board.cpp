#include "Board.h"
#include "Rook.h"
#include "King.h"
#include <stdexcept>
#include <iostream>
#include <Bishop.h>
#include "ConstUtils.h"
#include <Queen.h>
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

Board::Board(const Board& other) {
    // Allocate new memory for the 2D vector of pieces
    board = std::vector<std::vector<std::unique_ptr<Piece>>>(other.board.size());
    for (int i = 0; i < other.board.size(); ++i) {
        // Resize each inner vector and copy pieces using new pointers
        board[i].resize(other.board[i].size());
        for (int j = 0; j < other.board[i].size(); ++j) {
            if (other.board[i][j]) {
                // Deep copy the piece using the Piece's copy constructor (assumed to exist)
                board[i][j] = std::make_unique<Piece>(*other.board[i][j]);
            }
            else {
                board[i][j] = nullptr;
            }
        }
    }
    // Copy king positions
    whiteKingPos = other.whiteKingPos;
    blackKingPos = other.blackKingPos;
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
            case empty:
                board[row][col] = nullptr;
                break;
            case whiteRook:
                board[row][col] = std::make_unique<Rook>(white);
                break;
            case blackRook:
                board[row][col] = std::make_unique<Rook>(black);
                break;
            case whiteKing:
                board[row][col] = std::make_unique<King>(white);
                setWhiteKingPos(row, col);
                break;
            case blackKing:
                board[row][col] = std::make_unique<King>(black);
                setBlackKingPos(row, col);
                break;
            case whiteBishop:
                board[row][col] = std::make_unique<Bishop>(white);
                break;
            case blackBishop:
                 board[row][col] = std::make_unique<Bishop>(black);
                 break;
            case whiteQueen:
                board[row][col] = std::make_unique<Queen>(white);
                break;
			case blackQueen:
                board[row][col] = std::make_unique<Queen>(black);
    			break;
                // TODO Add cases for other pieces

            default:
                board[row][col] = nullptr;
                break;
            }
        }
    printBoardTest();
    
}

void Board::printBoardTest() const
{
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
bool Board::setPiece(int row, int col, std::unique_ptr<Piece> piece)
{
	if (!isWithinBounds(row, col))
		return false;
	board[row][col] = std::move(piece);
    return true;
}

bool Board::movePiece(int srcRow, int srcCol, int destRow, int destCol)
{

    // this function simply moves the piece from src to dest, it doesnt check if the move is valid
    if (!isWithinBounds(srcRow, srcCol) || !isWithinBounds(destRow, destCol))   
		return false;
	

    Piece* piece = getPiece(srcRow, srcCol);
    if (!piece)
        return false;
    if(piece->getSymbol() == whiteKing)
		setWhiteKingPos(destRow, destCol);
    if(piece->getSymbol() == blackKing)
		setBlackKingPos(destRow, destCol);


    board[destRow][destCol] = std::move(board[srcRow][srcCol]);
    if(board[srcRow][srcCol])
        board[srcRow][srcCol].reset();
    return true;
}

Board* Board::simulateMove(int srcRow, int srcCol, int destRow, int destCol) const
{
    Board* boardCopy = new Board(*this); // Copy the current board (deep copy of pieces
    boardCopy->movePiece(srcRow, srcCol, destRow, destCol);
    return boardCopy;
}

bool Board::isValidMove(int srcRow, int srcCol, int destRow, int destCol) const
{
    if (!isWithinBounds(srcRow, srcCol) || !isWithinBounds(destRow, destCol))
        return false;

    Piece* srcPiece = getPiece(srcRow, srcCol);
    if (!srcPiece)
        return false;

    auto validMoves = srcPiece->getValidMoves(srcRow, srcCol);
    for (const auto& move : validMoves)
    {
        if (move.first == destRow && move.second == destCol)
        {
            // Check for path blocking for sliding pieces: Rook, Bishop, and Queen
            if (dynamic_cast<Rook*>(srcPiece) ) //|| dynamic_cast<Bishop*>(srcPiece) || dynamic_cast<Queen*>(srcPiece)
            {
                int rowStep = (destRow - srcRow) ? (destRow - srcRow) / abs(destRow - srcRow) : 0;
                int colStep = (destCol - srcCol) ? (destCol - srcCol) / abs(destCol - srcCol) : 0;
                for (int r = srcRow + rowStep, c = srcCol + colStep; r != destRow || c != destCol; r += rowStep, c += colStep)  //Bug check this
                {
                    if (board[r][c])
                        return false;
                }
            }

            Piece* destPiece = getPiece(destRow, destCol);
            if (destPiece)
            {
                bool isSrcWhite = (srcPiece->getSymbol() >= 'A' && srcPiece->getSymbol() <= 'Z');
                bool isDestWhite = (destPiece->getSymbol() >= 'A' && destPiece->getSymbol() <= 'Z');
                if (isSrcWhite == isDestWhite)
                    return false;
            }

            return true;
        }
    }

    return false;
}


bool Board::isWithinBounds(int row, int col) 
{
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}
std::vector<std::unique_ptr<Piece>>& Board::operator[](int row)
{
    if (row < 0 || row > 7)
        throw std::out_of_range("Invalid row index");
    return board[row];
}

// Overload the subscript operator for const access
const std::vector<std::unique_ptr<Piece>>& Board::operator[](int row) const
{
    if(row < 0 || row > 7)
		throw std::out_of_range("Invalid row index");
    return board[row];
}