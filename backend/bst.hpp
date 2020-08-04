#ifndef _BST_H
#define _BST_H

#include "tree.hpp"
#include <algorithm>

template <typename T>
class bstBase: public Tree<T> {
public:
	struct node {
		T key;
		node *left = nullptr;
		node *right = nullptr;
		node(T k) : key(k) {}
	};

	//root node
	node *root = nullptr;

	//insert
	void insert(const T& x)
	{
		root = insertUtil(root, x);
	}

	//remove
	void remove(const T& x)
	{
		root = removeUtil(root, x);
	}

	//search in range (count)
	int search(const T& from, const T& to) const{
		return searchUtil(root, from, to);
	}

	//destructor
	virtual ~bstBase() {
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

	//search in range (count)
	int searchUtil(node *current, const T& from, const T& to) const
	{
		if (!current) //empty current root
			return 0;

		T k = current->key;

		if (k >= from && k <= to)//fall in range
		{
			return 1 + searchUtil(current->left, from, to) +
				searchUtil(current->right, from, to);
		}
		else if (k < from) //left outside of range [from:to]
		{
			return searchUtil(current->right, from, to);
		}
		else //right outside of range [from:to]
		{
			return searchUtil(current->left, from, to);
		}
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