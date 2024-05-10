#include <iostream>

#include "matrix.h"

/*
4
3
1	2	3
4	5	6
7	8	9
1	5	2
3
4
1	2	3	4
9	8	7	6
5	4	3	2


34	30	26	22
79	72	65	58
124	114	104	94
56	50	44	38
*/

/*
5
4
1	2	3	4
4	5	6	1
7	8	9	9
1	5	2	3
2	1	3	1
4
4
1	2	3	4
9	8	7	6
5	4	3	2
1	2	3	4


38	38	38	38
80	74	68	62
133	132	131	130
59	56	53	50
27	26	25	24
*/

int main(void)
{

    matrix_t a, b;

    std::cout << std::endl
              << "A matrix enter:" << std::endl;
    read_size(a.n, a.m);
    if (a.n <= 0 || a.m <= 0)
    {
        std::cout << std::endl
                  << "ERROR: Wrong matrix A size"<< std::endl;
        return -1;
    }
    matrix_read(a, a.n, a.m);

    std::cout << std::endl
              << "B matrix enter:" << std::endl;
    read_size(b.n, b.m);
    if (b.n <= 0 || b.m <= 0)
    {
        std::cout << std::endl
                  << "ERROR: Wrong matrix A size" << std::endl;
        matrix_free(a);
        return -1;
    }

    matrix_read(b, b.n, b.m);

    std::cout << std::endl
              << "A:" << std::endl;
    matrix_print(a);
    std::cout << std::endl
              << "B:" << std::endl;
    matrix_print(b);

    if (a.m != b.n)
    {
        std::cout << std::endl
                  << "ERROR: The number of columns in the first matrix should be "
                     "equal to the number of rows in the second."
                  << std::endl;
        matrix_free(a);
        matrix_free(b);
        return -1;
    }
    else
    {
        std::cout << std::endl
                  << "Result:" << std::endl;
        matrix_t res = matrix_mul_sse(a, b);
        matrix_print(res);

        matrix_free(res);
    }

    matrix_free(a);
    matrix_free(b);

    return 0;
}