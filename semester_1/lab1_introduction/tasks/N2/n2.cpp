#include <iostream>

int main() {
    int sum=0, multipl=1, n, i;

    std::cout << "Введите конец отрезка: " << std::endl;
    std::cin >> n;

    for (i=1; i<=n; i++) {
        if (i%2 == 0) {
            sum += i;
        }
        else {
            multipl *= i;
        }
    }
    std::cout << sum << " " << multipl << std::endl;
    return 0;
}