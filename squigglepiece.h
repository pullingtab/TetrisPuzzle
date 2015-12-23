#ifndef SQUIGGLEPIECE_H
#define SQUIGGLEPIECE_H

#include <piece.h>

class squigglePiece : public piece
{
public:
	squigglePiece();
	virtual ~squigglePiece(){}
public:
	virtual void Rotate();
	virtual int SpinCount()const;
	virtual bool IsFit()const;
	virtual int GetAttitude()const{return attitude;}
};

#endif // SQUIGGLEPIECE_H
