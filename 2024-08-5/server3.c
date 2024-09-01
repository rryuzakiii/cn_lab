//  create an udp socket through which client will send int array to server
// the server will sort the array and return back to client.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void error_handling(char *message) {
    perror(message);
    exit(1);
}

void sort(int arr[]) {

    int n = arr[0];

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n; j++) {

            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Receiver Port> <Sender Port>\n", argv[0]);
        exit(1);
    }

    int receiver_port = atoi(argv[1]);
    int sender_port = atoi(argv[2]);

    int sock;
    struct sockaddr_in receiver_addr, sender_addr;

    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        error_handling("socket() error");

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    receiver_addr.sin_port = htons(receiver_port);

    if (bind(sock, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) == -1)
        error_handling("bind() error");

    int buffer[BUFFER_SIZE];
    socklen_t sender_addr_size = sizeof(sender_addr);
    
    while (1) {
        int recv_len = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sender_addr, &sender_addr_size);

        sort(buffer);

        sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&sender_addr, sender_addr_size);
    }

    close(sock);
    return 0;
}