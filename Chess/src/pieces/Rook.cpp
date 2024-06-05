#include "Piece.h"
#include "Rook.h"


Rook::Rook() : Piece(whiteRook,white)
{
	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
}

Rook::Rook(char color)
{

	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
	symbol = color == white ? whiteRook : blackRook;
	this->color = color;
}
