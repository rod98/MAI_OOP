#ifndef TRAP_H
#define TRAP_H

#include "figure.h"

class Trap : public Figure {
	public:
		Trap ();
		Trap (std::istream& is);
		Trap (int side, int up, int down);

		double square();
		std::ostream& print(std::ostream &os) const;

		Trap& operator=(Trap& r);
		bool  operator==(Trap& r);

	private:
		int side, up, down;
};

#endif
