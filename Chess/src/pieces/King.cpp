#include "King.h"

King::King() :wasChecked(false), wasMoved(false), Piece(whiteKing, white)
{
	movementStrategies.push_back(std::make_unique<KingMovement>());
}

King::King(char color) :wasChecked(false), wasMoved(false)
{
	movementStrategies.push_back(std::make_unique<KingMovement>());
	symbol = color == white ? whiteKing : blackKing;
	this->color = color;
}

