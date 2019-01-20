#include "triangle.h"
#include "square.h"
#include "trap.h"
#include "tree_cont.h"
#include "debug.h"

void TestAllocationBlock() {
   TAllocationBlock allocator(sizeof(int),10);   
   
   int *a1 = nullptr;
   int *a2 = nullptr;
   int *a3 = nullptr;
   int *a4 = nullptr;
   int *a5 = nullptr;
   
   a1 = (int*)allocator.allocate();*a1 = 1; std::cout << "a1 pointer value:" << *a1 << std::endl;
   a2 = (int*)allocator.allocate();*a2 = 2; std::cout << "a2 pointer value:" << *a2 << std::endl;
   a3 = (int*)allocator.allocate();*a3 = 3; std::cout << "a3 pointer value:" << *a3 << std::endl;
   
   allocator.deallocate(a1);
   allocator.deallocate(a3);

   a4 = (int*)allocator.allocate();*a4 = 4; std::cout << "a4 pointer value:" << *a4 << std::endl;
   a5 = (int*)allocator.allocate();*a5 = 5; std::cout << "a5 pointer value:" << *a5 << std::endl;
   std::cout << "a1 pointer value:" << *a1 << std::endl;
   std::cout << "a2 pointer value:" << *a2 << std::endl;
   std::cout << "a3 pointer value:" << *a3 << std::endl;

   allocator.deallocate(a2);
   allocator.deallocate(a4);
   allocator.deallocate(a5);   
}

int main(void) {
	//std::string line;

	/*while (getline(std::cin, line)) {
		std::string cmd;
		int path[100];

	}*/
	
	TestAllocationBlock();

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
