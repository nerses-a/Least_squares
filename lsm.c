#include "sle.h"
#include "data_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



double sum_x_y(double *x, double *y, int n, int degree_x, int degree_y);
double *vector_coefficients(double *x, double *y, int n, int p); // Находит коэффициенты полинома 
double **allocate_matrix(int rows, int cols); // Выделение памяти для матрицы
double *allocate_sum_array(double *x, double *y, int n, int size); // Выделение памяти и заполнение массива сумм

 
int main() {

    double h[] = {0, 500, 1000, 2000, 3000, 4000, 5000, 6000};
    double g[] = {9.8066, 9.8051, 9.8036, 9.8005, 9.7974, 9.7943, 9.7912, 9.7882};
    double p[] = {1.22500, 1.16727, 1.11166, 1.00655, 0.909254, 0.819347, 0.736429, 0.660111};
    double a[] = {340.294, 338.370, 336.435, 332.532, 328.584, 324.589, 320.545, 316.452};
    
    double * array = vector_coefficients(h, g, 8, 3);
    printf("h, g : ");
    output_array(array, 4);
    free(array);
    
    array =  vector_coefficients(h, p, 8, 3);
    printf("h, p : ");
    output_array(array, 4);
    free(array);
   
    array =  vector_coefficients(h, a, 8, 3);
    printf("h, a : ");
    output_array(array, 4);
    free(array);
 
    return 0;
}

double *vector_coefficients(double *x, double *y, int n, int p) {

    double *res = malloc((p + 1) * sizeof(double)); //  Выделение памяти под массив коэффицентов

    // Выделение памяти для матрицы
    int rows = p + 1; // Количество строк
    int cols = rows + 1; // Количество столбцов
    double **matrix = allocate_matrix(rows, cols);
    
    // Выделение памяти и заполнение массива сумм
    double *sum_array = allocate_sum_array(x, y, n, 2 * p + 1); 
    
    // заполнение матрицы
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {

            int degree = 2 * p - i - j;
            if(j != cols - 1) {
                matrix[i][j] = sum_array[degree];
            } else {
                matrix[i][j] = sum_x_y(x, y, n, degree + 1, 1);
            }

        }
    }

    sle(matrix, rows, cols, res); // Решение СЛАУ и запись коэффициентов полинома в массив res

    free(sum_array); // Чистка памяти выделленую по массив сумм
    free(matrix); // чистка памяти выделенную под матрицу
    
    return res;
}

double **allocate_matrix(int rows, int cols) {
    double **matrix = malloc(rows * sizeof(double *));
    double *ptr = malloc(rows * cols * sizeof(double));
    for(int i = 0; i < rows; ++i) {
        matrix[i] = ptr + cols * i;
    }
    return matrix;
}

double *allocate_sum_array(double  *x, double  *y, int n, int size) {
    double *sum_array = malloc(size * sizeof(double));
    for(int i = 0; i < size; ++i) {
        sum_array[i] = sum_x_y(x, y, n, i, 0);
    }
    return sum_array;
}

double sum_x_y(double *x, double *y, int n, int degree_x, int degree_y) {
    double res = 0;

    for(int i = 0; i < n; ++i) {
        res += pow(x[i], degree_x) * pow(y[i], degree_y);
    }

    return res;
}


