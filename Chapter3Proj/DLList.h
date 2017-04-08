#pragma once
//Singly linked list of passenger names. Heavily relies on figure 3.10 in Data Structures text book
//So this was switched back and forth between a singly and doubly linked list a few times. I didn't have the time to change all the name, so that is why these files/classes are not
//called things like "PassengerList" and "PassengerNode"


#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST


#include<string>
using namespace std;

class DLLNode { //For nodes in the list
public:
	DLLNode() {
		next = 0;// prev = 0;
	}
	DLLNode(string el, DLLNode *ptr = 0) {    //*n = 0, DLLNode *p = 0) {
											  //next = n; prev = p;
		name = el; next = ptr;
	}
	string name;
	DLLNode *next;// , *prev;
};

class DLList { //For access to the list
public:
	DLList() {
		head = tail = 0;
	}
	~DLList();
	int isEmpty() {
		return head == 0;
	}
	void sortedAdd(string);
	void deleteNode(string);
	bool isInList(string) const;//Search for reservation (search for passenger)
	string getAll();
	void printAll();

private:
	DLLNode *head, *tail;
};

class FlightNode { //For nodes in the list
public:
	FlightNode() {
		next = 0;// prev = 0;
	}
	FlightNode(DLList& el, FlightNode *ptr = 0) {
		passenger = el; next = ptr;
	}
	DLList passenger;
	FlightNode *next;// , *prev;
};

class FlightList { //For access to the list
public:
	FlightList() {
		head = tail = 0;
	}
	~FlightList();
	int isEmpty() {
		return head == 0;
	}

	void addToHead(DLList&);
	DLList deleteFromHead();
	bool isInList(DLList&) const;//Search for reservation (search for passenger)

private:
	FlightNode *head, *tail;
};


#endif