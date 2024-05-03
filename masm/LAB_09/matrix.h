#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

struct matrix
{
    double **data;
    int n;
    int m;
};
using matrix_t = struct matrix;

matrix_t matrix_alloc(int n, int m);
void matrix_free(matrix_t &matrix);

void read_size(int &n, int &m);
void matrix_read(matrix_t &matrix, int rows, int cols);
void matrix_print(matrix_t &matrix);

matrix_t matrix_mul_sse(matrix_t &a, matrix_t &b);

#endif