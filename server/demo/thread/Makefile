.PHONY: all clean

#Add all source *.cpp files
SRC=$(shell find -name '*.cpp')

#Create all source *.cpp Mapping source *.o files
OBJ=$(SRC:.cpp=.o)

#Create the execute file name
ELF=test

INCLUDES := -I. 
LIBS :=

#Add gdb Debug and library ncurses
CFLAG=-Wall -g $(INCLUDES) 
LDFLAG=-lpthread -lrt -lsqlite3 $(LIBS)
CC=GCC $(CFLAG)
CXX=g++ $(CFLAG)

all:$(ELF)

$(ELF):$(OBJ)
	$(CXX) $^ -o $@ $(LDFLAG)

.c.o:
	#@echo $(@D) $(<F)  $(@F)
	$(CXX) -c $(@D)/$(<F) -o $(@D)/$(@F)

#%.o:%.cpp
.cpp.o:
	$(CXX) -c $(@D)/$(<F) -o $(@D)/$(@F)

clean:
	-rm -f $(OBJ) *.o $(ELF)
