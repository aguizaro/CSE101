//-----------------------------------------------------------------------------
// ListTest.cpp by Antonio Guizar Orozco 
// CruzID: aguizaro
//
// Client file for the List module that tests all operations of the ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

int main(){
    List a, b, c, d;
    for (int i= 1; i<= 12; i++){
        a.insertBefore(i);
        b.insertAfter(i);
        c.insertBefore(i*i);
    }
    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "C: " <<  c << std::endl;
    std::cout << "D: " <<  d << std::endl;
    
    std::cout << std::endl;


    a.moveFront(); b.moveFront();
    a.findNext(3); b.findNext(3);
    a.eraseBefore(); b.eraseBefore();

    b.moveBack();
    for(int j=0; j<b.length(); j++){
        d.insertAfter(b.movePrev());
    }

    std::cout << "(B == D) ->  ";
    (b==d)? std::cout << "TRUE" << std::endl : std::cout << "FALSE" << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "D: " << d << std::endl;

    a.moveBack(); a.movePrev();
    a.setBefore(20); a.setAfter(30);

    b.moveFront(); b.moveNext();
    b.setBefore(30); b.setAfter(20);

    c.moveFront(); c.moveNext(); c.moveNext();
    c.insertBefore(5); c.insertAfter(8);
    c.insertBefore(6); c.insertBefore(7);
    c.moveBack(); c.movePrev(); c.movePrev();

    List e= d;
    e.moveFront(); e.moveNext();
    e.setBefore(30); e.setAfter(20);


    std::cout << "(B == E) ->  ";
    (b==e)? std::cout << "TRUE" << std::endl : std::cout << "FALSE" << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "E: " << e << std::endl;

    a.clear();
    e= d= c= b= a;
    std::cout << std::endl;
    std::cout <<  "A: " << a;
    std::cout << " B: " << b;
    std::cout << " C: " << c;
    std::cout << " D: " << d;
    std::cout << " E: " << e;
    std::cout << std::endl << std::endl;

    a.insertAfter(2); a.insertAfter(-2);
    std::cout << "Front: " << a.front() << ", Back: " << a.back() << std::endl;
    a.moveNext(); a.insertBefore(-1); a.insertBefore(0); a.insertBefore(1);
    std::cout <<  "A: " << a << " - length: " << a.length() << std::endl;

    b= a;
    b.moveBack(); b.insertBefore(3); b.insertAfter(5); b.insertAfter(4);
    std::cout <<  "B: " << b << " - length: " << b.length() << std::endl;

    c= a.concat(b);
    std::cout << "C cursor position: " << c.position() << std::endl;
    std::cout <<  "before clean => C: " << c << " - length: " << c.length() << std::endl;
    c.cleanup();
    std::cout <<  "after clean => C: " << c << " - length: " << c.length() << std::endl;
    std::cout << "C cursor position: " <<c.position() << std::endl;
    std::cout << "A cursor position: " <<a.position() << std::endl;
    a.cleanup();
    std::cout << "A cursor position after clean: " <<a.position() << std::endl;
    std::cout << "A: " << a << std::endl;
    std::cout << a.peekPrev() << " " << a.peekNext() << std::endl;

    a.moveBack();
    a.findPrev(0);
    a.eraseAfter();

    std::cout << "A: " << a << std::endl;

    a.findPrev(-1);
    a.eraseAfter();
    a.findPrev(-2);
    a.eraseAfter();

    std::cout << "A: " << a << std::endl;
    std::cout << a.findPrev(-2) << std::endl;
    std::cout << a.position() << std::endl;
    a.moveNext();
    std::cout << "A: (" << a.peekPrev() << ", " << a.peekNext() << ")" << std::endl;

    List F;
    List G= F;
    G.insertAfter(1);
    G.insertAfter(2);
    G.insertAfter(3);
    G.insertAfter(5);
    G.insertAfter(12);
    
    std::cout << "len G:  " << G.length() << std::endl;

    F.insertBefore(1);
    F.insertBefore(5);
    F.insertBefore(16);
    F.insertBefore(176);
    F.insertBefore(200);
    F.insertBefore(16);
    F.findPrev(16);
    F.moveNext();
    F.insertAfter(225);
    std::cout << "F position:  " << F.position() << std::endl;
    F.movePrev();
    std::cout << "F position:  " << F.position() << std::endl;
    F.findPrev(16);
    std::cout << "F position:  " << F.position() << std::endl;

    return 0;
}
/*
Output of program:
A: (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)
B: (12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
C: (1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144)
D: ()

(B == D) ->  TRUE
B: (12, 11, 10, 9, 8, 7, 6, 5, 4, 2, 1)
D: (12, 11, 10, 9, 8, 7, 6, 5, 4, 2, 1)
(B == E) ->  TRUE
B: (30, 20, 10, 9, 8, 7, 6, 5, 4, 2, 1)
E: (30, 20, 10, 9, 8, 7, 6, 5, 4, 2, 1)

A: () B: () C: () D: () E: ()

Front: -2, Back: 2
A: (-2, -1, 0, 1, 2) - length: 5
B: (-2, -1, 0, 1, 2, 3, 4, 5) - length: 8
C cursor position: 13
before clean => C: (-2, -1, 0, 1, 2, -2, -1, 0, 1, 2, 3, 4, 5) - length: 13
after clean => C: (-2, -1, 0, 1, 2, 3, 4, 5) - length: 8
C cursor position: 8
A cursor position: 4
A cursor position after clean: 4
A: (-2, -1, 0, 1, 2)
1 2
A: (-2, -1, 1, 2)
A: (1, 2)
-1
0
A: (1, 2)
len G:  5
F position:  6
F position:  5
F position:  2
*/

