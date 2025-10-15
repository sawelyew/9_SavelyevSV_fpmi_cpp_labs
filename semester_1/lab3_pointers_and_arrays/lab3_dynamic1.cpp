#include <iostream>

void PrintArray(double arr[]){
    int size = (sizeof(arr)/sizeof(double));
    for (int i=0; i<size; ++i)
        std::cout << arr[i] << std::endl;
}

void FillFromKeyboard(double* arr, int n) {
    for (int i=0; i<n; ++i) {
        std::cout << "Введите " << i << "элемент: " << std::endl;
        std::cin >> arr[i];
    }
}

void FillRandom(double* arr, int n, double a, double b) {

}

bool FindElementWMinFreq (double arr[], int n, double foundValue, int findFrequency) {
    for ()
}