#include "piece.h"

piece::piece(int x, int y, int atti, vector< vector<int> >* puzzle):
	x(x),
	y(y),
	attitude(atti),
	puzzlePad(puzzle)
{
}

piece::~piece()
{
	;
}

void piece::SetPuzzlePad(vector<vector<int> > *puzzle)
{
	puzzlePad = puzzle;
}

void piece::MoveTo(int x, int y)
{
	this->x = x;
	this->y = y;
}

void piece::Place(int x, int y)
{
	MoveTo(x, y);
	if(puzzlePad)
	{
		for(const auto& point: pointSet)
			(*puzzlePad)[this->x+point.x][this->y+point.y] = type;
	}
}

void piece::Displace()
{
	if(puzzlePad)
	{
		for(const auto& point: pointSet)
			(*puzzlePad)[this->x+point.x][this->y+point.y] = EMPTY;
	}
}

int piece::SpinCount() const
{
	return 1;// not spinnable
}
