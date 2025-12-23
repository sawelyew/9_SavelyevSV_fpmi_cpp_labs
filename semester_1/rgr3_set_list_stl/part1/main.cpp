#include <iostream>
#include <set>
#include <exception>

std::set<int> EratosthenesSieve(int n){
    std::set<int> prime_nums;
    for (int i = 2; i <= n; ++i) {
        prime_nums.insert(i);
    }

    for (int j=2; pow(j,2) <= n; ++j){

        if (prime_nums.find(j) == prime_nums.end()) continue;

        int multiple = pow(j, 2);
        while(multiple <= n){
            prime_nums.erase(multiple);
            multiple+=j;
        }
    }
    return prime_nums;
}

void PrintSet(const std::set<int> &set){
    std::cout << "{";
    for (int elem: set){
        std::cout << " " << elem << " ";
    }
    std::cout << "}" << std::endl;
}


int main() {

    // your code goes here
    try{
        int N;
        std::cout << "Введите число N, до которого будут находиться простые числа: " << std::endl;
        if (!(std::cin >> N)){
            throw std::runtime_error("Ошибка! Неверно введено N.");
        }
        if (N <= 1){
            throw std::out_of_range("Ошибка! Число N должно быть натуральным и больше 1.");
        }
        std::set<int> prime_nums = EratosthenesSieve(N);
        if (prime_nums.size() != 0){
            std::cout << "Простые числа до N: " << std::endl;
            PrintSet(prime_nums);
        }
        else{
            std::cout << "Не удалось найти простые числа." << std::endl;
        }
        return 0;
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } 
    catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}