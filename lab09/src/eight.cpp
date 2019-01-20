#include <cmath>
#include "eight.h"

double Eight::square() {
	double res = 2 * side * side * (1 + sqrt(2.0));

	return res;
}

Eight::Eight() : Eight(std::cin) {

}

std::ostream& Eight::print(std::ostream &os)  {
	std::cout << "Eight: " << side << std::endl;
	return os;
}

Eight::Eight(std::istream& is) {
	std::cout << "Enter eight-angle side: ";
	std::cin  >> side;
}
