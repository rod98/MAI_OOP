#include "list.h"

template <class T> TList<T>::TList() : head(nullptr) {
	current = head;
}

template <class T> std::shared_ptr<T> TList<T>::getValue() {
	return current ? current->getValue() : nullptr;
}

template <class T> void TList<T>::goRight() {
	if (current &&  current->getNext())
		current = current->getNext();
}

template <class T> void TList<T>::goLeft () {
	if (current && current->getPrev())
		current = current->getPrev();
}

template <class T> void TList<T>::del() {
	if (current) {
		std::shared_ptr<TListItem<T>> next = current->getNext();
		std::shared_ptr<TListItem<T>> prev = current->getPrev();
		std::shared_ptr<TListItem<T>> item = next; 
		
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

template <class T> std::ostream& operator<<(std::ostream& os, const TList<T>& stack) {
	std::shared_ptr<TListItem<T>> item = stack.head;

	while(item != nullptr) {
		os << *item;
		item = item->getNext();
	}

	return os;
}

template <class T> void TList<T>::addRight(std::shared_ptr<T> &item) {
	std::shared_ptr<TListItem<T>> other(new TListItem<T>(item));

	if (current) {
		std::shared_ptr<TListItem<T>> next = current->getNext();
		current->setNext(other);
		other->setNext(next);
		other->setPrev(current);
	}
	else {
		current = other;
		head    = other;
	}
}

template <class T> void TList<T>::addRight(std::shared_ptr<T> &&item) {
	std::shared_ptr<TListItem<T>> other(new TListItem<T>(item));

	if (current) {
		std::shared_ptr<TListItem<T>> next = current->getNext();
		current->setNext(other);
		other->setNext(next);
		other->setPrev(current);
	}
	else {
		current = other;
		head    = other;
	}
}

template <class T> bool TList<T>::empty() {
    return head == nullptr;
}

/*template <class T> TIterator<TListItem<T>,T> TList<T>::begin()
{
    return TIterator<TListItem<T>,T>(head);
}

template <class T> TIterator<TListItem<T>,T> TList<T>::end()
{
    return TIterator<TListItem<T>,T>(nullptr);
}*/


template <class T> TList<T>::~TList() {
	std::cout << "Deleting List\n";
	
	for (std::shared_ptr<TListItem<T>> item = head; item; item = item->getNext())
		item->resetPtrs();
}

#include "figure.h"
template class TList<Figure>;
template class TList<void *>;
template std::ostream& operator<<(std::ostream& os, const TList<Figure>& stack);
