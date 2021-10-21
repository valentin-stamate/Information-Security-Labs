#ifndef HOMEWORK_01_NODE_H
#define HOMEWORK_01_NODE_H

#include "../../client/Client.h"

class Node : public Client {
public:
    const char* IV;
    const char* KP;

    Node();

};


#endif //HOMEWORK_01_NODE_H
