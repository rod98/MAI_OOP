#include "square.h"

Square::Square() : Square(std::cin) {

}

Square::Square(int side) {
	this->side = side;
}

Square::Square(std::istream& is) {
	std::cout << "Enter the side: ";
	is >> side;
}

double Square::square() {
	return side * side;
}

std::ostream& Square::print(std::ostream &os)  {
	return os << "Square: " << side;
}
