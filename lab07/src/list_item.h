#ifndef TLISTITEM_H
#define	TLISTITEM_H
#include <memory>

template <class T> class TListItem {
public:
    TListItem(T* value);
    TListItem(const std::shared_ptr<T>& value);
    
    std::shared_ptr<T> getValue();
    std::shared_ptr<TListItem<T>> getNext();
    void setNext(std::shared_ptr<TListItem<T>> next);
    void PushBack(std::shared_ptr<TListItem<T>> next);
    
    virtual ~TListItem();
private:
    std::shared_ptr<T> _value;
    std::shared_ptr<TListItem> _next;

};

#endif
