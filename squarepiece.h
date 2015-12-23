#ifndef SQUAREPIECE_H
#define SQUAREPIECE_H

#include "piece.h"

class SquarePiece : public piece
{
public:
	SquarePiece();
	virtual ~SquarePiece(){}
public:
	virtual void Rotate();
	virtual bool IsFit()const;
};

#endif // SQUAREPIECE_H
