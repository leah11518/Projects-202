/*
File: Navigator.cpp
Project: CMSC 202 Project 3, Spring 2022
Author: Leah Ball
Date: 3/23/22
Section: 44
E-mail: lball1@umbc.edu

This file contains the function definitons for all functions in the class Navigator
*/

#include "Navigator.h"


// Name: Navigator (string) - Overloaded Constructor
// Desc: Creates a navigator object to manage routes
// Preconditions:  Provided with a filename of ports to load
// Postconditions: m_filename is populated with fileName
Navigator::Navigator(string fileName) {m_fileName = fileName;}


// Name: Navigator (destructor)
// Desc: Deallocates all dynamic aspects of a Navigator
// Preconditions: There is an existing Navigator
// Postconditions: All ports and routes are cleared
Navigator::~Navigator() {
  //deletes ports
  for (unsigned int i = 0; i < m_ports.size(); ++i) 
    delete m_ports[i];

  //deletes routes
  for (unsigned int i = 0; i < m_routes.size(); ++i)
    delete m_routes[i];
}


// Name: Start
// Desc: Loads the file and calls the main menu
// Preconditions: m_fileName is populated
// Postconditions: All ports are loaded and the main menu runs
void Navigator::Start() {
  ReadFile();
  MainMenu();
}


// Name: DisplayPorts
// Desc: Displays each port in m_ports
// Preconditions: At least one port is in m_ports
// Postconditions: Displays all ports. Uses overloaded << provided in Port.h
void Navigator::DisplayPorts() {
  for (unsigned int i = 0; i < m_ports.size(); ++i) {

    cout << i + 1 << ". " << m_ports[i] -> GetName() << "," << m_ports[i] -> GetLocation() << endl;

  }
}


// Name: ReadFile
// Desc: Reads in a file that has data about each port including name, location, degrees
//       north and degrees west. Dynamically allocates ports and stores them in m_ports
//       The vector can hold many ports.
// Preconditions: Valid file name of ports
// Postconditions: Dynamically allocates each port and enters it into m_ports
void Navigator::ReadFile() {
  ifstream newFile;
  string name, location, north, west;

  //opens file
  newFile.open(m_fileName);

  // iterates through file
  if (newFile.is_open()){
      for (int i = 0; i < 36; ++i) {

	//gets string of name, location, north, and west
	getline(newFile, name, ','); 
	getline(newFile, location, ',');
	getline(newFile, north, ','); 
	getline(newFile, west);

	//changes north and west to doubles
	double newNorth = stod(north);
	double newWest = stod(west);

	//adds port into vector
	Port *newPort = new Port(name, location, newNorth, newWest);
	m_ports.push_back(newPort);
    }
      
      cout << "36 Port uploaded" << endl;
    }

  //if file cannot be opened
  else {
    cout << "File could not be opened" << endl;
  }
  
  newFile.close();
}



// Name: InsertNewRoute
// Desc: Dynamically allocates a new route with the user selecting each port in the route.
//       Route named based on the first and last port automatically
//       For example, Baltimore to Boston
//       Once route is created, inserted into m_routes.
// Preconditions: Populated m_routes
// Postconditions: Inserts a new route into m_routes
void Navigator::InsertNewRoute() {
  int count = 0;
  int port = 0;

  //creates route
  Route *newRoute = new Route();
  m_routes.push_back(newRoute);

  //gets user input
  cout << "Enter the number of the port you'd like to add (-1 to stop)" << endl;
  cin >> port;

  //adds ports until user inputs escape sequence
  while (port != -1) {

    //inserts port into route
    if (port >=1) {
      
      //inserts the port at the end of the route
      newRoute -> InsertEnd(m_ports[port - 1] -> GetName(), m_ports[port - 1] -> GetLocation(), m_ports[port - 1] -> GetNorth(), m_ports[port - 1] -> GetWest());
    }

    cout << "Enter the number of the port you'd like to add? (-1 to stop)" << endl;
    cin >> port;
    ++count;
  }
  
  //finishes building route
  cout << "Done building route from " << newRoute -> UpdateName() << endl;;
}
      


// Name: MainMenu
// Desc: Displays the main menu and manages exiting
// Preconditions: Populated m_ports
// Postconditions: Exits when someone chooses 5
void Navigator::MainMenu() {

  //options for user to choose
  int choice = 0;
  cout << "What would you like to do?" << endl;
  cout << "1. Create New Route" << endl;
  cout << "2. Display Route" << endl;
  cout << "3. Remove Port from Route" << endl;
  cout << "4. Reverse Route" << endl;
  cout << "5. Exit" << endl;
  cin >> choice;

  // runs functions based on choice
  while (choice != 5) {
    switch (choice) {
    case 1:
      DisplayPorts();
      InsertNewRoute();
      break;
    case 2:
      DisplayRoute();
      break;
    case 3:
      RemovePortFromRoute();
      break;
    case 4:
      ReverseRoute();
      break;
    default:
      cout << "Choice must be between 1 and 5" << endl;
    }

    //ask again until quit
    cout << "What would you like to do?" << endl;
    cout << "1. Create New Route" << endl;
    cout << "2. Display Route" << endl;
    cout << "3. Remove Port from Route" << endl;
    cout << "4. Reverse Route" << endl;
    cout << "5. Exit" << endl;
    cin >> choice;
  }
}
    
    


// Name: ChooseRoute
// Desc: Allows user to choose a specific route to work with by displaying numbered list
// Preconditions: Populated m_routes
// Postconditions: Returns the index of the selected route minus 1
int Navigator::ChooseRoute() {
  unsigned int port = 0;
  cout << "Which route would  you like to use?" << endl;

  //prints out routes in vector m_routes
  for (unsigned int i = 0; i < m_routes.size(); ++i) {
    cout << i + 1 << ". " << m_routes[i] -> GetName() << endl;
  }
  
  cin >> port;

  //continues to ask if user doesn't input a useable number
  if (port > m_routes.size()) {
    cout << "not an option" << endl;
    cout << "Which route would you like to use?" << endl;
    cin >> port;
    return port;
  }

  else
    return port;
}



// Name: DisplayRoute
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       If no routes, indicates that there are no routes to display
//       User selects a route from list to display
//       Displays numbered list of each port in route
//       Displays total miles of a route using RouteDistance
// Preconditions: Routes has more than one port
// Postconditions: Displays all ports in a route and the total miles of the route
void Navigator::DisplayRoute() {
  //gets user to choose route
  int userChoice = ChooseRoute();

  //if no routes in routes vector
  if (m_routes.size() == 0)
    cout << "No routes to display" << endl;
  
  else {
    //prints out name of chosen route
    cout << m_routes[userChoice - 1] -> GetName() << endl;
    //displays all ports in chosen routes
    m_routes[userChoice - 1] -> DisplayRoute();

    cout << "The total miles of this route is " << RouteDistance(m_routes[userChoice - 1]) << " miles" << endl;
  }
}



// Name: RemovePortFromRoute()
// Desc: Using ChooseRoute, displays a numbered list of all routes.
//       User selects one of the routes to remove a port from.
//       Displays a numbered list of all ports in selected route.
//       User selects port to remove from list.
//       Removes port from route. If first or last port removed, updates name of route.
// Preconditions: Routes has more than one port
// Postconditions: Displays updated route with removed port and new name
void Navigator::RemovePortFromRoute() {
  int userChoice = ChooseRoute();
  int port = 0;

  //if no routes in routes vector
  if (m_routes.size() == 0)
    cout << "No routes to remove" << endl;

  else {

    //prints out name of chosen route
    cout << m_routes[userChoice - 1] -> GetName() << endl;

    //displays all ports in chosen routes
    m_routes[userChoice - 1] -> DisplayRoute();
    cout << "What port would you like to remove?" << endl;
    cin >> port;

    //if port is available
    if ((port - 1) > -1 && (port - 1) < m_routes[userChoice - 1] -> GetSize())
      //removes port
      m_routes[userChoice - 1] -> RemovePort(port);

    cout << "Route named " << m_routes[userChoice - 1] -> UpdateName() << " updated" << endl; 
  }
}



// Name: RouteDistance
// Desc: Calculates the total distance of a route
//       Goes from port 1 to port 2 then port 2 to port 3 and repeats for
//       length of route. Calculates the distance using CalcDistance (provided)
//       Aggregates the total and returns the total in miles
// Preconditions: Populated route with more than one port
// Postconditions: Returns the total miles between all ports in a route
double Navigator::RouteDistance(Route* userRoute) {
  double totalDistance = 0.0;
  Port *curr = userRoute -> GetData(0);
  Port *next = userRoute -> GetData(1);

  //calculates distance between each of ports ands adds to total distance
  while (next != nullptr) {

    totalDistance += CalcDistance(curr -> GetNorth(), curr -> GetWest(), next -> GetNorth(), next -> GetWest());
    curr = next;
    next = next -> GetNext();

  }
  return totalDistance;
}



// Name: ReverseRoute
// Desc: Using ChooseRoute, users chooses route  and the route is reversed
//       If no routes in m_routes, indicates no routes available to reverse
//       Renames route based on new starting port and ending port
//       For example, Baltimore to Boston becomes Boston to Baltimore
// Preconditions: Populated m_routes
// Postconditions: Reverses a specific route by reversing the ports in place
//                 Must move ports, cannot just change data in ports.
void Navigator::ReverseRoute() {
  int userChoice = ChooseRoute();

  if (m_routes.size() == 0)
    cout << "No routes to reverse" << endl;

  else { 
    //reverses route and updates name
    m_routes[userChoice - 1] -> ReverseRoute();
    m_routes[userChoice - 1] -> UpdateName();

    cout << "Done reversing Route " << userChoice << endl;
  }
}
