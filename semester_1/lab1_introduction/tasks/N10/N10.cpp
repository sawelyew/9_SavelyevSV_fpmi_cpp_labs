#include <iostream>

int main() {
    int number; 

    std::cout << "Введите шестизначное число: " << std::endl;
    std::cin >> number;

    int abc = (number / 1000); // Первые 3 цифры
    int f = (number % 10); // Последняя цифра(6)
    int e = ((number % 10000 - f) / 10) % 10; // Предпоследняя цифра(5)
    int d = ((number % 10000 - f) / 10) / 100; // 4 цифра 
    int fed = f*100 + e*10 + d;

    if (abc == fed)
        std::cout << "Ваше число является счастливым." << std::endl;
    else
        std::cout << "Ваше число не является счастливым." << std::endl;
    return 0;
}