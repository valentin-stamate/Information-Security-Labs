#include "Server.h"
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>

Server::Server() = default;

void Server::start(short port) {
    int server_fd;
    struct sockaddr_in address;

    int opt = 1;
    addressLen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("SetSock Output error");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    this->address = address;
    this->serverFd = server_fd;

    printf("Server started...\n");
}

void Server::startListening() {
    if (listen(serverFd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

int Server::acceptClient() {
    printf("Accepting client...\n");
    int clientFd;

    if ((clientFd = accept(serverFd, (struct sockaddr *) &address, (socklen_t *) &addressLen)) < 0){
        perror("acceptClient");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for registering...\n");

    char name[32];
    receiveMessage(clientFd, name);

    string id(name);
    clients[id] = clientFd;

    printf("Client %s connected\n", name);

//    free(name);
    return clientFd;
}

void Server::sendMessage(int fd, void* buffer, int len) {
    send(fd, &len, sizeof(int), 0);
    send(fd, buffer, len, 0);
}

void Server::receiveMessage(int fd, void* buffer) {
    int len;
    read(fd, &len, sizeof(int));
    read(fd, buffer, len);
}

void Server::addClient(string id, int fd) {
    clients[id] = fd;
}

void Server::sendMessageTo(string id, void *buffer, int len) {
    sendMessage(clients[id], buffer, len);
}

void Server::receiveMessageFrom(string id, void *buffer) {
    receiveMessage(clients[id], buffer);
}
