#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <fstream>

template <class Container>
void split(const std::string& str, Container& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

std::string combineLines(const std::vector<std::string> strs, const std::vector<bool> mask, char delim = '\t'){
    std::string line = "";
    bool first = true;
    for(int i = 0; i < strs.size(); i++){
        if(mask[i]){
            if(!first){
                line += '\t';
            }
            line += strs[i];
            first = false;
        }
    }
    return line;
}

int main(int argc, char** argv){
    if(argc == 1)
        return 0;
    std::string filename = argv[1];
    std::ifstream inFile(filename);
    std::string newFilename = "newData.tsv";
    std::vector<std::string> roundTypes = {"222", "333", "333bf", "333oh", "444", "444bf", "555", "555bf", "666", "777"};
    std::vector<bool> releventColumns = {0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0};

    std::ofstream outFile(newFilename);
    unsigned int numLines = 0;
    std::string line;

    std::getline(inFile, line);
    std::vector<std::string> splits;
    split<std::vector<std::string>>(line, splits, '\t');
    outFile << combineLines(splits, releventColumns) << '\n';

    while(std::getline(inFile, line)){
        splits.clear();
        split<std::vector<std::string>>(line, splits, '\t');
        std::string type = splits[1];
        if(std::find(roundTypes.begin(), roundTypes.end(), type) != roundTypes.end()){
            numLines++;
            outFile << combineLines(splits, releventColumns) << '\n';
        }

        if((numLines + 1) % 10000 == 0){
            std::cout << numLines + 1 << " lines in" << std::endl;
        }
    }
    inFile.close();
    outFile.close();
    std::cout << "There are " << numLines << " lines.";
}