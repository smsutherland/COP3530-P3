#include "avl.hpp"
#include "bst.hpp"
#include "AVLMap.hpp"
#include "BSTMap.hpp"
#include "Bucket.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//test map with 
void test(Map<int, string>* map) {

	for(int i = 0; i < 10; i++){
		string str = "";
		for(int j = 0; j < i; j++){
			str += (char)(i + 97);
		}

		(*map)[i] = str;
	}
	for(int i = 0; i < 10; i++){
		cout << (*map)[i] << endl;
	}
}


//main function to start C++ application
int main() {

	cout << "Test Map with AVL" << endl;
	test(new AVLMap<int, string>());

	cout << endl << "Test Map with BST" << endl;
	test(new BSTMap<int, string>());

	return 0;
}

