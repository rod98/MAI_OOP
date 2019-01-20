#include "figure.h"

std::ostream& operator<<(std::ostream &os,  Figure& f) {
	return f.print(os);
}

int operator< ( Figure &l,  Figure& r) {
	//return t.print(os);
	return l.square() < r.square();
}
