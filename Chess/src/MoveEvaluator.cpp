#include "MoveEvaluator.h"

MoveEvaluator::MoveEvaluator(const Game& game, int depth) : game(game), depth(depth) {}

int MoveEvaluator::evalMove(Board& board, char player) {
    return evalThreatandPos(board, player);
}

int MoveEvaluator::evalThreatandPos(Board& board, char player) {
    int threatValue = 0;
    int posValue = 0;
    int boardCenterValue = 0;
    bool currentPlayerPiece;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (board.getPiece(row, col)) {
                currentPlayerPiece = board.getPiece(row, col)->getColor() == player;
                auto possibleMoves = game.getAllPossibleMovesFrom(row, col, &board);
                int srcPiece = evalPieceValues(board.getPiece(row, col)->getSymbol());
                if (currentPlayerPiece) {
                    posValue += possibleMoves.size();
                }
                else {
                    posValue -= possibleMoves.size();
                }
                for (auto move : possibleMoves) {
                    if (currentPlayerPiece) {
                        boardCenterValue += centerControl(move.first, move.second);
                    }
                    else {
                        boardCenterValue -= centerControl(move.first, move.second);
                    }
                    if (board.getPiece(move.first, move.second)) {
                        int destPiece = evalPieceValues(board.getPiece(move.first, move.second)->getSymbol());
                        if (destPiece > srcPiece) {
                            if (currentPlayerPiece) {
                                threatValue += destPiece;
                            }
                            else {
                                threatValue -= destPiece;
                            }
                        }
                    }
                }
            }
        }
    }
    return threatValue + posValue + boardCenterValue;
}

int MoveEvaluator::evalPieceValues(char piece) {
    switch (toupper(piece)) {
    case 'P': return 1;
    case 'N': return 3;
    case 'B': return 3;
    case 'R': return 5;
    case 'Q': return 9;
    case 'K': return 1000;
    default: return 0;
    }
}

int MoveEvaluator::centerControl(int destRow, int destCol) {
    return (destRow >= 3 && destRow <= 4 && destCol >= 3 && destCol <= 4) ? 1 : 0;
}
