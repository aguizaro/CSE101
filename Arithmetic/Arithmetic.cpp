//-----------------------------------------------------------------------------
// Arithmetic.cpp by Antonio Guizar Orozco
// PA6
// CruzID: aguizaro
//
// This is the top level client program that performs basic operations on
// 2 BigIntegers specified by the given input file. Output is printed to 
// the given output file.
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"

#define MAX_LEN 999999999999999

int main(int argc, char * argv[]){

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

   std::getline(in, line);   //Get first BigInt and set it to A
   BigInteger A(line);
   std::getline(in, line);   //Ignore second line
   std::getline(in, line);   //Get second BigInt and set it to B
   BigInteger B(line);

   out << A << std::endl;
   out<<std::endl;
   out << B << std::endl;
   out<<std::endl;
   out << A+B << std::endl;
   out<<std::endl;
   out << A-B << std::endl;
   out<<std::endl;
   out << A-A << std::endl;
   out<<std::endl;
   out << 3*A - 2*B << std::endl;
   out<<std::endl;
   out << A*B << std::endl;
   out<<std::endl;
   out << A*A << std::endl;
   out<<std::endl;
   out << B*B << std::endl;
   out<<std::endl;
   out << 9*(A*A*A*A) + 16*(B*B*B*B*B) << std::endl;
   
   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
