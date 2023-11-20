//-----------------------------------------------------------------------------
// Shuffle.cpp by Antonio Guizar Orozco
// CruzID: aguizaro
//
// Takes a positive integer as a command line argument specifying the maximum number
// of cards in the deck. The program will then for each n, perform shuffles on the 
// list (0,1,n-1) until the list is back in its original order. The program will print
// to STDOUT each n followed by the number of shuffles. 
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

#define MAX_LEN 300

//performs a single perfect shuffle on the list D (D is modified)
void shuffle(List& D){
    int len= D.length();
    if (len <=1){ return;} //do nothing if the list has only 1 element
    if (len <=2){ //if the list only has 2 elements, swap them
        //store front and back elements
        ListElement first= D.front();
        ListElement second= D.back();
        D.moveFront(); D.moveNext();
        //swap front and back elements
        D.setBefore(second); D.setAfter(first);
        return; //exit function
    }
    //handles cases of list.length() 3 and higher
    List split1, split2;
    int cursor_split_position= len / 2;
    //split list into 2 halves, split1 and split2
    D.moveFront();
    while (D.position() < cursor_split_position){
        split1.insertBefore(D.moveNext());
    }
    while (D.position() < len){
        split2.insertBefore(D.moveNext());
    }
    D.clear(); // clear the contents of D and merge/mix both halves of list.
    if (len % 2 != 0){ //the case for list having odd number of elements
        split1.moveFront(); split2.moveFront();
        for (int i= 0; i< len/2; i++){
            D.insertBefore(split2.moveNext());
            D.insertBefore(split1.moveNext());
        }
        D.insertBefore(split2.moveNext());
    }else{ //case for list having an even number of elements
        split1.moveFront(); split2.moveFront();
        for (int i= 0; i< len/2; i++){
            D.insertBefore(split2.moveNext());
            D.insertBefore(split1.moveNext());
        }
    }
}



int main(int argc, char * argv[]){
    int n= 0, count= 0;
    // check command line for correct number of arguments
    if(argc != 2){
        std::cerr << "Usage: " << argv[0] << " <POSITIVE INTEGER>" << std::endl;
        return(EXIT_FAILURE);
    }
    try { //convert command line arg to int if possible
        n= std::stoi(argv[1]);
        //throw exception if input is not a positive integer
        if (n < 1){ throw std::exception();}
    } catch (const std::exception& e) {
        std::cerr << "Usage: " << argv[0] << " <POSITIVE INTEGER>" << std::endl;
        return(EXIT_FAILURE);
    }

    //print table
    std::cout << "deck size       shuffle count"  << std::endl;
    std::cout << "------------------------------" << std::endl;

    //perform shuffle operations and print to STDOUT for each n
    for(int i=1; i<=n; i++){
        count= 0;
        // make a list of size i
        List L;
        for(int j=0; j<i; j++){
            L.insertBefore(j);
        }
        List copyL= L;
        shuffle(L);
        count++;
        while(!(copyL == L)){
            shuffle(L);
            count++;
        }
        std::cout << " " << i << "               " << count << " " << std::endl;
    }


    return(EXIT_SUCCESS);
}
