#include <iostream>
#include <cmath>

bool prime(long long n) { // Ф-ция проверяющая принадлежность числа к простым
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    long long n;
    std::cout << "Введите n: ";
    std::cin >> n;

    for (int p=2; (pow(2, p) - 1 <= n); p++) {
        if (prime(p)) { // Проверка числа p
            long long k = pow(2, p) - 1; // Вычисляет простое число Мерсенна
            if (prime(k)) { 
                std::cout << k << std::endl; // Выводит k если оно меньше заданного n и простое
            } 
        }
    }
    return 0;
}