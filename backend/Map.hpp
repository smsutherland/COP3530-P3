#ifndef _MAP_H
#define _MAP_H

#include "Bucket.hpp"
#include "Tree.hpp"
#include <vector>

class Map {
public:

	//constructor
	//
	Map(Tree<int> *tree): mTree(tree){
	}

	//insert
	void insert(int x) {
		mTree->insert(x);
	}

	//remove
	void remove(int x) {
		mTree->remove(x);
	}

	//search
	std::vector<Bucket> search(int from, int to);

	//destructor
	virtual ~Map() {
		delete mTree;
	}
private:
	Tree<int>* mTree;
};

//search
std::vector<Bucket> Map::search(int from, int to){
	
	std::vector<Bucket> buckets; //10 buckets

	//create 10 buckets
	double width = (double)(1 + (to - from - 9)) / 10.0;

	int low = from;
	for (size_t i = 1; i <= 10; i++)
	{		
		int high = (int)(low + width);
		if (i == 10)
		{
			high = to;
		}

		buckets.push_back(Bucket(low, high, mTree->search(low, high)));
		low = high + 1;
	}

	return buckets;
}

#endif