/**********************************************************************************************************
File:		Llama.cpp
Project:	1
CMSC:		341
Section:	03
Date:		10/4/06
Username:	ej77536
Name:		Phuoc Nguyen

***********************************************************************************************************/

#ifndef LLAMA_CPP
#define LLAMA_CPP

#include <iostream>
#include<ctype.h>
#include "Llama.h"

using namespace std;

//default constructor
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama() {
	this->sizeArr = 0;
	this->m_next = NULL;

}

//destructor
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::~Llama() {

	LlamaNode<T, LN_SIZE> *current = NULL;
	LlamaNode<T, LN_SIZE> *old = NULL;

	//going through all the nodes
	//delete as going
	while (this->m_next != NULL) {
		current = this->m_next;
		old = current;
		current = current->m_next;
		delete old;
		this->m_next = current;
	}

}


//get size
//it returns the size of the array
template <class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size() {
	return this->sizeArr;
}

//increase size of the array when new node added
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::sizeAdd() {
	this->sizeArr++;
}

//decrease size of the array when node is being remove
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::sizeDeduct() {
	this->sizeArr--;
}

//copy constructor
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama(Llama<T, LN_SIZE>& other) {

	LlamaNode<T, LN_SIZE> *current;						//current node
	LlamaNode<T, LN_SIZE> *newCurrent;					//new current node
	LlamaNode<T, LN_SIZE> *newNode;						//create new node

	//get the size of other Llama
	this->sizeArr = other.size();
	

	//set the actual nodeList to null if other Llama nodeList is null
	if (other.m_next == NULL) {
		this->m_next = NULL;

	}
	//other Llama nodelist is not null, copy to it
	else {
		
		//current node is the other Llama nodeList to track the list
		current = other.m_next;

		//the new current node is the nodeList to track while copying
		newCurrent = this->m_next;

		//read until it reaches null
		while (current) {

			//create new node to copy
			newNode = new LlamaNode<T, LN_SIZE>;

			//set current node data to new node data
			//newNode->arr = current->arr;
			for (int i = LN_SIZE - 1; i > 0; i--) {
				newNode->arr[i] = current->arr[i];
			}

			//the new node nodelist to null and update later
			newNode->m_next = NULL;

			//nodelist reaches end, update current node to the new node
			if (m_next == NULL) {
				newCurrent = newNode;
			}
			
			else {
				newCurrent->m_next = newNode;
			}

			//update current node to the latest node
			newCurrent = newNode;
		}

	}
	
}

//duplicate 
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dup() {

	//throw exception when stack size is <= zero
	if (this->size() <= 0) {
		throw LlamaUnderflow::out_of_range("Empty stack.\n");
		return;
	}

	//set insertnode to front
	LlamaNode<T, LN_SIZE>* insertNode = this->m_next;

	//check the size of array if it is 1
	//insert to the previous array to the next array
	if (this->size() == 1) {
		insertNode->arr[1] = insertNode->arr[0];
	}

	//not equal 1
	else {

		//get the modulo of the stack size
		int modulo = this->size() % LN_SIZE;

		//get the number of node
		int nodeNum = this->size() / LN_SIZE;

		//set previousNode to NULL
		LlamaNode<T, LN_SIZE>* previousNode = NULL;

		//node counter
		int nodeCounter = 1;

		
		T temp1;		//to hold specific value temperary
		
		//set insertnode to be at front
		insertNode = this->m_next;

		//traverse the list to the node counter and move the element to the next as we go
		while (nodeCounter < (nodeNum + 1 )) {

			T temp2;

			//set last element of the array to temp2
			temp2 =  insertNode->arr[LN_SIZE-1];

			//move the previous index element to the next index element 
			for (int i = LN_SIZE - 1; i > 0; i--) {
				insertNode->arr[i] = insertNode->arr[i - 1];
			}

			//assign the previous value that temp1 hold to array 0
			if (nodeCounter != 1) {
				insertNode->arr[0] = temp1;
			}

			//make sure temp1 = temp2
			temp1 = temp2;
			
			//assign previous node to current node
			previousNode = insertNode;

			//and set current node to the next node
			insertNode = insertNode->m_next;

			//keep track of the count of node
			nodeCounter++;

			}

		//array is full or empty and next node is null
		if (modulo == 0 ){

			//current node is null
			if (insertNode == NULL) {

				//create new node and set previous next node to new node
				//current node is also the new node
				LlamaNode<T, LN_SIZE> * newNode = new LlamaNode<T, LN_SIZE>;
				previousNode->m_next = newNode;
				insertNode = newNode;
			}

			//current node at array 0 is now set to previous node that is the last element
			insertNode->arr[0] = temp1;
		}

		//array is not full
		else {
			//move all the value to the next index
			for (int j = modulo - 1; j > 0; j--) {
				insertNode->arr[j] = insertNode->arr[j - 1];
			}

			//if it is the first element, then set it from temp1 value
			if (nodeCounter != 1) {
				insertNode->arr[0] = temp1;
			}
		}

		}
	}

//dump function
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dump() {


	//create a check node
	LlamaNode<T, LN_SIZE> *checkNode = NULL;


	//print out the requirements
	cout << endl;
	cout << "***** Llama Stack Dump ******" << endl;
	cout << "LN_SIZE = " << LN_SIZE << endl;
	cout << "# of items in the stack = " << this->size() << endl;
	checkNode->report();
	cout << endl;

	//get the number node at start
	int nodeNumBefore = LlamaNode<T, LN_SIZE>::newCount - LlamaNode<T, LN_SIZE>::deleteCount;
	
	//get the number of node after
	int	nodeNumAfter = this->size() / LN_SIZE;
	
	//get the array position
	int modulo = this->size() % LN_SIZE;
	
	//increase number of node if modulo is not zero
	if (modulo != 0) {
		nodeNumAfter++;
	}
	
	//create previous node and set to null
	LlamaNode<T, LN_SIZE> *previousNode = NULL;

	//assign check node to the front of the list
	checkNode = this->m_next;

	//traverse the list to the end
	while (checkNode != NULL) {

		//assign the node at end to previous
		previousNode = checkNode;
		checkNode = checkNode->m_next;
	}
	
		//compare the nodes before and after
		if(nodeNumBefore > nodeNumAfter){
			cout << "This stack has an extra node: " << previousNode << endl << endl;
			
		}

		else {
			cout << "This stack does not have an extra node" << endl << endl;
		}
	
		//create current node to front
		LlamaNode<T, LN_SIZE> * currentNode = this->m_next;

		//get the size of the array
		int nodeCount = this->size();

		//traverse the list
		while (currentNode) {
			cout << "----- " << currentNode << " -----" << endl;
			
			//set max size
			int max = nodeCount >= LN_SIZE ? LN_SIZE : nodeCount;

			//print out all the values in the array
			for (int i = 0; i < max; i++) {
				cout << currentNode->arr[i] << endl;
			}
			currentNode = currentNode->m_next;
			nodeCount -= LN_SIZE;
		}
		cout << "----- Top of stack -----" << endl;
	}




//push function
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::push(const T& data) {
	
	LlamaNode<T, LN_SIZE>* insertNode;

	//get the modulo of the stack size
	int modulo = this->sizeArr % LN_SIZE;
	int nodeNum = this->size() / LN_SIZE;
	
	//add new node if m_next is null which is the first element added to list
	if (this->m_next == NULL) {
		insertNode = new LlamaNode<T, LN_SIZE>;
		this->m_next = insertNode;
	}

	else {

		//node counter
		int nodeCounter = 1;

		insertNode = this->m_next;

		//still in the first node of the list
		if (nodeNum != 0) {

			//traverse the list to the node counter
			while ( nodeCounter < nodeNum) {
				insertNode = insertNode->m_next;
				nodeCounter++;
			}

			//check for next node if it exists when modulo is zero
			if (modulo == 0) {
				if (insertNode->m_next == NULL) {
					LlamaNode<T, LN_SIZE> *newNode = new LlamaNode<T, LN_SIZE>;
					insertNode->m_next = newNode;
					insertNode = newNode;
				}
				else {
					insertNode = insertNode->m_next;
				}
			}

			//modulo is not zero since next node exists
			else {
				insertNode = insertNode->m_next;
			}
		 }
	}
	//add data to node and update size
	insertNode->arr[modulo] = data;
	this->sizeAdd();
	}


//push function
template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::pop() {

	//throw exception when stack size is <= zero
	if (this->size() <= 0) {
		throw LlamaUnderflow::out_of_range("Empty stack.\n");
		return *what;
	}


	//assign current node to front
	LlamaNode<T, LN_SIZE> *insertNode = this->m_next;


	//get the modulo which is the position of the array
	int modulo = this->sizeArr % LN_SIZE;

	//get the number of nodes
	int nodeNum = this->size() / LN_SIZE;

	
	int nodeCounter = 1;

	//traverse to the destinated node
	while(nodeCounter < nodeNum) {
		insertNode = insertNode->m_next;
		nodeCounter++;
	}

	//not the first node and node is not exist
	if (nodeNum != 0 && modulo != 0) {
		insertNode = insertNode->m_next;
	}

	//decrease size
	this->sizeDeduct();

	//get the new modulo
	int newModulo = this->size() % LN_SIZE;

	//so newModulo is half the stack & next node is not null. Remove node. 
	if (newModulo == (LN_SIZE / 2) && insertNode->m_next != NULL) {
		LlamaNode<T, LN_SIZE> * removeNode = insertNode->m_next;
		delete removeNode;
		insertNode->m_next = NULL;
	}

	return insertNode->arr[newModulo];
}


//swap function
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::swap() {

	//throw exception when stack size is < 2
	if (this->size() < 2) {
		throw LlamaUnderflow::out_of_range("Empty stack or not enough element to swap.\n");
		return;
	}

	//create and set current node to front
	LlamaNode<T, LN_SIZE> *insertNode = this->m_next;

	//create and set the node before previous to null
	LlamaNode<T, LN_SIZE> *prevpreviousNode = NULL;

	//create and set previous node to null
	LlamaNode<T, LN_SIZE> *previousNode = NULL;

	//get the array position
	int modulo = this->sizeArr % LN_SIZE;
	

	int nodeCounter = 1;

	//traverse to the destinated node
	while (insertNode != NULL) {
		prevpreviousNode = previousNode;
		previousNode = insertNode;
		insertNode = insertNode->m_next;
		nodeCounter++;
	}
	
		//array in previous node is empty and position is at 1 in the array
		if (previousNode->arr  && modulo == 1) {
			//swap the two last elements in the end of list
			T temp = previousNode->arr[modulo - 1];
			previousNode->arr[modulo - 1] = prevpreviousNode->arr[LN_SIZE - 1];
			prevpreviousNode->arr[LN_SIZE - 1] = temp;
		}

		//array in previous node is not empty
		else {

			//swap the two last elements in the end of the list
			T temp2 = previousNode->arr[modulo - 1];
			previousNode->arr[modulo - 1] = previousNode->arr[modulo - 2];
			previousNode->arr[modulo - 2] = temp2;

		}


}

//rotate function
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::rot() {
	
	//throw exception when stack size is < 3
	if (this->size() < 3) {
		throw LlamaUnderflow::out_of_range("Empty stack or not enough element to rotate.\n");
		return;
	}

	//set current node to front
	LlamaNode<T, LN_SIZE> *insertNode = this->m_next;

	//create and set the before previous node to null
	LlamaNode<T, LN_SIZE> *prevpreviousNode = NULL;

	//create and set previous node to null
	LlamaNode<T, LN_SIZE> *previousNode = NULL;

	//get the array position
	int modulo = this->sizeArr % LN_SIZE;

	int nodeCounter = 1;

	//traverse to the destinated node
	while (insertNode != NULL) {
		prevpreviousNode = previousNode;
		previousNode = insertNode;
		insertNode = insertNode->m_next;
		nodeCounter++;
	}
	
		//array in previous node is empty and position at 2 in array
		if (previousNode->arr && modulo == 2) {

			//swap the last three elements
			T temp = prevpreviousNode->arr[LN_SIZE - 1];
			prevpreviousNode->arr[LN_SIZE - 1] = previousNode->arr[modulo - 2];
			previousNode->arr[modulo - 2] = previousNode->arr[modulo - 1];
			previousNode->arr[modulo - 1] = temp;

		}

		//array in previous node is empty and position at 1 in array
		else if (previousNode->arr && modulo == 1) {

			//swap the last three elements
			T temp2 = prevpreviousNode->arr[LN_SIZE - 2];
			prevpreviousNode->arr[LN_SIZE - 2] = prevpreviousNode->arr[LN_SIZE - 1];
			prevpreviousNode->arr[LN_SIZE - 1] = previousNode->arr[modulo - 1];
			previousNode->arr[modulo - 1] = temp2;

		}

		//array in previous node is not empty
		else {

			//swap the last three elements
			T temp3 = previousNode->arr[modulo - 3];
			previousNode->arr[modulo - 3] = previousNode->arr[modulo - 2];
			previousNode->arr[modulo - 2] = previousNode->arr[modulo - 1];
			previousNode->arr[modulo - 1] = temp3;

		}

}


//peak function
template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::peek(int offset) const {


	//get the stack size
	const int stackSize = this->sizeArr;

	//throw exception
	if (stackSize <= 0 || offset < 0 || offset > stackSize - 1) {
		throw LlamaUnderflow::out_of_range("Empty stack. Cannot peek.\n");
		return NULL;
	}

	//create and set current node to front
	LlamaNode<T, LN_SIZE> * insertNode = this->m_next;

	//offset is greater or equal to ln_size
	while (offset >= LN_SIZE) {
		//moving to next node
		insertNode = insertNode->m_next;

		//decrease the offset based on ln_size
		offset -= LN_SIZE;
	}

	
	return insertNode->arr[offset];
}


#endif