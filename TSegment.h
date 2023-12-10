#include <iostream>
#include "TPoint.h"
#pragma once
#define ERROR_RATE 100000000
using namespace std;

int r(int left = -1000, int right = 1000);

class Segment
{
	Point begin;
	Point end;
	double k, b;
public:
	Segment();
	Segment(Point p1, Point p2);
	Segment(const Segment& seg);
	void calcCoef();
	Point getBegin() const { return begin; }
	Point getEnd() const { return end; }
	double calcY(double time);
	friend ostream& operator<<(ostream& os, Segment& seg);
	friend istream& operator>>(istream& is, Segment& seg);
	void setSegIndex(int index);
	friend bool operator==(Segment s1, Segment s2);
	friend bool operator!=(Segment s1, Segment s2);
};
