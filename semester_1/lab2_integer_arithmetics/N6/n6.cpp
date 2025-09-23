#include <iostream>
#include <cmath>

bool IsPrime(int n) { // Ф-ция проверяющая принадлежность числа к простым
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}


int main() {
    int n;
    std::cout << "Введите натуральное (целое, положительное) число n: " << std::endl;
    if (!(std::cin>>n)) { // По сути должно отсекать все типы, кроме int, но почему-то не работает с float :( С символами работает
        std::cout << "Вы неправильно ввели n." << std::endl;
    }
    else {
        if (n > 0) { // Проверка на натуральность
            for (int p=2; (pow(2, p) - 1 <= n); p++) {
            if (IsPrime(p)) { // Проверка числа p
                int k = pow(2, p) - 1; // Вычисляет простое число Мерсенна
                if (IsPrime(k)) { 
                    std::cout << k << std::endl; // Выводит k если оно меньше заданного n и простое
                    }
                }
            }
        }
        else {
            std::cout << "Ваше число не является натуральным. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}