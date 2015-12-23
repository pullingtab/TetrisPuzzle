#include "tpiece.h"
#include "utility.h"

TPiece::TPiece()
	: piece()
{
	type = T;
	// the attitude of current piece
	// 0: ***
	//     *
	// 1:  *
	//    **
	//     *
	// 2:  *
	//    ***
	// 3: *
	//    **
	//    *
	attitude = 0;
	pointSet.resize(4, Point());
	// 123
	//  4
	pointSet[0].x = 0;
	pointSet[0].y = 0;
	pointSet[1].x = 0;
	pointSet[1].y = 1;
	pointSet[2].x = 0;
	pointSet[2].y = 2;
	pointSet[3].x = 1;
	pointSet[3].y = 1;
}

void TPiece::Rotate()
{
	switch(attitude)
	{
		// 0->1
		case 0:
		{
			//  1
			// 42
			//  3
			attitude = 1;
			pointSet[0].x = 0;
			pointSet[0].y = 0;
			pointSet[1].x = 1;
			pointSet[1].y = 0;
			pointSet[2].x = 2;
			pointSet[2].y = 0;
			pointSet[3].x = 1;
			pointSet[3].y = -1;

		}
		break;
		// 1->2
		case 1:
		{
			//  4
			// 321
			attitude = 2;
			pointSet[0].x = 0;
			pointSet[0].y = 0;
			pointSet[1].x = 0;
			pointSet[1].y = -1;
			pointSet[2].x = 0;
			pointSet[2].y = -2;
			pointSet[3].x = -1;
			pointSet[3].y = -1;
		}
		break;
		// 2->3
		case 2:
		{
			// 3
			// 24
			// 1
			attitude = 3;
			pointSet[0].x = 0;
			pointSet[0].y = 0;
			pointSet[1].x = -1;
			pointSet[1].y = 0;
			pointSet[2].x = -2;
			pointSet[2].y = 0;
			pointSet[3].x = -1;
			pointSet[3].y = 1;
		}
		break;
		// 3->0
		case 3:
		{
			// 123
			//  4
			attitude = 0;
			pointSet[0].x = 0;
			pointSet[0].y = 0;
			pointSet[1].x = 0;
			pointSet[1].y = 1;
			pointSet[2].x = 0;
			pointSet[2].y = 2;
			pointSet[3].x = 1;
			pointSet[3].y = 1;
		}
		break;
		default:
			break;
	}
}

int TPiece::SpinCount() const
{
	return 4;
}

bool TPiece::IsFit() const
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
