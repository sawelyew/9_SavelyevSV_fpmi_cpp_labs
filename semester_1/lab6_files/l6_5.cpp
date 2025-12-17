#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int LongestPalSubLen(const std::string& string){
    int n = string.size();
    if (n == 0){
        return 0;
    }

    int best = 1;

    for (int center = 0; center < n; ++center){

        int left = center;
        int right = center;
        int len = 0;
        while (left >= 0 && right < n && string[left] == string[right]){
            len = right - left + 1;
            --left;
            ++right;
        }
        if (len>best) {
            best = len;
        }

        left = center;
        right = center + 1;
        len = 0;
        while (left >= 0 && right < n && string[left] == string[right]){
            len = right - left + 1;
            --left;
            ++right;
        }
        if (len>best) {
            best = len;
        }
    }
    return best;
}


int main() {
    try{
    setlocale(LC_ALL, "Russian");
    std::ifstream in;
    in.open("input.txt");
    std::string line;

    if (!in.is_open()){
        throw "Error. Couldn't open the file.";
    }

    if (!in.good()){
        throw "File is empty.";
    }

    int globalMax = 0;
    std::vector<std::string> strings;

    while(std::getline(in, line)){
        int currentLen = LongestPalSubLen(line);
        if (currentLen > globalMax) {
            globalMax = currentLen;
            strings.clear();
            strings.push_back(line);
        }
        else if (currentLen == globalMax){
            strings.push_back(line);
        }

    }

    std::cout << "Максимальная длина подстроки-палиндрома: " << globalMax << std::endl;
    std::cout << "Строки с данной длиной: \n";
    int limit = 10;
    if (strings.size() < limit){
        limit = strings.size();
    }
    
    for (int i=0; i < limit; ++i){
        std::cout << (i+1) << ". " << strings[i] << std::endl;
    }

    in.close();
    }
    catch (const char* msg){
        std::cerr << msg << std::endl;
    }
    return 0;
}