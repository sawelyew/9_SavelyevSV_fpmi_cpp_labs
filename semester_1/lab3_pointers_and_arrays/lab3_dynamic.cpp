#include <iostream>
#include <cstdlib>


// Заполнение с клавиатуры
void FillFromKeyboard(double* arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "Введите " << i << " элемент: ";
        std::cin >> arr[i];
    }
}

// Заполнение случайными числами из интервала [a,b]
void FillRandom(double* arr, int n, double a, double b) {
    
    // for (int i = 0; i < n; i++) {
    //     double RandomNum = rand() % (b - a + 1) + a;
    //     arr[i] = RandomNum;

    for (int i = 0; i < n; i++) {
        // Генерируем случайное число от 0 до 1
        double random01 = rand() / (double)RAND_MAX;
        // Масштабируем в интервал [a, b]
        arr[i] = a + random01 * (b - a);

    }
}

// 1 задача
bool FindElementWMinFreq(double* arr, int n, double &foundValue, int &foundFrequency) {
    for (int freqCount = 1; freqCount <= n; freqCount++) {
        double maxVal = -1e308;
        bool found = false;

        for (int i = 0; i < n; i++) {
            // Считаем, сколько раз встречается arr[i]
            int count = 0;
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
double SumBetweenFirstLastZero(double* arr, int n) {
    int firstZero = -1, lastZero = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0.0) { 
            if (firstZero == -1) firstZero = i;
            lastZero = i;
        }
    }
    if (firstZero == -1 || firstZero == lastZero) 
        return 0.0;
    double sum = 0.0;
    for (int i = firstZero + 1; i < lastZero; i++) {
        sum += arr[i];
    }
    return sum;
}

// 3
void RearrangeArray(double* arr, int n) {
    int insertPos = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            if (i != insertPos) {
                double temp = arr[i];
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

    double* arr = new double[n];

    int choice;
    std::cout << "Выберите способ заполнения массива:\n1 - с клавиатуры\n2 - случайными числами\nВаш выбор: ";
    std::cin >> choice;

    double a, b;
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

    double val;
    int freq;
    if (FindElementWMinFreq(arr, n, val, freq)) {
        std::cout << "Найденный элемент: " << val << ", встречается " << freq << " раз" << std::endl;
    }

    double sumZero = SumBetweenFirstLastZero(arr, n);
    std::cout << "Сумма между первым и последним нулём: " << sumZero << std::endl;

    RearrangeArray(arr, n);
    std::cout << "Преобразованный массив: ";
    for (int i = 0; i < n; i++) std::cout << arr[i] << " ";

    delete[] arr;
    return 0;
}