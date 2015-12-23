#ifndef UTILITY_H
#define UTILITY_H

#include "puzzlepad.h"
#include "piece.h"

bool isLegalPos(int x, int y);
bool isEmptyPos(const PuzzlePad& puzzle, unsigned x, unsigned y);
bool isEmptyPos(const PuzzlePad* puzzle, unsigned x, unsigned y);

piece* GetNewPiece(PIECE_TYPE type);

#endif // UTILITY_H
