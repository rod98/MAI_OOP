#include "listitem.h"
#include <iostream>

template <class T> TListItem<T>::TListItem(const std::shared_ptr<T>& item) {
	this->item = item;
	this->next = nullptr;
	this->prev = nullptr;
	//std::cout << "List item: created" << std::endl;
}

//template <class T> TAllocationBlock TListItem<T>::_allocator(sizeof(TListItem<T>), 10);

template <class T> std::shared_ptr<TListItem<T>> TListItem<T>::setNext(std::shared_ptr<TListItem<T>> &next) {
    std::shared_ptr<TListItem <T>> old = this->next;
    this->next = next;
    return old;
}

template <class T> std::shared_ptr<TListItem<T>> TListItem<T>::setPrev(std::shared_ptr<TListItem<T>> &prev) {
	std::shared_ptr<TListItem <T>> old = this->prev;
	this->prev = prev;
	return old;
}

template <class T> std::shared_ptr<T> TListItem<T>::getValue() const {
    return this->item;
}

template <class T> std::shared_ptr<TListItem<T>> TListItem<T>::getNext() {
    return this->next;
}

template <class T> std::shared_ptr<TListItem<T>> TListItem<T>::getPrev() {
    return this->prev;
}

template <class T> TListItem<T>::~TListItem() {
    //std::cout << "List item: deleted" << std::endl;
}

template <class A> std::ostream& operator<<(std::ostream& os, const TListItem<A>& obj) {
    os << "[" << *obj.item << "]" << std::endl;
   // os << "[" << obj.prev << " | " << obj.next << "]" << std::endl;
    return os;
}

#include "triangle.h"
template class TListItem<Figure>;
template class TListItem<void *>;
template std::ostream& operator<<(std::ostream& os, const TListItem<Figure>& obj);
