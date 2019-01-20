#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <iostream>

class Figure {
	public:
		virtual std::ostream& print(std::ostream &os)  = 0;
		virtual double square() = 0;

		friend std::ostream& operator<<(std::ostream &os,  Figure& f);
		friend int           operator< ( Figure&l,    Figure& r);
};

#endif
