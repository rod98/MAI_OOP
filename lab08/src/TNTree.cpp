#include <string>
#include <memory>
#include <exception>

#include "TNTree.h"
#include "TNTreeItem.h"

template <class T>
void TNTree<T>::push(std::shared_ptr<T> &ptr) {
	Insert("0", std::to_string(sz), ptr);
}

template <class T>
void TNTree<T>::push(std::shared_ptr<T>&& ptr) {
	Insert("0", std::to_string(sz), ptr);
}

template <class T> void TNTree<T>::sort() {
    if (size() > 1) {
        std::shared_ptr<T> middle = pop();
        TNTree<T> left, right;

        while (!empty()) {
            std::shared_ptr<T> item = pop();
            if (*item < *middle) {
                left.push(item);
            } else {
                right.push(item);
            }
        }

        left.sort();
        right.sort();

        while (!left.empty())
			push(left.pop_last());
        push(middle);
        while (!right.empty())
			push(right.pop_last());
  
    }
}

template<class T > std::future<void> TNTree<T>::sort_in_background() {
    std::packaged_task<void(void) > task(std::bind(std::mem_fn(&TNTree<T>::sort_parallel), this));
    std::future<void> res(task.get_future());
    std::thread th(std::move(task));
    th.detach();
    return res;
}

template <class T> void TNTree<T>::sort_parallel() {
    if (size() > 1) {
        std::shared_ptr<T> middle = pop_last();
        TNTree<T> left, right;

        while (!empty()) {
            std::shared_ptr<T> item = pop_last();
            if (*item < *middle) {
                left.push(item);
            } else {
                right.push(item);
            }
        }

        std::future<void> left_res = left.sort_in_background();
        std::future<void> right_res = right.sort_in_background();

        left_res.get();

        while (!left.empty())
			push(left.pop_last());
        push(middle);
        
        right_res.get();
        while (!right.empty())
			push(right.pop_last());

    }
}

template <class T>
std::shared_ptr<T> TNTree<T>::pop() {
	std::shared_ptr<T> vp = nullptr;
	
	if (head && size()) {
		std::shared_ptr<TNTreeItem<T>> titem = FindNode(head, std::to_string(size() - 1));

		if (titem) {
			//std::cout << titem << "??\n";
			std::string did = titem->getID();
			vp = titem->getFigure();
			Remove(did);
		}
	}

	return vp;
}

template <class T>
std::shared_ptr<T> TNTree<T>::pop_last() {
	std::shared_ptr<T> vp = nullptr;
	
	if (head && size()) {
		//std::cout << head << "??\n";
		std::string did = head->getID();
		vp = head->getFigure();
		Remove(did);

		//std::cout << size() << "\n";
	}

	return vp;
}

template <class T>
TNTree<T>::TNTree() { //our tree is alive and well
	sz = 0;
    head = nullptr;
}

template <class T>
TNTree<T>::TNTree( TNTree<T>& orig) { //head = head of our trreee
	sz = 0;
    head = orig.head;
}
//done
template <class T>
void TNTree<T>::Insert(std::string parent_id, std::string id, std::shared_ptr<T> &figure) {
	sz++;
	
    if (!this->head) { //no item in head basically
        this->head = std::make_shared<TNTreeItem<T>>(id, figure); //in TNTreeItem.h
        return;
    }
    else { //oh my there is some stuff here
        std::shared_ptr<TNTreeItem<T>> parent_node = FindNode(this->head, parent_id); //so we look for a parent of where to put it
        if (parent_node) { //if there is an id for a parent
            if (!parent_node->GetSon()) { //if there is no son
                parent_node->SetSon(std::make_shared<TNTreeItem<T>>(id, figure)); //make a new one
            }
            else { //if there is a son
                std::shared_ptr<TNTreeItem<T>> brother = parent_node->GetSon();
                while (brother->Next()) {
                    brother = brother->Next(); //used to be GetBrother
                } //make bro
                brother->SetBrother(std::make_shared<TNTreeItem<T>>(id, figure));
            }
        }
        else { //if there is no parent_id found
			PrintTree();
            std::cout << "Error: invaild parent_id " << parent_id << '\n';
        }
    }
}

template <class T>
size_t TNTree<T>::size() {
	return sz;
}

//done
template <class T>
std::shared_ptr<TNTreeItem<T>> TNTree<T>::FindNode(std::shared_ptr<TNTreeItem<T>> treeItem, std::string id) { //find a pointer to our item
    if (treeItem->getID() == id) { //if our item has id we our looking for
        return treeItem;
    }
    if (treeItem->GetSon()) { //if our item has a son
        std::shared_ptr<TNTreeItem<T>>tr = FindNode(treeItem->GetSon(), id); //let's take a look at his son as an item
        if (tr != nullptr) { //success hence tr is what we are looking for
            return tr;
        }
    }
    if (treeItem->Next()) { //same as with son, but going through brothers
        std::shared_ptr<TNTreeItem<T>> tr = FindNode(treeItem->Next(), id);
        if (tr != nullptr) {
            return tr;
        }
    }
    return nullptr;
}

template <class T>
void TNTree<T>::SetNull(std::shared_ptr<TNTreeItem<T>> t) {//pointer to an item is nullptr
    t = nullptr;
}

template <class T>
bool TNTree<T>::empty()  { //empty treetio has a head of nullptr
    //return head == nullptr;
    return !sz;
}

template <class T>
void TNTree<T>::Des() {
	head = head->GetSon();

	if (head) {
		std::shared_ptr<TNTreeItem<T>> ptr = head->GetBrother();

		while (ptr) {
			std::shared_ptr<T> vp = ptr->getFigure();
			std::string id = ptr->getID();
			
			node_remove(ptr, id);
			sz--;
			Insert(head->getID(), id, vp);
			
			ptr = ptr->GetBrother();
		}
	}
}

template <class T>
void TNTree<T>::node_remove(std::shared_ptr<TNTreeItem<T>> treeItem, std::string id) { //let's deletio our node
    if (treeItem->GetSon()) { //if there are sons we have to delete them as well
        if (treeItem->GetSon()->getID() == id) { //id of the son is the id we are looking for
            std::shared_ptr<TNTreeItem<T>> tr = treeItem->GetSon();
            treeItem->SetSon(treeItem->GetSon()->Next()); //use to be GetBrother() getting rid of the brothers
            SetNull(tr->Next());// = nullptr;
			//delete tr ! nope, cause shared_ptr
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
            SetNull(tr->Next());// = nullptr;
            //delete tr; hohoho you know what i mean nudgenudge winkwink
            return;
        }
        else {
            TNTree<T>::node_remove(treeItem->Next(), id); //get bro!!!
        }
    }
}

template <class T>
std::shared_ptr<TNTreeItem<T>> TNTree<T>::getHead() {//get pointer to a head of a tree
    return this->head;
}

template <class T>
void TNTree<T>::Remove(std::string id) { //remove by id
	sz--;
    if (head->getID() == id) {
        TNTree<T>::Des();
    } else {
        TNTree<T>::node_remove(head, id);
   }
}

template <class T>
void TNTree<T>::PrintTree() { 
    if (this->head != nullptr) {
		print_nodes(this->head, 0);
	}
}

//done
template <class T>
void TNTree<T>::print_nodes(std::shared_ptr<TNTreeItem<T>> treeItem, size_t num)  {
	if (treeItem) {
        for (int i = 0; i < num; ++i)
            printf("   ");
        
        std::cout << *treeItem << '\n';
        
        if (treeItem->GetSon())
            print_nodes(treeItem->GetSon(), num + 1);
        if (treeItem->Next())
            print_nodes(treeItem->Next(), num);
    }	
}

template <class T>
void TNTree<T>::PrintItem(std::string id) {//let's print our item
    std::shared_ptr<TNTreeItem<T>> tmp = FindNode(this->head, id); //getting our pointer
    if(tmp) { //if there is a pointer
		std::cout << tmp->getFigure() << std::endl;
    }
    //delete tmp; ohh boii shared_ptr
}

template <class T>
TIterator <TNTreeItem<T>, T> TNTree<T>::begin() {
	if (head) { //if there is a head
		return TIterator<TNTreeItem<T>, T>(head);
	}
	else {
		return TIterator<TNTreeItem<T>, T>(nullptr);
	}	
}

template <class T>
TIterator <TNTreeItem<T>, T> TNTree<T>::end() {
	return TIterator<TNTreeItem<T>, T>(nullptr);	
}

template<class U>
std::ostream& operator<<(std::ostream& os,  TNTree<U> &obj) {
	obj.PrintTree();
	return os;
}

#include "figure.h"
template class TNTree<Figure>;
template std::ostream& operator<<(std::ostream& os,  TNTree<Figure> &obj);
