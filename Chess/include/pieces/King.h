#pragma once
#include "Piece.h"

class King : public Piece
{
private:

public:
	King();
	King(char color);
	bool wasChecked;
	bool wasMoved;




};