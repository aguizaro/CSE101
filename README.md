# CSE101_PROJECTS
Select C and C++ projects from the CSE:101: Data Structures and Algorithms course at UCSC. 

## Lex
This project contains files:
Lex.c           This program takes an input file and uses the List module to output each line to another file in lexicographical order.
List.h          This is the header file for the List module.
List.c          This is the implementation file for the List module.
ListTest.c      This is a test client for the List module.
Makefile        This file is used to build the project.

## Find Path
This project contains files:
FindPath.c      This program takes an input file and uses the Graph module to output the adjacency list and shortest paths to an output file.
Graph.h         This is the header file for the Graph module.
Graph.c         This is the implementation file for the Graph module.
List.h          This is the header file for the List module.
List.c          This is the implementation file for the List module.
GraphTest.c     This is a test client for the Graph module.
Makefile        This file is used to build the project.

## Find Components
This project contains files:
FindComponents.c      This program takes an input file and uses the Graph module to output the adjacency list and the sets of strongly connected components.
Graph.h               This is the header file for the Graph module.
Graph.c               This is the implementation file for the Graph module.
List.h                This is the header file for the List module.
List.c                This is the implementation file for the List module.
GraphTest.c           This is a test client for the Graph module.
Makefile              This file is used to build the project.

## Sparse
This project contains files:
Sparse.c              This program takes an input file and performs matrix operations, printing results to an output file.
Matrix.h              This is the header file for the Matrix module.
Matrix.c              This is the implementation file for the Matrix module.
MatrixTest.c          This is the test client for the Matrix module.
List.h                This is the header file for the List module.
List.c                This is the implementation file for the List module.
ListTest.c            This is a test client for the List module.
Makefile              This file is used to build the project.

## Shuffle
This project contains files:
Shuffle.c             Takes a positive integer as a command line argument specifying the maximum number of cards in the deck. The program will then for each n, perform shuffles on the list (0,1,n-1) until the list is back in its original order. The program will print to STDOUT each n followed by the number of shuffles. 
List.h                This is the header file for the List module.
List.c                This is the implementation file for the List module.
ListTest.c            This is a test client for the List module.
Makefile              This file is used to build the project.

## Arithmetic
This project contains files:
Arithmetic.cpp        This is the top level client program that performs basic operations on 2 BigIntegers specified by the given input file. Output is printed to the given output file.
List.h                This is the header file for the List module.
List.cpp              This is the implementation file for the List module.
ListTest.cpp          This is a test client for the List module.
BigInteger.h          This is the header file for the BigInteger module
BigInteger.cpp        This is the implementation file for the BigInteger module
BigIntegerTest.cpp    This is a test client for the BigInteger module.
Makefile              This file is used to build the project.

## Tree Order
This project contains files:
Order.cpp             This program will read in words from an input file and insert them into a Dictionary ADT. The program will then print the in-order string representation of the dictionary, then will print the keys as defined by a pre-order tree walk on the underlying BST.
Dictionary.h          This is the header file for the Dictionary module
Dictionary.cpp        This is the implementation file for the Dictionary module
DictionaryTest.cpp    This is a test client for the Dictionary module.
Makefile              This file is used to build the project.

## Word Frequency
This project contains files:
WordFrequency.cpp     This program will read from an input file and insert each word as a key and its value will be equal to the number of occurrences of that word in the input file. This program will print the Dictionary to an output file.
Order.cpp             This program will read in lines of words from an input file and insert them into a Dictionary ADT. The program will then print the in-order string representation of the dictionary, then will print the keys as defined by a pre-order tree walk on the underlying BST.
Dictionary.h          This is the header file for the Dictionary module
Dictionary.cpp        This is the implementation file for the Dictionary module
DictionaryTest.cpp    This is a test client for the Dictionary module.
Makefile              This file is used to build the project.