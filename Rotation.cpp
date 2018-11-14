#include "Rotation.h"

Rotation::Rotation() {
	elems = new double*[3];
	
	for(int i = 0; i < 3; i++) {
		elems[i] = new double[3];
		for(int j = 0; j < 3; j++) {
			if (i == j)
				elems[i][j] = 1;
			else
				elems[i][j] = 0;
		}
	}
}

Rotation::Rotation(Rotation& from) {
	elems = new double*[3];
	for(int i = 0; i < 3; i++)
		elems[i] = new double[3];
	
	copy(from);
}

Rotation::Rotation(double** from) {
	elems = new double*[3];
	
	for(int i = 0; i < 3; i++) {
		elems[i] = new double[3];
		for(int j = 0; j < 3; j++) {
			if (i == j)
				elems[i][j] = from[i][j];
			else
				elems[i][j] = from[i][j];
		}
	}
}

Rotation::~Rotation() {
	for(int i = 0; i < 3; i++)
		delete [] (*this)[i];
	delete [] elems;
}

void Rotation::copy(const Rotation& from) {
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			(*this)[i][j] = from.getElem(i, j);
	
}

double* Rotation::operator[](int pos) {
	return elems[pos];
}

Rotation& Rotation::operator=(const Rotation& from) {
	copy(from);
	return *this;
}

Rotation Rotation::operator*(Rotation& from) {
	Rotation res;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++) {
			res[i][j] = 0;
			for(int k = 0; k < 3; k++)
				res[i][j] += from[i][k] * (*this)[k][j];
		}
	return res;
}

double* Rotation::operator()(double *vct) {
	double *res = new double[3] {0, 0, 0};
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			res[i] += (*this)[i][j] * vct[j];
	return res;
}

R3Point Rotation::operator()(R3Point& pt) {
	R3Point res(pt.getX()*(*this)[0][0] + pt.getY()*(*this)[0][1] + pt.getZ()*(*this)[0][2],
				pt.getX()*(*this)[1][0] + pt.getY()*(*this)[1][1] + pt.getZ()*(*this)[1][2],
				pt.getX()*(*this)[2][0] + pt.getY()*(*this)[2][1] + pt.getZ()*(*this)[2][2]);
	return res;
}

Rotation Rotation::inverse() { // пока что не работает
	auto **matrix = new double*[3];
    matrix[0] = new double[3]
            {(*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1],
			 -((*this)[1][0] * (*this)[2][2] - (*this)[1][2] * (*this)[2][0]),
			 (*this)[1][0] * (*this)[2][1] - (*this)[1][1] * (*this)[2][0]};
    matrix[1] = new double[3]
            {-((*this)[0][1] * (*this)[2][2] - (*this)[0][2] * (*this)[2][1]),
			 (*this)[0][0] * (*this)[2][2] - (*this)[0][2] * (*this)[2][0],
			 -((*this)[0][0] * (*this)[2][1] - (*this)[0][1] * (*this)[2][1])};
    matrix[2] = new double[3]
            {(*this)[0][1] * (*this)[1][2] - (*this)[0][2] * (*this)[1][1],
			 -((*this)[0][0] * (*this)[1][2] - (*this)[0][2] * (*this)[1][0]),
			 (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0]};

    Rotation res(matrix);
    return res;
}

void Rotation::print() {
    std::cout << elems[0][0] << " " << elems[0][1] << " " << elems[0][2] << std::endl;
    std::cout << elems[1][0] << " " << elems[1][1] << " " << elems[1][2] << std::endl;
    std::cout << elems[2][0] << " " << elems[2][1] << " " << elems[2][2] << std::endl;
}

Rotation Rotation::rotate(R3Point& vct, double phi) {
    auto **matrix = new double*[3];
    matrix[0] = new double[3]
            {vct.getX() * vct.getX() + 0 + cos(phi) * (1 - vct.getX()*vct.getX()),
			 vct.getY() * vct.getX() + -sin(phi) * vct.getZ() + cos(phi) * (-vct.getX() * vct.getY()),
			 vct.getZ() * vct.getX() + sin(phi) * vct.getY() + cos(phi) * (-vct.getX()*vct.getZ())};
    matrix[1] = new double[3]
            {vct.getX() * vct.getY() + sin(phi) * vct.getZ() + cos(phi) * (-vct.getX()*vct.getY()),
             vct.getY() * vct.getY() + 0 + cos(phi) * (1 - vct.getY()*vct.getY()),
			 vct.getZ() * vct.getY() + -sin(phi) * vct.getX() + cos(phi) * (-vct.getY()*vct.getZ())};
    matrix[2] = new double[3]
            {vct.getX() * vct.getZ() + -sin(phi) * vct.getY() + cos(phi) * (-vct.getX() * vct.getZ()),
			 vct.getY() * vct.getZ() + sin(phi) * vct.getX() + cos(phi) * (-vct.getY()*vct.getZ()),
             vct.getZ() * vct.getZ() + 0 + cos(phi) * (1 - vct.getZ()*vct.getZ())};

    Rotation res(matrix);
    return res;

}

Rotation Rotation::inrease(double alpha) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
            (*this)[i][j] *= alpha;

	return (*this);
}
