#ifndef _TREE_H
#define _TREE_H

//super Tree class
//works as interface of BST and AVL
template <typename T>
class Tree {
public:

	virtual void insert(T& x) = 0;

	virtual void remove(T& x) = 0;

	virtual T& getRef(T x) = 0;

	virtual ~Tree() {}
	
};

#endif