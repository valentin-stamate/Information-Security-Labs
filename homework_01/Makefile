all:
	g++ src/key.cpp src/client/Client.cpp src/node/key_manager/KeyManager.cpp src/security/Crypto.cpp src/util/Util.cpp src/file/File.cpp -o build/key -lcrypto
	g++ src/node.cpp src/client/Client.cpp src/node/node/Node.cpp src/security/Crypto.cpp src/util/Util.cpp src/file/File.cpp -o build/node -lcrypto
	g++ src/server.cpp src/server/Server.cpp src/security/Crypto.cpp src/util/Util.cpp src/file/File.cpp -o build/server -lcrypto

demo:
	g++ test/test.cpp src/util/Util.cpp src/security/Crypto.cpp src/file/File.cpp -o build/test -lcrypto
	build/test

node:
	build/node

key:
	build/key

server:
	build/server

clean:
	rm build/*
