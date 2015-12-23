#include <QCoreApplication>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ctime>

#include "puzzlepad.h"
#include "piece.h"
#include "utility.h"

using namespace std;

void ShowHint();// show hint
SolutionSet SolvePuzzle(vector<piece*> pieces, PuzzlePad& pad, unsigned startX=0, unsigned startY=0);
void ShowResult(const SolutionSet& solutions);// show result

// first-solution-flag
// set false after the first solution is get and shown.
static bool isFirstSolution = true;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// show hint
	ShowHint();

	// get total row, column
	int row = 0;
	int column = 0;
	cin >> row >> column;

	// get piece set
	map<PIECE_TYPE,int> pieceSet;
	int type = 0;
	int count = 0;
	while(true)
	{
		cin >> type;
		if(type==-1)
			break;
		cin >> count;
		if(type&&count>-1)
		{
			if(pieceSet.find(PIECE_TYPE(type)) != pieceSet.end())
				pieceSet[PIECE_TYPE(type)] += count;
			else
				pieceSet.insert(make_pair(PIECE_TYPE(type),count));
		}
	}

	// init puzzle pad
	PuzzlePad puzzlePad;
	MakeEmptyPuzzle(puzzlePad, row, column);

	// init piece objects
	vector<piece*> pieces;
	for(auto& i: pieceSet)
		for(int j = 0; j < i.second; ++j)
		{
			piece* pPiece = GetNewPiece(i.first);
			pPiece->SetPuzzlePad(&puzzlePad);

			pieces.push_back(pPiece);
		}

	// mark 1th timestamp
	clock_t tt1 = clock();

	// try to solve the puzzle
	SolutionSet solutions = SolvePuzzle(pieces, puzzlePad);

	// mark 2th timestamp
	clock_t tt2 = clock();

	// output the result
	ShowResult(solutions);

	// release alloced memory
	for(auto i: pieces)
		delete i;

	// calculate total searching-time.
	double dMs = double(tt2-tt1)/double(1000.0);
	cout << "total time: " << dMs << "s\n";

	// exit
	return a.exec();
}

// show hint
void ShowHint()
{
	cout << "Tetris Puzzle 1.2" << endl;
	cout << endl;
	cout << "This program is used to solve tetris puzzle." << endl;
	cout << "Usage:" << endl;
	cout << "1. Input the size of puzzle's pad as follows:" << endl;
	cout << "   [total row] [total column]" << endl;
	cout << "2. Input the pieces of the puzzle as follows:" << endl;
	cout << "   [piece type] [piece count]" << endl;
	cout << "   end with \"-1\"." << endl;
	cout << "3. The type number of each kind of piece are as follows:" << endl;
	cout << "   1. **     2.  **"<< endl;
	cout << "       **       **"  << endl;
	cout << " " << endl;
	cout << "   3. ***    4. *" << endl;
	cout << "      *         ***"<< endl;
	cout << " " << endl;
	cout << "   5. **     6. ****" << endl;
	cout << "      **" << endl;
	cout << " " << endl;
	cout << "   7. ***" << endl;
	cout << "       *" << endl;
}

// solve the puzzle
// parameters:
//     pieces: remaining pieces
//     pad:    puzzle pad
//     startX: x-offset of search's start point
//     startY: y-offset of search's start point
SolutionSet SolvePuzzle(vector<piece*> pieces, PuzzlePad& pad, unsigned startX, unsigned startY)
{
	SolutionSet solutions;
	solutions.begin();
	auto block = pieces.back();
	pieces.pop_back();
	unsigned attitude = block->SpinCount();
	block->SetPuzzlePad(&pad);

	// check every cell on the pad to see if current
	// tetris piece can be placed on puzzle pad by
	// any attitude
	for(unsigned i = 0; i < pad.size(); ++i) // every row
	{
		// if start point is specified,
		// start at specified start point
		if(i<startX)
			continue;
		for(unsigned j = 0; j < pad[i].size(); ++j) // every column
		{
			// if start point is specified,
			// start at specified start point
			if(i==startX && j<startY)
				continue;
			for(unsigned k = 0; k < attitude; ++k) // every attitude
			{
				block->MoveTo(i,j);
				bool isFit = block->IsFit();

				// keep searching...
				if(isFit && !pieces.empty())
				{
					// put the piece on puzzle pad
					block->Place(i,j);

					// continue if blank part(s) of puzzle pad is not solvable
					if(IsSolvable(pad))
					{
						// avoid duplicated search
						int startAtX = 0;
						int startAtY = 0;
						if(pieces.back()->GetType()==block->GetType())
						{
							startAtX = i;
							startAtY = j+1;
						}
						// find the solution recursively
						auto newSolutions = SolvePuzzle(pieces, pad, startAtX, startAtY);

						// merge the two SolutionSet
						solutions.splice(solutions.begin(), newSolutions);
					}

					// displace the piece because next loop still need current pad to be dischanged.
					block->Displace();
				}
				// solution found!
				else if(isFit && pieces.empty())
				{
					// createe new pad to store current solution
					PuzzlePad newPad = Clone(pad);
					block->SetPuzzlePad(&newPad);
					block->Place(i,j);

					// print first solution
					if(isFirstSolution)
					{
						Print(newPad);
						isFirstSolution = false;
					}

					solutions.push_front( std::move(newPad) );
				}

				// rotate for next loop
				block->Rotate();
			}
		}
	}

	return std::move(solutions);
}

void ShowResult(const SolutionSet& solutions)
{
	if(solutions.size()==0)
	{
		cout << "Failed solving the puzzle!" << endl;
	}
	else
	{
		map<string,Solution> solutionMap;
		stringstream sStream;
		for(auto& i: solutions)
		{
			string s;
			for(auto& j: i)
				for(auto& k: j)
				{
					string tmp;
					sStream << k;
					sStream >> tmp;
					sStream.clear();
					s += tmp;
				}
			solutionMap.insert(make_pair(s,i));
		}
		cout << "total solutions are " << solutionMap.size() << ".\n";
		unsigned i = 0;
		for(auto& pair: solutionMap)
		{
			cout << "the " << i+1 << "th solution is:\n";
			Print(pair.second);
			++i;
		}
		cout << "end.\n";
	}
}
