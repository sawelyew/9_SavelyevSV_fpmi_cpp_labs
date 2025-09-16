#include <iostream>

int main() {
    float x1,x2,x3,x4,x5,x6,x7,x8,x9,x10, amount = 0;
    std::cout << "Введите первое вещественное число: " << std::endl;
    std::cin >> x1;

    std::cout << "Введите второе вещественное число: " << std::endl;
    std::cin >> x2;

    std::cout << "Введите третье вещественное число: " << std::endl;
    std::cin >> x3;

    std::cout << "Введите четвертое вещественное число: " << std::endl;
    std::cin >> x4;

    std::cout << "Введите пятое вещественное число: " << std::endl;
    std::cin >> x5;

    std::cout << "Введите шестое вещественное число: " << std::endl;
    std::cin >> x6;

    std::cout << "Введите седьмое вещественное число: " << std::endl;
    std::cin >> x7;

    std::cout << "Введите восьмое вещественное число: " << std::endl;
    std::cin >> x8;

    std::cout << "Введите девятое вещественное число: " << std::endl;
    std::cin >> x9;

    std::cout << "Введите десятое вещественное число: " << std::endl;
    std::cin >> x10;

    if (x1<x2) 
        amount++;

    if (x2<x1 && x2<x3)
        amount++;
        
    if (x3<x2 && x3<x4)
        amount++;

    if (x4<x3 && x4<x5)
        amount++;

    if (x5<x4 && x5<x6)
        amount++;

    if (x6<x5 && x6<x7)
        amount++;

    if (x7<x6 && x7<x8)
        amount++;

    if (x8<x7 && x8<x9)
        amount++;

    if (x9<x8 && x9<x10)
        amount++;
        
    if (x10<x9)
        amount++;

    
    std::cout << "Количество чисел, которые меньше предыдущего и последующего равно: " << amount << std::endl;
    return 0; 
    }