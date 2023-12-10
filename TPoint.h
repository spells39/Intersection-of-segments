#include <iostream>
#pragma once
using namespace std;

struct Point
{
public:
	double x, y; 
	double z = 0.0;
	bool isLeft = false;
	int segIndex = -1;

	Point() { x = 0.0; y = 0.0; z = 0.0; }

	Point(double x_, double y_, double z_ = 0.0)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	/*Point(const Point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		isLeft = p.isLeft;
		segIndex = p.segIndex;
	}*/
	/*Point& operator=(const Point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		isLeft = p.isLeft;
		segIndex = p.segIndex;
		return *this;
	}*/
	friend Point operator-(Point& p1, Point& p2)
	{
		//Point p;
		//p.x = p2.x - p1.x;
		//p.y = p2.y - p1.y;
		return Point(p2.x - p1.x, p2.y - p1.y);
	}
	friend ostream& operator<<(ostream& os, Point p)
	{
		os << p.x << " " << p.y;
		return os;
	}
	friend bool operator==(Point& p1, Point& p2)
	{
		if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
			return true;
		return false;
	}
	friend bool operator<(Point& p1, Point& p2)
	{
		if (p1.x < p2.x)
			return true;
		return false;
	}
	friend bool operator<=(Point& p1, Point& p2)
	{
		if (p1.x == p2.x)
		{
			if (p1.isLeft)
				return false;
			return true;
		}
		if (p1.x < p2.x)
			return true;
		return false;
	}
	friend bool operator>(Point& p1, Point& p2)
	{
		return !(p1 < p2);
	}
	friend bool operator>=(Point& p1, Point& p2)
	{
		if (p1.x > p2.x)
			return true;
		return false;
	}
	friend istream& operator>>(istream& is, Point& p)
	{
		cout << "x: ";
		is >> p.x;
		cout << "y: ";
		is >> p.y;
		return is;
	}
};

struct Vector
{
	Point p;
	double x() { return p.x; }
	double y() { return p.y; }
	double z() { return p.z; }
	Vector(Point p_)
	{
		p.x = p_.x;
		p.y = p_.y;
		p.z = p_.z;
	}
	friend Vector operator*(Vector& v1, Vector& v2)
	{
		double x = v1.y() * v2.z() - v1.z() * v2.y();
		double y = v1.x() * v2.z() - v1.z() * v2.x();
		double z = v1.x() * v2.y() - v1.y() * v2.x();
		return Vector(Point(x, y, z));
	}
};
