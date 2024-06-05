#include "Bishop.h"

Bishop::Bishop() : Piece(whiteBishop, white)
{
	movementStrategies.push_back(std::make_unique<DiagonalMovement>());
	
}
Bishop::Bishop(char color) : Piece(symbol, color)
{
	movementStrategies.push_back(std::make_unique<DiagonalMovement>());
	symbol = color == white ? whiteBishop : black;
	this->color = color;
}
