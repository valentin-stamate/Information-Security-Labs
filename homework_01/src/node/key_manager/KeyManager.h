#ifndef HOMEWORK_01_KEYMANAGER_H
#define HOMEWORK_01_KEYMANAGER_H


#include "../../client/Client.h"
#include "../../security/Crypto.h"

class KeyManager: public Client {
public:
    const char* IV;
    const char* KP;

    KeyManager();

};


#endif //HOMEWORK_01_KEYMANAGER_H
