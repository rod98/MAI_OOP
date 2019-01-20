#include "alloc.h"
#include <iostream>
#include "list.h"

TAllocationBlock::TAllocationBlock(size_t size,size_t count): _size(size),_count(count)  {
	blcks = new TList<void *>();
	
	_free_count = _count;
	
    for (size_t i = 0; i < _count; ++i) {
		void *ptr = malloc(_size);
		std::shared_ptr<void *> sp((void **)ptr);

		blcks->addRight(sp);
	}

	//std::cout << "List: " << std::endl;
	//std::cout << blcks << std::endl;
}

void *get_ptr(TList<void *> *ls) {
	void *r = nullptr;
	
	if (ls) {
		r = ls->getValue().get();
	}
	
	return r;
}

void *TAllocationBlock::allocate() {
    void *result = nullptr;
    
	if (_free_count > 0) {
        result = blcks->getValue().get();
        blcks->goRight();
        _free_count--;
        std::cout << "TAllocationBlock: Allocate " << (_count - _free_count) << " of " << _count << std::endl;
    } else 
		std::cout << "TAllocationBlock: No memory exception :-)" << std::endl;
    
    return result;
}

void TAllocationBlock::deallocate(void *pointer) {
	std::cout << "TAllocationBlock: Deallocate block " << pointer << std::endl;

	//_free_blocks[_free_count] = pointer;
	
	blcks->goLeft();
	_free_count++;
	
	//t_print(lsus, 0, std::cout);
	//t_print(lsfr, 0, std::cout);
}

bool TAllocationBlock::has_free_blocks() {
    return _free_count > 0;
}

TAllocationBlock::~TAllocationBlock() {
    if (_free_count < _count)
		std::cout << "TAllocationBlock: Memory leak?" << std::endl;
	else
		std::cout << "TAllocationBlock: Memory freed" << std::endl;
		
	delete blcks;
	
	//delete lsfr;
	//delete lsus;

	blcks = nullptr;
}
