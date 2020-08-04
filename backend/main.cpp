#include "tree.hpp"
#include "avl.hpp"
#include "bst.hpp"
#include "map.hpp"
#include "Bucket.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//test map with 
void test(Tree<int>* tree) {

	Map map(tree);

	ifstream input;
	input.open("newData.tsv");
	string line;//a line

	string eventId;
	int best, average, value1, value2, value3, value4, value5;

	//eventId best average value1 value2 value3 value4 value5
	getline(input, line);//ignore the first line
	if (input.good()) {
		
		while (input >> eventId >> best >> average >> value1 >> value2 >> value3 >> value4 >> value5)
		{
			map.insert(best);
		}
	}

	vector<Bucket> results = map.search(1968, 2452);

	for (vector<Bucket>::iterator it = results.begin(); it != results.end(); ++it)
	{
		cout << it->from << "-" << it->to << ": " << it->count << endl;
	}
}


//main function to start C++ application
int main() {

	cout << "Test Map with AVL" << endl;
	test(new avlBase<int>());

	cout << endl << "Test Map with BST" << endl;
	test(new bstBase<int>());

	return 0;
}

