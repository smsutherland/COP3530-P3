#pragma once
#include <algorithm>
#include <string>
template <typename T>
class avlBase : public Tree<T> {
public:
    struct node {
        T key;
        int height = 1;
        node *left = nullptr;
        node *right = nullptr;
        node(T k) : key(k) {}
    };
    node *root = nullptr;
    int n{};
    void insert(const T &x)
    {
        root = insertUtil(root, x);
    }
    void remove(const T &x)
    {
        root = removeUtil(root, x);
    }
    //return number of elements that fit the given range
    int search(const T &from, const T &to) const
    {
        return searchUtil(root, from, to);
    }
    template <typename UnaryOp>
    node *searchName(std::string &str, UnaryOp &op)
    {
        return searchNameUtil(root, str, op);
    }

private:
    int height(node *head)
    {
        if (!head) {
            return 0;
        }
        return head->height;
    }
    int maxLR(node *nd)
    {
        return std::max(height(nd->left), height(nd->right));
    }
    node *rightRotation(node *head)
    {
        node *newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + maxLR(head);
        newhead->height = 1 + maxLR(head);
        return newhead;
    }
    node *leftRotation(node *head)
    {
        node *newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + maxLR(head);
        newhead->height = 1 + maxLR(head);
        return newhead;
    }
    node *insertUtil(node *head, T x)
    {
        if (!head) {
            ++n;
            node *temp = new node(x);
            return temp;
        }
        if (x < head->key)
            head->left = insertUtil(head->left, x);
        else if (x > head->key)
            head->right = insertUtil(head->right, x);
        head->height = 1 + maxLR(head);
        int bal = height(head->left) - height(head->right);
        if (bal > 1) {
            if (x < head->left->key) {
                return rightRotation(head);
            }
            else {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }
        else if (bal < -1) {
            if (x > head->right->key) {
                return leftRotation(head);
            }
            else {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
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
        if (!head)
            return head;
        head->height = 1 + maxLR(head);
        int bal = height(head->left) - height(head->right);
        if (bal > 1) {
            if (x > head->left->key) {
                return rightRotation(head);
            }
            else {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }
        else if (bal < -1) {
            if (x < head->right->key) {
                return leftRotation(head);
            }
            else {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
    int searchUtil(node *current, const T &from, const T &to) const
    {
        if (!current) //empty current root
            return 0;
        T k = current->key;
        if (k >= from && k <= to) //fall in range
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
    //the op is supposed to return a specific string according to to the given *head
    template <typename unaryOP>
    node *searchNameUtil(node *head, std::string &str, unaryOP &op)
    {
        if (!head)
            return head;
        auto nm = op(head);
        if (nm == str)
            return head;
        if (nm > str)
            return searchNameUtil(head->left, str, op);
        if (nm < str)
            return searchNameUtil(head->right, str, op);
    }
};