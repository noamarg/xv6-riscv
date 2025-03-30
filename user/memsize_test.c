#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    printf("memsize before allocation: %d\n", memsize());
    char *arr = malloc(20000 * sizeof(char));
    printf("memsize after allocation: %d\n", memsize());
    free(arr);
    printf("memsize after free: %d\n", memsize());
    exit(0, "");
}
