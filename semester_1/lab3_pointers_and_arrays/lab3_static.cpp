#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>

const int MAX_SIZE = 100; 

void PrintArray(int* arr, int n) {
    for (int i=0; i < n; ++i){
        std::cout << arr[i] << std::endl;
    }
}

int FillFromKeyboard(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "Введите " << i+1 << " элемент: ";
        if (!(std::cin >> arr[i])) {
            std::cout << "Неверный ввод" << std::endl;
            return 1;
        }
    }
    return 0;
}

void FillRandom(int* arr, int n, int a, int b) {

    std::mt19937 gen(45218965);
    std::uniform_int_distribution<int> dist(a,b);
    for (int i = 0; i < n; i++) {    
        arr[i] = dist(gen);
    }
}

int FindMinDiffIndex(int arr[], int n) {
    int totalSum = 0;
    for (int i = 0; i < n; i++)
        totalSum += arr[i];
    int leftSum = 0;
    int minIndex = 0;
    int minDiff = totalSum;
    int rightSum;
    int diff;

    for (int i = 0; i < n; i++) {
        rightSum = totalSum - leftSum - arr[i];
        diff = abs(leftSum - rightSum);
        if (diff < minDiff) {
            minDiff = diff;
            minIndex = i;
        }
        leftSum += arr[i];
    }
    return minIndex;
}


int FindMaxAbsIndex(int arr[], int n) {
    int maxIdx = 0;
    int maxAbsVal = abs(arr[0]);

    for (int i = 1; i < n; i++) {
        int currentAbs = abs(arr[i]);
        if (currentAbs > maxAbsVal) {
            maxAbsVal = currentAbs;
            maxIdx = i;
        }
    }
    std::cout << "Максимальный модуль = " << maxAbsVal << "\n Индекс этого элемента = " << maxIdx << std::endl;

    return maxIdx;
}


void CompressArray(int* arr, int n, int a, int b) {
    int writeIdx = 0;
    for (int i = 0; i < n; i++) {
        if (!(arr[i] >= a && arr[i] <= b)) {
            arr[writeIdx++] = arr[i];
        }
    }
    for (int i = writeIdx; i < n; i++) {
        arr[i] = 0;
    }
}

int main() {
    int n;
    std::cout << "Введите количество элементов (максимально " << MAX_SIZE << "): ";
    std::cin >> n;
    if (n < 1 || n > MAX_SIZE) {
        std::cout << "Количество элементов вне допустимого диапазона." << std::endl;
        return 1;
    }

    int arr[MAX_SIZE];

    int choice;
    std::cout << "Выберите способ заполнения массива: \n 1 - с клавиатуры \n 2 - случайными числами \n Ваш выбор: ";
    std::cin >> choice;

    int a, b;
    int result;
    if (choice == 1) {
        result = FillFromKeyboard(arr, n);
    } 
    else if (choice == 2) {
        std::cout << "Введите границы интервала для случайных чисел [a, b]: " << std::endl;
        if (!(std::cin >> a && std::cin >> b)) {
                std::cout << "Неправильный ввод" << std::endl;
                return 1;
    }
        FillRandom(arr, n, a, b);
        std::cout << "Сгенерированный массив: ";
        PrintArray(arr, n);
    } 
    else {
        std::cout << "Неверный выбор!" << std::endl;
        return 1;
    }

    if (result == 0){
    int idxMinDiff = FindMinDiffIndex(arr, n);
    std::cout << "Индекс элемента с минимальной разницей между суммами слева и справа: " << idxMinDiff << std::endl;

    FindMaxAbsIndex(arr, n);
    // std::cout << "Максимальный по модулю элемент: " << maxAbsVal << ", его индекс: " << maxAbsIdx << std::endl;

    std::cout << "Введите границы интервала для удаления элементов [a, b]: " << std::endl;
    if (!(std::cin >> a && std::cin >> b)) {
        std::cout << "Неправильный ввод" << std::endl;
        return 1;
    }

    CompressArray(arr, n, a, b);
    std::cout << "Сжатый массив: ";
    PrintArray(arr, n);
}

   return 0;
}