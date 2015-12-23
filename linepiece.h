#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "piece.h"

class LinePiece : public piece
{
public:
	LinePiece();
	virtual ~LinePiece(){}
public:
	virtual void Rotate();
	virtual int SpinCount()const;
	virtual bool IsFit()const;
	virtual int GetAttitude()const{return attitude;}
};

#endif // LINEPIECE_H
