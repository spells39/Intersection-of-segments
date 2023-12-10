#include "TSegment.h"

int r(int left, int right)
{
	return rand() % (right - left + 1) + left;
}

Segment::Segment()
{
	//begin = Point(r(500, 600), r(500, 600));
	//end = Point(r(500, 600), r(500, 600));
	k = 0;
	b = 0;
}

Segment::Segment(Point p1, Point p2)
{
	if (p1.x == p2.x)
	{
		begin = p1;
		end = p2;
		return;
	}
	if (p1.x < p2.x)
	{
		begin = p1;
		end = p2;
	}
	else
	{
		begin = p2;
		end = p1;
	}
	begin.isLeft = true;
	calcCoef();
}

Segment::Segment(const Segment& seg)
{
	begin = seg.begin;
	end = seg.end;
	k = seg.k;
	b = seg.b;
}

void Segment::calcCoef()
{
	double a1 = end.y - begin.y;
	double a2 = end.x - begin.x;
	k = a1 / a2;
	b = (begin.y * end.x - begin.x * end.y) / a2;
}

double Segment::calcY(double time)
{
	calcCoef();
	return k * time + b;
}

ostream& operator<<(ostream& os, Segment& seg)
{
	os << seg.getBegin() << " " << seg.getEnd();
	return os;
}

istream& operator>>(istream& is, Segment& seg)
{
	cout << "Begin" << endl;
	is >> seg.begin;
	seg.begin.isLeft = true;
	cout << "End" << endl;
	is >> seg.end;
	return is;
}

bool operator==(Segment seg1, Segment seg2)
{
	return seg1.begin == seg2.begin && seg1.end == seg2.end;
}

bool operator!=(Segment s1, Segment s2)
{
	return !(s1 == s2);
}

void Segment::setSegIndex(int index)
{
	begin.segIndex = index;
	end.segIndex = index;
}