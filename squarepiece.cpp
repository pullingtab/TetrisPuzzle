#include "squarepiece.h"
#include "utility.h"

SquarePiece::SquarePiece()
	: piece()
{
	type = SQUARE;
	pointSet.resize(4, Point());
	// 14
	// 23
	pointSet[0].x = 0;
	pointSet[0].y = 0;
	pointSet[1].x = 1;
	pointSet[1].y = 0;
	pointSet[2].x = 1;
	pointSet[2].y = 1;
	pointSet[3].x = 0;
	pointSet[3].y = 1;
}

void SquarePiece::Rotate()
{
	return;
}

bool SquarePiece::IsFit() const
{
	if(puzzlePad)
	{
		int ptX = 0;
		int ptY = 0;

		// test point 1
		ptX = pointSet[0].x + x;
		ptY = pointSet[0].y + y;
		if(!isLegalPos(ptX, ptY))
			return false;
		if(!isEmptyPos(puzzlePad, ptX, ptY))
			return false;

		// test point 2
		ptX = pointSet[1].x + x;
		ptY = pointSet[1].y + y;
		if(!isLegalPos(ptX, ptY))
			return false;
		if(!isEmptyPos(puzzlePad, ptX, ptY))
			return false;

		// test point 3
		ptX = pointSet[2].x + x;
		ptY = pointSet[2].y + y;
		if(!isLegalPos(ptX, ptY))
			return false;
		if(!isEmptyPos(puzzlePad, ptX, ptY))
			return false;

		// test point 4
		ptX = pointSet[3].x + x;
		ptY = pointSet[3].y + y;
		if(!isLegalPos(ptX, ptY))
			return false;
		if(!isEmptyPos(puzzlePad, ptX, ptY))
			return false;

		// all pass
		return true;
	}

	return false;
}
