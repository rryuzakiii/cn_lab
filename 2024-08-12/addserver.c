// write a C program to create tcp socket to which client will send an integer number to server. Server will find sum of digits of the number, and send back the sum to the client.
// Write a C program to create a TCP socket through which client will send two commands to the server as follows:
// 1. When client will send least, then server will send back the least of file names present in current working guide. 
// 2. When client will send retr <file_name>, then server will send back the content of that file to the client.

// sum_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int sum_of_digits(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int num, sum;

    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    read(new_socket, buffer, BUFFER_SIZE);
    num = atoi(buffer);

    
    sum = sum_of_digits(num);


    sprintf(buffer, "%d", sum);
    send(new_socket, buffer, strlen(buffer), 0);

    printf("Sum of digits sent: %d\n", sum);

    
    close(new_socket);
    close(server_fd);

    return 0;
}
