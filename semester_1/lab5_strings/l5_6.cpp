#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> SplitText(const std::string& text, const std::string& delimeters) {
    
    std::vector<std::string> words;

    std::string::size_type beg_index = 0;
    std::string::size_type end_index = text.find_first_of(delimeters, beg_index);
    
    while (beg_index != std::string::npos) {
    
        std::string word = text.substr(beg_index, end_index - beg_index);
        if (!word.empty()) {
            words.push_back(word);
        }

        beg_index = text.find_first_not_of(delimeters, end_index);
        end_index = text.find_first_of(delimeters, end_index + 1);
    }

    return words;
}

bool IsEvenNumber(std::string text){
    if (text.find_first_not_of("0123456789") == std::string::npos){
        if(std::stoi(text) % 2 == 0) return true;
        else return false;
    }
    else{
        return false;
    }
}

std::string FindNumbers(const std::vector<std::string>& vector) {
    std::string nums;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (IsEvenNumber(vector[i])){
            nums += vector[i];
            if(!(i == (vector.size() - 1))){
                nums += ",,";
            }
        }
    }
    return nums;
}


int main() {
    std::string text;
    std::string delimeters = " ,.?!:;";

    std::cout << "Введите строку: " << std::endl;
    if (!(std::getline(std::cin, text))){
        throw "Не удалось прочитать строку";
    }
    try {
    std::vector<std::string> words = SplitText(text, delimeters);
    if (words.size() == 0){
        throw "Your string is empty.";
    }
    
    std::string nums = FindNumbers(words);
    if (nums.size() == 0){
        throw "No one even number has been founded.";
    }

    std::cout << "Четные числа из исходной строки: " << nums << std::endl;
    }
    catch(const char* msg){
        std::cerr << msg << std::endl;
    }
    return 0;
}