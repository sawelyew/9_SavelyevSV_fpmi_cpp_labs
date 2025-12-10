#include <iostream>
#include <cmath>


bool IsPrime(int q) {
    if (q > 0){
        for (int i=2; i<= sqrt(q); i++) {
            if (q%i==0)
                return false;
        }
        return true;
    }
    return false;
}

int CalculateMersenNum(int p){
    if (IsPrime(p)){
        int k = pow(2, p) - 1;
        return k;
    }
    else{
        throw "Your number is not prime";
    }
}

std::vector<int> CalculateMersenNumsToN(int n){
    if (n > 0) {
        std::vector<int> mnumbers;
        for (int p=1; (pow(2,p) - 1 <= n); p++){
            if(IsPrime(p)){
                int k = CalculateMersenNum(p);
                mnumbers.push_back(k);
            }
        }
        return mnumbers;
    }
    else {
        throw "N must be positive.";
    }
}



int main() {
    int n;
    std::cout << "Введите натуральное число n: " << std::endl;
    if (!(std::cin>>n))
        std::cout << "Вы неправильно ввели n" << std::endl;
    else {
        if (n>0) {
            std::vector<int> vector;
            for (int p=2; (pow(2,p) - 1 <= n); p++) {
                if (IsPrime(p)) {
                    int k = CalculateMersenNum(p);
                    vector.push_back(k);
                }
            }



        }
        else {
            std::cout << "Ваше число не является натуральным. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}