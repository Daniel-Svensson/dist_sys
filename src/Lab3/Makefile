
CCC = g++
CCFLAGS =  -g
LIBS = -lsocket -lxnet 
O_OBJ = Card.o CardDatabase.o arg.o
V_OBJ = Card.o CardDatabase.o arg.o
C_OBJ = Card.o CardDatabase.o CardWrite.o arg.o
LAB2_OBJ = Card.o CardDatabase.o CardWrite.o arg.o

all: overview viewimage createcard

overview: overview.cpp $(O_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(O_OBJ) overview.cpp  -o ../../overview.cgi

viewimage: viewimage.cpp $(V_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(V_OBJ) viewimage.cpp  -o ../../viewimage.cgi

createcard: createcard.cpp $(C_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(C_OBJ) createcard.cpp  -o ../../createcard.cgi

CardDatabase.o:  CardDatabase.cpp CardDatabase.h Card.h
	$(CCC) $(CCFLAGS) -c CardDatabase.cpp

CardWrite.o:  CardWrite.cpp CardWrite.h
	$(CCC) $(CCFLAGS) -c CardWrite.cpp

Card.o:  Card.cpp Card.h
	$(CCC) $(CCFLAGS) -c Card.cpp

arg.o : arg.cpp arg.h
	$(CCC) $(CCFLAGS) -c arg.cpp
clean:
	rm -f *.o
