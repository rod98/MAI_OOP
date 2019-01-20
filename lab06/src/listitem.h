#ifndef TLISTITEM_H
#define	TLISTITEM_H

#include <memory>
#include "figure.h"

template<class T> class TListItem {
public:
    TListItem(const std::shared_ptr<T>& triangle);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TListItem<A>& obj);
    
    std::shared_ptr<TListItem<T>> setNext(std::shared_ptr<TListItem> &next);
    std::shared_ptr<TListItem<T>> getNext();
    std::shared_ptr<TListItem<T>> setPrev(std::shared_ptr<TListItem> &next);
    std::shared_ptr<TListItem<T>> getPrev();
    std::shared_ptr<T> getValue() const;
    
    virtual ~TListItem();
    void resetPtrs() { if (prev) prev.reset(); }
private:
    std::shared_ptr<T> item;
    std::shared_ptr<TListItem<T>> next;
    std::shared_ptr<TListItem<T>> prev;
};

#endif	/* TLISTITEM_H */
