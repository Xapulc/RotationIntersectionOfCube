#ifndef R3GRAPH_H
#define R3GRAPH_H

#include "R2Graph.h"
#include <iostream>

class R3Point {
protected:
	double x, y, z;
	
public:
	R3Point ():
		x(0),
		y(0),
		z(0)
	{}
	R3Point (double x, double y, double z):
		x(x),
		y(y),
		z(z)
	{}
	
	double getX() { return x; };
	double getY() { return y; };
	double getZ() { return z; };
	
	void print();
	bool inCube();
};

class InterPlane: public R3Point {
private:
	double A;
	double B;
	double C;
	double D;
	
	double findT(double a, double b, double c,
				  double x, double y, double z);
	
	void findInter(R3Point *pts, int n,
					double a, double b, double c,
					double x, double y, double z);
					
public:
	InterPlane():
		A(1),
		B(0),
		C(0),
		D(0)
	{}
	InterPlane(double A, double B, double C,
		  double x, double y, double z):
		A(A),
		B(B),
		C(C),
		D(-(A*x + B*y + C*z))
	{}
	
	InterPlane& operator=(const InterPlane &plane);
	void set(double A, double B, double C,
		double x, double y, double z);
	
	R3Point* interWithCube();
};

#endif
