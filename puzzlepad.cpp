#include "puzzlepad.h"
#include "piece.h"

#include <iostream>
#include <vector>

using std::cout;

void MakeEmptyPuzzle(PuzzlePad& pad, int row, int column)
{
	pad.clear();

	pad.resize(row);
	for(auto& i: pad)
	{
		i.resize(column);
	}

	for(auto& i: pad)
		for(auto& j: i)
			j = 0;
}


void Print(const PuzzlePad &pad)
{
	for(auto& row: pad)
	{
		for(auto& cell: row)
			cout << cell;
		cout << '\n';
	}
}


PuzzlePad Clone(const PuzzlePad &pad)
{
	PuzzlePad newPad;
	newPad.resize(pad.size());

	std::copy(pad.begin(), pad.end(), newPad.begin());

	return std::move(newPad);
}

unsigned int CalculateBlockSize(int x, int y, PuzzlePad& pad)
{
	if(pad[x][y]!=EMPTY)
		return 0;

	pad[x][y] = PL;
	unsigned int blockSize = 1;

	if(y+1 < pad[x].size())
		blockSize += CalculateBlockSize(x,y+1,pad);
	if(y-1 >= 0)
		blockSize += CalculateBlockSize(x,y-1,pad);
	if(x+1 < pad.size())
		blockSize += CalculateBlockSize(x+1,y,pad);
	if(x-1 >= 0)
		blockSize += CalculateBlockSize(x-1,y,pad);

	return blockSize;
}

bool IsSolvable(PuzzlePad &pad)
{
	bool rtv = true;

	// count the size of divided empty blocks
	for(int i=0; i < pad.size(); ++i)
		for(int j=0; j < pad[i].size(); ++j)
		{
			// find a divided empty block
			if(pad[i][j]==EMPTY)
			{
				unsigned blockSize = CalculateBlockSize(i,j,pad);

				// if it is unsolvable, return false
				if(blockSize%4 != 0)
					rtv = false;
			}
		}

	// restore puzzle pad
	for(int i=0; i < pad.size(); ++i)
		for(int j=0; j < pad[i].size(); ++j)
			if(pad[i][j]==PL)
				pad[i][j] = EMPTY;

	return rtv;
}
