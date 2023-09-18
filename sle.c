#include "sle.h"
#include "det.h"

#include <stdlib.h>

int sle(double **matrix, int m, int n, double *roots) {
    int res = 0;
    double **matr = malloc(m * sizeof(double *) + (n - 1) * m * sizeof(double));
    double *arr = (double *)(matr + m);
    for (int i = 0; i < m; i++) {
        matr[i] = arr + m * i;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            matr[i][j] = matrix[i][j];
        }
    }
    
    double detr = det(matr, m);
    if (detr == 0) {
        res = 1;
    } else {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m; k++) {
                    if (i != k) {
                        matr[j][k] = matrix[j][k];
                    } else {
                        matr[j][k] = matrix[j][m];
                    }
                }
            }
            double det_o = det(matr, m);
            roots[i] = det_o / detr;
        }
    }
    free(matr);
    return res;
}

