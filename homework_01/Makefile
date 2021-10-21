all:
	g++ src/client.cpp src/client/Client.cpp -o build/client
	g++ src/server.cpp src/server/Server.cpp -o build/server

demo:
	g++ test/test.cpp src/util/Util.cpp src/security/Crypto.cpp src/file/File.cpp -o build/test -lcrypto
	build/test

client:
	build/client

server:
	build/server

clean:
	rm build/*
