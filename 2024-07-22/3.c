/*. Write a C program to extract each byte from a given number and store them in
separate character variables and print the content of those variables.*/

#include <stdio.h>

int main(int argc, char* argv[]) {

    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    int bytes[4];

    int pos = 0;
    for (int shift = 0; shift <= 24; shift += 8) {
        bytes[pos++] = ( num >> shift ) & 0xff;
    }

    for (int i = 0; i < 4; i++) {
        printf("Byte %d: %d\n", (i + 1), bytes[i]);
    }

    return 0;
}