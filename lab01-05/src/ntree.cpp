#include "debug.h"
#include "ntree.h"

template<class T> Ntree<T>::Ntree() {
	rsz = 0;
	noc = 0;
	ch  = NULL;
	par = NULL;
	crn = 0;
}

template<class T> void Ntree<T>::del(int *path) {
	Ntree<T> *ptr = this;

	if (path) {
		while (*path >= 0 && *(path + 1) >= 0) {
			ptr = ptr->ch[*path];
			path++;
		}
	}

	std::cout << "deleting " << *(path) << "\n";

	delete ptr->ch[*(path)];

	ptr->ch[*(path)] = NULL;
}

template<class T> Ntree<T>::Ntree(
	std::shared_ptr<T>& val
) : Ntree() {
	this->val = val;
}

template<class T> Ntree<T>::Ntree(
	std::shared_ptr<T>&& val
) : Ntree() {
	this->val = val;
}

template<class T> Ntree<T>::~Ntree() {
	for (int i = 0; i < noc; ++i)
		delete ch[i];

	delete [] ch;
}

template<class T> std::shared_ptr<T> Ntree<T>::get_val(int *path) {
	std::shared_ptr<T> res = nullptr;
	
	if (!path)
		res = val;
		
	return res;
}

template<class T> std::ostream& Ntree<T>::print(std::ostream& os, int depth) {
	for (int i = 0; i < depth; ++i)
		os << " ";
		
	if (val)
		os << noc << " " << *val << std::endl;
	else
		os << "(NULL)\n";
		
	for (int i = 0; i < noc; ++i)
		if (ch && ch[i]) 
			ch[i]->print(os, depth + 1);
			
	return os;
}

template<class T> Ntree<T> *Ntree<T>::getLast() {
	Ntree<T> *res = this;
	
	while (res->noc > 0) 
		res = res->ch[res->noc - 1];
	
	return res;
}

template <class T> Ntree<T> *Ntree<T>::getNext() {
	Ntree<T> *ptr = this;
	
	if (noc && ch && crn >= 0 && crn < noc) {
		ptr = ch[crn];
		crn++;
	}
	else if (par)
		ptr = par->getNext();
	else
		ptr = nullptr;
		
	return ptr;
}

template<class T> void Ntree<T>::add_child(std::shared_ptr<T>& val) {
	if (noc >= rsz - 1) {
		int    drsz = (rsz + 1) * 2;
		Ntree<T> **nptr = new Ntree<T> *[drsz];
		
		if (ch) {
			for (int i = 0; i < noc; ++i)
				nptr[i] = ch[i];

			delete [] ch;
		}
		rsz = drsz;
		ch  = nptr;
	}

	ch[noc++] = new Ntree<T>(val);
	ch[noc - 1]->par = this;
}

template<class T> void Ntree<T>::add(std::shared_ptr<T>& val, int *path) {
	Ntree<T> *ptr = this;

	if (path)
		while (*path >= 0) {
			ptr = ptr->ch[*path];
			path++;
		}

	ptr->add_child(val);
}

template<class T> void Ntree<T>::add(std::shared_ptr<T>&& val, int *path) {
	Ntree<T> *ptr = this;

	if (path)
		while (*path >= 0) {
			ptr = ptr->ch[*path];
			path++;
		}

	ptr->add_child(val);
}

template<class A> std::ostream& operator<<(std::ostream& os, Ntree<A> &t) {
	return t.print(os, 0);
}

#include "figure.h" 
template class Ntree<Figure>; 
template<class Figure> std::ostream& operator<<(std::ostream& os, Ntree<Figure>& t);
