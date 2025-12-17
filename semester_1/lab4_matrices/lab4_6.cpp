#include <iostream>
#include <random>


void PrintArray(int** arr, int rows, int columns){
    std::cout << "Матрица: " << std::endl;
    for ( int i = 0; i < rows ; ++i ){
        for ( int j = 0 ; j < columns ; ++j){
            std::cout<<arr[i][j]<<"\t";
        }
        std::cout<<std::endl;
}
}

int FillFromKeyboard(int** arr, int rows, int columns) {
    for (int i=0; i<rows; i++) {
        std::cout << "Введите числа для " << (i + 1) << " строки: " << std::endl;
        for (int j=0; j<columns; j++){
            std::cout << j+1 << " колонка: ";
            if (!(std::cin >> arr[i][j])){
                throw "Некорректный ввод";
            }
        }
    }
    return 0;
}

void FillRandom(int** arr, int rows, int columns, int a, int b) {
    std::mt19937 gen(45218965);
    std::uniform_int_distribution<int> dist(a, b);
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++){
            arr[i][j] = dist(gen);
        }
    }
}

void SumInRowsWOZero(int** arr, int rows, int columns){
    for (int row=0; row<rows; row++){
        bool IncludeZero = false;
        for (int i=0; i<columns; i++) {
            if (arr[row][i] == 0) {
                IncludeZero = true;
            }
        }
        if (!IncludeZero){
            int sum = 0;
            for (int i=0; i<columns; i++) {
                sum += arr[row][i];
            }
            std::cout << "Сумма элементов " << row+1 << " строки равна " << sum << std::endl;
        }
    }
}


void ChangeColumns(int** arr, int rows, int columns) {
    int EndColumn = columns - 1;
    int EndRow = rows - 1;
    for (int StartColumn=0; StartColumn <= EndColumn; StartColumn++){
        for (int StartRow=0; StartRow <= EndRow; StartRow++){
            std::swap(arr[StartRow][StartColumn], arr[StartRow][EndColumn]);
        }
        EndColumn--;
    }
    std::cout << "Измененная матрица: " << std::endl;
    PrintArray(arr, rows, columns);
}

int main() {
    int columns, rows;

    try {
    setlocale(LC_ALL, "Russian");  
    std::cout << "Введите количество строк матрицы: ";
    if (!(std::cin >> rows) || rows <= 0) {
        throw "Количество строк матрицы должно быть целым положительным числом";
    }

    std::cout << "Введите количество столбцов матрицы: ";
    if (!(std::cin >> columns) || columns <= 0) {
        throw "Количество столбцов матрицы должно быть целым положительным числом";
    }

    int **arr = new int* [rows];
    for (int i=0; i<rows; i++) {
        arr[i] = new int[columns];
    }

    int choice;
    std::cout << "Выберите способ заполнения массива:\n1 - с клавиатуры\n2 - случайными числами\nВаш выбор: ";
    std::cin >> choice;

    int a, b;
    int result;
    if (choice == 1) {
        result = FillFromKeyboard(arr, rows, columns);
    }
    else if (choice == 2) {
        std::cout << "Введите границы интервала [a, b]: ";
        if (!(std::cin >> a) || (!(std::cin >> b))) {
            throw "Неверный ввод интервала.";
        }
        FillRandom(arr, rows, columns, a, b);
    }
    else {
        for (int i=0; i<rows; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        throw "Некорректный выбор\n";
    }
    PrintArray(arr, rows, columns);
    SumInRowsWOZero(arr, rows, columns);
    ChangeColumns(arr, rows, columns);
    
    
    for (int i=0; i<rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}
    catch (const char* msg){
        std::cerr << msg;
    }
}
