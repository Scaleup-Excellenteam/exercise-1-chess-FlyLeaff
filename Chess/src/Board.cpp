#include "Board.h"
#include "Rook.h"
#include "King.h"
#include <stdexcept>
#include <iostream>
#include <Bishop.h>
#include "ConstUtils.h"
#include <Queen.h>
#include <Knight.h>
#include <Pawn.h>
// Include other piece headers as needed

void Board::updateEnPassantMoves()
{
    for (int i = enPassantMoves.size() - 1; i >= 0; --i)
    {
        if (enPassantMoves[i].second == 0)
            enPassantMoves.erase(enPassantMoves.begin() + i);
        else
            enPassantMoves[i].second--;
    }
}

bool Board::isEnpassant(int srcRow, int srcCol, int destRow, int destCol) const
{
    int direction = board[srcRow][srcCol]->getColor() == 'W' ? -1 : 1;

    for (auto enpasantMove : enPassantMoves)
    {
        if (enpasantMove.first.first == destRow && enpasantMove.first.second == destCol)
        {
            if (srcRow + direction == destRow && abs(srcCol - destCol) == 1)
            {
                return true;
            }
        }
    }
}

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
            case whiteKnight:
                board[row][col] = std::make_unique<Knight>(white);
                break;
            case blackKnight:
                board[row][col] = std::make_unique<Knight>(black);
                break;
            case whitePawn:
                board[row][col] = std::make_unique<Pawn>(white);
                break;
            case blackPawn:
                board[row][col] = std::make_unique<Pawn>(black);
				break;


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
    char symbol = piece->getSymbol();
    if(symbol == whiteKing)
		setWhiteKingPos(destRow, destCol);
    if(symbol == blackKing)
		setBlackKingPos(destRow, destCol);

    if (symbol == whitePawn || symbol == blackPawn) //TODO optimize this
    {
        int direction = symbol == 'W' ? -1 : 1;
        if (symbol == whitePawn && destRow == 0)
        {//TODO handle promotion 
        }
        if (symbol == blackPawn && destRow == 7)
        {//TODO handle promotion 
            // on a second look, there is no implementation for promotion in the chess.cpp file provided, so this is not needed
            // ill leave this here for now just in case
        }
        if (symbol == whitePawn && srcRow == 1 && destRow == 3)
            enPassantMoves.push_back(std::make_pair(std::make_pair(destRow + direction, destCol), 1));

        if (symbol == blackPawn && srcRow == 6 && destRow == 4)
            enPassantMoves.push_back(std::make_pair(std::make_pair(destRow + direction, destCol), 1));

        if (isEnpassant(srcRow, srcCol, destRow, destCol))
            board[destRow + direction][destCol].reset();
    }
	Piece* destPiece = board[destRow][destCol].get();
    if (destPiece)
    {
		char destSymbol = destPiece->getSymbol();
		if (destSymbol == whiteKing)
			setWhiteKingPos(-1, -1);
		if (destSymbol == blackKing)
			setBlackKingPos(-1, -1);
	}
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
    char srcColor = srcPiece->getColor();
    char srcSymbol = srcPiece->getSymbol();

    auto validMoves = srcPiece->getValidMoves(srcRow, srcCol);
    for (const auto& move : validMoves)
    {
        if (move.first == destRow && move.second == destCol)
        {
            // Check for path blocking for sliding pieces: Rook, Bishop, and Queen
            if (srcSymbol == whiteRook || srcSymbol == blackRook || srcSymbol == whiteBishop || blackBishop || srcSymbol == whiteQueen || srcSymbol == blackQueen)
            {
                int rowStep = (destRow - srcRow) ? (destRow - srcRow) / abs(destRow - srcRow) : 0;
                int colStep = (destCol - srcCol) ? (destCol - srcCol) / abs(destCol - srcCol) : 0;

                for (int r = srcRow + rowStep, c = srcCol + colStep; r != destRow || c != destCol; r += rowStep, c += colStep)
                {
                    if (board[r][c])
                        return false;
                }
            }

            switch (srcSymbol)
            {
                case whiteRook:
                {

                }
                // fall through
                case blackRook:
                {
                    break;
                }
                case whiteBishop:
                {
					break;
				}
                case blackBishop:
                {
                    break;
                }




                {
                default:
                    break;
                }
            }
               

            Piece* destPiece = getPiece(destRow, destCol);
            if (destPiece)
            {
                char destColor = destPiece->getColor();

                if(srcColor == destColor)
					return false;   // self capture

            }

            // Handle pawn captures
            if (srcSymbol == whitePawn || srcSymbol == blackPawn)
            {
                if (isEnpassant(srcRow, srcCol, destRow, destCol))
                    return true; 
                if (destCol != srcCol && !destPiece)
                    return false; // Pawns can only move diagonally if capturing

            }

            return true;
        }
    }

    return false;
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