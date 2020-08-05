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
	}
}

void loadData(string eventID, string dateLower, string dateUpper, int timeLower, int timeUpper, bool averageOrSingle, bool AVLOrBST);
void exportData(Map<Bucket, unsigned int>* data, vector<Bucket> buckets);
vector<Bucket> generateBuckets(int lower, int upper, string eventID);
void loadCompetitions(Map<string, SimpleDate>* compMap);
vector<string> split(const std::string& str, char delim = '\t');

//main function to start C++ application
int main(int argc, char** argv) {
	if(argc == 1){
		test(new AVLMap<int, string>());

		test(new BSTMap<int, string>());
	}else{
		string eventID = argv[1];
		string dateLower = argv[2];
		string dateUpper = argv[3];
		int timeLower = stoi(argv[4]);
		int timeUpper = stoi(argv[5]);
		bool averageOrSingle = stoi(argv[6]);
		bool AVLOrBST = stoi(argv[7]);
		loadData(eventID, dateLower, dateUpper, timeLower, timeUpper, averageOrSingle, AVLOrBST);
	}
	return 0;
}

//loads appropriate data from times and competitions.tsv
void loadData(string eventID, string dateLower, string dateUpper, int timeLower, int timeUpper, bool averageOrSingle, bool AVLOrBST){
	ifstream timesFile("..\\..\\backend\\times.tsv");
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

	for(unsigned int i = 0; i < buckets.size(); i++){
		(*histogramData)[buckets[i]];
	}

	bool usingDate = (dateLower != "-1") && (dateUpper != "-1");

	SimpleDate lower;
	SimpleDate upper;
	if(usingDate){
		loadCompetitions(competitionDates);
		lower = SimpleDate(dateLower);
		upper = SimpleDate(dateUpper);
	}


	if(timesFile.is_open()){
		string line;
		vector<string> parts;
		getline(timesFile, line); // pass first line w/ column headers
		while(getline(timesFile, line)){
			parts = split(line);

			if(parts[1] != eventID)
				continue;
			
			if(usingDate){
				SimpleDate date = (*competitionDates)[parts[0]];
				if((date < lower) || (date > upper))
					continue;
			}

			if(averageOrSingle){
				for(unsigned int i = 0; i < buckets.size(); i++){
					if(buckets[i].in(stoi(parts[2])) && stoi(parts[2]) > 0){
						(*histogramData)[buckets[i]]++;
					}
				}
			}
			else{
				for(unsigned int i = 0; i < buckets.size(); i++){
					for(int j = 3; j <= 7; j++){
						if(buckets[i].in(stoi(parts[j])) && stoi(parts[j]) > 0){
							(*histogramData)[buckets[i]]++;
						}
					}
				}
			}
		}
	}
	timesFile.close();

	exportData(histogramData, buckets);
}

//generates the buckets corresponding to the time range
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
	vector<Bucket> buckets(25);
	float bucketSize = (upper - lower)/(float)buckets.size();
	for(unsigned int i = 0; i < buckets.size(); i++){
		buckets[i] = (Bucket(lower + i*bucketSize, lower + (i+1)*bucketSize));
		Bucket b(lower + i*bucketSize, lower + (i+1)*bucketSize);
	}
	return buckets;
}

//creates the map from competition id to date
void loadCompetitions(Map<string, SimpleDate>* compMap){
	ifstream compFile("..\\..\\backend\\competitions.tsv");
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
	compFile.close();
}

//splits a string at each delim
vector<string> split(const std::string& str, char delim){
	vector<string> splits;
    std::stringstream ss(str);
    std::string part;
    while (std::getline(ss, part, delim)) {
        splits.push_back(part);
    }
	return splits;
}

//takes the time data map and turns it into a json
void exportData(Map<Bucket, unsigned int>* data, vector<Bucket> buckets){
	ofstream out("data\\HistogramOutput.json");
	if(out.is_open()){
		out << "[";
		for(unsigned int i = 0; i < buckets.size(); i++){
			if(i != 0)
				out << ",";
			
			out << "{";
			out << "\"bottom limit\": " << buckets[i].from << ",";
			out << "\"top limit\": " << buckets[i].to << ",";
			out << "\"height\": " << (*data)[buckets[i]];
			out << "}";
		}
		out << "]";
	}
	out.close();
}
