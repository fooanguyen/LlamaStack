/**********************************************************************************************************
File:		Llama.h
Project:	1
CMSC:		341
Section:	03
Date:		10/4/06
Username:	ej77536
Name:		Phuoc Nguyen

***********************************************************************************************************/


#ifndef _LLAMA_H_
#define _LLAMA_H_

/* File: Llama.h

   UMBC CMSC 341 Fall 2016 Project 1

   This file has the class declaration for the LlamaNode class
   for Project 1. See project description for details.

   You may add public and private data members to the Llama class.

   You may add public and private member functions to the Llama class.

*/


#include <stdexcept>
#include <string>
#include "LlamaNode.h"

using namespace std ;


class LlamaUnderflow : public std::out_of_range {

   public:

   LlamaUnderflow(const string& what) : std::out_of_range(what) { }

} ;


template <class T, int LN_SIZE>
class Llama {

   public:

   Llama() ;
   Llama( Llama<T,LN_SIZE>& other) ;   // copy constructor
   ~Llama() ;


   int size() ; 
   void dump() ;
   void push(const T& data) ;
   T pop() ;


   void dup() ;    //  (top) A B C D -> A A B C D
   void swap() ;   //  (top) A B C D -> B A C D 
   void rot() ;    //  (top) A B C D -> C A B D


   T peek(int offset) const ;


   // overloaded assignment operator
   //
   const Llama<T,LN_SIZE>& operator = (const Llama<T,LN_SIZE>& rhs) ;


   //
   // Add your public member functions & public data mebers here:
   //

   //increase size
   void sizeAdd();

   //reduce size
   void sizeDeduct();

   private:
	   int sizeArr;						//array size
	   LlamaNode<T, LN_SIZE> *m_next;	//linklist


   //
   // Add your private member functions & private data mebers here:
   //


} ;


#include "Llama.cpp"


#endif
