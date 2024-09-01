/*Write a C program to check whether the Host machine is in Little Endian or
Big Endian. Enter a number, print the content of each byte location and
Convert the Endianness of the same i.e. Little to Big Endian and vice-versa.*/

#include <stdio.h>

void convert_endian(int bytes[], int n) {

    for (int i = 0; i < n / 2; i++) {
        int temp = bytes[i];
        bytes[i] = bytes[n - 1 - i];
        bytes[n - 1 - i] = temp;
    }
}

int main() {

    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    int bytes[4];

    int pos = 0;
    for (int shift = 0; shift <= 24; shift += 8) {
        bytes[pos++] = ( num >> shift ) & 0xff;
    }

    printf("Little Endian\n");
    for (int i = 0; i < 4; i++) {
        printf("Byte %d: %d\n", (i + 1), bytes[i]);
    }

    convert_endian(bytes, 4);
    printf("\n\n");

    printf("Big Endian\n");
    for (int i = 0; i < 4; i++) {
        printf("Byte %d: %d\n", (i + 1), bytes[i]);
    }

    return 0;
}