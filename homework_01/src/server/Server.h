#ifndef HOMEWORK_01_SERVER_H
#define HOMEWORK_01_SERVER_H

#include <netinet/in.h>
#include <string>
#include <unordered_map>
#include "../security/Crypto.h"

using namespace std;

class Server {
private:
    unordered_map<string, int> clients;

    int serverFd;
    struct sockaddr_in address;
    int addressLen;

    /* TODO */
    const char* SECRET_KEY = "";
public:
    Server();
    void start(short port);
    void startListening();
    int acceptClient();
    void addClient(string id, int fd);
    void sendMessage(int fd, void* buffer, int len);
    void receiveMessage(int fd, void* buffer);
};


#endif //HOMEWORK_01_SERVER_H
