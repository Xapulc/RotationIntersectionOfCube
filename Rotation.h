#ifndef ROTATION_H
#define ROTATION_H

#include "R3Graph.h"
#include <cmath>

class Rotation {
	private:
		double **elems;
		void copy(const Rotation& from);
	public:
		Rotation();
		Rotation(Rotation& from);
		Rotation(double** from);
		~Rotation();
		
		const double getElem(int i, int j) const { return this->elems[i][j]; }; 
		double* operator[](int pos);
		Rotation& operator=(const Rotation& from);
		Rotation operator*(Rotation& from);
		double* operator()(double *vct);
		R3Point operator()(R3Point& pt);

		Rotation& increase(double alpha);
		Rotation& decrease(double alpha);
		Rotation inverse();
		Rotation rotate(R3Point& vct, double phi);
		void print();
};

#endif
