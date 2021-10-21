#include "Client.h"
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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

    const char *rawId = id.c_str();
    char name[32];
    strncpy(name, rawId, 32);

    sendMessage(name, 32);

    printf("%s connected to server\n", name);
}

void Client::sendMessage(void *buffer, int len) {
    send(serverFd, &len, sizeof(int), 0);
    send(serverFd, buffer, len, 0);
}

int Client::receiveMessage(void* buffer) {
    int bytes;
    read(serverFd, &bytes, sizeof(bytes));
    read(serverFd, buffer, bytes);

    return bytes;
}

string Client::getId() {
    return id;
}
