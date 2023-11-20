//-----------------------------------------------------------------------------
// BigIntegerTest.cpp by Antonio Guizar Orozco
// PA6
// CruzID: aguizaro
//
// Test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"BigInteger.h"

void runTest(BigInteger *pA, BigInteger *pB, BigInteger *pC, BigInteger *pD){
    BigInteger A = *pA;
    BigInteger B = *pB;
    BigInteger C = *pC;
    BigInteger D = *pD;

    A= BigInteger("+111122223333");
    B = BigInteger("-112122223333");
    D = BigInteger("-1000000000");
    C = A + B;

    std::cout << "A= " << A << std::endl;
    std::cout << "B= " << B << std::endl;
    std::cout << "C= " << C << std::endl;
    std::cout << "D= " << D << std::endl;


    if (C.sign() != -1)
      std::cout << "WRONG1" << std::endl;
    if (!(C == D))
      std::cout << "WRONG2" << std::endl;

    std::cout << "AFTER TEST" <<std::endl;  
}

int main(){
    BigInteger A(-2147483647);
    BigInteger B(4352116);
    BigInteger C(A);
    BigInteger D;
    BigInteger E(4362116);

    BigInteger F(1);
    BigInteger G(81438860);
    BigInteger H(70327749);
    BigInteger I(80327799);

    C.makeZero();

    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;
    std::cout << "C: " << C << std::endl;
    std::cout << "D: " << D << std::endl;
    std::cout << "E: " << E << std::endl;
    std::cout << "F: " << F << std::endl;
    std::cout << "G: " << G << std::endl;
    std::cout << std::endl;

    (A < B)? std::cout << "A < B" << std::endl: std::cout << "NOT A < B" << std::endl;
    (B > A)? std::cout << "B > A" << std::endl: std::cout << "NOT B > A" << std::endl;
    (C == D)? std::cout << "C = D" << std::endl: std::cout << "NOT C = D" << std::endl;
    (E > B)? std::cout << "E > B" << std::endl: std::cout << "NOT E > B" << std::endl;

    F= F+G;
    G= G-H;
    std::cout << "F = F + G  -> " <<  F << std::endl;
    std::cout << "G = G - H  -> " <<  G << std::endl;
    G= G-G;
    H= H-I;
    std::cout << "G = G - H  -> " <<  G << std::endl;
    std::cout << "H = H - I  -> " <<  H << std::endl;
    
    BigInteger J(123);
    BigInteger K(-4506);
    BigInteger L(11);
    BigInteger M(2153580265);
    BigInteger N(656565);
    BigInteger O(656565);
    BigInteger P(656564);

    std::cout << std::endl;

    std::cout << "G= " <<  G << std::endl;
    std::cout << "J= " <<  J << std::endl;
    std::cout << "K= " <<  K << std::endl;
    std::cout << "L= " <<  L << std::endl;
    std::cout << "M= " <<  M << std::endl;
    std::cout << "N= " <<  N << std::endl;
    std::cout << "O= " <<  O << std::endl;
    std::cout << "P= " <<  P << std::endl;

    std::cout << std::endl;

    J= J * K;
    std::cout << "J= J * K  -> " <<  J << std::endl;
    K.negate();
    if (K.sign() == 1){ std::cout << "CORRECT" << std::endl;}
    J*= L;
    std::cout << "J*= L -> " <<  J << std::endl;
    if (J.sign() == -1){ std::cout << "CORRECT" << std::endl;}
    J+= A;
    std::cout << "J+= A -> " <<  J << std::endl;
    J-= G;
    std::cout << "J-= G -> " <<  J << std::endl;
    J+= M;
    std::cout << "J+= M -> " <<  J << std::endl;
    if (J.sign() == 0){ std::cout << "CORRECT" << std::endl;}
    J.negate();
    if (J.sign() == 0){ std::cout << "CORRECT" << std::endl;}

    std::cout << std::endl;
    (N >= O)? std::cout << "N >= O" << std::endl: std::cout << "NOT N >= O" << std::endl;
    (N <= O)? std::cout << "N <= O" << std::endl: std::cout << "NOT N <= O" << std::endl;
    (P <= O)? std::cout << "P <= O" << std::endl: std::cout << "NOT P <= O" << std::endl;
    (O >= P)? std::cout << "O >= P" << std::endl: std::cout << "NOT O >= P" << std::endl;
    std::cout << std::endl;

    BigInteger Q("+000001234567891011121314151617181920");
    BigInteger R("-1234567891011121314151617181920");
    BigInteger S("-5033");
    BigInteger T("12345");
    BigInteger U("-62132385");

    std::cout << "Q= " << Q << std::endl;
    std::cout << "R= " << R << std::endl;
    std::cout << "S= " << S << std::endl;
    std::cout << "T= " << T << std::endl;
    std::cout << "U= " << U << std::endl;

    std::cout << std::endl;

    ((Q + R) == 0)? std::cout << "CORRECT" << std::endl: std::cout << "NOT CORRECT" << std::endl;
    ((S * T) == U)? std::cout << "S * T = U" << std::endl: std::cout << "NOT CORRECT" << std::endl;

    BigInteger V("9876545439000000345634560000000002000034565430000000006543654365346534");
    BigInteger W("98765454390000034563456191872363456345619187236000456456345756780000065436543");

    V -= W;

    std::cout << "V= " << V << std::endl;

    BigInteger X("91287346670000043892345634563400005619187236478");
    BigInteger Y("9876545439000000345634560000000002000034565430000000006543654365346534");

    BigInteger Z= X * Y;
    std::cout << "Z= " << Z << std::endl;

    BigInteger AA,BB,CC,DD;
    
    runTest(&AA,&BB,&CC,&DD);

    return(EXIT_SUCCESS);
}
/*
  Output of program:
  A: -2147483647
  B: 4352116
  C: 0
  D: 0
  E: 4362116
  F: 1
  G: 81438860

  A < B
  B > A
  C = D
  E > B
  F = F + G  -> 81438861
  G = G - H  -> 11111111
  G = G - H  -> 0
  H = H - I  -> -10000050

  G= 0
  J= 123
  K= -4506
  L= 11
  M= 2153580265
  N= 656565
  O= 656565
  P= 656564

  J= J * K  -> -554238
  CORRECT
  J*= L -> -6096618
  CORRECT
  J+= A -> -2153580265
  J-= G -> -2153580265
  J+= M -> 0
  CORRECT
  CORRECT

  N >= O
  N <= O
  P <= O
  O >= P

  Q= 1234567891011121314151617181920
  R= -1234567891011121314151617181920
  S= -5033
  T= 12345
  U= -62132385

  CORRECT
  S * T = U
  V= -98765444513454595563455846237803456345617187201435026456345750236345700090009
  Z= 901603627392000803186807983911639635120177567956653774933087809594845872987983475989051173678812345278791356275667252
  A= 111122223333
  B= -112122223333
  C= -1000000000
  D= -1000000000
  AFTER TEST
*/
