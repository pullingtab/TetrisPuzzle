#ifndef REVERSESQUIGGLEPIECE_H
#define REVERSESQUIGGLEPIECE_H

#include "piece.h"

class reverseSquigglePiece : public piece
{
public:
	reverseSquigglePiece();
	virtual ~reverseSquigglePiece(){}
public:
	virtual void Rotate();
	virtual int SpinCount()const;
	virtual bool IsFit()const;
	virtual int GetAttitude()const{return attitude;}
};

#endif // REVERSESQUIGGLEPIECE_H
