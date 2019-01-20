#ifndef TLISTITEM_H
#define	TLISTITEM_H

#include <memory>
#include "figure.h"

template<class T> class TListItem_alloc {
public:
    TListItem_alloc(const std::shared_ptr<T>& triangle);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TListItem_alloc<A>& obj);
    
    std::shared_ptr<TListItem_alloc<T>> setNext(std::shared_ptr<TListItem_alloc> &next);
    std::shared_ptr<TListItem_alloc<T>> getNext();
    std::shared_ptr<TListItem_alloc<T>> setPrev(std::shared_ptr<TListItem_alloc> &next);
    std::shared_ptr<TListItem_alloc<T>> getPrev();
    std::shared_ptr<T> getValue() const;
    
    virtual ~TListItem_alloc();
    void resetPtrs() { if (prev) prev.reset(); }
private:
    std::shared_ptr<T> item;
    std::shared_ptr<TListItem_alloc<T>> next;
    std::shared_ptr<TListItem_alloc<T>> prev;
};

#endif	/* TLISTITEM_H */
