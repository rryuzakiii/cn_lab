// file_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char command[BUFFER_SIZE];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    while (1) {
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        send(sock, command, strlen(command), 0);

        if (strncmp(command, "retr ", 5) == 0) {
            while (1) {
                int bytes_received = read(sock, buffer, BUFFER_SIZE);
                if (bytes_received <= 0) {
                    break;
                }
                fwrite(buffer, 1, bytes_received, stdout);
            }
            printf("\n");
        } else {
            memset(buffer, 0, BUFFER_SIZE);
            read(sock, buffer, BUFFER_SIZE);
            printf("%s\n", buffer);
        }
    }

    close(sock);
    return 0;
}
