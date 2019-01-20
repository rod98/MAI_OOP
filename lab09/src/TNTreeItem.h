#ifndef TNTREEITEM_H
#define TNTREEITEM_H

#include <string>
#include <memory>
#include <mutex>

#include "TIterator.h"

template <class T> class TNTree;

template <class T>
class TNTreeItem : public std::enable_shared_from_this<TNTreeItem<T>> {
	public:
		TNTreeItem(std::recursive_mutex *parent);
		TNTreeItem(std::string id, std::shared_ptr<T> &figure, std::recursive_mutex *parent); 

		template <class U> friend std::ostream& operator<<(std::ostream& os,  TNTreeItem<U>& obj);

		void SetSon(std::shared_ptr<TNTreeItem<T>> son);
		void SetBrother(std::shared_ptr<TNTreeItem<T>> brother);
		
		std::shared_ptr<TNTreeItem<T>> GetSon();
		std::shared_ptr<TNTreeItem<T>> GetBrother(); 
		std::shared_ptr<T> getValue() ; 
		std::string getID(); 

		std::shared_ptr<TNTreeItem<T>> Begin();
		std::shared_ptr<TNTreeItem<T>> Next();

		virtual ~TNTreeItem() {};

		std::ostream& print(std::ostream os);

	private:
		std::string id; 
		std::shared_ptr<T> figure;

		std::shared_ptr<TNTreeItem<T>> son;
		std::shared_ptr<TNTreeItem<T>> brother;

		std::recursive_mutex *tree_mutex;
};

#endif  /* TNTREEITEM_H */
