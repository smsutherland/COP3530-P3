#include "avl.hpp"
#include "bst.hpp"
#include "AVLMap.hpp"
#include "BSTMap.hpp"
#include "Bucket.hpp"
#include "SimpleDate.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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

void loadData(string eventID, string dateLower, string dateUpper, int timeLower, int timeUpper, bool singleOrAverage, bool AVLOrBST);
vector<Bucket> generateBuckets(int lower, int upper, string eventID);
void loadCompetitions(Map<string, SimpleDate>* compMap);
vector<string> split(const std::string& str, char delim = '\t');

//main function to start C++ application
int main(int argc, char** argv) {
	if(argc == 1){
		cout << "Test Map with AVL" << endl;
		test(new AVLMap<int, string>());

		cout << endl << "Test Map with BST" << endl;
		test(new BSTMap<int, string>());
	}else{
		string eventID = argv[1];
		string dateLower = argv[2];
		string dateUpper = argv[3];
		int timeLower = stoi(argv[4]);
		int timeUpper = stoi(argv[5]);
		bool singleOrAverage = stoi(argv[6]);
		bool AVLOrBST = stoi(argv[7]);
		cout << eventID << dateLower << dateUpper << timeLower << timeUpper << singleOrAverage << AVLOrBST << endl;
		loadData(eventID, dateLower, dateUpper, timeLower, timeUpper, singleOrAverage, AVLOrBST);
	}
	return 0;
}

void loadData(string eventID, string dateLower, string dateUpper, int timeLower, int timeUpper, bool singleOrAverage, bool AVLOrBST){
	ifstream timesFile("times.tsv");
	Map<Bucket, unsigned int>* histogramData = nullptr;
	Map<string, SimpleDate>* competitionDates = nullptr;
	if(AVLOrBST){
		histogramData = new AVLMap<Bucket, unsigned int>();
		competitionDates = new AVLMap<string, SimpleDate>();
	}
	else{
		histogramData = new BSTMap<Bucket, unsigned int>();
		competitionDates = new BSTMap<string, SimpleDate>();
	}
	vector<Bucket> buckets = generateBuckets(timeLower, timeUpper, eventID);
	loadCompetitions(competitionDates);
}

vector<Bucket> generateBuckets(int lower, int upper, string eventID){
	if(upper == -1 || lower == -1){
		lower = 0;
		if(eventID == "222"){
			upper = 1000;
		}
		else if(eventID == "333"){
			upper = 1000;
		}
		else if(eventID == "333bf"){
			upper = 3000;
		}
		else if(eventID == "333oh"){
			upper = 1500;
		}
		else if(eventID == "444"){
			upper = 4000;
		}
		else if(eventID == "444bf"){
			upper = 12000;
		}
		else if(eventID == "555"){
			upper = 6000;
		}
		else if(eventID == "555bf"){
			upper = 60000;
		}
		else if(eventID == "666"){
			upper = 9000;
		}
		else if(eventID == "777"){
			upper = 30000;
		}
	}
	vector<Bucket> buckets(10);
	float bucketSize = (upper - lower)/10;
	for(int i = 0; i < 10; i++){
		buckets.push_back(Bucket(lower + i*bucketSize, lower + (i+1)*bucketSize));
	}
	return buckets;
}

void loadCompetitions(Map<string, SimpleDate>* compMap){
	ifstream compFile("competitions.tsv");
	if(compFile.is_open()){
		string line;
		vector<string> parts;
		getline(compFile, line); // pass first line w/ column headers
		while(getline(compFile, line)){
			parts = split(line);
			string id = parts[0];
			int year = stoi(parts[1]);
			int month = stoi(parts[2]);
			int day = stoi(parts[3]);
			(*compMap)[id] = SimpleDate(year, month, day);
		}
	}
}

vector<string> split(const std::string& str, char delim){
	vector<string> splits;
    std::stringstream ss(str);
    std::string part;
    while (std::getline(ss, part, delim)) {
        splits.push_back(part);
    }
	return splits;
}