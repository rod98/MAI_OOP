#include "list_alloc.h"

template <class T> TList_alloc<T>::TList_alloc() : head(nullptr) {
	current = head;
}

template <class T> std::shared_ptr<T> TList_alloc<T>::getValue() {
	return current ? current->getValue() : nullptr;
}

template <class T> void TList_alloc<T>::goRight() {
	if (current &&  current->getNext())
		current = current->getNext();
}

template <class T> void TList_alloc<T>::goLeft () {
	if (current && current->getPrev())
		current = current->getPrev();
}

template <class T> void TList_alloc<T>::del() {
	if (current) {
		std::shared_ptr<TListItem_alloc<T>> next = current->getNext();
		std::shared_ptr<TListItem_alloc<T>> prev = current->getPrev();
		std::shared_ptr<TListItem_alloc<T>> item = next; 
		
		if (!item)
			item = prev;
		
		if (prev)
			prev->setNext(next);
			
		if (next)
			next->setPrev(prev);
		
		//delete current;
		
		if (current == head)
			head = item;
			
		next.reset();
		prev.reset();
		
		std::cout << current.unique() << "\n";
		
		current = item;
	}
}

template <class T> std::ostream& operator<<(std::ostream& os, const TList_alloc<T>& stack) {
	std::shared_ptr<TListItem_alloc<T>> item = stack.head;

	while(item != nullptr) {
		os << *item;
		item = item->getNext();
	}

	return os;
}

template <class T> void TList_alloc<T>::addRight(std::shared_ptr<T> &item) {
	std::shared_ptr<TListItem_alloc<T>> other(new TListItem_alloc<T>(item));

	if (current) {
		std::shared_ptr<TListItem_alloc<T>> next = current->getNext();
		current->setNext(other);
		other->setNext(next);
		other->setPrev(current);
	}
	else {
		current = other;
		head    = other;
	}
}

template <class T> void TList_alloc<T>::addRight(std::shared_ptr<T> &&item) {
	std::shared_ptr<TListItem_alloc<T>> other(new TListItem_alloc<T>(item));

	if (current) {
		std::shared_ptr<TListItem_alloc<T>> next = current->getNext();
		current->setNext(other);
		other->setNext(next);
		other->setPrev(current);
	}
	else {
		current = other;
		head    = other;
	}
}

template <class T> bool TList_alloc<T>::empty() {
    return head == nullptr;
}

/*template <class T> TIterator<TListItem_alloc<T>,T> TList_alloc<T>::begin()
{
    return TIterator<TListItem_alloc<T>,T>(head);
}

template <class T> TIterator<TListItem_alloc<T>,T> TList_alloc<T>::end()
{
    return TIterator<TListItem_alloc<T>,T>(nullptr);
}*/


template <class T> TList_alloc<T>::~TList_alloc() {
	std::cout << "Deleting List\n";
	
	for (std::shared_ptr<TListItem_alloc<T>> item = head; item; item = item->getNext())
		item->resetPtrs();
}

#include "figure.h"
template class TList_alloc<Figure>;
template class TList_alloc<void *>;
template std::ostream& operator<<(std::ostream& os, const TList_alloc<Figure>& stack);
