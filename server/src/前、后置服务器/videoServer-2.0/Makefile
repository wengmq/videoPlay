.PHONY: clean all
CC  = gcc
CXX = g++ 
CPPFLAGS = -Wall -Wno-deprecated
LDFLAGS  = -lpthread -lrt -lsqlite3

BINSRCS	:= FrontServer.cpp  BackServer.cpp client1.cpp

SRCS 	:= $(wildcard *.cpp)
SRCS	:= $(filter-out $(BINSRCS),$(SRCS))

BIN = FrontServer BackServer client
all: $(BIN)

FrontServer: $(SRCS) FrontServer.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@  $(LDFLAGS)

BackServer: $(SRCS) BackServer.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@  $(LDFLAGS)
	
client: $(SRCS) client1.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@  $(LDFLAGS) 
	
%.o:%.cpp  
	$(CXX) $(CPPFLAGS) -c $<  	

%.o:%.c 
	$(CC) -c $<

clean:
	-rm -rf $(BIN)  *.o
