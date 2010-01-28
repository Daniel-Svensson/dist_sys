
CCC = g++
CCFLAGS = -Wall -Wextra -ansi
LIBS = -lsocket -lxnet 
LAB2_OBJ = Card.o CardDatabase.o

all: lab2

lab2: lab2.cpp Card.o CardDatabase.o
	$(CCC) $(CCFLAGS) $(LIBS) $(LAB2_OBJ) lab2.cpp  -o lab2 

CardDatabase.o:  CardDatabase.cpp CardDatabase.h
	$(CCC) $(CCFLAGS) -c CardDatabase.cpp

Card.o:  Card.cpp Card.h
	$(CCC) $(CCFLAGS) -c Card.cpp

clean:
	rm -f *.o
