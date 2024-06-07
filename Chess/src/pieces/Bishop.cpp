#include "Bishop.h"

Bishop::Bishop() : Piece(WHITE_BISHOP, WHITE)
{
	movementStrategies.push_back(std::make_unique<DiagonalMovement>());
	
}
Bishop::Bishop(char color) : Piece(symbol, color)
{
	movementStrategies.push_back(std::make_unique<DiagonalMovement>());
	symbol = color == WHITE ? WHITE_BISHOP : BLACK;
	this->color = color;
}
