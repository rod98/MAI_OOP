#ifndef TLIST_H
#define	TLIST_H

#include "listitem.h"
#include "figure.h"

#include <memory>

template <class T> class TList {
	public:
		TList();
		
		void addRight(std::shared_ptr<T>  &item);
		void addRight(std::shared_ptr<T> &&item);
		bool empty();
		std::shared_ptr<T> getValue();
		void del();
		
		//TIterator<TListItem<T>,T> begin();
		//TIterator<TListItem<T>,T> end();
		
		template <class A> friend std::ostream& operator<<(std::ostream& os,const TList<A>& LIST);
		virtual ~TList();
		
		void goRight();
		void goLeft ();
		
	private:
		std::shared_ptr<TListItem<T>> head;
		std::shared_ptr<TListItem<T>> current;
};

#endif	/* TLIST_H */
