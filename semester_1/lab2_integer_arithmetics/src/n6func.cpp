#include <cmath>
#include <vector>

bool IsPrime(int q) {
    if (q > 0 || q == 1){
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