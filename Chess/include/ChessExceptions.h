#ifndef CHESS_EXCEPTIONS_H
#define CHESS_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class ChessException : public std::runtime_error {
    // this class is a base class for all chess exceptions, it simply holds an error code as well as the error msg
    // the error msgs are the same as in the assignment file 
private:
    int errorCode;
public:
    ChessException(int code, const std::string& message)
        : std::runtime_error(message), errorCode(code) {}
    int getErrorCode() const { return errorCode; }
};

class NoPieceAtSourceException : public ChessException {
public:
    NoPieceAtSourceException() : ChessException(11, "No piece at source") {}
};

class OpponentPieceAtSourceException : public ChessException {
public:
    OpponentPieceAtSourceException() : ChessException(12, "Piece at source belongs to opponent") {}
};

class OwnPieceAtDestinationException : public ChessException {
public:
    OwnPieceAtDestinationException() : ChessException(13, "Destination occupied by own piece") {}
};

class IllegalMoveException : public ChessException {
public:
    IllegalMoveException() : ChessException(21, "Move is not legal for this piece") {}
};

class MoveCausesSelfCheckException : public ChessException {
public:
    MoveCausesSelfCheckException() : ChessException(31, "Move causes check to the player making the move") {}
};

class OutOfBoundsException : public ChessException 
{
public:
    OutOfBoundsException() : ChessException(14, "Destination is out of bounds") {}
};


class MoveChecksOpponentException : public ChessException {
public:
    MoveChecksOpponentException() : ChessException(41, "Move causes check to the opponent") {}
};

class LegalMoveException : public ChessException {
public:
    LegalMoveException() : ChessException(42, "Move is legal") {}
};

#endif // CHESS_EXCEPTIONS_H
