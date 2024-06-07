#pragma once
/**
* @file ConstUtils.h
* this is simply to hold all the constants used in the project and a few utility functions that
* are used in multiple files so including them in a class would be redundant or cause circular dependencies
*/
static const char WHITE = 'w';
static const char BLACK = 'b';
static const char WHITE_KING = 'K';
static const char BLACK_KING = 'k';
static const char WHITE_ROOK = 'R';
static const char BLACK_ROOK = 'r';
static const char WHITE_BISHOP = 'B';
static const char BLACK_BISHOP = 'b';
static const char WHITE_KNIGHT = 'N';
static const char BLACK_KNIGHT = 'n';
static const char WHITE_QUEEN = 'Q';
static const char BLACK_QUEEN = 'q';
static const char WHITE_PAWN = 'P';
static const char BLACK_PAWN = 'p';
static const char EMPTY_SPACE = '#';


/**
* @brief Check if the given position is within the bounds of the board
* @param row The row
* @param col The column
* @return true if the position is within the bounds of the board, false otherwise
* 
*/
static bool isWithinBounds(int row, int col)
{
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}