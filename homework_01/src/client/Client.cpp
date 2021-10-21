#include "Client.h"
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>

Client::Client(string id) {
    this->id = id;
}

void Client::connectToServer(char* serverAddress, short serverPort) {
    strcpy(this->address, serverAddress);
    this->port = serverPort;

    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Client socket creation error\n");
        return;
    }

    printf("Client running\n");

    servAddress.sin_family = AF_INET;
    servAddress.sin_port = htons(this->port);

    if (inet_pton(AF_INET, this->address, &servAddress.sin_addr) <= 0) {
        printf("Invalid address\n");
        return;
    }

    if (connect(this->serverFd, (struct sockaddr*) &servAddress, sizeof(servAddress)) < 0) {
        printf("Connection Failed\n");
        return;
    }

    printf("Connected to server\n");
}

void Client::sendMessage(void *buffer, int len) {
    send(serverFd, &len, sizeof(int), 0);
    send(serverFd, buffer, len, 0);
}

void Client::receiveMessage(void* buffer) {
    int bytes;
    read(serverFd, &bytes, sizeof(bytes));
    read(serverFd, buffer, bytes);
}

string Client::getId() {
    return id;
}
