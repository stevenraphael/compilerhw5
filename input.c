#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    uint32_t num = atoi(argv[1]);
    uint32_t sum = (((num & (uint32_t)0b1111000000000000) >> (uint32_t)12) + (num & (uint32_t)0b1111)) & (0b11);
    
    char str[12]; 

    sprintf(str, "%d", sum);
    printf("Hello, %s!\n", str);

    return 0;
}