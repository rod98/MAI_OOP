#include <iostream>
#include <string>

#include "TNTreeItem.h"

template <class T>
TNTreeItem<T>::TNTreeItem(std::recursive_mutex *parent) {
	this->tree_mutex = parent;
    this->brother = nullptr;
    this->son = nullptr;
    this->id = "";
}

template <class T>
TNTreeItem<T>::TNTreeItem(std::string id,  std::shared_ptr<T> &figure, std::recursive_mutex *parent) { 
	this->tree_mutex = parent;
    this->figure = figure;
    this->brother = nullptr;
    this->son = nullptr;
    this->id = id;
}

template <class T>
void TNTreeItem<T>::SetSon(std::shared_ptr<TNTreeItem<T>> son) {
	std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
    this->son = son;
}

template <class T>
void TNTreeItem<T>::SetBrother(std::shared_ptr<TNTreeItem<T>> brother) {
	std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
    this->brother = brother;
}

template <class T>
std::shared_ptr<T> TNTreeItem<T>::getValue()  {
	std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    return this->figure; 
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTreeItem<T>::GetSon() {
	std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
    return this->son; 
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTreeItem<T>::GetBrother() {
	std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
    return this->brother;
}

template <class T>
std::string TNTreeItem<T>::getID() {
	std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
    return this->id;
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTreeItem<T>::Begin() {
	std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
	if (!this->son) {
		return this->shared_from_this();
	}
	else {
        auto iter = this->son;
        while (iter->son)
            iter = iter->son;
        return iter;
    }
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTreeItem<T>::Next() {
	std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
	if (this->brother)
		return this->brother;
	else if (this->son)
		return this->son;
	return
		nullptr;
}

template <class T>
std::ostream& operator<<(std::ostream& os,  TNTreeItem<T>& obj) {
	std::lock_guard<std::recursive_mutex> lock(*obj.tree_mutex);
    os << obj.id << " " << *obj.figure;
    return os; 
}

#include "figure.h"
#include <functional>
template class TNTreeItem<Figure>;
template class TNTreeItem<std::function<void ()>>;
template std::ostream& operator<<(std::ostream& os,  TNTreeItem<Figure> &obj);
