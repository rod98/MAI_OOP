#ifndef NTREE_H
#define NTREE_H

#include <memory>
#include "trap.h"
#include "alloc.h"

template<class T> class Ntree {
	public:
		Ntree();
		Ntree(std::shared_ptr<T>&  val);
		Ntree(std::shared_ptr<T>&& val);
		~Ntree();

		void add(std::shared_ptr<T>&  val, int *path);
		void add(std::shared_ptr<T>&& val, int *path);
		void del(int *path);
		std::shared_ptr<T> get_val(int *path);
		std::ostream& print(std::ostream& os, int depth);
		
		Ntree<T> *getNext();
		Ntree<T> *getLast();

		template<class A> friend std::ostream& operator<<(std::ostream& os, Ntree<A> &t);
		
		static TAllocationBlock _allocator;
		
		void *operator new   (size_t size);
		void  operator delete(void *p);

	private:
		void add_child(
			std::shared_ptr<T>& val
		);

		Ntree **ch;
		Ntree  *par;
		int     noc;
		int     rsz;
		int     crn;
		std::shared_ptr<T> val;
};

#endif
