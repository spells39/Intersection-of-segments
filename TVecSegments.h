#include "TTree.h"
#include "vector"
#include "string"
#include "fstream"
#include "sstream"
#define _USE_MATH_DEFINES
#include <math.h>

#pragma once

using namespace std;

bool intersection(const Segment& a, const Segment& b);

class VecSeg
{
	std::vector<Segment> segs;
	std::vector<Point> points;
	int partition(int l, int r);
	Segment* randCreateSeg(int w);
	Segment* randSegByLength(double length);
public:
	VecSeg() {};
	//VecSeg(const VecSeg& s);
	int getLength() { return segs.size(); }
	int getPointLength() { return points.size(); }
	void pushback(Segment seg_);
	void pushbackP(Point p) { points.push_back(p); }
	void sortPoints(int l, int r);
	void read(const string& filePath);
	void write(const string& filePath, bool clearFile = false);
	void printS();
	void clear();
	bool intersecNaive();
	bool intersecEf();
	bool interBeforeK(const Segment& seg_, int k);
	bool interWithoutLast(const Segment& seg_, int k);
	void createRSByPoints(int n, int k = -1, int w = 1);
	void createRSByLength(double len, int n);
	//int orientation(Point p, Point q, Point r);
	//bool doIntersect(const Segment& a, const Segment& b);
	//bool onSeg(Point p, Point q, Point r);
	VecSeg& operator=(const VecSeg& vs);
	Segment front() { return segs.front(); }
	Segment back() { return segs.back(); }
	Segment operator[](int i)
	{
		if (i < 0 || i >= segs.size())
			throw - 1;
		return segs[i];
	}
	friend istream& operator>>(istream& is, VecSeg& vSeg);
	friend ostream& operator<<(ostream& os, VecSeg& vSeg);
};
