#include <iostream>
#include <cmath>

bool IsPrime(int q) {
    for (int i=2; i<= sqrt(q); i++) {
        if (q%i==0)
            return false;
    }
    return true;
}


int main() {
    int n;
    std::cout << "Введите натуральное число n: " << std::endl;
    if (!(std::cin>>n))
        std::cout << "Вы неправильно ввели n" << std::endl;
    else {
        if (n>0) {
            for (int p=2; (pow(2,p) - 1 <= n); p++) {
                if (IsPrime(p)) {
                    int k = pow (2,p) - 1;
                    if (IsPrime(k))
                        std::cout << k << std::endl;
                }
            }
        }
        else {
            std::cout << "Ваше число не является натуральным. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}