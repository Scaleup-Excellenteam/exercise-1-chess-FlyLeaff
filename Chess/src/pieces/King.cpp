#include "King.h"

King::King() : Piece(whiteKing, white)
{
	movementStrategies.push_back(std::make_unique<KingMovement>());
}

King::King(char color)
{
	movementStrategies.push_back(std::make_unique<KingMovement>());
	symbol = color == white ? whiteKing : blackKing;
	this->color = color;
}