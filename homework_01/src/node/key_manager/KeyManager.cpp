#include "KeyManager.h"

KeyManager::KeyManager(): Client("KeyManager") {
    Crypto crypto;
    IV = crypto.IV;
    KP = crypto.KEY;
}
