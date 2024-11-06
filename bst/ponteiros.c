#include <stdio.h>

void colocaEndereco(int *num, int **endnum) {

    (*endnum) = num;

}

int main() {

    int num = 10;
    int *endNum = NULL;

    colocaEndereco(&num, &endNum);

    printf("%p\n", &num);

    printf("%p\n", endNum);

}