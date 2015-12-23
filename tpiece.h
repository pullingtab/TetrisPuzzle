#ifndef TPIECE_H
#define TPIECE_H

#include "piece.h"

class TPiece : public piece
{
public:
	TPiece();
	virtual ~TPiece(){}
public:
	virtual void Rotate();
	virtual int SpinCount()const;
	virtual bool IsFit()const;
	virtual int GetAttitude()const{return attitude;}
};

#endif // TPIECE_H
