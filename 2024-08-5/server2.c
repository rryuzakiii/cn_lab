// create an udp socket through which client will send 2 integer no.
// and to server, server wiol add the value &return back the result.
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
        // buffer[recv_len] = 0;

        printf("Received from sender: %d %d\n", buffer[0], buffer[1]);

        // printf("Enter message: ");
        // fgets(buffer, BUFFER_SIZE, stdin);
        // buffer[strcspn(buffer, "\n")] = 0;  // Remove the newline character

        buffer[0] = buffer[0] + buffer[1];

        sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&sender_addr, sender_addr_size);
    }

    close(sock);
    return 0;
}