#include "det.h"

#include <stdlib.h>


double det(double **a, int n) {
    double detr = 0;
    if (n == 1) {
        detr = a[0][0];
    } else {
        double **matr = malloc((n - 1) * sizeof(double *) + (n - 1) * (n - 1) * sizeof(double));
        double *arr = (double *)(matr + (n - 1));
        for (int i = 0; i < n - 1; ++i) {
            matr[i] = arr + i * (n - 1);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - 1; j++) {
                int flag = 0;
                for (int k = 0; k < n - 1; ++k) {
                    if (k == i) {
                        flag = 1;
                    }
                    matr[j][k] = a[j + 1][k + flag];
                }
            }
            if (i % 2 == 0) {
                detr += a[0][i] * det(matr, n - 1);
            } else {
                detr -= a[0][i] * det(matr, n - 1);
            }
        }
        free(matr);
    }
    return detr;
}

