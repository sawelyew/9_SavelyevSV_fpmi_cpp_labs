#include <iostream>
#include <cstdlib>
#include <random>
#include <climits>

void PrintArray(int* arr, int n) {
    for (int i=0; i < n; ++i){
        std::cout << arr[i] << std::endl;
    }
}

void FillFromKeyboard(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "Введите " << i+1 << " элемент: ";
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

// 1 задача
bool FindElementWMinFreq(int* arr, int n, int &foundValue, int &foundFrequency) {
    for (int freqCount = 1; freqCount <= n; freqCount++) {
        int maxVal = INT_MAX;
        bool found = false;

        for (int i = 0; i < n; i++) {
            int count = 0; // Считаем, сколько раз встречается arr[i]
            for (int j = 0; j < n; j++) {
                if (arr[i] == arr[j]) {
                    count++;
                }
            }

            if (count == freqCount) {
                if (!found || arr[i] > maxVal) {
                    maxVal = arr[i];
                    found = true;
                }
            }
        }

        if (found) {
            foundValue = maxVal;
            foundFrequency = freqCount;
            return true;
        }
    }
    return false;
}


// 2 задача
int SumBetweenFirstLastZero(int* arr, int n) {
    int firstZero = -1, lastZero = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) { 
            if (firstZero == -1) firstZero = i;
            lastZero = i;
        }
    }
    if (firstZero == -1 || firstZero == lastZero) 
        return 0;
    int sum = 0;
    for (int i = firstZero + 1; i < lastZero; i++) {
        sum += arr[i];
    }
    return sum;
}

// 3
void RearrangeArray(int* arr, int n) {
    int insertPos = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            if (i != insertPos) {
                int temp = arr[i];
                for (int j = i; j > insertPos; j--) { // Сдвигаем все элементы между insertPos и i вправо
                    arr[j] = arr[j - 1];
                }
                arr[insertPos] = temp;
            }
            insertPos++;
        }
    }
}

int main() {
    int n;
    std::cout << "Введите количество элементов массива: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Размер должен быть положительным!\n";
        return 1;
    }

    int* arr = new int[n];

    int choice;
    std::cout << "Выберите способ заполнения массива:\n1 - с клавиатуры\n2 - случайными числами\nВаш выбор: ";
    std::cin >> choice;

    int a, b;
    if (choice == 1) {
        FillFromKeyboard(arr, n);
    } else if (choice == 2) {
        std::cout << "Введите границы интервала [a, b]: ";
        std::cin >> a >> b;
        FillRandom(arr, n, a, b);
        std::cout << "Сгенерированный массив: ";
        for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
        std::cout << std::endl;
    } else {
        std::cout << "Некорректный выбор\n";
        delete[] arr;
        return 1;
    }

    int val;
    int freq;
    if (FindElementWMinFreq(arr, n, val, freq)) {
        std::cout << "Найденный элемент: " << val << ", встречается " << freq << " раз" << std::endl;
    }

    int sumZero = SumBetweenFirstLastZero(arr, n);
    std::cout << "Сумма между первым и последним нулём: " << sumZero << std::endl;

    RearrangeArray(arr, n);
    std::cout << "Преобразованный массив: ";
    PrintArray(arr, n);

    delete[] arr;
    return 0;
}