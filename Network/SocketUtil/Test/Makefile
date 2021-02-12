all:Server Client
Server:
	g++ -g -Wall -O0 -std=c++14 ../../SocketAddress/SocketAddress.cpp ../../TCPSocket/TCPSocket.cpp ../SocketUtil.cpp Server.cpp -o Server
clean:
	rm -r *.o Server Client
Client:
	g++ -g -Wall -O0 -std=c++14 ../../SocketAddress/SocketAddress.cpp ../../TCPSocket/TCPSocket.cpp ../SocketUtil.cpp Client.cpp -o Client
