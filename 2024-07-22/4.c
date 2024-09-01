/*Write a C Program to enter a number and store the number across the
following structure and print the content of each member of the structure.
Then aggregate each member of the structure to form the original number and
print the same.
struct pkt {
char ch1;
char ch2[2];
char ch3;
};*/

#include <stdio.h>
#include <string.h>

typedef struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
} pkt;

int main(int argc, char* argv[]) {

    pkt packet;

    packet.ch1 = 'A';
    strncpy(packet.ch2, "MA", 2);
    packet.ch3 = 'N';

    printf("%c %s %c", packet.ch1, packet.ch2, packet.ch3);

    return 0;
}

