#ifndef LPIECE_H
#define LPIECE_H

#include "piece.h"

class LPiece : public piece
{
public:
	LPiece();
	virtual ~LPiece(){}
public:
	virtual void Rotate();
	virtual int SpinCount()const;
	virtual bool IsFit()const;
	virtual int GetAttitude()const{return attitude;}
};

#endif // LPIECE_H
