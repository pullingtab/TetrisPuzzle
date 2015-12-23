#ifndef REVERSELPIECE_H
#define REVERSELPIECE_H

#include "piece.h"

class ReverseLPiece : public piece
{
public:
	ReverseLPiece();
	virtual ~ReverseLPiece(){}
public:
	virtual void Rotate();
	virtual int SpinCount()const;
	virtual bool IsFit()const;
	virtual int GetAttitude()const{return attitude;}
};

#endif // REVERSELPIECE_H
