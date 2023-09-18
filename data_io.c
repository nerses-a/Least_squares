#include "data_io.h"

#include <stdio.h>



int input_matrix(double **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%lf", &a[i][j]) != 1) {
                return 1;
            }
        }
    }
    return 0;
}



void output_array(double *array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%e", array[i]);
        if (i != n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}


void output_matrix(double **a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%lf", a[i][j]);
            if (j != m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
