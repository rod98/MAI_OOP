#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

class Square : public Figure {
	public:
		Square();
		Square(int side);
		Square(std::istream& is);

		double square();
		std::ostream& print(std::ostream &os) const;
	private:
		double side;
};

#endif
