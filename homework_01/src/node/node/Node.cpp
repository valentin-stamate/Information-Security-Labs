#include "Node.h"

Node::Node(): Client("Node") {
    Crypto crypto;
    IV = crypto.IV;
    KP = crypto.KEY;
}
