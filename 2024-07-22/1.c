#include <stdio.h>
#include <stdlib.h>

void swap(int* n1, int* n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int main(int argc, char* argv[]) {

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    swap(&n1, &n2);

    printf("%d %d", n1, n2);

    return 0;
}  