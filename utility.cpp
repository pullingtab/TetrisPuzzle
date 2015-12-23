#include "utility.h"
#include "piece.h"

#include "squigglepiece.h"
#include "reverselpiece.h"
#include "reversesquigglepiece.h"
#include "lpiece.h"
#include "squarepiece.h"
#include "linepiece.h"
#include "tpiece.h"

bool isLegalPos(int x, int y)
{
	return x>=0 && y>=0;
}


bool isEmptyPos(const PuzzlePad& puzzle, unsigned x, unsigned y)
{
	return isEmptyPos(&puzzle, x, y);
}


bool isEmptyPos(const PuzzlePad *puzzle, unsigned x, unsigned y)
{
	if(!isLegalPos(x,y))
		return false;
	if(puzzle)
	{
		if(puzzle->size() <= 0)
			return false;
		if(x >= puzzle->size())
			return false;
		if(y >= (*puzzle)[x].size())
			return false;

		return (*puzzle)[x][y]==EMPTY;
	}
	return false;
}

piece* GetNewPiece(PIECE_TYPE type)
{
	switch(type)
	{
		case SQUIGGLE:
			return new squigglePiece;
			break;
		case R_SQUIGGLE:
			return new reverseSquigglePiece;
			break;
		case L:
			return new LPiece;
			break;
		case R_L:
			return new ReverseLPiece;
			break;
		case SQUARE:
			return new SquarePiece;
			break;
		case LINE:
			return new LinePiece;
			break;
		case T:
			return new TPiece;
			break;
		default:
			return nullptr;
	}
}
