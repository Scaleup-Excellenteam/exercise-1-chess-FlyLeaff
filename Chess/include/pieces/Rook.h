#include "Piece.h"



class Rook : public Piece
{
public:
	Rook();
	Rook(char color);

	bool wasMoved;	// no reason to make this private, fight me in the comments for that :D
	
private:

};