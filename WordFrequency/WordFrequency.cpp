//-----------------------------------------------------------------------------
// WordFrequency.cpp by Antonio Guizar Orozco
// PA8
// CruzID: aguizaro
//
// This program will read from an input file and insert each word as a
// key and its value will be equal to the number of occurances of that word 
// in the input file. This program will print the Dictionary to an output file.
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include"Dictionary.h"

using namespace std;

#define MAX_LEN 9999999

int main(int argc, char * argv[]){
    Dictionary D;
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string tokenBuffer;
    string token;
    string delim = " \t\\\"\',<.>/%?;:[{]}|`~!@#$^&*()-_=+0123456789";

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }
    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read each line of input file
    while( getline(in, line) )  {
        len = line.length();
        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        
        while( token!="" ){  // we have a token
            //make token all lowercase using str transform
            std::transform(token.begin(), token.end(), token.begin(), ::tolower);
            //check if token is already in dictionary
            if (D.contains(token)){
                D.getValue(token)++; //increment the value/frequency of token by 1
            }else{//add token to Dictionary if token does not exist
                D.setValue(token, 1);
            }

            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
    }

    out << D << std::endl;

    // close files 
    in.close();
    out.close();

   return(EXIT_SUCCESS);
}
