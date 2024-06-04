#include "King.h"

King::King() : Piece('K', 'w')
{
	movementStrategies.push_back(std::make_unique<KingMovement>());
}

King::King(char color)
{
	movementStrategies.push_back(std::make_unique<KingMovement>());
	symbol = color == 'w' ? 'K' : 'k';
	this->color = color;
}