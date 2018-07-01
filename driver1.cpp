/**********************************************************************************************************
File:		driver1.cpp
Project:	1
CMSC:		341
Section:	03
Date:		10/4/06
Username:	ej77536
Name:		Phuoc Nguyen

***********************************************************************************************************/

/* File: driver2.cpp

   UMBC CMSC 341 Fall 2016 Project 1

   Basic tests for the Llama class.

   This driver program tests Llama Stacks with floating 
   point numbers. 

*/

#include <iostream>
using namespace std ;

#include "Llama.h"

int main() {

   Llama<float,8> S ;
   float s1;

   // Push a bunch of floats
  
   try {
      S.push(1.234) ;
      S.push(2.345) ;

      s1 = S.pop() ;
      s1 = S.pop() ;
      s1 = S.pop() ;

   } catch (LlamaUnderflow &e) {
      cerr << "*****\n" ;
      cerr << "Llama Stack error: " << e.what() << endl ;
      cerr << "*****\n" ;
   }

   S.push(1.234) ;
   S.push(2.345) ;
   S.push(3.456) ;
   S.push(4.567) ;
   S.push(5.678) ;
   S.push(6.789) ;
   S.push(7.890) ;
   S.push(8.901) ;
   S.push(9.012) ;

  // S.push(1.234);
   //S.push(2.345);
   //S.push(3.456);
   //S.push(4.567);
   //S.push(5.678);
   //S.push(6.789);
   //S.push(7.890);
   //S.push(8.901);
   //S.push(9.012);

  // S.swap() ;
   S.dump() ;   

   S.push(10.123) ; 

   S.rot() ;
   S.dump() ;

   S.swap() ;
   S.dump() ;


   cerr << "\n***** Dump using peek *****" ;
   int size = S.size() ;
   cerr << "\nsize = " << size << endl ;

   for (int i=0 ; i < S.size() ; i++) {
      cerr << i << ": " << S.peek(i) << endl ;
   }


   // Pop some float off

   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   S.dump() ; //extra node


   cerr << "\n***** Push Test *****\n" ;
   S.push(789.98) ;
   S.push(456.78) ;
   S.push(123.67) ;

   S.dump() ;  


   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   S.dump() ;  //extra node


   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   S.dump() ;  //extra node

   //// Testing assignment and copy constructor
   ////
   //Llama<float,8> T(S) ;

   //
   //T.pop() ;
   //T.pop() ;
   //cerr << "============================\n" ;
   //cerr << "Copied stack T has: \n" ;
   //T.dump() ;
   //cerr << "============================\n" ;
   //cerr << "Orginal stack S has: \n" ;
   //S.dump() ;


   //Llama<float,8> U ;

   //U = S ;
   //U.pop() ;
   //U.push(11.234) ;
   //cerr << "============================\n" ;
   //cerr << "Copied stack U has: \n" ;
   //U.dump() ;
   //cerr << "============================\n" ;
   //cerr << "Orginal stack S has: \n" ;
   //S.dump() ;
  // system("pause");
   return 0 ;
}
