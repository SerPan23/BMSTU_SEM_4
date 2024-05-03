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
    matrix_read(a);
    matrix_read(b);
    std::cout << std::endl;

    matrix_print(a);
    std::cout << std::endl;
    matrix_print(b);

    std::cout << std::endl;
    matrix res = matrix_mul_sse(a, b);
    matrix_print(res);

    return 0;
}