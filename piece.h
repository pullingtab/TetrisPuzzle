#ifndef PIECE_H
#define PIECE_H

#include <vector>

using std::vector;

enum PIECE_TYPE
{
	EMPTY,			// empty place that no block is on
	SQUIGGLE,		// squigglly piece
	R_SQUIGGLE,		// reverse squigglly piece
	L,				// L block
	R_L,			// reverse L block
	SQUARE,			// square block
	LINE,			// line piece
	T,				// T block

	PL				// placeholder
};

class Point
{
public:
	int x;
	int y;
	Point():x(0),y(0){}
	Point(int a, int b):x(a), y(b){}
	bool operator < (const Point& p)const
	{
		if(x != p.x)
			return x < p.x;
		if(y != p.y)
			return y < p.y;

		return false;
	}
	bool operator == (const Point& p)const
	{
		return x == p.x && y == p.y;
	}
	bool operator != (const Point& p)const
	{
		return x != p.x || y != p.y;
	}
	const Point operator + (const Point& p)const
	{
		Point t;
		t.x = p.x + x;
		t.y = p.y + y;

		return std::move(t);
	}
};
typedef Point Position;

class piece
{
protected:
	PIECE_TYPE type;
	int x;
	int y;
	int attitude;
	vector< vector<int> >* puzzlePad;
	vector<Point> pointSet;
public:
	explicit piece(int x = 0, int y = 0, int attitude = 0, vector< vector<int> >* puzzle = nullptr);
	virtual ~piece();
public:
	virtual PIECE_TYPE GetType()const{return type;}
	virtual int GetX()const{return x;}
	virtual int GetY()const{return y;}
	virtual unsigned GetPointCount()const{return pointSet.size();}
	virtual const Point GetPointAt(unsigned index)const{return pointSet[index];}
	virtual const Position GetPosition()const{return Position(x,y);}
	virtual void SetPuzzlePad(vector< vector<int> >*);
	virtual void MoveTo(int x, int y); // move current tetris piece to specified place
	virtual void Place(int x, int y); // put current tetris piece on puzzle pad
	virtual void Displace(); // remove current tetris piece from puzzle pad
	virtual void Rotate()=0; // rotate current tetris piece
	virtual int SpinCount()const; // return the total number of attitude that current tetris piece have
	virtual bool IsFit()const =0; // is current position is fit for current tetris piece?
	virtual int GetAttitude()const{return 0;} // return the attitude of current tetris piece
};

#endif // PIECE_H
