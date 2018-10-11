#include "R3Graph.h"

bool R3Point::inCube() {
	return ((0 <= x) && (x <= 1) &&
			(0 <= y) && (y <= 1) &&
			(0 <= z) && (z <= 1));
}

void R3Point::print() {
	std::cout << x << " " << y << " " << z << std::endl;
}

InterPlane& InterPlane::operator=(const InterPlane &plane) {
	this->A = plane.A;
	this->B = plane.B;
	this->C = plane.C;
	this->D = plane.D;
	this->x = plane.x;
	this->y = plane.y;
	this->z = plane.z;
	
	return *this;
}

void InterPlane::set(double A, double B, double C,
					 double x, double y, double z) {
	this->A = A;
	this->B = B;
	this->C = C;
	D = -(A*x + B*y + C*z);
	this->x = x;
	this->y = y;
	this->z = z;
}

double InterPlane::findT(double a, double b, double c,
					 double x, double y, double z) {
	return -(A*x + B*y + C*z + D)/(A*a + B*b + C*c);
}

void InterPlane::findInter(R3Point *pts, int n,
				double a, double b, double c,
				double x, double y, double z) {
	double t;
	
	if (fabs(A*a + B*b + C*c) < 1e-16)
		pts[n] = {-1, -1, -1};
	else {
		t = findT(a, b, c, x, y, z);
		pts[n] = {x + a*t, y + b*t, z + c*t};
	}
}

R3Point* InterPlane::interWithCube() {
	R3Point *pts = new R3Point[12];
	
	// search intersection points with all lines
	findInter(pts,  0, 0, 1, 0, 0, 0, 0);
	findInter(pts,  1, 1, 0, 0, 0, 1, 0);
	findInter(pts,  2, 0, 1, 0, 1, 0, 0);
	findInter(pts,  3, 1, 0, 0, 0, 0, 0);
	findInter(pts,  4, 0, 0, 1, 0, 0, 0);
	findInter(pts,  5, 0, 0, 1, 0, 1, 0);
	findInter(pts,  6, 0, 0, 1, 1, 1, 0);
	findInter(pts,  7, 0, 0, 1, 1, 0, 0);
	findInter(pts,  8, 0, 1, 0, 0, 0, 1);
	findInter(pts,  9, 1, 0, 0, 0, 1, 1);
	findInter(pts, 10, 0, 1, 0, 1, 0, 1);
	findInter(pts, 11, 1, 0, 0, 0, 0, 1);
	
	return pts;
}

