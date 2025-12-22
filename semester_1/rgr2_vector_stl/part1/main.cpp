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

// std::string FindNumbers(const std::vector<std::string>& vector) {
//     std::string nums;
//     for (size_t i = 0; i < vector.size(); ++i) {
//         if (IsNumber(vector[i])){
//             nums += vector[i];
//             if(!(i == (vector.size() - 1))){
//                 nums += ",,";
//             }
//         }
//     }
//     return nums;
// }

bool IsNumber(std::string text){
    if (text.find_first_not_of("0123456789") == std::string::npos){
        return true;
    }
    else{
        return false;
    }
}

int VectorElemSum(const std::vector<int> &vector){
    int sum = 0;
    for (size_t i = 0; i < vector.size(); ++i){
        sum += vector[i];
    }
    return sum;
}

std::vector<int> FillVectorWithInts(const std::vector<std::string> &vector){
    std::vector<int> nums;
    for(int i=0; i<vector.size(); ++i){
        if(IsNumber(vector[i])){
            nums.push_back(std::stoi(vector[i]));
        }
        else{
            throw "Ошибка! Все элементы вектора должны быть целыми числами.";
        }
    }
    return nums;
}

void PrintVector(const std::vector<int> &vector){
    for(int i=0; i<vector.size(); ++i){
            std::cout << vector[i] << "\t";
    }
    std::cout << "\n";
}

int FindCountOfElementsWithEqVal(const std::vector<int> &vector, int value){
    int count = 0;
    for(int i=0; i<vector.size(); ++i){
        if (vector[i] == value){
            count++;
        }
    }
    return count;
}

void ChangeAllZeroElemWAvgVal(std::vector<int> &vector, int avg_val){
    for (int i=0; i<vector.size(); ++i){
        if(vector[i]==0){
            vector[i] = avg_val;
        }
    }
}

int CalcSumOfElemsInInterval(std::vector<int> vector, int a, int b){
    int sum = 0;
    for (int i=0; i<vector.size(); ++i){
        if (vector[i] >= a && vector[i] < b){
            sum += vector[i];
        }
    }
    return sum;
}

void AddToEachElemSumOfElemsInInterval(std::vector<int> &vector, int sum){
    for (int i=0; i<vector.size(); ++i){
        vector[i] += sum;
    }
}

int CalcDifMinAndMaxVal(std::vector<int> vector){
    int min = vector[0];
    int max = vector[0];

    for (int i=0; i<vector.size(); ++i){
        if (min>vector[i]){
            min = vector[i];
        }
        if(max<vector[i]){
            max = vector[i];
        }
    }
    return (max-min);
}

void ChangeElemWEvenValToDiffMinAndMaxVal(std::vector<int> &vector, int diff){
    for(int i=0; i<vector.size(); ++i){
        if (std::abs(vector[i]) % 2 == 0){
            vector[i] = diff;
        }
    }
}

void EraseElemsWithEqAbs(std::vector<int> &vect){
    for(int i=0; i<vect.size(); ++i){
        for(int j=i+1; j<vect.size(); j++){
            if(abs(vect[i]) == abs(vect[j])){
                vect.erase(vect.begin() + j);
                --j;
            }
        }
    }
}

int main() {
    try {
        std::string delimeters = " ,!><?";

        std::vector<int> vect;
        std::string input;
        std::cout << "Введите элементы вектора(целые числа) через запятую: \n";
        std::cin >> input;

        if (input.size() == 0){
            throw "Ошибка! Пустой ввод.";
        }

        int input_num;
        std::cout << "Введите число, с которым будут сравниваться элементы вектора: ";
        if (!(std::cin >> input_num)){
            throw "Ошибка. Не удалось ввести число, с которым будут сравниваться элементы вектора.";
        }

        int a, b;
        std::cout << "Введите границы интервала: ";
        if(!(std::cin >> a >> b)){
            throw "Ошибка! Неверный ввод границ интервала.";
        }

        if (a<b){
            std::swap(a,b);
        }

        std::vector<std::string> splitted_elements = SplitText(input, delimeters);
        vect = FillVectorWithInts(splitted_elements);

        int sum_of_elems = VectorElemSum(vect);
        int avg_val = sum_of_elems/vect.size();
        int count_eq_el = FindCountOfElementsWithEqVal(vect, input_num);
        

        std::cout << "Полученный вектор: " << std::endl;
        PrintVector(vect);

        std::cout << "Сумма элементов вектора равна " << sum_of_elems << std::endl;

        std::cout << "Общее количество чисел в векторе равно " << vect.size() << std::endl;

        std::cout << "Количество чисел, равных заданному: " << count_eq_el << std::endl;


        // количество чисел, удовлетворяющих условию, например, «больше, чем n»
    

        ChangeAllZeroElemWAvgVal(vect, avg_val);
        std::cout << "Полученный вектор после замены нулей средним арифметическим: " << std::endl;
        PrintVector(vect);

        int sum_of_elem_in_interval = CalcSumOfElemsInInterval(vect, a, b);
        AddToEachElemSumOfElemsInInterval(vect, sum_of_elem_in_interval);
        std::cout << "Полученный вектор после добавления к каждому элементу вектора суммы всех чисел из интервала |a, b|: " << std::endl;
        PrintVector(vect);

        int diff_min_and_max_val = CalcDifMinAndMaxVal(vect);
        ChangeElemWEvenValToDiffMinAndMaxVal(vect, diff_min_and_max_val);
        std::cout << "Полученный вектор после замены четных чисел на разность min и max элементов вектора: " << std::endl;
        PrintVector(vect);


        EraseElemsWithEqAbs(vect);
        std::cout << "Полученный вектор после удаления всех равных по модулю чисел, кроме первого из них: " << std::endl;
        PrintVector(vect);
        





    }
    catch(const char* msg){
        std::cerr << msg << std::endl;
    }

    return 0;
}