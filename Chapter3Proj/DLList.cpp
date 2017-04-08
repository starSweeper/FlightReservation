#include<iostream>
#include"DLList.h"


DLList::~DLList() {
	for (DLLNode *p; !isEmpty();) {
		p = head->next;
		delete head;
		head = p;
	}
}


//Adds new nodes in alphebetical order. Heavily relies on code found here http://stackoverflow.com/questions/4825030/c-add-to-linked-list-in-sorted-order
void DLList::sortedAdd(string el) {
	DLLNode* temp = new DLLNode(el);
	temp->name = el;

	DLLNode* temp2 = head;
	DLLNode** temp3 = &head;
	while (temp2 != 0 && temp2->name < temp->name)
	{
		temp3 = &temp2->next;
		temp2 = temp2->next;
	}
	*temp3 = temp;
	temp->next = temp2;
}


//Cancel a reservation (delete a passenger)
void DLList::deleteNode(string el) {
	if (head != 0) {
		if (head == tail && el == head->name) {
			delete head;
			head = tail = 0;
		}
		else if (el == head->name) {
			DLLNode *tmp = head;
			head = head->next;
			delete tmp;
		}
		else {
			DLLNode *pred, *tmp;
			for (pred = head, tmp = head->next;
				tmp != 0 && !(tmp->name == el);
				pred = pred->next, tmp = tmp->next);
			if (tmp != 0) {
				pred->next = tmp->next;
				if (tmp == tail) {
					tail = pred;
				}
				delete tmp;
			} //if
		} //else
	} //if
}//method

 //Search for reservation (search for passenger)
bool DLList::isInList(string el) const {
	DLLNode *tmp;
	for (tmp = head; tmp != 0 && !(tmp->name == el); tmp = tmp->next);
	return tmp != 0;
}

//Returns all passengers
string DLList::getAll() {
	DLLNode *tmp;
	string allPassengers = "";
	for (tmp = head; tmp != tail; tmp = tmp->next) {
		allPassengers = allPassengers + tmp->name;
	}

	return allPassengers;
}

//Prints all passengers
void DLList::printAll() {
	DLLNode *tmp;
	int i = 0;
	string allPassengers = "";
	for (tmp = head; tmp != tail; tmp = tmp->next) {
		cout << i + 1 << ") " << tmp->name << endl;
		i++;
		allPassengers = allPassengers + tmp->name;
	}
}


FlightList::~FlightList() {
	for (FlightNode *p; !isEmpty();) {
		p = head->next;
		delete head;
		head = p;
	}
}

void FlightList::addToHead(DLList& el) {
	head = new FlightNode(el, head);
	if (tail == 0) {
		tail = head;
	}
}

//deleteFromHead
DLList FlightList::deleteFromHead() {
	DLList el = head->passenger;
	FlightNode *tmp = head;
	if (head == tail) { //"If only one node in the list"
		head = tail = 0;
	}
	else {
		head = head->next;
	}
	delete tmp;
	return el;

}

//Search for reservation (search for passenger)
bool FlightList::isInList(DLList& el) const {
	FlightNode *tmp;
	for (tmp = head; tmp != 0 && !(tmp->passenger.getAll() == el.getAll()); tmp = tmp->next);
	return tmp != 0;
}

