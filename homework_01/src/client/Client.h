#ifndef HOMEWORK_01_CLIENT_H
#define HOMEWORK_01_CLIENT_H

#include <netinet/in.h>
#include <string>
#include "../server/Server.h"
#include "../security/Crypto.h"

using namespace std;

class Client {
private:
    string id;

    char address[64];
    int port;

    int serverFd = 0;
    struct sockaddr_in servAddress;
public:
    Client(string id);
    void connectToServer(char* address, short port);

    void sendMessage(void* buffer, int len);
    int receiveMessage(void* buffer);

    string getId();
};


#endif //HOMEWORK_01_CLIENT_H
