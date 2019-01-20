#ifndef TLIST_H
#define	TLIST_H

#include "list_item_alloc.h"
#include "figure.h"

#include <memory>

template <class T> class TList_alloc {
	public:
		TList_alloc();
		
		void addRight(std::shared_ptr<T>  &item);
		void addRight(std::shared_ptr<T> &&item);
		bool empty();
		std::shared_ptr<T> getValue();
		void del();
		
		//TIterator<TListItem_alloc<T>,T> begin();
		//TIterator<TListItem_alloc<T>,T> end();
		
		template <class A> friend std::ostream& operator<<(std::ostream& os,const TList_alloc<A>& LIST);
		virtual ~TList_alloc();
		
		void goRight();
		void goLeft ();
		
	private:
		std::shared_ptr<TListItem_alloc<T>> head;
		std::shared_ptr<TListItem_alloc<T>> current;
};

#endif	/* TLIST_H */
