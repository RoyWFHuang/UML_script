#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int *stack_para_ptr;
char *leak_ptr = NULL;

int testcall(int in, int in2)
{
    int a = in;
    int b = in2;
    int c = a + b*10;
    stack_para_ptr = &a;
    return c;
}

void leak_memory() {
    leak_ptr = calloc(100, sizeof(char));
    strcpy(leak_ptr, "LeakedMemory");
    printf("Allocated but not freed: %s\n", leak_ptr);
    leak_ptr = calloc(50, sizeof(char));
    strcpy(leak_ptr, "LeakedMemory2");
}

int heap_overflow()
{
    char *buff = calloc(10, sizeof(char));
    strcpy(buff, "heap_ovf");
    printf("buff addr = %p\n", buff);
    buff = buff - 10;
    buff[0] = 'A';
    return 0;
}

int use_after_free()
{
    char *buff = calloc(10, sizeof(char));
    strcpy(buff, "uafree");
    printf("buff addr = %p\n", buff);
    free(buff);
    buff[0] = 'A';
    return 0;
}

int main() {
    // testcall(1 ,20);
    // *stack_para_ptr = 10;
    // printf("heap overflow.....\n");
    // heap_overflow();
    // printf("use after free.....\n");
    // use_after_free();
    printf("create leak....\n");
    leak_memory();
    return 0;
}
