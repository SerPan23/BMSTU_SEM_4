#include <stdio.h>

#define STRLEN 20

#define N 5

typedef struct arr
{
    double *data;
    int size;
} arr_t;


size_t my_strlen(const char *str)
{
    size_t len;

    // __asm__ __volatile__(
    //     "mov X1, %1\n"
    //     "mov X2, #0\n" // длина изначально 0
    //     "loop:\n"
    //     "ldrb w0, [x1, x2]\n" // Загружаем байт из памяти, находящейся по адресу x1 + x2
    //     "cbz w0, end\n"       // Проверяется w0 == 0, Если да, то переход к метке end
    //     "add x2, x2, #1\n"
    //     "B loop\n"
    //     "end:\n"
    //     "mov %0, X2\n"
    //     : "=r"(len)
    //     : "r"(str)
    //     : "r0", "r1", "r2");

    __asm__ __volatile__(
        "mov X0, %1\n"
        "mov W1, 0\n"
        "loop: LDRB W5, [X0], #1\n"
        // "cmp W5, W1\n"
        // "B.NE loop\n"
        "cbnz W5, loop\n"
        "sub x0, x0, %1\n"
        "sub x0, x0, #1\n"
        "mov %0, X0\n"
        : "=r"(len)
        : "r"(str)
        : "r0", "r1", "r2");

    return len;
}

void arr_add(const arr_t *arr1, const arr_t *arr2, const arr_t *res)
{
    double *p1 = arr1->data;
    double *p2 = arr2->data;
    double *p_res = res->data;
    for (int i = 0; i < arr1->size / 2; i++, p1 += 2, p2 += 2, p_res += 2)
    {
        __asm__ __volatile__(
            "ld1 {v0.2d}, [%0]\n"        // ld1 загружает 2 значения типа doble в регистр NEON v0
            "ld1 {v1.2d}, [%1]\n"        // ld1 загружает 2 значения типа doble в регистр NEON v1
            "fadd v2.2d, v0.2d, v1.2d\n" // Выполняется сложение векторов
            "st1 {v2.2d}, [%2]\n"
            :
            : "r"(p1), "r"(p2), "r"(p_res)
            : "v0", "v1", "v2");
    }

    if (arr1->size % 2 != 0)
    {
        __asm__ __volatile__(
            "ldr d0, [%0]\n" // ldr загружает значения типа doble в регистр NEON d0 (64 битная часть v0)
            "ldr d1, [%1]\n"
            "fadd d2, d0, d1\n"
            "str d2, [%2]\n"
            :
            : "r"(p1), "r"(p2), "r"(p_res)
            : "v0", "v1", "v2");
    }
}

void arr_print(const char *name, const arr_t *arr)
{
    printf("%s: ", name);
    for (int i = 0; i < arr->size; ++i)
        printf("%lf ", arr->data[i]);
    printf("\n");
}

int main(void)
{
    char str[STRLEN] = "123456";

    size_t len = my_strlen(str);

    printf("Str = %s, len = %zu\n", str, len);

    double d1[N] = {1, 2, 3, 4, 5};
    double d2[N] = {0.1, 0.2, 0.3, 0.4, 0.5};
    double d_res[N] = {0};

    arr_t a1 = {d1, N};
    arr_t a2 = {d2, N};
    arr_t a_res = {d_res, N};

    arr_add(&a1, &a2, &a_res);

    arr_print("Arr 1", &a1);
    arr_print("Arr 2", &a2);
    arr_print("Result", &a_res);

    return 0;
}