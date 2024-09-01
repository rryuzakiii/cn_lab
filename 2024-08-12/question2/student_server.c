// student_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define STUDENT_COUNT 3

typedef struct {
    int roll_number;
    char name[50];
} Student;

Student students[STUDENT_COUNT] = {
    {101, "Alice"},
    {102, "Bob"},
    {103, "Charlie"}
};

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    int roll_number;
    int found = 0;

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

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE);
        roll_number = atoi(buffer);
        found = 0;

        for (int i = 0; i < STUDENT_COUNT; i++) {
            if (students[i].roll_number == roll_number) {
                sprintf(buffer, "Roll Number: %d, Name: %s", students[i].roll_number, students[i].name);
                send(new_socket, buffer, strlen(buffer), 0);
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(buffer, "Student not found");
            send(new_socket, buffer, strlen(buffer), 0);
        }
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
