#include "Queen.h"

Queen::Queen() : Piece(WHITE_QUEEN,WHITE) 
{
	movementStrategies.push_back(std::make_unique<DiagonalMovement>());
	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
}

Queen::Queen(char color)
{
	movementStrategies.push_back(std::make_unique<DiagonalMovement>());
	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
	symbol = color == WHITE ? WHITE_QUEEN : BLACK_QUEEN;
	this->color = color;
}

