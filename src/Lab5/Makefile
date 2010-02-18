ORBDIR		= /home/TDDD25/ORB4
IDL		= $(ORBDIR)/bin/idl
CXX             = g++
CXXFLAGS        = -fPIC -Wall -g -ggdb
LIBS            = -lOB -lJTC -lsocket -lnsl -ldl -lposix4 -lpthread -lCosNaming -lboost_thread-gcc-mt
OB_CPPFLAGS     = -I. -I$(ORBDIR)/include -O0
OB_LDFLAGS      = -L$(ORBDIR)/lib

COMMON_OBJS	= Lock_skel.o Lock_impl.o Lock.o

TESTCLIENT_OBJS = Testclient.o 

all: testclient

testclient: $(COMMON_OBJS) $(TESTCLIENT_OBJS)
	rm -f $@
	$(CXX) $(CXXFLAGS) $(OB_LDFLAGS) -o $@ \
	$(COMMON_OBJS) $(TESTCLIENT_OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(OB_CPPFLAGS) $(CXXFLAGS) $<


Lock.cpp Lock.h: Lock.idl
	rm -f Lock.cpp Lock.h
	rm -f Lock_skel.cpp Lock_skel.h
	$(IDL) Lock.idl

Lock_skel.cpp Lock_skel.h: Lock.cpp

clean:
	rm -f *.o core *~ *.ref
