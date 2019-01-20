#ifndef EIGHT_H
#define EIGHT_H

#include "figure.h"

class Eight : public Figure {
	public:
		Eight();
		Eight(std::istream& is);

		double square();
		std::ostream& print(std::ostream &os) const;


	private:
		int side;
};

#endif
