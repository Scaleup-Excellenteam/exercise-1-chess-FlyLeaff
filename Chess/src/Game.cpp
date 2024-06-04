#include "Game.h"
#include <iostream>
Game::Game() : whiteTurn(true)
{
}

void Game::initialize(const std::string& boardString)
{
    board.initializeBoard(boardString);
}

void Game::switchTurn()
{
    whiteTurn = !whiteTurn;
}

bool Game::movePiece(int srcRow, int srcCol, int destRow, int destCol)
{
    if (board.movePiece(srcRow, srcCol, destRow, destCol))
    {
        if (board[srcRow][srcCol]->getSymbol() == 'K')
        {   // keep track of kings position for check checks
            whiteKingPos.first = destRow;
            whiteKingPos.second = destCol;
        }
        if (board[srcRow][srcCol]->getSymbol() == 'k')
        {
            blackKingPos.first = destRow;
            blackKingPos.second = destCol;			
		}
        switchTurn();
        return true;
    }
    return false;
}

bool Game::isLegalMove(int srcRow, int srcCol, int destRow, int destCol) const
{
    if (!Board::isWithinBounds(srcRow, srcCol) || !Board::isWithinBounds(destRow, destCol))
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

    //TODO add self check move check

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

bool Game::doesMoveCauseSelfCheck(int srcRow, int srcCol, int destRow, int destCol) const
{
    // Backup the current state of the board
    auto& nonConstBoard = const_cast<Board&>(board);
    std::unique_ptr<Piece> srcPiece = std::move(nonConstBoard[srcRow][srcCol]);
    std::unique_ptr<Piece> destPiece = std::move(nonConstBoard[destRow][destCol]);

    // Perform the move
    nonConstBoard.movePiece(destRow, destCol, destRow,destCol);

    // Check if the move causes check
    bool causesCheck = isCheck(whiteTurn ? Board::white : Board::black);

    // Revert the move
    nonConstBoard.setPiece(srcRow, srcCol, std::move(nonConstBoard[srcRow][srcCol]));
    nonConstBoard.setPiece(destRow,destCol, destPiece ? std::move(destPiece) : nullptr);

    return causesCheck;
}



bool Game::isCheck(char color) const
{
    auto kingPos = (color == Board::white) ? whiteKingPos : blackKingPos;
    char opponentColor = (color == Board::white) ? Board::black : Board::white;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece* piece = board.getPiece(row, col);
            if (piece && (isWhitePiece(piece->getSymbol()) == (opponentColor == Board::white)))
            {
                if (board.isValidMove(row,col,kingPos.first,kingPos.second))                  
                    return true;
            }
        }
    }
    return false;
}


bool Game::isGameOver() const
{
    // Add logic to determine if the game is over
    return false;
}

bool Game::isWhitePiece(char pieceSymbol) const
{
    return pieceSymbol >= 'A' && pieceSymbol <= 'Z';
}

char Game::getCurrentPlayerColor() const
{
    return isWhiteTurn() ? Board::white : Board::black;
}


// Static function to parse chess notation
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

