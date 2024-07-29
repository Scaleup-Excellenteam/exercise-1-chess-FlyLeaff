#include "Knight.h"

Knight::Knight() : Piece(WHITE_KNIGHT, WHITE)
{
	movementStrategies.push_back(std::make_unique<KnightMovement>());
}

Knight::Knight(char color) : Piece(symbol, color)
{
	movementStrategies.push_back(std::make_unique<KnightMovement>());
	symbol = color == WHITE ? WHITE_KNIGHT : BLACK_KNIGHT;
	this->color = color;
}

