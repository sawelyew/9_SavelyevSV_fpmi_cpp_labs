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

bool IsNumber(std::string text){
    if (std::stoi(text))
        return true;
    else 
        return false;
}

std::string FindNumbers(const std::vector<std::string>& vector) {

    std::string nums;
    for (size_t i = 0; i < vector.size(); ++i) {
        if (IsNumber(vector[i])){
            nums += vector[i];
            while(i < vector.size()-1)
                nums += ",,";
        }
    }
    return nums;
}


int main() {

    std::string text;

    std::cout << "Введите строку: " << std::endl;
    std::getline(std::cin, text);


    std::string delimeters = " ,.?!:;";
    std::vector<std::string> words = SplitText(text, delimeters);
    std::string nums = FindNumbers(words);
    std::cout << "Четные числа из исходной строки: " << nums << std::endl;
    return 0;
}