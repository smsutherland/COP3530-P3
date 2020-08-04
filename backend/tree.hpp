#ifndef _TREE_H
#define _TREE_H

//super Tree class
//works as interface of BST and AVL
template <typename T>
class Tree {
public:

	//insert
	virtual void insert(const T& x) = 0;

	//remove
	virtual void remove(const T& x) = 0;

	//search
	virtual int search(const T& from, const T& to) const = 0;

	//destructor
	virtual ~Tree() {
	}
	
};

#endif