#include <iostream>
#include <string>

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



void PrintVector(const std::vector<std::string>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << ' ';
    }
    std::cout << std::endl;
}


int main() {

    std::string text;

    std::cout << "Введите строку: " << std::endl;
    std::getline(std::cin, text);


    std::string delimeters = " ,.?!:;";
    std::vector<std::string> words = SplitText(text, delimeters);


    return 0;
}