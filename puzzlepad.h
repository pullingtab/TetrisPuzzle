#ifndef PUZZLEPAD_H
#define PUZZLEPAD_H

#include <vector>
#include <list>

using std::vector;
using std::list;

typedef vector<vector<int>> PuzzlePad;
typedef PuzzlePad Solution;
typedef list<Solution> SolutionSet;

void MakeEmptyPuzzle(PuzzlePad& pad, int row, int column);
PuzzlePad Clone(const PuzzlePad& pad);
void Print(const PuzzlePad& pad);
bool IsSolvable(PuzzlePad& pad);

#endif // PUZZLEPAD_H
