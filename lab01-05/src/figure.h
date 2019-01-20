#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <iostream>

class Figure {
	public:
		virtual std::ostream& print(std::ostream &os) const = 0;
		virtual double square() = 0;

		friend std::ostream& operator<<(std::ostream &os, const Figure& f);
};

#endif
