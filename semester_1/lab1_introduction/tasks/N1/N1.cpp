#include <iostream>

int main() {
    int a,b,d,x;
    
    std::cout<<"Введите число-начало отрезка"<<std::endl;
    std::cin>>a;

    std::cout<<"Введите число-конец отрезка"<<std::endl;
    std::cin>>b;

    std::cout<<"Введите разность прогрессии"<<std::endl;
    std::cin>>d;

    if (a<b){
        while (a < b) {
            x=a;
            a=x+d;
            if(a%3==0){
                std::cout<<a<<std::endl;
            }
        }
    }
    else {
        std::cout<<"Число начала отрезка не может превышать или быть равным числу конца."<<std::endl;
    }
}