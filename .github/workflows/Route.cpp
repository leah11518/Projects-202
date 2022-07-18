/*
File: Route.cpp
Project: CMSC 202 Project 3, Spring 2022
Author: Leah Ball
Date: 3/23/22
Section: 44
E-mail: lball1@umbc.edu

This file contains the function definitions for the class Route
*/

#include "Route.h"
#include "Port.h"


// Name: Route() - Default Constructor
// Desc: Used to build a new Route (linked list) make up of ports
// Preconditions: None
// Postconditions: Creates a new Route where m_head and m_tail point to nullptr and size = 0
Route::Route(){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}


// Name: SetName(string)
// Desc: Sets the name of the route (usually first port to last port)
// Preconditions: None
// Postconditions: Sets name of route
void Route::SetName(string name) {m_name = name;}


// Name: ~Route() - Destructor
// Desc: Used to destruct a strand of Route
// Preconditions: There is an existing Route strand with at least one port
// Postconditions: Route is deallocated (including all dynamically allocated ports)
//                 to have no memory leaks!
Route::~Route() {
  Port *curr = m_head;

  //iterates and removes each port
  while (curr != nullptr) {
    m_head = curr;
    curr = curr -> GetNext();
    delete m_head;
  }
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}



// Name: InsertEnd (string, string, double double)
// Desc: Creates a new port using the data passed to it.
//       Inserts the new port at the end of the route
// Preconditions: Takes in a Port
//                Requires a Route
// Postconditions: Adds the new port to the end of a route
void Route::InsertEnd(string name, string location, double north, double west) {
  Port *newPort = new Port(name, location, north, west);

  //if no ports make port head
  if (m_size == 0) {
    m_head = newPort;
    m_tail = newPort;
    //set taill to nullptr
    m_tail -> SetNext(nullptr);
  }

  //adds newport to the end
  else {
    newPort -> SetNext(nullptr);
    m_tail -> SetNext(newPort);
    //makes newport tail
    m_tail = newPort;
  }

  ++m_size;
}



// Name: RemovePort(int index)
// Desc: Removes a port from the route at the index provided
//       Hint: Special cases (first port, last port, middle port)
// Preconditions: Index must be less than the size of the route
//       Cannot make route less than two ports. If the route has
//       two or fewer ports, fails.
// Postconditions: Name may be updated. Size is reduced. Route has one less port
void Route::RemovePort(int port) {
  //sets prev, curr, and next ports
  int size = 2;
  Port *prev = m_head;
  Port *curr = m_head -> GetNext();
  Port *next = curr -> GetNext();
  
  // can only remove if enough ports
  if (m_size < 3) {
    cout << "Not enough Ports to remove" << endl;
    return;
  }

  //if at the beginning
  else if (port == 1) {
    delete m_head;
    m_head = curr;
    --m_size;
  }

  // iterates through linked list
  else if (port > 1 && port < m_size) {
    while (next != nullptr) {

      //if current equals the user chose
      if (size == (port)) {

	//sets prev to next
	prev -> SetNext(next);
	delete curr;

	//sets curr to next and shifts next one over
	curr = next;
	next = next -> GetNext();
      }

      //shifts prev, curr, and next over
      prev = prev -> GetNext();
      curr = curr -> GetNext();
      next = next -> GetNext();
      ++size;
    }

    --m_size;
  }

  //if removing last item
  else {
    
    while (curr != m_tail) {
      //shifts prev and curr over
      prev = prev -> GetNext();
      curr = curr -> GetNext();
      ++size;
    }

    //if curr equals user input
    if (size == port) {
      prev -> SetNext(nullptr);
      delete curr;
      m_tail = prev;
    }
    --m_size;
  }
}



// Name: GetName()
// Desc: Returns the name of the route (Usually starting port to last port)
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route
// Postconditions: Returns m_name;
string Route::GetName() {return m_name;}


// Name: UpdateName()
// Desc: Updates m_name based on the name of the first port in the route
//       and the last port in the route
//       For example: Baltimore to Brunswick
// Preconditions: Requires a Route with at least two ports
// Postconditions: Returns m_name;
string Route::UpdateName() {
  //concatenates head and tail names
  m_name = m_head -> GetName();
  m_name = m_name + " to ";
  m_name = m_name + (m_tail -> GetName());
  return m_name;
}


// Name: GetSize()
// Desc: Returns the number of ports in a route
// Preconditions: Requires a Route
// Postconditions: Returns m_size;
int Route::GetSize() {return m_size;}


// Name: ReverseRoute
// Desc: Reverses a route
// Preconditions: Reverses the Route
// Postconditions: Route is reversed in place; nothing returned
void ReverseRoute();
void Route::ReverseRoute() {
  //sets prev, curr, and next to ports in route
  Port *prev = m_head;
  Port *curr = m_head -> GetNext();
  Port *next = curr -> GetNext();

  //continues until second to last element
  while (next != m_tail) {

    //sets prev to next
    prev -> SetNext(next);
    //current points back to head
    curr -> SetNext(m_head);
    //makes current beginning port
    m_head = curr;

    //resets to the next ports
    curr = next;
    next = next -> GetNext();
  }
  
  //for last two ports
  if (next == m_tail) {
    //switches last element before tail
    prev -> SetNext(next);
    curr -> SetNext(m_head);
    m_head = curr;

    //makes tail the head
    prev -> SetNext(nullptr);
    next -> SetNext(m_head);
    m_head = next;
    m_tail = prev;
  }
}


// Name: GetData (int)
// Desc: Returns a port at a specific index
// Preconditions: Requires a Route
// Postconditions: Returns the port from specific item
Port* Route::GetData(int index) {
  int size = 0;
  Port *curr = m_head;

  //iterates through ports
  while (curr != nullptr) {

    //if curr equals user input
    if (size == index) {
      return curr;

    }
    curr = curr -> GetNext();
    size++;
  }
  return nullptr;
}


// Name: DisplayRoute
// Desc: Displays all of the ports in a route
// Preconditions: Requires a Route
// Postconditions: Displays all of the ports in a route
// Formatted: Baltimore, Maryland (N39.209 W76.517)
void Route::DisplayRoute() {
  int size = 1;//for displaying with numbered list
  Port *curr = m_head;

  //continue to itterates for a numbered list of ports
  while (curr != nullptr) {
    cout << size << ". " << curr -> GetName() << ", " << curr -> GetLocation() << " (N" << curr -> GetNorth() << " W" << curr -> GetWest() << ")" << endl;

    curr = curr -> GetNext();
    ++size;
  }
}
