#include <iostream>

int main() {
    int number;

    std::cout << "Введите четырехзначное число: " << std::endl;
    std::cin >> number;

    int ab = (number / 100); // Первые 2 цифры
    int d = (number % 10); // Последняя цифра
    int c = (number % 100 - d) / 10; // Предпоследняя цифра
    int dc = (d*10 + c); // Перевернутые последние 2

    if (ab == dc)
        std::cout << "Ваше число является палиндромом." << std::endl;
    else
        std::cout << "Ваше число не является палиндромом." << std::endl;
    return 0;
}