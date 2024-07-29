#include "Pawn.h"
Pawn::Pawn() : Piece(WHITE_PAWN, WHITE)
{
	movementStrategies.push_back(std::make_unique<PawnMovement>(true));
}

Pawn::Pawn(char color) : Piece(symbol, color)
{
	movementStrategies.push_back(std::make_unique<PawnMovement>(color == WHITE));
	symbol = color == WHITE ? WHITE_PAWN : BLACK_PAWN;
	this->color = color;
}