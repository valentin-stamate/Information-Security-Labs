#include <cstdio>
#include <cstring>
#include "client/Client.h"

char address[] = "127.0.0.1";

int main() {
    char id[] = "A";
    string idStr(id);
    int len = strlen(id) + 1;

    Client c(idStr);
    c.connectToServer(address, 8080);

    c.sendMessage(id, len);

    return 0;
}

