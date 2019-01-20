#include "list_item_alloc.h"
#include <iostream>

template <class T> TListItem_alloc<T>::TListItem_alloc(const std::shared_ptr<T>& item) {
	this->item = item;
	this->next = nullptr;
	this->prev = nullptr;
	//std::cout << "List item: created" << std::endl;
}

//template <class T> TAllocationBlock TListItem_alloc<T>::_allocator(sizeof(TListItem_alloc<T>), 10);

template <class T> std::shared_ptr<TListItem_alloc<T>> TListItem_alloc<T>::setNext(std::shared_ptr<TListItem_alloc<T>> &next) {
    std::shared_ptr<TListItem_alloc <T>> old = this->next;
    this->next = next;
    return old;
}

template <class T> std::shared_ptr<TListItem_alloc<T>> TListItem_alloc<T>::setPrev(std::shared_ptr<TListItem_alloc<T>> &prev) {
	std::shared_ptr<TListItem_alloc <T>> old = this->prev;
	this->prev = prev;
	return old;
}

template <class T> std::shared_ptr<T> TListItem_alloc<T>::getValue() const {
    return this->item;
}

template <class T> std::shared_ptr<TListItem_alloc<T>> TListItem_alloc<T>::getNext() {
    return this->next;
}

template <class T> std::shared_ptr<TListItem_alloc<T>> TListItem_alloc<T>::getPrev() {
    return this->prev;
}

template <class T> TListItem_alloc<T>::~TListItem_alloc() {
    //std::cout << "List item: deleted" << std::endl;
}

template <class A> std::ostream& operator<<(std::ostream& os, const TListItem_alloc<A>& obj) {
    os << "[" << *obj.item << "]" << std::endl;
   // os << "[" << obj.prev << " | " << obj.next << "]" << std::endl;
    return os;
}

#include "triangle.h"
template class TListItem_alloc<Figure>;
template class TListItem_alloc<void *>;
template std::ostream& operator<<(std::ostream& os, const TListItem_alloc<Figure>& obj);
