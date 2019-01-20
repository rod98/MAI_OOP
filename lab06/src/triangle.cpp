#include <cmath>
#include "triangle.h"

Triangle::Triangle() : Triangle(std::cin) {

}

Triangle::Triangle(std::istream& is) {
	std::cout << "Enter three sides: ";
	is >> a >> b >> c;
}

Triangle::Triangle(int a, int b, int c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

std::ostream& Triangle::print(std::ostream &os) const {
	return os << "Triangle: " << a << " " << b << " " << c;
}

double Triangle::square() {
	double p = (a + b + c) / 2.0;

	return sqrt(p * (p - a) * (p - b) * (p - c));
}
