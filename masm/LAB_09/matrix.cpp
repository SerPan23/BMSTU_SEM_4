#include "matrix.h"

matrix_t matrix_alloc(int n, int m)
{
    matrix_t matrix;
    matrix.n = n;
    matrix.m = m;

    matrix.data = (double **) calloc(matrix.n, sizeof(double*));

    for (int i = 0; i < matrix.n; i++)
        matrix.data[i] = (double *)calloc(matrix.m + matrix.m % 2, sizeof(double));

    return matrix;
}
void matrix_free(matrix_t &matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        if (matrix.data[i])
            free(matrix.data[i]);
        matrix.data[i] = NULL;
    }

    if (matrix.data)
        free(matrix.data);
    
    matrix.data = NULL;
    matrix.n = 0;
    matrix.m = 0;
}

void read_size(int &n, int &m)
{
    std::cout << "Enter rows count: ";
    std::cin >> n;

    std::cout << "Enter cols count: ";
    std::cin >> m;
}

void matrix_read(matrix_t &matrix, int rows, int cols)
{
    std::cout << "Enter matrix elements:" << std::endl;

    matrix = matrix_alloc(rows, cols);

    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.m; j++)
            std::cin >> matrix.data[i][j];
}

void matrix_print(matrix_t &matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.m; j++)
            std::cout << matrix.data[i][j] << "\t";
        std::cout << std::endl;
    }
}

matrix_t matrix_transpose(matrix_t &matrix)
{
    matrix_t res = matrix_alloc(matrix.m, matrix.n);

    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.m; j++)
            res.data[j][i] = matrix.data[i][j];

    return res;
}

static double mul_and_sum_standart(double *a, double *b, int m)
{
    double tmp = 0;
    for (int k = 0; k < m; k++)
        tmp += a[k] * b[k];

    return tmp;
}


static double mul_and_sum_sse(double *sa, double *sb, int n)
{
    double tmp = 0.0, res = 0.0;
    __float128 *a = (__float128 *)sa;
    __float128 *b = (__float128 *)sb;
    for (size_t i = 0; i < n; i += sizeof(__float128) / sizeof(double), a++, b++)
    {
        __asm__(
            "movapd xmm0, %1\n"   // копирование выровненных данных (в нашем случае двух чисел типа double)
            "movapd xmm1, %2\n"   // так как у нас всего 128 бит, а double 8 байт
            "mulpd xmm0, xmm1\n"  // перемножает 2 дорожки операндов с числами с плавающей точкой двойной точности
            "haddpd xmm0, xmm0\n" // горизонтально складывает 2 дорожки операндов с числами с плавающей точкой двойной точности
            "movsd %0, xmm0\n"
            : "=m"(tmp)
            : "m"(*a), "m"(*b)
            : "xmm0", "xmm1");

    // std::cout << tmp << std::endl;
        res += tmp;
    }


    return res;
}

matrix_t matrix_mul_sse(matrix_t &a, matrix_t &b)
{
    matrix_t trans_b = matrix_transpose(b);

    matrix_t res = matrix_alloc(a.n, b.m);

    for (int i = 0; i < res.n; i++)
        for (int j = 0; j < res.m; j++)
            // res.data[i][j] = mul_and_sum_standart(a.data[i], trans_b.data[j], b.m);
            res.data[i][j] = mul_and_sum_sse(a.data[i], trans_b.data[j], a.m);

    matrix_free(trans_b);

    return res;
}