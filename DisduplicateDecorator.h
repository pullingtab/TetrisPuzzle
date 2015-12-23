#ifndef BADPOSITIONNOTE_H
#define BADPOSITIONNOTE_H

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>

#include "piece.h"

using std::string;
class Token;

namespace std{
	template<>
	struct hash<Token>
	{
		size_t operator () (const Token& t) const;
	};
}

class Token
{
	std::vector<Point> pointSet;
public:
	Token();
	explicit Token(const std::vector<Point>& vP);
	explicit Token(Token &&t);
	Token(const Token& t);
public:
	void SetPointSet(const std::vector<Point>& vP);
	void Clear();
	bool operator < (const Token& )const;
	bool operator == (const Token& )const;
	void operator = (const Token&);
	friend size_t std::hash<Token>::operator()(const Token&)const;
};
//size_t hash_value(const Token&);

// this class overwrites interface IsFit()
// to return false when searched position
// get searched again
class DisduplicateDecorator : public piece
{
	piece* pPiece;
	std::unordered_set<string> checkedPositionSet;
	std::unordered_set<Token> checkedPositionSet_t;
public:
	DisduplicateDecorator(piece* p);
	virtual ~DisduplicateDecorator();
public:
	// decorated interface
	virtual bool IsFit()const;

	// clear
	void clearHistory();
	// mark current token as searched
	void Mark();

	// repeater
	virtual PIECE_TYPE GetType()const{return pPiece->GetType();}
	virtual int GetX()const{return pPiece->GetX();}
	virtual int GetY()const{return pPiece->GetY();}
	virtual unsigned GetPointCount()const{return pPiece->GetPointCount();}
	virtual const Point GetPointAt(unsigned index)const{return pPiece->GetPointAt(index);}
	virtual const Position GetPosition()const{return pPiece->GetPosition();}
	virtual void SetPuzzlePad(vector< vector<int> >* p){pPiece->SetPuzzlePad(p);}
	virtual void MoveTo(int x, int y){pPiece->MoveTo(x,y);}
	virtual void Place(int x, int y){pPiece->Place(x,y);}
	virtual void Displace(){pPiece->Displace();}
	virtual void Rotate(){return pPiece->Rotate();}
	virtual int SpinCount()const{return pPiece->SpinCount();}
	virtual int GetAttitude()const{return pPiece->GetAttitude();}


private:
	string GetToken()const;
	Token GetToken_T()const;
	//static string GetPositionKey(const position& p);
};

#endif // BADPOSITIONNOTE_H
