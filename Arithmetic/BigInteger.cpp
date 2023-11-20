//-----------------------------------------------------------------------------
// BigInteger.cpp by Antonio Guizar Orozco
// PA6
// CruzID: aguizaro
//
// Impementation file for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<cmath>
#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include"BigInteger.h"
#include"List.h"

int POWER= 9;
ListElement BASE= std::pow(10,POWER);

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum= 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    bool neg; //neg is true if x is negative
    int result, digit;
    if (x < 0){ neg= true; x*= -1; } //set x to always non-negative
    else if (x > 0){ neg= false;}
    else { signum= 0; return;} //if x == 0: signum= 0 and digits= ()

    if (x < BASE){ //if x can be represented by single entry in list [0-BASE)
        if (x < 0){ digits.insertBefore(x);} //insert single long into list
        else if (x > 0){ digits.insertBefore(x);} //insert single long into list
        else{ signum= 0; return;} //if x is 0, set sign to 0 and list is empty
    }else if (x > BASE){ //x must be represented as multiple long entries in a list
        //this algorithm inserts base [BASE] digits into list digits
        for(int i= 1; x > 0; i*=BASE){
            result= x % (i*BASE);
            digit= result/i;
            digits.insertAfter(digit);
            x-=result;
        }
    }else{ //x is equal to base
        digits.insertAfter(0);
        digits.insertAfter(1);
    }
    (neg)? signum= -1: signum= 1;//set coorect sign
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    //throw exception if string is empty
    if (s.length() <= 0) throw std::invalid_argument("BigInteger: Constructor: empty string");

    std::string digs;
    //figure out signum of the new BigInt object
    char first_c= s[0];
    bool first_done= false;
    if (first_c == '-'){ first_done= true; signum= -1;}
    else if (first_c == '0' && s.length() == 1){ signum= 0; return;}
    else if (first_c == '+'){ first_done= true; signum= 1;}
    else{ signum= 1;}
    //set up string for parse
    if (first_done){ 
        digs= s.substr(1);
        if (digs.length() <= 0) throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }else{ digs= s;}

    int j=0; //remove leading zeros if there are any
    if (digs[j] == '0'){
        while (digs[j] == '0'){ j++; }
        digs= digs.substr(j);
    }

    std::string currentGroup;
    ListElement group;
    int index= 0;

    //iterate from back of string to front of sring
    for (auto it= digs.rbegin(); it != digs.rend(); it++){
        index++;
        //check if character is non-numeric
        if (!(std::isdigit(*it))){ throw std::invalid_argument("BigInteger: Constructor: non-numeric string");}
        currentGroup= *it + currentGroup;
        if (index%POWER == 0){
            //throw exception if string cannot be converted to long type
            try{ group= std::stol(currentGroup);}
            catch (std::invalid_argument const&){ throw std::invalid_argument("BigInteger: Constructor: non-numeric string");}
            catch (std::out_of_range const&){ throw std::invalid_argument("BigInteger: Constructor: non-numeric string");}
            digits.insertAfter(group);
            currentGroup= "", group= -1;
        }
    }
    if (index%POWER > 0){ 
        //throw exception if string cannot be converted to long type
        try{ group= std::stol(currentGroup);}
        catch (std::invalid_argument const&){ throw std::invalid_argument("BigInteger: Constructor: non-numeric string");}
        catch (std::out_of_range const&){ throw std::invalid_argument("BigInteger: Constructor: non-numeric string");}
        digits.insertAfter(group);
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    signum= N.signum;
    digits= N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    if ((signum == 0) && (N.signum == 0)){ return 0;}
    if (signum < N.signum){ return -1; }
    if (signum > N.signum){ return 1; }

    //if signums are non-zero and equal, check if lists are equal
    if (digits == N.digits) return 0;
    //if lists not equal, compare each digit from left to right
    std::string dig1= digits.to_string();
    std::string dig2= N.digits.to_string();
    for(int i= 0; i< (int)dig1.length(); i++){
        if (dig1[i] > dig2[i] ) return 1;
        else if (dig1[i] <  dig2[i] ) return -1;
    }
    return 0;
}

// Helper functions -------------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
// cursor position is modified then restored after function call
void negateList(List& L){
    int pos= L.position(); //store current position of cursor
    L.moveFront();
    while (L.position() < L.length()){
        L.setAfter(L.peekNext() * -1); //set each entry to its opposite
        L.moveNext();
    }
    //return cursor to original position
    L.moveFront();
    for (int i= 0; i< pos; i++){
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    long result;
    bool nonzero_entry= false;
    int lenA= A.length(), lenB= B.length();
    if (sgn == -1){ negateList(B);} //negate B if for vector dif
    //handle case where both A and B are empty
    if ((lenA == 0) && (lenB == 0)){ return;}
    //handle case where B is empty
    if (lenB == 0){ S=A; return;}
    //handle case where A is empty
    if (lenA == 0){ S=B; return;}

    S.clear(); //clear S in case its non-empty
    //insert sum of each list element from right to left
    int min_length= std::min(A.length(), B.length());
    A.moveBack(); B.moveBack();
    for (int i= 0; i< min_length; i++){
        result= A.movePrev() + B.movePrev();
        if (result != 0){ nonzero_entry= true;}
        S.insertAfter(result);
    }
    //case where there are still more digits in A
    if(A.position() != 0){
        while(A.position() > 0){
            result= A.movePrev();
            if (result != 0){ nonzero_entry= true;}
            S.insertAfter(result);
        }
    }
    //case where there are still more digits in B
    else if(B.position() != 0){
        while(B.position() > 0){
            result= B.movePrev();
            if (result != 0){ nonzero_entry= true;}
            S.insertAfter(result);
        }
    }
    //if sum resulted in an integer of zero, clear list
    if (!nonzero_entry) S.clear();
    S.moveFront();
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
    //do nothing if list is empty
    if (L.length() <= 0){ return 0;}
    ListElement entry; //stores current list element
    int pos= L.position();
    L.moveBack(); //check each entry from back to index 1 
    while(L.position() > 1){
        entry= L.movePrev();
        if ( (entry >= BASE) ){
            L.setAfter(entry%BASE);
            L.setBefore(L.peekPrev() + (entry/BASE));
        }
        else if (entry < 0){
            L.setAfter(entry+BASE*(entry*(-1)/BASE+1));
            L.setBefore(L.peekPrev() - (entry*(-1)/BASE+1));
        }
    }
    //check most significant digit
    entry= L.movePrev();
    if ( (entry >= BASE) ){
        L.setAfter(entry%BASE);
        L.insertAfter(entry/BASE);
        //return cursor to original position
        L.moveFront();
        for (int i= 0; i< pos; i++){
            L.moveNext();
        }
        return -1;
    }
    else if(entry < 0){
        L.setAfter(entry+BASE*(entry*(-1)/BASE+1));
        L.insertAfter(entry/BASE-1);
        //return cursor to original position
        L.moveFront();
        for (int i= 0; i< pos; i++){
            L.moveNext();
        }
        return -1;
    }
    //return cursor to original position
    L.moveFront();
    for (int i= 0; i< pos; i++){
        L.moveNext();
    }
    return 1;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    if (p == 0) return;
    int pos= L.position();
    ListElement pad= 0;
    L.moveBack();
    for (int i= 0; i<p; i++){
        L.insertBefore(pad);
    }
    //return cursor to original position
    L.moveFront();
    for (int i= 0; i< pos; i++){
        L.moveNext();
    }
}
// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    if (m == 0){ L.clear(); return;} //if mutliplying by zero, make list empty
    int pos= L.position(); //store current position of cursor
    L.moveBack();
    while (L.position() > 0){
        L.setBefore(L.peekPrev() * m); //set each entry to its opposite
        L.movePrev();
    }
    //return cursor to original position
    L.moveFront();
    for (int i= 0; i< pos; i++){
        L.moveNext();
    }
}

// Manipulation procedures -------------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum= 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if (signum == 0){ return; }
    signum*= -1;
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger B;
    //prepare lists for vector addition by making each entry signed
    List this_list= this->digits;
    List N_list= N.digits;
    if (this->signum == -1){ negateList(this_list);}
    if (N.signum == -1){ negateList(N_list);}

    //perform vector addition and save sum into B.digits
    sumList(B.digits,this_list,N_list, 1);
    //normalize list for current base
    normalizeList(B.digits);

    //check if sum of A + B is 0.
    if (B.digits.length() == 0){
        B.signum= 0;
        return B;
    }
    //check if most significant digit is neg
    if (B.digits.front() < 0){
        B.signum= -1;
        negateList(B.digits);
        normalizeList(B.digits);
    }else{
        B.signum= 1;
    }

    //check if there are any leading zeros, remove them if so
    B.digits.moveFront();
    while((B.digits.length() > 0) && (B.digits.peekNext() == 0)){
        B.digits.moveFront();
        B.digits.eraseAfter();
    }
    return B;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger B;
    //prepare lists for vector subtraction by making each entry signed
    List this_list= this->digits;
    List N_list= N.digits;
    if (this->signum == -1){ negateList(this_list);}
    if (N.signum == -1){ negateList(N_list);}
    //perform vector subtraction and save diff into B.digits
    sumList(B.digits,this_list,N_list, -1);
    //check if diff of A - B is 0.
    if (B.digits.length() == 0){
        B.signum= 0;
        return B;
    }
    //check if most significant digit is neg
    if (B.digits.front() < 0){
        B.signum= -1;
        negateList(B.digits);
    }else{
        B.signum= 1;
    }
    //normalize list for current base
    normalizeList(B.digits);
    //check if there are any leading zeros, remove them if so
    B.digits.moveFront();
    while((B.digits.length() > 0) && (B.digits.peekNext() == 0)){
        B.digits.moveFront();
        B.digits.eraseAfter();
    }
    return B;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    int num_zero_pad= 0;
    BigInteger product;
    List L= N.digits, buff= this->digits;
    //if either BigInt is zero, return a zero BitgInt
    if ((this->signum == 0) || (N.signum == 0)){ product.signum= 0; return product;}

    L.moveBack();
    while(L.position() > 0){
        buff= this->digits;
        ListElement entry= L.movePrev();
        shiftList(buff, num_zero_pad); //add trailing zeros
        num_zero_pad++;
        scalarMultList(buff, entry);                        //scalarMult
        normalizeList(buff);                                //normalize
        sumList(product.digits, buff, product.digits, 1);   //product.digits+= buff
        normalizeList(product.digits);
    }
    bool this_sgn= this->signum == 1;
    bool N_sgn= N.signum == 1;
    //xor condition to determine sign of product
    if ((this_sgn && !N_sgn) || (!this_sgn && N_sgn)) product.signum= -1;
    else product.signum= 1;
    return product;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::stringstream ss("");
    if (signum == 0){ return "0";}
    else{ //for non empty case
        (signum == -1)? ss << "-": ss << "";
        digits.moveFront();
        for(int i= 0; i<digits.length(); i++){
            //don't print leading zeros
            if (i == 0) ss << std::to_string(digits.moveNext());
            //print value in its base form padded with 0s
            else ss << std::setw(POWER) << std::setfill('0') << std::to_string(digits.moveNext());
        }
    }
    return ss.str();
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 0) return true;
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1) return true;
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) <= 0) return true;
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1) return true;
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) >= 0) return true;
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

// operator+s=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A= A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A= A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A= A.mult(B);
    return A;
}

