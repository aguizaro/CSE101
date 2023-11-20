#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes Arithmetic
#  make BigIntegerClient    makes BigIntegerClient
#  make BigIntegerTest      makes BigIntegerTest
#  make ListClient          makes ListClient
#  make ListTest            makes ListTest
#  make clean               removes all binaries
#  make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
#  make BigIntegerCheck1    runs BigIntegerClient in valgrind
#  make BigIntegerCheck2    runs BigIntegerTest in valgrind
#  make ListCheck1          runs ListCheck in valgrind
#  make ListCheck2          runs ListTest in valgrind
#------------------------------------------------------------------------------

MAIN           = Arithmetic
ADT1           = BigInteger
ADT2           = List
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT1_TEST1     = $(ADT1)Client
ADT1_TEST2     = $(ADT1)Test
ADT1_SOURCE    = $(ADT1).cpp
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_TEST1     = $(ADT2)Client
ADT2_TEST2     = $(ADT2)Test
ADT2_SOURCE    = $(ADT2).cpp
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT1_TEST1): $(ADT1_TEST1).o $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(ADT1_TEST1) $(ADT1_TEST1).o $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT1_TEST2): $(ADT1_TEST2).o $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(ADT1_TEST2) $(ADT1_TEST2).o $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT2_TEST1): $(ADT2_TEST1).o $(ADT2_OBJECT)
	$(LINK) $(ADT2_TEST1) $(ADT2_TEST1).o $(ADT2_OBJECT)

$(ADT2_TEST2): $(ADT2_TEST2).o $(ADT2_OBJECT)
	$(LINK) $(ADT2_TEST2) $(ADT2_TEST2).o $(ADT2_OBJECT)

$(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_TEST1).o: $(ADT1_TEST1).cpp $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(ADT1_TEST1).cpp

$(ADT1_TEST2).o: $(ADT1_TEST2).cpp $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(ADT1_TEST2).cpp

$(ADT2_TEST1).o: $(ADT2_TEST1).cpp $(ADT2_HEADER)
	$(COMPILE) $(ADT2_TEST1).cpp

$(ADT2_TEST2).o: $(ADT2_TEST2).cpp $(ADT2_HEADER)
	$(COMPILE) $(ADT2_TEST2).cpp

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT1_TEST1) $(ADT1_TEST2) $(ADT2_TEST1) $(ADT2_TEST2) 
	$(REMOVE) $(OBJECT) $(ADT1_TEST1).o $(ADT1_TEST2).o $(ADT2_TEST1).o $(ADT2_TEST2).o $(ADT1_OBJECT) $(ADT2_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) in4 junk4

$(ADT1)Check1: $(ADT1_TEST1)
	$(MEMCHECK) $(ADT1_TEST1)

$(ADT1)Check2: $(ADT1_TEST2)
	$(MEMCHECK) $(ADT1_TEST2)

$(ADT2)Check1: $(ADT2_TEST1)
	$(MEMCHECK) $(ADT2_TEST1)

$(ADT2)Check2: $(ADT2_TEST2)
	$(MEMCHECK) $(ADT2_TEST2)