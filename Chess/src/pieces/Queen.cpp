#include "Queen.h"

Queen::Queen() : Piece(whiteQueen,white) 
{
	movementStrategies.push_back(std::make_unique<DiagonalMovement>());
	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
}

Queen::Queen(char color)
{
	movementStrategies.push_back(std::make_unique<DiagonalMovement>());
	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
	symbol = color == white ? whiteQueen : blackQueen;
	this->color = color;
}

