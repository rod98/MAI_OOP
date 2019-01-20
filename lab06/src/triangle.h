#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include "figure.h"

class Triangle : public Figure {
	public:
		Triangle ();
		Triangle (int a, int b, int c);
		Triangle (std::istream& is);

		double square();
		std::ostream& print(std::ostream &os) const;

	private:
		int a, b, c;
};

#endif
