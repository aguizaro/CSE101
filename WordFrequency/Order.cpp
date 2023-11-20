//-----------------------------------------------------------------------------
// Order.cpp by Antonio Guizar Orozco
// PA8
// CruzID: aguizaro
//
// This program will read in words from an input file and insert them
// into a Dictionary ADT. The program will then print the in-order string
// representation of the dictionary, then will print the keys as defined
// by a pre-order tree walk on the underlying BST.
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

int main(int argc, char * argv[]){
    int line_count=0;
    std::ifstream in;
    std::ofstream out;
    std::string line;
    // check command line for correct number of arguments
    if( argc != 3 ){
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return(EXIT_FAILURE);
    }
    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
        return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
        std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
        return(EXIT_FAILURE);
    }

    Dictionary D;
    while( getline(in, line) )
        D.setValue(line, ++line_count);


    out << D << std::endl;
    out << D.pre_string() << std::endl;

    // close files 
    in.close();
    out.close();
    return(EXIT_SUCCESS);
}
