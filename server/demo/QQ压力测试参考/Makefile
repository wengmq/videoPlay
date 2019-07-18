.PHONY: clean all
CC = g++
CPPFLAGS = -Wall  -pthread

BIN = server client
SOURCES = $(BIN.=.cpp)

all: $(BIN)
$(BIN): Socket.cpp EpollBase.cpp EpollTcpServer.cpp  BaseThread.cpp  EpollTcpClient.cpp $(SOURCES)

clean:
	-rm -rf $(BIN) bin/ obj/ core
