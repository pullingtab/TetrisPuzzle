#include "DisduplicateDecorator.h"
#include "boost/functional/hash.hpp"

#include <sstream>
#include <iostream>
#include <set>
#include <algorithm>

using std::stringstream;
using std::unordered_set;
using std::set;
using std::string;
using std::vector;

DisduplicateDecorator::DisduplicateDecorator(piece *p)
	: piece()
	, pPiece(p)
	, checkedPositionSet()
{
	;
}

DisduplicateDecorator::~DisduplicateDecorator()
{
	delete pPiece;
}

bool DisduplicateDecorator::IsFit() const
{
	//return pPiece->IsFit();
	bool isFit = pPiece->IsFit();

	if(!isFit)
		return false;
	else
	{
		// get token
		//string token = GetToken();
		Token token_t = GetToken_T();

		// is token already exist
		bool isCheckedPosition = false;
		if(checkedPositionSet_t.find(token_t)!=checkedPositionSet_t.end())
		//if(checkedPositionSet.find(token)!=checkedPositionSet.end())
		{
			isCheckedPosition = true;
		}

		return !isCheckedPosition;
	}
}

void DisduplicateDecorator::clearHistory()
{
	//checkedPositionSet.clear();
	checkedPositionSet_t.clear();
}

void DisduplicateDecorator::Mark()
{
	// get token
	//string token = GetToken();
	//checkedPositionSet.insert(std::move(token));

	Token token_t = GetToken_T();
	checkedPositionSet_t.insert(token_t);
}

//void DisduplicateDecorator::NotedAsBadPosition()
//{
//	GetToken();
//	position p;
//	p.type = typeid(*pPiece).hash_code();
//	p.x = pPiece->GetX();
//	p.y = pPiece->GetY();
//	p.attitude = pPiece->GetAttitude();

//	badPositionSet.insert(std::make_pair(key,p));
//}

//void DisduplicateDecorator::ClearTheNote()
//{
//	badPositionSet.clear();
//}

string DisduplicateDecorator::GetToken() const
{
	// sort the points
	set<Point> sort;
	unsigned pc = pPiece->GetPointCount();
	for(unsigned i = 0; i < pc; ++i)
		sort.insert(pPiece->GetPointAt(i) + pPiece->GetPosition());

	// calculate token
	string token;// [x0][y0][x1][y1]...[xn][yn]
	token.reserve(pc*5*2);
	for(const auto& p: sort)
	{
		const unsigned size = 100;
		char buf[size];

		// [x]
		sprintf_s(buf,size,"[%d]",p.x);
		token += buf;

		// [y]
		sprintf_s(buf,size,"[%d]",p.y);
		token += buf;
	}

	return std::move(token);
}

Token DisduplicateDecorator::GetToken_T()const
{
	unsigned pc = pPiece->GetPointCount();
	vector<Point> points;
	points.reserve(pc);
	for(unsigned i = 0; i < pc; ++i)
		points.push_back(pPiece->GetPointAt(i) + pPiece->GetPosition());

	return std::move(Token(points));
}

//std::string DisduplicateDecorator::GetPositionKey(const position& p)
//{
//	string key;// format of the key: [type][x][y][attitude]

//	string tmp;
//	stringstream i2str;

//	// [type]
//	i2str << int(p.type);
//	i2str >> tmp;
//	key += "[" + tmp + "]";

//	// [x]
//	i2str << p.x;
//	i2str >> tmp;
//	key += "[" + tmp + "]";

//	// [y]
//	i2str << p.y;
//	i2str >> tmp;
//	key += "[" + tmp + "]";

//	// [attitude]
//	i2str << p.attitude;
//	i2str >> tmp;
//	key += "[" + tmp + "]";

//	return std::move(key);
//}


Token::Token()
	: pointSet()
{
	;
}

Token::Token(const std::vector<Point> &vP)
	: pointSet()
{
	SetPointSet(vP);
}

Token::Token(Token &&t)
	: pointSet(std::move(t.pointSet))
{
	;
}

Token::Token(const Token &t)
	: pointSet(t.pointSet)
{
	;
}

void Token::SetPointSet(const std::vector<Point> &vP)
{
	// in case there still exists values
	Clear();

	// save points
	pointSet.reserve(vP.size());
	for(const auto& p: vP)
		pointSet.push_back(p);

	// sort points
	std::sort(pointSet.begin(),pointSet.end());
}

void Token::Clear()
{
	pointSet.clear();
}

bool Token::operator <(const Token &t) const
{
	size_t minSize = std::min(pointSet.size(), t.pointSet.size());

	for(unsigned i = 0; i < minSize; ++i)
		if(pointSet[i] != t.pointSet[i])
			return pointSet[i] < t.pointSet[i];

	return pointSet.size() < t.pointSet.size();
}

bool Token::operator ==(const Token &t) const
{
	if(pointSet.size()!=t.pointSet.size())
		return false;

	size_t size = pointSet.size();
	for(unsigned i = 0; i < size; ++i)
		if(pointSet[i] != pointSet[i])
			return false;
	return true;
}

void Token::operator =(const Token &t)
{
	pointSet = t.pointSet;
}

std::size_t std::hash<Token>::operator ()(const Token &t) const
{
	size_t seed = 0;
	for(const auto& p: t.pointSet)
	{
		boost::hash_combine(seed, boost::hash_value(p.x));
		boost::hash_combine(seed, boost::hash_value(p.y));
	}

	return seed;
}
