#include <cstdio>
#include "server/Server.h"

int main() {
    Server s;
    s.start(8080);
    s.startListening();

    char buffer[128];
    int bufferLength;
    auto* id = new string();

    int d = s.acceptClient();

    s.receiveMessage(d, buffer);
    printf("%s\n", buffer);

}
