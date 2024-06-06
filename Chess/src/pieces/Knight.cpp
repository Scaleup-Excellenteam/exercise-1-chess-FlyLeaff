#include "Knight.h"

Knight::Knight() : Piece(whiteKnight, white)
{
	movementStrategies.push_back(std::make_unique<KnightMovement>());
}

Knight::Knight(char color) : Piece(symbol, color)
{
	movementStrategies.push_back(std::make_unique<KnightMovement>());
	symbol = color == white ? whiteKnight : blackKnight;
	this->color = color;
}

