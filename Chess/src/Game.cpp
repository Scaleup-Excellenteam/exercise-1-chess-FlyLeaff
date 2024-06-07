#include "Game.h"
#include <iostream>
#include <King.h>


Game::Game() : whiteTurn(true)
{
	board.setWhiteKingPos(0, 4);
	board.setBlackKingPos(7, 4);

    didBlackCastleLastTurn = false;
    didWhiteCastleLastTurn = false;
}

void Game::initialize(const std::string& boardString)
{
    board.initializeBoard(boardString);
}

/**
 * @brief Switch the turn of the player
 */
void Game::switchTurn()
{
    whiteTurn = !whiteTurn;
    board.updateEnPassantMoves();
}

/**
 * @brief Move a piece on the board
 * * @param srcRow Source row
 * * @param srcCol Source column
 * * @param destRow Destination row
 * * @param destCol Destination column
 * * @return true if the move was successful, false otherwise
 */

bool Game::movePiece(int srcRow, int srcCol, int destRow, int destCol)
{
    if (board.movePiece(srcRow, srcCol, destRow, destCol))
    {
        if (board[destRow][destCol]->getSymbol() == WHITE_KING)
        {   // keep track of kings position for check checks
            board.setWhiteKingPos(destRow, destCol);
            // below here is for castling, which isnt supported via chess.cpp
            if (King* king = dynamic_cast<King*>(board[destRow][destCol].get())) 
                king->wasMoved = true;
            
            if (srcRow == 0 && srcCol == 4 && destRow == 0 && destCol == 6)
            {
				board.movePiece(0, 7, 0, 5);
                didWhiteCastleLastTurn = true;
			}
			if (srcRow == 0 && srcCol == 4 && destRow == 0 && destCol == 2)
			{
				board.movePiece(0, 0, 0, 3);
                didWhiteCastleLastTurn = true;
			}
        }
        else if (board[destRow][destCol]->getSymbol() == BLACK_KING)
        {
            board.setBlackKingPos(destRow, destCol);
            if (King* king = dynamic_cast<King*>(board[destRow][destCol].get()))           
                king->wasMoved = true;
            if (srcRow == 7 && srcCol == 4 && destRow == 7 && destCol == 6)
            {
                board.movePiece(7, 7, 7, 5);
                didBlackCastleLastTurn = true;
            }
            if (srcRow == 7 && srcCol == 4 && destRow == 7 && destCol == 2)
            {
				board.movePiece(7, 0, 7, 3);
                didBlackCastleLastTurn = true;
			}
		}
        else 
        {
            didBlackCastleLastTurn = false;
            didWhiteCastleLastTurn = false;
        }
        switchTurn();
        return true;
    }
    return false;
}

/**
 * @brief Check if a move is legal
 * * @param srcRow Source row
 * * @param srcCol Source column
 * * @param destRow Destination row
 * * @param destCol Destination column
 * * @return true if the move is legal, false otherwise
 * it also throws exceptions if the move is illegal which is how we know which one in main
 */
bool Game::isLegalMove(int srcRow, int srcCol, int destRow, int destCol) const
{
    if (!isWithinBounds(srcRow, srcCol) || !isWithinBounds(destRow, destCol))
        throw OutOfBoundsException();
	

    Piece* srcPiece = board.getPiece(srcRow, srcCol);
    if (!srcPiece)
        return false;
    

    char pieceSymbol = srcPiece->getSymbol();
    bool isSrcPieceWhite = (isWhitePiece(pieceSymbol));

    if ((whiteTurn && !isSrcPieceWhite) || (!whiteTurn && isSrcPieceWhite))
        throw OpponentPieceAtSourceException();
    

    if (!board.isValidMove(srcRow, srcCol, destRow, destCol))
        throw IllegalMoveException();

    if (doesMoveCauseSelfCheck(srcRow, srcCol, destRow, destCol))
        throw MoveCausesSelfCheckException();


    Piece* destPiece = board.getPiece(destRow, destCol);
    if (destPiece)
    {
        char destSymbol = destPiece->getSymbol();
        bool isDestPieceWhite = isWhitePiece(destSymbol);

        if ((whiteTurn && isDestPieceWhite) || (!whiteTurn && !isDestPieceWhite))
        {
            throw OwnPieceAtDestinationException();
        }
    }

    return true;
}
/**
 * @brief Check if a move causes self check
 * * @param srcRow Source row
 * * @param srcCol Source column
 * * @param destRow Destination row
 * * @param destCol Destination column
 * * @return true if the move causes self check, false otherwise
 * 
 * it simulates the move and checks if the player is in check after the move
 */
bool Game::doesMoveCauseSelfCheck(int srcRow, int srcCol, int destRow, int destCol) const
{
    return innerIsCheck(*board.simulateMove(srcRow, srcCol, destRow, destCol), board[srcRow][srcCol]->getColor());
}




std::string Game::lastCastleMove() const
{
    if (didWhiteCastleLastTurn)
		if(board.getWhiteKingPos().second == 6)
            return "a8a6";
    else
            return "a1a4";
    if (didBlackCastleLastTurn)
        if(board.getBlackKingPos().second == 6)
			return "h8h4";
	else
			return "h8h2";
    return "didnt Castle";
}

/**
 * @brief Check if a player is in check via certain board state
 * * @param color Color of the player
 * * @return true if the player is in check, false otherwise
 * 
 * it takes a board as an argument to assist in the simulation of moves
 */
bool Game::innerIsCheck(Board& tempBoard,char color) const
{
    auto kingPos = (color == WHITE) ? tempBoard.getWhiteKingPos() : tempBoard.getBlackKingPos();
    char opponentColor = (color == WHITE) ? BLACK : WHITE;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece* piece = tempBoard.getPiece(row, col);
            if (piece && (getCurrentPlayerColor() != piece->getColor()))
            {
                if (tempBoard.isValidMove(row, col, kingPos.first, kingPos.second))
                { 
                    if (King* king = dynamic_cast<King*>(board[kingPos.first][kingPos.second].get()))
                        king->wasChecked = true;
                    return true;
                
                }
                    
            }
        }
    }
    return false;
}




/**
 * @brief Check if a player is in check
 * * @param color Color of the player
 * * @return true if the player is in check, false otherwise
 */
bool Game::isCheck(char color) const
{
   return innerIsCheck(board, color);
}

/**
 * @brief Check if the game is over
 * * @return true if the game is over, false otherwise
 * king positions will be set to -1,-1 after a king is captured
 */
bool Game::isGameOver() const
{
    if (board.getBlackKingPos().first == -1)
        throw GameOverException("Game over!. White won!");
    if (board.getWhiteKingPos().first == -1)
        throw GameOverException("Game over!. Black won!");
    return false;
}

bool Game::isWhitePiece(char pieceSymbol) const
{
    return pieceSymbol >= 'A' && pieceSymbol <= 'Z';
}

char Game::getCurrentPlayerColor() const
{
    return isWhiteTurn() ? WHITE : BLACK;
}

char Game::getOpponentColor() const
{
    return isWhiteTurn() ? BLACK : WHITE;
}


/**
 * @brief Parse a move in chess notation
 * * @param move Move in chess notation
 * * @return Pair of source and destination positions
 */
std::pair<std::pair<int, int>, std::pair<int, int>> Game::parseMove(const std::string& move)
{
    if (move.size() != 4)
        throw std::invalid_argument("Invalid move format");

    auto parsePosition = [](const std::string& position) -> std::pair<int, int> {
        if (position.size() != 2)
            throw std::invalid_argument("Invalid position format");

        char file = position[0];
        char rank = position[1];

        if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
            throw std::invalid_argument("Invalid position format");

        int col = file - 'a';
        int row = rank - '1';

        return { row, col };
        };

    std::string src = move.substr(0, 2);
    std::string dest = move.substr(2, 2);

    auto srcPos = parsePosition(src);
    auto destPos = parsePosition(dest);

    return { srcPos, destPos };
}

