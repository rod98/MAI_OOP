#include "figure.h"

std::ostream& operator<<(std::ostream &os, const Figure& f) {
	return f.print(os);
}
