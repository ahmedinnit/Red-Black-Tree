#include "Node.h"

template <class T>
class Tree
{
protected:
	Node<T>* root;
public:
	Tree();
	virtual void Insert(T) = 0;
	virtual bool Search(T,char&) = 0;
	virtual void InOrder(int) = 0;
	virtual void PreOrder(int) = 0;
	virtual void PostOrder(int) = 0;
	virtual void DisplayParent(T) = 0;			
	virtual void ReadFile() = 0;				 
	virtual void RemoveDuplicates() = 0;		 
	virtual void DestroyTree() = 0;				 
	~Tree();
};

template <class T>
Tree<T>::Tree()
{
	root = nullptr;
}

template <class T>
Tree<T>::~Tree()
{
	
}
