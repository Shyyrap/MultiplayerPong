#SERVER
SERVER = SERVER.cpp
OBJS = main.cpp
#GAME
GAME = Game.cpp 
#CC
CC = g++
#Actor
Actor = Actor.cpp
#Player
Player = Player.cpp
#Shape 
Shape = Shape.cpp 
#COMPILER_FLAGS specifies the additional compilation options COMPILER_FLAGS = -w
#Network
SocketUtil = Network/SocketUtil/SocketUtil.cpp
#Player Player = Player.cpp
#LINKER FLAGS specifies the libraries linking against
LINKER_FLAGS = -lSDL2
SDL_IMAGE = -lSDL2_image
#Position 
POS = Position.cpp
#OBJ_NAME
OBJ_NAME = First
#SERVER_NAME
SERVER_NAME = Server
#Server
Server = Server.cpp
#This is the target that compiles our executable
#HERE ARE THE ALL REQUIRING EXECUTABLE FILES FOR WORK NETWORK
#Address
Address = Network/SocketAddress/SocketAddress.cpp
#TCPSocket 
TCPSocket = Network/TCPSocket/TCPSocket.cpp
#MEMORY
InputMem = Network/Stream/InputMemoryStream.cpp
OutputMem = Network/Stream/OutputMemoryStream.cpp
#Enemy
Enemy = Enemy.cpp
#Ball

Ball = Ball.cpp

all: $(OBJ_NAME) $(SERVER_NAME)
$(OBJ_NAME):
	$(CC) -g -O0 -std=c++14 $(OBJS) $(Ball) $(Enemy) $(Actor) $(Shape) $(Player) $(GAME) $(POS) $(SocketUtil) $(Address) $(InputMem) $(OutputMem) $(TCPSocket) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(SDL_IMAGE) -o $(OBJ_NAME) 
clean:
	rm -f *.o $(OBJ_NAME) $(SERVER_NAME)
$(SERVER_NAME):
	 $(CC) -g -O0 -std=c++14 SERVER.cpp $(SocketUtil) $(Address) $(InputMem) $(OutputMem) $(TCPSocket) $(Server) $(POS) $(COMPILER_FLAGS) -o $(SERVER_NAME) 
