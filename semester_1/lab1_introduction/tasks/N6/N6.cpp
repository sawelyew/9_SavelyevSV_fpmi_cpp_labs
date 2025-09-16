#include <iostream>

int main() {
    int n, i, sum=0;

    std::cout << "Введите число n" << std::endl;
    std::cin >> n;

    for (i=0; i<n*2; i++) {
        if (i%2 == 1) {
            sum += i;
        }
    }
    
    std::cout << "Сумма n нечетных чисел равна " << sum << std::endl;
    return 0;
}