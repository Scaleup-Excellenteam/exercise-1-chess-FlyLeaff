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




/**
* @brief Update the enpassant moves by decrementing the counter and removing the move if it has expired
* 
*/
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

/**
* @brief Check if the move is an enpassant move
* @param srcRow Source row
* @param srcCol Source column
* @param destRow Destination row
* @param destCol Destination column
* @return true if the move is an enpassant move, false otherwise
*/
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
    return false;
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

Board::Board(const Board& other) 
{
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

/**
* @brief Initialize the board with the given board string
* @param boardString String representation of the board
* 
* i used the same format of boardString as the one in the chess.cpp file
* so this simply allows me to initialize both with the same string
*/
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
            case EMPTY_SPACE:
                board[row][col] = nullptr;
                break;
            case WHITE_ROOK:
                board[row][col] = std::make_unique<Rook>(WHITE);
                break;
            case BLACK_ROOK:
                board[row][col] = std::make_unique<Rook>(BLACK);
                break;
            case WHITE_KING:
                board[row][col] = std::make_unique<King>(WHITE);
                setWhiteKingPos(row, col);
                break;
            case BLACK_KING:
                board[row][col] = std::make_unique<King>(BLACK);
                setBlackKingPos(row, col);
                break;
            case WHITE_BISHOP:
                board[row][col] = std::make_unique<Bishop>(WHITE);
                break;
            case BLACK_BISHOP:
                 board[row][col] = std::make_unique<Bishop>(BLACK);
                 break;
            case WHITE_QUEEN:
                board[row][col] = std::make_unique<Queen>(WHITE);
                break;
			case BLACK_QUEEN:
                board[row][col] = std::make_unique<Queen>(BLACK);
    			break;
            case WHITE_KNIGHT:
                board[row][col] = std::make_unique<Knight>(WHITE);
                break;
            case BLACK_KNIGHT:
                board[row][col] = std::make_unique<Knight>(BLACK);
                break;
            case WHITE_PAWN:
                board[row][col] = std::make_unique<Pawn>(WHITE);
                break;
            case BLACK_PAWN:
                board[row][col] = std::make_unique<Pawn>(BLACK);
				break;


            default:
                board[row][col] = nullptr;
                break;
            }
        }
    printBoardTest();
    
}

/**
* @brief Print the board for testing purposes
* */
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
/**
* @brief Get the piece at the given row and column
*/
Piece* Board::getPiece(int row, int col) const
{
    if (!isWithinBounds(row, col))
        return nullptr;
    
    return board[row][col].get();

}

/**
* @brief Set the piece at the given row and column
* @param row Row index
* @param col Column index
* @param piece Piece to set
* @return true if the piece was set successfully, false otherwise
*/
bool Board::setPiece(int row, int col, std::unique_ptr<Piece> piece)
{
	if (!isWithinBounds(row, col))
		return false;
	board[row][col] = std::move(piece);
    return board[row][col] != nullptr;
}


/**
* @brief Move a piece from the source to the destination
* @param srcRow Source row
* @param srcCol Source column
*   @param destRow Destination row
* @param destCol Destination column
* @return true if the move was successful, false otherwise
* */
bool Board::movePiece(int srcRow, int srcCol, int destRow, int destCol)
{

    /// this function simply moves the piece from src to dest, it doesnt check if the move is valid
    if (!isWithinBounds(srcRow, srcCol) || !isWithinBounds(destRow, destCol))   
		return false;
	

    Piece* piece = getPiece(srcRow, srcCol);
    if (!piece)
        return false;
    char symbol = piece->getSymbol();
    if(symbol == WHITE_KING)
		setWhiteKingPos(destRow, destCol);
    if(symbol == BLACK_KING)
		setBlackKingPos(destRow, destCol);

    if (symbol == WHITE_PAWN || symbol == BLACK_PAWN) ///TODO optimize this
    {
        int direction = symbol == 'W' ? -1 : 1;
        if (symbol == WHITE_PAWN && destRow == 0)
        {///TODO handle promotion 
        }
        if (symbol == BLACK_PAWN && destRow == 7)
        {///TODO handle promotion 
            /// on a second look, there is no implementation for promotion in the chess.cpp file provided, so this is not needed
            /// ill leave this here for now just in case
        }
        if (symbol == WHITE_PAWN && srcRow == 1 && destRow == 3)
            enPassantMoves.push_back(std::make_pair(std::make_pair(destRow + direction, destCol), 1));

        if (symbol == BLACK_PAWN && srcRow == 6 && destRow == 4)
            enPassantMoves.push_back(std::make_pair(std::make_pair(destRow + direction, destCol), 1));

        if (isEnpassant(srcRow, srcCol, destRow, destCol))
            board[destRow + direction][destCol].reset();
    }
	Piece* destPiece = board[destRow][destCol].get();
    if (destPiece)
    {
		char destSymbol = destPiece->getSymbol();
		if (destSymbol == WHITE_KING)
			setWhiteKingPos(-1, -1);
		if (destSymbol == BLACK_KING)
			setBlackKingPos(-1, -1);
	}
    board[destRow][destCol] = std::move(board[srcRow][srcCol]);
    if(board[srcRow][srcCol])
        board[srcRow][srcCol].reset();
    return true;
}


/**
* @brief Simulate a move on the board
* @param srcRow Source row
* @param srcCol Source column
* @param destRow Destination row
* @param destCol Destination column
* @return A new board with the move simulated
* 
* used to check if a move will cause check without actually moving the piece
*/
Board* Board::simulateMove(int srcRow, int srcCol, int destRow, int destCol) const
{
    Board* boardCopy = new Board(*this); /// Copy the current board (deep copy of pieces
    boardCopy->movePiece(srcRow, srcCol, destRow, destCol);
    return boardCopy;
}

/**
* @brief Check if the move is valid
* 
* @param srcRow Source row
* @param srcCol Source column
* @param destRow Destination row
* @param destCol Destination column
* @return true if the move is valid, false otherwise
* 
*/
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
            /// Check for path blocking for sliding pieces: Rook, Bishop, and Queen
            if (isSlidingPiece(srcSymbol))
            {
                int rowStep = (destRow - srcRow) ? (destRow - srcRow) / abs(destRow - srcRow) : 0;
                int colStep = (destCol - srcCol) ? (destCol - srcCol) / abs(destCol - srcCol) : 0;

                for (int r = srcRow + rowStep, c = srcCol + colStep; r != destRow || c != destCol; r += rowStep, c += colStep)
                {
                    if (board[r][c])
                        return false;
                }
            }
            

            Piece* destPiece = getPiece(destRow, destCol);
            if (destPiece)
            {
                char destColor = destPiece->getColor();

                if(srcColor == destColor)
					return false;   /// self capture

            }

            /// Handle pawn captures
            if (srcSymbol == WHITE_PAWN || srcSymbol == BLACK_PAWN)
            {
                if(destPiece && destCol==srcCol)
					return false; /// Pawns cant eat forward
                //if (isEnpassant(srcRow, srcCol, destRow, destCol)) /// EnPassant captures
                    // Enpassant capture apparently not supported via chess.cpp
                  //  return true; 
                if (destCol != srcCol && !destPiece)
                    return false; /// Pawns can only move diagonally if capturing

            }

            return true;
        }
    }
   

 //   if (srcSymbol == whiteKing || srcSymbol == blackKing)
 //   {
	//	if (canCastle(srcSymbol, destRow, destCol))
	//		return true;
	//}
    // chess.cpp doesnt support castling so i cannot utilize this
 

    return false;
}

/**
* @brief Check if the king can castle
* @param srcSymbol Symbol of the king
* @param destRow Destination row
* @param destCol Destination column
* @return true if the king can castle, false otherwise
*/
bool Board::canCastle(char srcSymbol, int destRow, int destCol) const
{
    int row = (srcSymbol == WHITE_KING) ? 0 : 7;
    int kingsideRookCol = 7;
    int queensideRookCol = 0;

    King* king = dynamic_cast<King*>(board[row][4].get());  // this will fail if not a king
    if (king && !king->wasMoved && !king->wasChecked)
    {
        if (destCol == 6 && destRow == row) // Kingside
        {
            if (Rook* rook = dynamic_cast<Rook*>(board[row][kingsideRookCol].get()))
            {
                if (!rook->wasMoved)
                {
                    for (int i = 5; i < 7; ++i)
                        if (board[row][i])
                            return false;
                    return true;
                }
            }
        }
        else if (destCol == 2 && destRow == row) // Queenside
        {
            if (Rook* rook = dynamic_cast<Rook*>(board[row][queensideRookCol].get()))
            {
                if (!rook->wasMoved)
                {
                    for (int i = 1; i < 4; ++i)
                        if (board[row][i])
                            return false;
                    return true;
                }
            }
        }
    }

    return false;
}

/**
* @brief Check if the piece is a sliding piece
* @param srcSymbol Symbol of the piece
* @return true if the piece is a sliding piece, false otherwise
* 
* Sliding pieces are Rook, Bishop, and Queen

*/
bool Board::isSlidingPiece(char srcSymbol) const
{
    return srcSymbol == WHITE_ROOK || srcSymbol == BLACK_ROOK || srcSymbol == WHITE_BISHOP ||
             srcSymbol == BLACK_BISHOP || srcSymbol == WHITE_QUEEN || srcSymbol == BLACK_QUEEN;
}

// Overload the subscript operator for non const access

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