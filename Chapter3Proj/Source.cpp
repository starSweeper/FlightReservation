//Flight reservation program
//Annonymous Name
//October 2016

#include<iostream>
#include"DLList.h" //Include header file with link lists
using namespace std;



bool returnToMenu(); //Asks if user would like to return to menu
bool searchFlight(DLList&, DLList&, DLList&, FlightList&); 
bool reserveFlight(DLList&, DLList&, DLList&, FlightList&);
bool cancelReservation(DLList&, DLList&, DLList&, FlightList&); //Delete reservation from linked list of passengers
string whereTo(string, DLList&, DLList&, DLList&, FlightList&); //Checks for reservation and if it finds a flight, tells you where it is to.
bool oneFlightManifest(DLList&, DLList&, DLList&, FlightList&); //See all passengers for a specific flight
bool allFlightManifest(DLList&, DLList&, DLList&, FlightList&); //See all passengers for all flights
int inputValidation(string, bool);
void exitNow();

int main()
{
	int menu;
	bool again = false;
	bool tryAgain = false;
	//Passengers Pass;
	DLList norway, alaska, mexico;
	FlightList fly;

	fly.addToHead(norway); //Create flight to Norway
	fly.addToHead(alaska); //Create flight to Alaska
	fly.addToHead(mexico); //Create flight to Mexio

		//Main menu
	do{
		cout << "Welcome to Ullr Airlines!\n";
		cout << "Please select an option below...\n\n";

		cout << "Enter a '1' to Reserve Ticket(s)\n";
		cout << "Enter a '2' to Cancel a Reservation\n";
		cout << "Enter a '3' to Check Whether a Ticket is Reserved for a Particular Person\n";
		cout << "Enter a '4' to Display a Manifest for a Specific Flight\n";
		cout << "Enter a '5' to Display a Manifest for all Flights\n";
		cout << "Enter a '6' to Exit\n\n";

		do {
			tryAgain = false;
			menu = inputValidation("Your selection: ", false);


			switch (menu) { //Calls functions user needs based on menu selection
			case 1:
				again = reserveFlight(norway, alaska, mexico, fly);
				break;
			case 2:
				again = cancelReservation(norway, alaska, mexico, fly);
				break;
			case 3:
				again = searchFlight(norway, alaska, mexico, fly);
				break;
			case 4:
				again = oneFlightManifest(norway, alaska, mexico, fly);
				break;
			case 5:
				again = allFlightManifest(norway, alaska, mexico, fly);
				break;
			case 6:
				exitNow();
				break;
			default:
				cout << "That wasn't an option. Try again.\n"; //More input validation
				tryAgain = true;
				break;
			}
		} while (tryAgain);
	} while (again);

	return 0;
}

//Asks user if they would like to return to main menu
bool returnToMenu() {
	int returnToMenu;
	bool menuReturnTo = false;

	returnToMenu = inputValidation("\nWould you like to return to the main menu? (Enter \'1\' for yes or \'2\' for no)\nYour selection: ",false);

	if (returnToMenu == 1) {
		menuReturnTo = true;
		system("cls"); //Clear screen
	}
	else {
		exitNow();
	}

	return menuReturnTo;
}

//Displays list of passengers for one specified flight
bool oneFlightManifest(DLList& Flight2430, DLList& Flight2515, DLList& Flight2750, FlightList& myFlight) {
	int flight;
	bool badInput = false;

	system("cls"); //Clear screen
		cout << "SINGLE FLIGHT MANIFEST\n";
		flight = inputValidation("Please enter flight number: ", true);
		if (flight == 2430) { //Checking to see which flight they are on
			Flight2430.printAll();
		}
		else if (flight == 2515) {
			Flight2515.printAll();
		}
		else if (flight == 2750) {
			Flight2750.printAll();
		}
		else {
			cout << "That is not a valid flight number, please try again\n";
			badInput = true;
		}


	return returnToMenu();
}
//Displays list of passengers for all flights (all 3 of them!)
bool allFlightManifest(DLList& Flight2430, DLList& Flight2515, DLList& Flight2750, FlightList& myFlight) {
	system("cls"); //Clear screen
	cout << "ALL FLIGHT MANIFEST\n";
	cout << "Flight 2430 to Oslo, Norway:\n";
	Flight2430.printAll();
	cout << "\n\nFlight 2525 to Ancorage, Alaska:\n";
	Flight2515.printAll();
	cout << "\n\nFlight 2750 to Accopulco, Mexico:\n";
	Flight2750.printAll();
	cout << endl;

	return returnToMenu();
}

//Deletes passenger from flight list
bool cancelReservation(DLList& Flight2430, DLList& Flight2515, DLList& Flight2750, FlightList& myFlight)
{
	string nameDelete;
	system("cls");
	cout << "FLIGHT CANCELLATION FORM\n";
	cout << "**Please enter passenger name exactly as it was entered at reservation time**\n";
	cout << "Passenger name: ";
	//cin.ignore();
	getline(cin, nameDelete);
	string flightExists = whereTo(nameDelete, Flight2430, Flight2515, Flight2750, myFlight);

	if (flightExists == "Norway") {
		Flight2430.deleteNode(nameDelete);
		cout << "Reservation has been deleted.\n";
	}
	else if (flightExists == "Alaska") {
		Flight2515.deleteNode(nameDelete);
		cout << "Reservation has been deleted.\n";
	}
	else if (flightExists == "Mexico") {
		Flight2750.deleteNode(nameDelete);
		cout << "Reservation has been deleted.\n";
	}
	else if (flightExists == "No") {
		cout << "Feel free to make a reservation in our Main Menu.\n";
	}


	return returnToMenu();
}

//Searches for passenger 
bool searchFlight(DLList& Flight2430, DLList& Flight2515, DLList& Flight2750, FlightList& myFlight)
{

	string fullName;

	system("cls");
	cout << "PASSENGER LOOK UP\n";
	cout << "**Please enter passenger name exactly as it was entered at reservation time**\n";
	cout << "Passenger name: ";
	//cin.ignore();
	getline(cin, fullName);
	whereTo(fullName, Flight2430, Flight2515, Flight2750, myFlight);


	return returnToMenu();
}

//searches for passenger and tells you what flight they are on
string whereTo(string full, DLList& Flight2430, DLList& Flight2515, DLList& Flight2750, FlightList& myFlight) {
	bool flyingToNorway;
	bool flyingToAlaska;
	bool flyingToMexico;

	//Checking to see which flight they are on
	flyingToNorway = Flight2430.isInList(full);
	flyingToAlaska = Flight2515.isInList(full);
	flyingToMexico = Flight2750.isInList(full);

	if (flyingToNorway || flyingToAlaska || flyingToMexico) { //If they are on any flight...
		cout << "\n\nIt looks like there is a passenger by that name.\n";
		cout << "This passenger has a ticket reserved for ";
		if (flyingToNorway) {
			cout << "Flight 2430 to Oslo, Norway.\n";
			return "Norway";
		}
		else if (flyingToAlaska) {
			cout << "Flight 2515 to Ancorage, Alaska. \n";
			return "Alaska";
		}
		else if (flyingToMexico) {
			cout << "Flight 2750 to Accapulco, Mexico.\n";
			return "Mexico";
		}
	}
	else {
		cout << "I'm sorry, it doesn't look like we have any reservations under that name.\n"; //Passenger was not found on any flight
		return "No";
	}

}

//Reserves flight(creates new node for list of passengers)
bool reserveFlight(DLList& Flight2430, DLList& Flight2515, DLList& Flight2750, FlightList& myFlight)
{
	int numOfPassengers;
	int flightNumber;

	system("cls"); //Clear screen
	cout << "We are so pleased that you have chosen Ullr Airlines for your next adventure!\n\n";
	cout << "Here is a list of our avaliable flights:\n";
	cout << "Flight 2430 to Olso, Norway\n";
	cout << "Flight 2515 to Anchorage, Alaska, United States\n";
	cout << "Flight 2750 to Accapulco, Mexico\n\n";
	cout << "RESERVATION FORM\n";
	numOfPassengers = inputValidation("Number of passengers: ", false);

	string name;
	bool badInput = false;

	do {
		for (int i = 0; i < numOfPassengers; i++)
		{
			cout << "\nPassenger " << i + 1 << ":\n";
			cout << "Full Name (last name first): ";
			getline(cin, name);
			flightNumber = inputValidation("Flight Number: ", true);

			if (flightNumber == 2430) {
				Flight2430.sortedAdd(name); //Adding passenger to flight
			}
			else if (flightNumber == 2515) {
				Flight2515.sortedAdd(name);
			}
			else if (flightNumber == 2750) {
				Flight2750.sortedAdd(name);
			}
			else {
				cout << flightNumber << " is not a valid flight number. Please try again.";
				badInput = true;
			}

		}

	} while (badInput); //While flight number entered is invalid


	return returnToMenu();
}

//recieves input as a string, checks to see if it is valid, then converts it to an int
int inputValidation(string prompt, bool flightNum) {
	//conversion from string to int from http://stackoverflow.com/questions/7663709/convert-string-to-int-c
	bool badInput;
	string response;
	int responseInt;

	do {
		badInput = false;
		cout << prompt;
		//cin.ignore();
		getline(cin, response);

		if (flightNum && (response != "2430" && response != "2515" && response != "2750")) {
				cout << "Invalid input. Please try again!\n";
				badInput = true;
			}
		else {
			try {
				responseInt = std::stoi(response);
			}
			catch (invalid_argument) {
				cout << "Invalid input. Please try again!\n";
				badInput = true;
			}
		}

		

	} while (badInput == true);

	return responseInt;
}

//For a quick exit of the program
void exitNow() {
	system("cls");//clear screen
	cout << "Thank you for choosing Ullr Arlines! Have a wonderful day!\n";
	system("pause");
	exit(0); //Close program
}




//Menu (Reserve a ticket, Cancel a reservation, check who ticket is for, flight manifest(specific), flight manifest(all flights)
