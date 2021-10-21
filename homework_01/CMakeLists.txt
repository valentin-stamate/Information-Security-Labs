cmake_minimum_required(VERSION 3.20)
project(homework_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(homework_01 src/client/Client.cpp src/client/Client.h src/server/Server.cpp src/server/Server.h src/util/Util.cpp src/util/Util.h test/test.cpp src/node.cpp src/server.cpp src/security/Crypto.cpp src/security/Crypto.h src/node/key_manager/KeyManager.cpp src/node/key_manager/KeyManager.h src/file/File.cpp src/file/File.h src/node/node/Node.cpp src/node/node/Node.h src/key.cpp)
