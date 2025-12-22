#include <iostream>
#include <fstream>
#include <string>

std::string replaceAll(const std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return str;
    
    std::string result = str;
    size_t pos = 0;
    
    while ((pos = result.find(from, pos)) != std::string::npos) {
        result.erase(pos, from.length());
        result.insert(pos, to);
        pos += to.length();
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }
    
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];
    
    if (s1.empty()) {
        std::cerr << "Error: s1 cannot be empty" << std::endl;
        return 1;
    }
    
    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    
    std::string outputFilename = filename + ".replace";
    std::ofstream outputFile(outputFilename.c_str());
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not create output file " << outputFilename << std::endl;
        inputFile.close();
        return 1;
    }
    
    std::string line;
    while (std::getline(inputFile, line)) {
        std::string modifiedLine = replaceAll(line, s1, s2);
        outputFile << modifiedLine << std::endl;
    }
    
    inputFile.close();
    outputFile.close();
    
    std::cout << "File processed successfully. Output saved to " << outputFilename << std::endl;
    return 0;
}
