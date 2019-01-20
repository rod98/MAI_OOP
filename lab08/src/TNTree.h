#ifndef TNTREE_H
#define TNTREE_H

#include <iostream>
#include <string>
#include <memory>
#include <future>
#include <functional>
#include "TNTreeItem.h"
#include "TIterator.h"

template <class T>
class TNTree {
	public:
		TNTree();
		TNTree( TNTree<T>& orig);

		void Insert(std::string parent_id, std::string id, std::shared_ptr<T> &figure);
		void Remove(std::string id); 
		void PrintTree() ;
		void PrintItem(std::string id);
		void SetNull(std::shared_ptr<TNTreeItem<T>> treeItem);
		void Des();

		std::shared_ptr<TNTreeItem<T>> getHead();
		bool empty() ;
		size_t size();

		TIterator<TNTreeItem<T>, T> begin();
		TIterator<TNTreeItem<T>, T> end();

		virtual ~TNTree() {};

		template<class U>friend std::ostream &operator<<(std::ostream os,  TNTree<U> &tree);

		void push(std::shared_ptr<T>&  ptr);
		void push(std::shared_ptr<T>&& ptr);
		std::shared_ptr<T> pop();
		std::shared_ptr<T> pop_last();

		void sort();
		void sort_parallel();

	private:
		std::shared_ptr<TNTreeItem<T>> head; 
		std::shared_ptr<TNTreeItem<T>> FindNode(std::shared_ptr<TNTreeItem<T>> node, std::string id);
		std::future<void> sort_in_background(); 
		void print_nodes(std::shared_ptr<TNTreeItem<T>> treeItem, size_t num) ;
		void node_remove(std::shared_ptr<TNTreeItem<T>> treeItem, std::string id);
		size_t sz;
};
#endif /* TNTREE_H */
