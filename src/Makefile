
CCC = g++
CCFLAGS =  -I ./asio-1.4.1/include -g 
LIBS = -lsocket -lxnet 
LAB2_OBJ = Card.o CardDatabase.o NetworkBase.o
O_OBJ = Card.o CardDatabase.o NetworkBase.o
V_OBJ = Card.o CardDatabase.o NetworkBase.o
C_OBJ = Card.o CardDatabase.o NetworkBase.o CardWrite.o

all: overview viewimage createcard

overview: overview.cpp $(O_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(O_OBJ) lab2.cpp  -o overview.cgi

viewimage: lab2.cpp $(V_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(V_OBJ) lab2.cpp  -o viewimage.cgi

createcard: lab2.cpp $(C_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(C_OBJ) lab2.cpp  -o createcard.cgi

lab2: lab2.cpp $(LAB2_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(LAB2_OBJ) lab2.cpp  -o lab2 

CardDatabase.o:  CardDatabase.cpp CardDatabase.h NetworkBase.h Card.h
	$(CCC) $(CCFLAGS) -c CardDatabase.cpp

NetworkBase.o:  NetworkBase.cpp NetworkBase.h
	$(CCC) $(CCFLAGS) -c NetworkBase.cpp

Card.o:  Card.cpp Card.h
	$(CCC) $(CCFLAGS) -c Card.cpp

clean:
	rm -f *.o
