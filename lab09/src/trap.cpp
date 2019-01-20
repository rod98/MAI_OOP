#include <cmath>
#include "trap.h"

Trap::Trap() : Trap(std::cin){

}

Trap::Trap(int side, int up, int down) {
	this->side = side;
	this->up   = up;
	this->down = down;
}

Trap::Trap(std::istream& is) {
	std::cout << "Enter side, up & down: ";
	is >> side >> up >> down;
}

std::ostream& Trap::print(std::ostream &os)  {
	os << "Trap: " << side << " " << up << " " << down;

	return os;
}

double Trap::square() {
	return 0;
}

Trap& Trap::operator=(Trap& r) {
	this->side = r.side;
	this->up   = r.up;
	this->down = r.down;

	return r;
}

bool Trap::operator==(Trap& r) {
	return (side == r.side) && (up == r.up) && (down == r.down);
}
