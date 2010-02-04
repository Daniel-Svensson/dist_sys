
CCC = g++
ORBDIR	= /home/TDDD25/ORB4
CCFLAGS =  -g -fPIC -Wall -I. -I$(ORBDIR)/include
LIBS =  -L$(ORBDIR)/lib -lsocket -lxnet -lOB -lJTC -lnsl -ldl -lposix4 -lpthread -lCosNaming

COMMON_OBJ = arg.o Writer.o Database.o
O_OBJ = $(COMMON_OBJ)
V_OBJ = $(COMMON_OBJ)
C_OBJ = $(COMMON_OBJ)


IDL		= $(ORBDIR)/bin/idl


all: lab3

lab3: lab3.cpp $(O_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(O_OBJ) lab3.cpp  -o lab3

viewimage: viewimage.cpp $(V_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(V_OBJ) viewimage.cpp  -o ../../viewimage.cgi

createcard: createcard.cpp $(C_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(C_OBJ) createcard.cpp  -o ../../createcard.cgi

Database.o:  Database.cpp Database.h
	$(CCC) $(CCFLAGS) -c Database.cpp

Writer.o:  Writer.cpp Writer.h
	$(CCC) $(CCFLAGS) -c Writer.cpp


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
