
CCC = g++
ORBDIR		= /home/TDDD25/ORB4
CCFLAGS =  -g -fPIC -Wall -I. -I$(ORBDIR)/include
LIBS =  -L$(ORBDIR)/lib -lsocket -lxnet -lOB -lJTC -lnsl -ldl -lposix4 -lpthread


O_OBJ = Card.o CardDatabase.o arg.o
V_OBJ = Card.o CardDatabase.o arg.o
C_OBJ = Card.o CardDatabase.o CardWrite.o arg.o


IDL		= $(ORBDIR)/bin/idl


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


%.o: %.cpp %.h
	$(CCC) $(CCFLAGS) -c $<

Writer.cpp Writer.h: Writer.idl
	rm -f Writer.cpp Writer.h
	$(IDL) --no-type-codes Writer.idl
	rm -f Writer_skel.cpp Writer_skel.h

Database.cpp Database.h: Database.idl
	rm -f Database.cpp Database.h
	$(IDL) --no-type-codes Database.idl
	rm -f Database_skel.*

clean:
	rm -f *.o
