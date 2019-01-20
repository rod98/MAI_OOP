#include "debug.h"
#include "tree_cont.h"
#include "ntree.h"

template <class T> TreeCont<T>::TreeCont() : head(nullptr) {
	
}

template <class T> TreeCont<T>::TreeCont(std::shared_ptr<T>&& val) {
	head = new Ntree<T>(val);
}

template <class T> TreeCont<T>::TreeCont(std::shared_ptr<T>& val) {
	head = new Ntree<T>(val);
}

template <class T> void TreeCont<T>::add(std::shared_ptr<T>&& val, int *path) {
	if (head)
		head->add(val, path);
	else
		head = new Ntree<T>(val);
}

template <class T> void TreeCont<T>::del(int *path) {
	if (head)
		head->del(path);
}

template<class T> std::shared_ptr<T> TreeCont<T>::get_val(int *path) {
	return nullptr;
}

template<class T> std::ostream& TreeCont<T>::print(std::ostream& os) {
	return head->print(os, 0);
}

template<class A> std::ostream& operator<<(std::ostream& os, TreeCont<A> &t) {
	return t.print(os);
}

template<class T> TIterator<Ntree<T>,T> TreeCont<T>::begin() {
	return TIterator<Ntree<T>, T>(head);
}

template<class T> TIterator<Ntree<T>,T> TreeCont<T>::end() {
	//return TIterator<Ntree<T>, T>(head->getLast());
	return TIterator<Ntree<T>,T>(nullptr);
}

template<class T> TreeCont<T>::~TreeCont() {
	DEBUG("Destructor called");
	delete head;
}

#include "figure.h"
template class TreeCont<Figure>;
template class TIterator<Ntree<Figure>, Figure>;
