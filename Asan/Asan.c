#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_USE_AFTER 1
#define HEAP_OF 0
#define USE_AFTER_FREE 0
#define MEM_LEAK 0


#if STACK_USE_AFTER
int *stack_para_ptr;
int testcall(int in, int in2)
{
    int a = in;
    int b = in2;
    int c = a + b*10;
    stack_para_ptr = &a;
    return c;
}

#elif HEAP_OF
int heap_overflow()
{
    char *buff = calloc(10, sizeof(char));
    strcpy(buff, "heap_ovf");
    printf("buff addr = %p\n", buff);
    buff = buff - 10;
    buff[0] = 'A';
    return 0;
}

#elif USE_AFTER_FREE
int use_after_free()
{
    char *buff = calloc(10, sizeof(char));
    strcpy(buff, "uafree");
    printf("buff addr = %p\n", buff);
    free(buff);
    buff[0] = 'A';
    return 0;
}

#elif MEM_LEAK
char *leak_ptr = NULL;
void leak_memory() {
    leak_ptr = calloc(100, sizeof(char));
    strcpy(leak_ptr, "LeakedMemory");
    printf("Allocated but not freed: %s\n", leak_ptr);
    leak_ptr = calloc(50, sizeof(char));
    strcpy(leak_ptr, "LeakedMemory2");
}

#endif

int main() {

#ifdef STACK_USE_AFTER
    testcall(1 ,20);
    *stack_para_ptr = 10;

#elif HEAP_OF
    printf("heap overflow.....\n");
    heap_overflow();

#elif USE_AFTER_FREE
    printf("use after free.....\n");
    use_after_free();

#elif MEM_LEAK
    printf("create leak....\n");
    leak_memory();

#endif

    return 0;
}
