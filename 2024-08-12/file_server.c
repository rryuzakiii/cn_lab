
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>

#define PORT 8081
#define BUFFER_SIZE 1024

void send_file_content(int client_socket, const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("File not found");
        send(client_socket, "File not found", 15, 0);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(client_socket, buffer, bytesRead, 0);
    }
    
    fclose(file);
}

void send_least_file_name(int client_socket) {
    DIR *dir;
    struct dirent *entry;
    char *least_file_name = NULL;
    size_t least_length = SIZE_MAX;

    if ((dir = opendir(".")) == NULL) {
        perror("Could not open directory");
        send(client_socket, "Error opening directory", 24, 0);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {  
            size_t length = strlen(entry->d_name);
            if (length < least_length) {
                least_length = length;
                least_file_name = entry->d_name;
            }
        }
    }

    closedir(dir);

    if (least_file_name != NULL) {
        send(client_socket, least_file_name, strlen(least_file_name), 0);
    } else {
        send(client_socket, "No files found", 15, 0);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    
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
        printf("Received command: %s\n", buffer);

        if (strncmp(buffer, "least", 5) == 0) {
            send_least_file_name(new_socket);
        } else if (strncmp(buffer, "retr ", 5) == 0) {
            send_file_content(new_socket, buffer + 5);
        } else {
            send(new_socket, "Unknown command", 15, 0);
        }
    }

   
    close(new_socket);
    close(server_fd);

    return 0;
}
