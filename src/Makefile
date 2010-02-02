
CCC = g++
CCFLAGS =  -I ./asio-1.4.1/include -g 
LIBS = -lsocket -lxnet 
LAB2_OBJ = Card.o CardDatabase.o NetworkBase.o CardWrite.o

all: lab2

lab2: lab2.cpp $(LAB2_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(LAB2_OBJ) lab2.cpp  -o lab2 

CardDatabase.o:  CardDatabase.cpp CardDatabase.h NetworkBase.h Card.h
	$(CCC) $(CCFLAGS) -c CardDatabase.cpp

NetworkBase.o:  NetworkBase.cpp NetworkBase.h
	$(CCC) $(CCFLAGS) -c NetworkBase.cpp

CardWrite.o:  CardWrite.cpp CardWrite.h
	$(CCC) $(CCFLAGS) -c CardWrite.cpp

Card.o:  Card.cpp Card.h
	$(CCC) $(CCFLAGS) -c Card.cpp

clean:
	rm -f *.o
