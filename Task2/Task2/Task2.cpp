#include <iostream>
using namespace std;
bool isColumnSortedDescending(int** matrix, int rows, int col) {
    for (int i = 1; i < rows; ++i) {
        if (matrix[i][col] >= matrix[i - 1][col]) {
            return false;
        }
    }
    return true;
}
int** inputMatrix(int rows, int cols) {
    int** matrix = new int* [rows];
    cout << "Введите элементы массива:" << endl;
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[rows];
        for (int j = 0; j < cols; ++j) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

int countDescendingColumns(int** matrix, int rows, int cols) {
    int count = 0;
    for (int j = 0; j < cols; ++j) {
        if (isColumnSortedDescending(matrix, rows, j)) {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "rus");
    int rows, cols;
    cout << "Введите количество строк, а затем столбцов: ";
    cin >> rows >> cols;

    int** matrix = inputMatrix(rows, cols);

    int descendingColumns = countDescendingColumns(matrix, rows, cols);
    cout << "Количество столбцов, упорядоченных по убыванию: " << descendingColumns << endl;

    return 0;
}