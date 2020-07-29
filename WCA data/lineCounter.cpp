#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv){
    if(argc == 1)
        return 0;
    std::string filename = argv[1];
    std::ifstream inFile(filename);
    unsigned int numLines = 0;
    while(inFile.ignore(10000000, '\n'))
        numLines++;
    std::cout << "There are " << numLines << " lines.";
}