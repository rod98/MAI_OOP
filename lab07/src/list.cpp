#include "list.h"

template <class T, class TT> TList<T, TT>::TList() {
    head = nullptr;
}

template <class T, class TT> void TList<T, TT>::RemoveSubitem(IRemoveCriteria<TT> * criteria) {
    std::cout << "---------------------->" << std::endl;
    for (auto i : * this) {
        T copy;

        //i->print(std::cout);

        while (i && !i->empty()) {
            std::shared_ptr<TT> value = i->pop();
            
            if (criteria->isIt(&*value))
                std::cout << "List: Delete element " << *value << std::endl;
            else {
				std::cerr << *value << std::endl;
                copy.insert(new TT(*value));
            }
        }
        while (!copy.empty())
			i->insert(new TT(*copy.pop()));

    }
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

template <class T, class TT> void TList<T, TT>::InsertSubitem(TT* value) {
    bool inserted = false;
    if (head != nullptr) {

        for (auto i : * this) {
            if (i->size() < 5) {
                i->insert(value);
                std::cout << "List: Add Element in list:" << i->size() << std::endl;
                inserted = true;
            }
        }
    }

    if (!inserted) {
        std::cout << "List: New list element created" << std::endl;
        T* t_value = new T();
        t_value->insert(value);
        PushBack(t_value);
    }
}

template <class T, class TT> void TList<T, TT>::PushBack(T* value) {
    std::shared_ptr<TListItem < T >> value_item(new TListItem<T>(value));
    std::cout << "List: Added to list" << std::endl;
    if (head != nullptr) {
        head->PushBack(value_item);
    } else {
        head = value_item;
    }
}

template <class T, class TT> bool TList<T, TT>::Remove(T* value) {
    std::shared_ptr<TListItem < T>> item = head;
    std::shared_ptr<TListItem < T>> prev_item = nullptr;
    bool result = false;

    while ((item != nullptr)&&(!result)) {
        if (item->getValue().get() == value) {
            if (prev_item != nullptr) prev_item->setNext(item->getNext());
            else head = item->getNext();
            result = true;
        } else {
            prev_item = item;
            item = item->getNext();
        }
    }

    return result;
}

template <class T, class TT> size_t TList<T, TT>::Size() {
    size_t result = 0;

    for (auto a : * this) 
		result++;

    return result;
}

template <class T, class TT> TIterator<TListItem<T>, T> TList<T, TT>::begin() const{
    return TIterator<TListItem<T>, T>(head);
}

template <class T, class TT> TIterator<TListItem<T>, T> TList<T, TT>::end() const{
    return TIterator<TListItem<T>, T>(nullptr);
}

template <class T, class TT> TList<T, TT>::~TList() {
    std::cout << "List: deleted" << std::endl;
}

template <class A, class AA> std::ostream& operator<<(std::ostream& os, const TList<A, AA>& list) {
    std::cout << "List:" << std::endl;
    for(auto i:list) 
		//std::cout << *i << std::endl;
		(*i).print(std::cout);
    return os;
}

#include "ttree.h"
#include "triangle.h"

template class TList<TTree<Triangle>, Triangle>;
template std::ostream& operator<<(std::ostream &os,const TList<TTree<Triangle>,Triangle> &list);
