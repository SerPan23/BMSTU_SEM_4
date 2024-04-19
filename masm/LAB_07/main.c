#include <stdio.h>

extern char *my_strncpy(char *dst, char *src, size_t len);

size_t my_strlen(const char* str)
{
    size_t len;

    asm(
        ".intel_syntax\n" // для удобства чтобы писать как раньше писали
        "mov %%rcx, -1\n" // кладем максимально положительное (что равно -1), так как не знаем длину
        "xor %%al, %%al\n"
        "cld\n" // очистка флагов
        "repne scasb\n" // ищем нулевой байт в строке
        // получаем наше количество 
        "not %%rcx\n"
        "dec %%rcx\n"
        "mov %0, %%rcx\n"
        ".att_syntax\n" // так как мы на линуксе то возращаемся обратно в att
        : "=r"(len) // выходной параметр, говорим что из регистра %0 кладем в len
        : "r"(str)  // входной параметр, помещаем поместим str в регистр %0
        // список регистров, которые будут использоваться программой и
        // значения которых будут затерты в процессе выполнения программы.
        : "rcx", "al");

    return len;
}

int main()
{
    char *str = "Test";
    char buff[255];

    size_t len = my_strlen(str);

    printf("Str = %s, len = %zu\n", str, len);

    my_strncpy(buff, str, len);

    printf("Buff = %s\n", buff);

    return 0;
}