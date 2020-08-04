#ifndef _BST_H
#define _BST_H

#include "tree.hpp"
#include <algorithm>
#include <stdexcept>

template <typename T>
class bst : public Tree<T> {
	struct node {
		T key;
		node *left = nullptr;
		node *right = nullptr;
		node(T k) : key(k) {}
	};

	node *root = nullptr;
public:

	void insert(T& x)
	{
		root = insertUtil(root, x);
	}

	void remove(T& x)
	{
		root = removeUtil(root, x);
	}

	T& getRef(T x){
		return getRefUtil(root, x);
	}

	//destructor
	virtual ~bst() {
		clear(root);
	}

private:

	//recursive insert helper method
	node *insertUtil(node *head, T x)
	{
		if (!head) {

			node *temp = new node(x);
			return temp;
		}
		if (x < head->key)
			head->left = insertUtil(head->left, x);
		else if (x > head->key)
			head->right = insertUtil(head->right, x);
		
		return head;
	}

	//recursive remove helper method
	node *removeUtil(node *head, T x)
	{
		if (!head)
			return head;
		if (x < head->key) {
			head->left = removeUtil(head->left, x);
		}
		else if (x > head->key) {
			head->right = removeUtil(head->right, x);
		}
		else {
			node *r = head->right;
			if (head->right == NULL) {
				node *l = head->left;
				delete (head);
				head = l;
			}
			else if (!head->left) {
				delete (head);
				head = r;
			}
			else {
				while (r->left)
					r = r->left;
				head->key = r->key;
				head->right = removeUtil(head->right, r->key);
			}
		}
		
		return head;
	}

	// return a reference to an element equaling x
	T& getRefUtil(node* current, T x){
		if(current == nullptr)
			throw std::out_of_range("This data is not in the tree.");
		
		if(x == current->key)
			return current->key;
		if(x > current->key)
			return getRefUtil(current->right, x);
		else
			return getRefUtil(current->left, x);
	}

	// clear avl
	void clear(node* current) {

		if (current != NULL)
		{
			//clear left sub tree
			clear(current->left);

			//clear right sub tree
			clear(current->right);

			//delete current node
			delete current;
		}
	}
};

#endif