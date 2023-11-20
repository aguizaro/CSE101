#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8 by Antonio Guizar Orozco
#  CruzID: aguizaro
#
#  make                     makes WordFrequency
#  make Order               makes Order
#  make DictionaryTest      makes DictionaryTest
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make OrderCheck          runs Order under valgrind on test input
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
CLIENT		   = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
SOURCE2        = $(CLIENT).cpp
OBJECT2        = $(CLIENT).o
ADT_TEST       = $(ADT)Test
ADT_CLIENT     = $(ADT)Client
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c -g
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --track-origins=yes --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(CLIENT): $(OBJECT2) $(ADT_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT2) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(ADT_CLIENT): $(ADT_CLIENT).o $(ADT_OBJECT)
	$(LINK) $(ADT_CLIENT) $(ADT_CLIENT).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(OBJECT2): $(SOURCE2) $(ADT_HEADER)
	$(COMPILE) $(SOURCE2)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_CLIENT).o: $(ADT_CLIENT).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_CLIENT).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(CLIENT) $(ADT_TEST) $(ADT_CLIENT) $(OBJECT) $(OBJECT2) $(ADT_TEST).o $(ADT_CLIENT).o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg Gutenberg-out

$(CLIENT)Check: $(CLIENT)
	$(MEMCHECK) $(CLIENT) in1 out1

$(ADT)Check1: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)

$(ADT)Check2: $(ADT_CLIENT)
	$(MEMCHECK) $(ADT_CLIENT)
