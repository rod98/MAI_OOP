#ifndef TREE_CONT
#define TREE_CONT

#include <iostream>
#include <memory>
#include "titerator.h"
#include "ntree.h"

template<class T> class TreeCont {
	public:
		TreeCont (void);
		TreeCont (std::shared_ptr<T>&  val);
		TreeCont (std::shared_ptr<T>&& val);
		~TreeCont();
		
		void add(std::shared_ptr<T>&& val, int *path);
		void del(int *path);
		std::shared_ptr<T> get_val(int *path);

		template<class A> friend std::ostream& operator<<(std::ostream& os, TreeCont<A> &t);
		
		TIterator<Ntree<T>,T> begin();
		TIterator<Ntree<T>,T> end  ();
		
		std::ostream& print(std::ostream& os);
	private:	
		Ntree<T> *head;
};

#endif
