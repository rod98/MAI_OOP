#include "triangle.h"
#include "square.h"
#include "trap.h"
#include "tree_cont.h"
#include "debug.h"

int main(void) {
	std::string line;

	/*while (getline(std::cin, line)) {
		std::string cmd;
		int path[100];

	}*/

	TreeCont<Figure> nt(std::shared_ptr<Figure>(new Triangle(9, 9, 9)));
	int pa[] = {-1};
	int pb[] = {2, -1};
	int pd[] = {1, -1};
	
	nt.add(std::shared_ptr<Figure>(new Triangle(0, 0, 0)), pa);
	nt.add(std::shared_ptr<Figure>(new Triangle(1, 1, 1)), pa);
	nt.add(std::shared_ptr<Figure>(new Triangle(2, 2, 2)), pa);
	nt.add(std::shared_ptr<Figure>(new Triangle(4, 5, 6)), pb);
	nt.add(std::shared_ptr<Figure>(new Square  (2)),       pa);
	nt.add(std::shared_ptr<Figure>(new Square  (3)),       pa);
	//nt.del(pd);
	
	nt.print(std::cout);
	
	for (auto t: nt)
		if (t) {
			t->print(std::cout);
			std::cout << "\n";
		}
	
	return 0;
}
