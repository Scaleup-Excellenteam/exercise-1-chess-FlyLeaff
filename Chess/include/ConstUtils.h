#pragma once
static const char white = 'w';
static const char black = 'b';
static const char whiteKing = 'K';
static const char blackKing = 'k';
static const char whiteRook = 'R';
static const char blackRook = 'r';
static const char whiteBishop = 'B';
static const char blackBishop = 'b';
static const char whiteKnight = 'N';
static const char blackKnight = 'n';
static const char whiteQueen = 'Q';
static const char blackQueen = 'q';
static const char whitePawn = 'P';
static const char blackPawn = 'p';
static const char empty = '#';


static bool isWithinBounds(int row, int col)
{
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}