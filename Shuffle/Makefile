#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make ListTest       make ListTest
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on ListTest
#  make check3         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

Shuffle : Shuffle.o List.o
	g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
	g++ -std=c++17 -Wall -c -g Shuffle.cpp

ListClient : ListClient.o List.o
	g++ -std=c++17 -Wall -o ListClient ListClient.o List.o 

ListClient.o : List.h ListClient.cpp
	g++ -std=c++17 -Wall -c -g ListClient.cpp

ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c -g ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c -g List.cpp

clean :
	rm -f Shuffle Shuffle.o ListClient ListTest ListClient.o ListTest.o List.o

check1 : ListClient
	valgrind --leak-check=full ListClient

check2 : ListTest
	valgrind --leak-check=full ListTest

check3 : Shuffle
	valgrind --leak-check=full Shuffle 35