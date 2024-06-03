#include "Piece.h"
#include "Rook.h"


Rook::Rook() : Piece('R','w')
{
	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
}

Rook::Rook(char color)
{

	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
	symbol = color == 'w' ? 'R' : 'r';
	this->color = color;
}
