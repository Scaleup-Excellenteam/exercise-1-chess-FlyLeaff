#include "Piece.h"
#include "Rook.h"


Rook::Rook() :wasMoved(false), Piece(WHITE_ROOK,WHITE)
{
	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
}

Rook::Rook(char color) :wasMoved(false)
{

	movementStrategies.push_back(std::make_unique<HorizontalVerticalMovement>());
	symbol = color == WHITE ? WHITE_ROOK : BLACK_ROOK;
	this->color = color;
}
