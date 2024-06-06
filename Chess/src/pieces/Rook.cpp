#include "Piece.h"
#include "Rook.h"


Rook::Rook() :wasMoved(false), Piece(whiteRook,white)
{
	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
}

Rook::Rook(char color) :wasMoved(false)
{

	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
	symbol = color == white ? whiteRook : blackRook;
	this->color = color;
}
