#include <iostream>
#include <cstdlib>
#include <cmath>

const int MAX_SIZE = 100; // Максимальный размер статического массива

// Заполнение с клавиатуры
void FillFromKeyboard(double arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "Введите элемент:" << i;
        std::cin >> arr[i];
    }
}

// Заполнение случайными числами из интервала [a,b]
void FillRandom(double arr[], int n, double a, double b) {
    
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

// Нахождение индекса с минимальной разницей сумм слева и справа
int FindMinDiffIndex(double arr[], int n) {
    double totalSum = 0;
    for (int i = 0; i < n; i++)
        totalSum += arr[i];
    double leftSum = 0;
    int minIndex = 0;
    double minDiff = totalSum;

    for (int i = 0; i < n; i++) {
        double rightSum = totalSum - leftSum - arr[i];
        double diff = abs(leftSum - rightSum);
        if (diff < minDiff) {
            minDiff = diff;
            minIndex = i;
        }
        leftSum += arr[i];
    }
    return minIndex;
}


// Функция возвращает индекс элемента массива с максимальным модулем
int FindMaxAbsIndex(double arr[], int n) {
    int maxIdx = 0;
    double maxAbsVal = abs(arr[0]);

    for (int i = 1; i < n; i++) {
        double currentAbs = abs(arr[i]);
        if (currentAbs > maxAbsVal) {
            maxAbsVal = currentAbs;
            maxIdx = i;
        }
    }
    std::cout << "Максимальный модуль = " << maxAbsVal << "\n Индекс этого элемента = " << maxIdx << std::endl;

    return maxIdx;
}


// Сжатие массива с удалением элементов из интервала [a,b]
void CompressArray(double arr[], int n, double a, double b) {
    int writeIdx = 0;
    for (int i = 0; i < n; i++) {
        if (!(arr[i] >= a && arr[i] <= b)) {
            arr[writeIdx++] = arr[i];
        }
    }
    for (int i = writeIdx; i < n; i++) {
        arr[i] = 0.0;
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

    double arr[MAX_SIZE];

    int choice;
    std::cout << "Выберите способ заполнения массива: \n 1 - с клавиатуры \n 2 - случайными числами \n Ваш выбор: ";
    std::cin >> choice;

    double a, b;

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
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

   return 0;
}