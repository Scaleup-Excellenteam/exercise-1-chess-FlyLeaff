#include "King.h"

King::King() :wasChecked(false), wasMoved(false), Piece(WHITE_KING, WHITE)
{
	movementStrategies.push_back(std::make_unique<KingMovement>());
}

King::King(char color) :wasChecked(false), wasMoved(false)
{
	movementStrategies.push_back(std::make_unique<KingMovement>());
	symbol = color == WHITE ? WHITE_KING : BLACK_KING;
	this->color = color;
}

