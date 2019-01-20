#ifndef TALLOCATIONBLOCK_H
#define	TALLOCATIONBLOCK_H

#include <cstdlib>
#include "list_alloc.h"

class TAllocationBlock {
public:
    TAllocationBlock(size_t size,size_t count);
    void *allocate();
    void deallocate(void *pointer);
    bool has_free_blocks();
    
    virtual ~TAllocationBlock();
    
private:
    size_t _size;
    size_t _count;
    
    size_t _free_count;
    
	TList_alloc<void *> *blcks;
};

#endif	/* TALLOCATIONBLOCK_H */
