#include "Pawn.h"
Pawn::Pawn() : Piece(whitePawn, white)
{
	movementStrategies.push_back(std::make_unique<PawnMovement>(true));
}

Pawn::Pawn(char color) : Piece(symbol, color)
{
	movementStrategies.push_back(std::make_unique<PawnMovement>(color == white));
	symbol = color == white ? whitePawn : blackPawn;
	this->color = color;
}