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

void FillFromKeyboard(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "Введите " << i << " элемент: ";
        std::cin >> arr[i];
    }
}

void FillRandom(int* arr, int n, int a, int b) {

    std::mt19937 gen(45218965);
    std::uniform_int_distribution<int> dist(a,b);
    for (int i = 0; i < n; i++) {    
        arr[i] = dist(gen);
    }
}

int FindMinDiffIndex(int arr[], int n) { // Нахождение индекса с минимальной разницей сумм слева и справа
    int totalSum = 0;
    for (int i = 0; i < n; i++)
        totalSum += arr[i];
    int leftSum = 0;
    int minIndex = 0;
    int minDiff = totalSum;

    for (int i = 0; i < n; i++) {
        int rightSum = totalSum - leftSum - arr[i];
        int diff = abs(leftSum - rightSum);
        if (diff < minDiff) {
            minDiff = diff;
            minIndex = i;
        }
        leftSum += arr[i];
    }
    return minIndex;
}


int FindMaxAbsIndex(int arr[], int n) { // Функция возвращает индекс элемента массива с максимальным модулем
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


void CompressArray(int* arr, int n, int a, int b) { // Сжатие массива с удалением элементов из интервала [a,b]
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

    if (choice == 1) {
        FillFromKeyboard(arr, n);
    } 
    else if (choice == 2) {
        std::cout << "Введите границы интервала для случайных чисел [a, b]: ";
        std::cin >> a >> b;
        FillRandom(arr, n, a, b);
        std::cout << "Сгенерированный массив: ";
        for (int i = 0; i < n; i++) 
            std::cout << arr[i] << " "<< std::endl;
    } 
    else {
        std::cout << "Неверный выбор!" << std::endl;
        return 1;
    }

    int idxMinDiff = FindMinDiffIndex(arr, n);
    std::cout << "Номер элемента с минимальной разницей между суммами слева и справа: " << idxMinDiff << std::endl;

    FindMaxAbsIndex(arr, n); // Выводит строчку ниже при выполнении самой функции
    // std::cout << "Максимальный по модулю элемент: " << maxAbsVal << ", его индекс: " << maxAbsIdx << std::endl;

    std::cout << "Введите границы интервала для удаления элементов [a, b]: ";
    std::cin >> a >> b;

    CompressArray(arr, n, a, b);
    std::cout << "Сжатый массив: ";
    PrintArray(arr, n);

   return 0;
}