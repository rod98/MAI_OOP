#include <string>
#include <memory>
#include <exception>

#include "TNTree.h"
#include "TNTreeItem.h"

template <class T>
void TNTree<T>::push(std::shared_ptr<T> &ptr) {
	std::lock_guard<std::recursive_mutex> lock(tree_mutex);
	Insert("0", std::to_string(sz), ptr);
}

template <class T>
void TNTree<T>::push(std::shared_ptr<T>&& ptr) {
	std::lock_guard<std::recursive_mutex> lock(tree_mutex);
	Insert("0", std::to_string(sz), ptr);
}

template <class T>
std::shared_ptr<T> TNTree<T>::pop() {
	std::shared_ptr<T> vp = nullptr;

	std::lock_guard<std::recursive_mutex> lock(tree_mutex);
	
	if (head && size()) {
		std::shared_ptr<TNTreeItem<T>> titem = FindNode(head, std::to_string(size() - 1));

		if (titem) {
			std::string did = titem->getID();
			vp = titem->getValue();
			Remove(did);
		}
	}

	return vp;
}

template <class T>
std::shared_ptr<T> TNTree<T>::pop_last() {
	std::shared_ptr<T> vp = nullptr;
	
	if (head && size()) {
		std::string did = head->getID();
		vp = head->getValue();
		Remove(did);
	}

	return vp;
}

template <class T>
TNTree<T>::TNTree() { 
	sz = 0;
    head = nullptr;
}

template <class T>
TNTree<T>::TNTree(TNTree<T>& orig) {
	sz = 0;
    head = orig.head;
}

template <class T>
void TNTree<T>::Insert(std::string parent_id, std::string id, std::shared_ptr<T> &figure) {
	sz++;
	std::lock_guard<std::recursive_mutex> lock(tree_mutex);
	
    if (!this->head) { 
        this->head = std::make_shared<TNTreeItem<T>>(id, figure, &tree_mutex); 
        return;
    }
    else {
        std::shared_ptr<TNTreeItem<T>> parent_node = FindNode(this->head, parent_id);
        if (parent_node) { 
            if (!parent_node->GetSon()) { 
                parent_node->SetSon(std::make_shared<TNTreeItem<T>>(id, figure, &tree_mutex));
            }
            else { 
                std::shared_ptr<TNTreeItem<T>> brother = parent_node->GetSon();
                while (brother->Next()) {
                    brother = brother->Next(); 
                } 
                brother->SetBrother(std::make_shared<TNTreeItem<T>>(id, figure, &tree_mutex));
            }
        }
        else { 
			PrintTree(std::cout);
            std::cout << "Error: invaild parent_id " << parent_id << '\n';
        }
    }
}

template <class T>
size_t TNTree<T>::size() {
	return sz;
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTree<T>::FindNode(std::shared_ptr<TNTreeItem<T>> treeItem, std::string id) { 
    if (treeItem->getID() == id) { 
        return treeItem;
    }
    if (treeItem->GetSon()) { 
        std::shared_ptr<TNTreeItem<T>>tr = FindNode(treeItem->GetSon(), id); 
        if (tr != nullptr) { 
            return tr;
        }
    }
    if (treeItem->Next()) { 
        std::shared_ptr<TNTreeItem<T>> tr = FindNode(treeItem->Next(), id);
        if (tr != nullptr) {
            return tr;
        }
    }
    return nullptr;
}

template <class T>
void TNTree<T>::SetNull(std::shared_ptr<TNTreeItem<T>> t) {
    t = nullptr;
}

template <class T>
bool TNTree<T>::empty()  {
    return !sz;
}

template <class T>
void TNTree<T>::delHead() {
	head = head->GetSon();

	if (head) {
		std::shared_ptr<TNTreeItem<T>> ptr = head->GetBrother();

		while (ptr) {
			std::shared_ptr<T> vp = ptr->getValue();
			std::string id = ptr->getID();
			
			node_remove(ptr, id);
			sz--;
			Insert(head->getID(), id, vp);
			
			ptr = ptr->GetBrother();
		}
	}
}

template <class T>
void TNTree<T>::node_remove(std::shared_ptr<TNTreeItem<T>> treeItem, std::string id) { 
    if (treeItem->GetSon()) { 
        if (treeItem->GetSon()->getID() == id) { 
            std::shared_ptr<TNTreeItem<T>> tr = treeItem->GetSon();
            treeItem->SetSon(treeItem->GetSon()->Next());
            SetNull(tr->Next());
            return;
        }
        else {
			TNTree<T>::node_remove(treeItem->GetSon(), id);
        }
    }
    if (treeItem->GetBrother()) {
        if (treeItem->GetBrother()->getID() == id) {
            std::shared_ptr<TNTreeItem<T>> tr = treeItem->Next();
            treeItem->SetBrother(treeItem->Next()->Next());
            SetNull(tr->Next());
            return;
        }
        else {
            TNTree<T>::node_remove(treeItem->Next(), id);
        }
    }
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTree<T>::getHead() {
    return this->head;
}

template <class T>
void TNTree<T>::Remove(std::string id) {
	std::lock_guard<std::recursive_mutex> lock(tree_mutex);
	sz--;
    if (head->getID() == id) {
        TNTree<T>::delHead();
    } else {
        TNTree<T>::node_remove(head, id);
   }
}

template <class T>
void TNTree<T>::PrintTree(std::ostream& os) { 

}

template <class T>
void TNTree<T>::print_nodes(std::shared_ptr<TNTreeItem<T>> treeItem, size_t num)  {
	if (treeItem) {
        for (int i = 0; i < num; ++i)
            printf("   ");
        
        if (treeItem->GetSon())
            print_nodes(treeItem->GetSon(), num + 1);
        if (treeItem->Next())
            print_nodes(treeItem->Next(), num);
    }	
}

template <class T>
void TNTree<T>::PrintItem(std::string id) {
    std::shared_ptr<TNTreeItem<T>> tmp = FindNode(this->head, id); 
    if(tmp) 
		std::cout << tmp->getValue() << std::endl;
}

template <class T>
TIterator <TNTreeItem<T>, T> TNTree<T>::begin() {
	return TIterator<TNTreeItem<T>, T>(head);	
}

template <class T>
TIterator <TNTreeItem<T>, T> TNTree<T>::end() {
	return TIterator<TNTreeItem<T>, T>(nullptr);	
}

template<class U>
std::ostream& operator<<(std::ostream& os,  TNTree<U> &obj) {
	for (auto i : obj)
		os << *i << std::endl;
	return os;
}

#include <functional>
#include "figure.h"
template class TNTree<Figure>;
template class TNTree<std::function<void ()>>;
template std::ostream& operator<<(std::ostream& os,  TNTree<Figure> &obj);
