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
        switchTurn();
        return true;
    }
    return false;
}

bool Game::isGameOver() const
{
    // Add logic to determine if the game is over
    return false;
}

bool Game::isLegalMove(int srcRow, int srcCol, int destRow, int destCol)
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
    

    if (!srcPiece->isValidMove(srcRow, srcCol, destRow, destCol))
        throw IllegalMoveException();



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

bool Game::isWhitePiece(char pieceSymbol)
{
    return pieceSymbol >= 'A' && pieceSymbol <= 'Z';
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

