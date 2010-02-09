
CCC = g++
ORBDIR	= /home/TDDD25/ORB4
CCFLAGS =  -g -fPIC -Wall -I. -I$(ORBDIR)/include
LIBS =  -L$(ORBDIR)/lib -lsocket -lxnet -lOB -lJTC -lnsl -ldl -lposix4 -lpthread -lCosNaming

COMMON_OBJ =  Database_skel.o Database.o Database_impl.o
O_OBJ = $(COMMON_OBJ)
V_OBJ = $(COMMON_OBJ)
C_OBJ = $(COMMON_OBJ)

# setenv LD_LIBRARY_PATH /home/TDDD25/ORB4/lib:"$LD_LIBRARY_PATH"
# setenv LD_LIBRARY_PATH "home/TDDD25/gcc-3.2.0/lib:/home/TDDD25/ORB4/lib:$LD_LIBRARY_PATH"

IDL		= $(ORBDIR)/bin/idl


all: lab4


lab4: lab4.cpp $(O_OBJ)
	$(CCC) $(CCFLAGS) $(LIBS) $(O_OBJ) lab4.cpp  -o lab4

Database_skel.o:  Database_skel.cpp Database_skel.h
	$(CCC) $(CCFLAGS) -c Database_skel.cpp

Database.o:  Database.cpp Database.h
	$(CCC) $(CCFLAGS) -c Database.cpp

Database_impl.o:  Database_impl.cpp Database_impl.h
	$(CCC) $(CCFLAGS) -c Database_impl.cpp

Database_skel.cpp Database_skel.h: Database.idl
	rm -f Database_skel.*
	$(IDL) --no-type-codes Database.idl


clean:
	rm -f *.o
	rm -f Database_skel.*
	rm -f Database.h Database.cpp
	
