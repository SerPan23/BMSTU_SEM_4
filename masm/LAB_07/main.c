#include <stdio.h>

extern void my_strncpy(char *dst, char *src, size_t len);

#define STRLEN 20

size_t my_strlen(const char* str)
{
    size_t len;

    asm(
        ".intel_syntax noprefix\n" // для удобства чтобы писать как раньше писали
        "mov rcx, -1\n" // кладем максимально положительное (что равно -1), так как не знаем длину
        "xor rax, rax\n"
        "mov rax, 0\n" // символ поиска
        "mov rdi, %1\n"
        "cld\n" // очистка флагов
        "repne scasb\n" // ищем нулевой байт в строке
        // получаем наше количество 
        "sub rdi, %1\n" // из адреса найденого символа вычитаем адрес строки
        "dec rdi\n"
        "mov %0, rdi\n"
        ".att_syntax\n" // так как мы на линуксе то возращаемся обратно в att
        : "=r"(len) // выходной параметр, говорим что из регистра %0 кладем в len
        : "r"(str)  // входной параметр, помещаем str в регистр %1
        // список регистров, которые будут использоваться программой и
        // значения которых будут затерты в процессе выполнения программы.
        : "rcx", "rax", "rdi");

    return len;
}

int main(void)
{
    setbuf(stdout, NULL);
    // char buff[STRLEN]; // dst src без перекрытия
    // char buff[7]; // dst src с перекрытием

    char str[STRLEN] = "123456";
    
    char buff[STRLEN]; // src dst без перекрытия
    // char *buff = &str[3]; // src dst  с перекрытием
    // char *buff = str; // dst == src

    size_t len = my_strlen(str);

    printf("Str = %s, len = %zu\n", str, len);

    my_strncpy(buff, str, len);

    printf("Buff = %s\n", buff);

    return 0;
}