/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Leah Ball
 ** Date:    04/05/2022
 ** Email:   lball1@umbc.edu
 **
 Description: CPP file for Lqueu class. Includes both class definition and
 class function definitions. Creates linked lists with different commands to change the list
*****************************************************************************/
#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();
  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int x);
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Lqueue Class Here***********
//**********All Functions Are Required Even If Not Used for Trivia**************
// Name: Lqueue() (Linked List Queue) - Default Constructor
// Desc: Used to build a new linked queue (as a linked list)
// Preconditions: None
// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
// Requ
template <class T>
Lqueue<T>::Lqueue() {
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
}


// Name: ~Lqueue() - Destructor
// Desc: Used to destruct a Lqueue
// Preconditions: There is an existing lqueue with at least one node
// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
// Required
template <class T>
Lqueue<T>::~Lqueue() {

  Node<T> *curr = m_head;

  //continues to iterate and delete until end of list
  while(curr != nullptr) {
    m_head = curr;
    curr = curr -> GetNext();
    delete m_head;
  }
  
  //resets variables
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}


// Name: Lqueue (Copy Constructor)
// Preconditions: Creates a copy of existing LQueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
// Required
template <class T>
Lqueue<T>::Lqueue(const Lqueue& newQueue) {

  //copies head
  m_head = new Node<T>(newQueue.m_head -> GetData());

  //to keep track of currect node
  Node<T> *curr = m_head;
  m_tail = newQueue.m_head;
  
  while (m_tail -> GetNext() != nullptr) {
    //sets the next node
    curr -> SetNext(new Node<T>(m_tail -> GetNext()-> GetData()));
    m_tail = m_tail -> GetNext();
    curr = curr -> GetNext();
  }
  
  //copies size
  m_size = newQueue.m_size;
}


// Name: operator= (Overloaded Assignment Operator)
// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
// Required
template <class T>
Lqueue<T>& Lqueue<T>::operator= (Lqueue& newQueue) {
  //if already copies
  if (this == &newQueue)
    return *this;
  
  else {
    //must clear before starting
    Clear();
    
    //copies head
    m_head = new Node<T>(newQueue.m_head -> GetData());
    Node<T> *curr = m_head;//keeps track of current node
    m_tail = newQueue.m_head;

    while (m_tail -> GetNext() != nullptr) {
      //sets the next node
      curr -> SetNext(new Node<T>(m_tail -> GetNext()-> GetData()));
      m_tail = m_tail -> GetNext();
      curr = curr -> GetNext();
    }
    //copies size
    m_size = newQueue.m_size;
    return *this;
  }
}


// Name: Push
// Preconditions: Takes in data. Creates new node.
//                Requires a Lqueue
// Postconditions: Adds a new node to the end of the lqueue.
// Required
template <class T>
void Lqueue<T>::Push(const T& data) {
  //puts data into node
  Node<T> *newNode = new Node(data);

  if (m_size == 0) {
    m_head = newNode;
    m_tail = newNode;
  }
  
  else {

    //points node to nullptr
    newNode -> SetNext(nullptr);
    //connects tail to current node
    m_tail -> SetNext(newNode);
    //makes current node tail
    m_tail = newNode;
  }
  
  ++m_size;
}


// Name: Pop
// Preconditions: Lqueue with at least one node.
// Postconditions: Removes first node in the lqueue, returns data from first node.
// Required
template <class T>
T Lqueue<T>::Pop() {
  //gets data from the front
  T data = Front();
  
  //save second node
  Node<T> *next = m_head -> GetNext();

  delete m_head;//deletes first node
  m_head = next;
  
  m_size--;//changes size
  return data;
}


// Name: Display
// Preconditions: Outputs the lqueue.
// Postconditions: Displays the data in each node of lqueue
// Required (used only for testing)
template <class T>
void Lqueue<T>::Display() {
  Node<T> *curr = m_head;

  //prints data out until end
  while (curr != nullptr) {
    cout << curr -> GetData() << " ";
    curr = curr -> GetNext();
  }
}


// Name: Front
// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front
// Required
template <class T>
T Lqueue<T>::Front() {
  return m_head -> GetData();
}


// Name: IsEmpty
// Preconditions: Requires a lqueue
// Postconditions: Returns if the lqueue is empty.
// Required
template <class T>
bool Lqueue<T>::IsEmpty() {
  if (m_size == 0)
    return true;
  else
    return false;
}


// Name: GetSize
// Preconditions: Requires a lqueue
// Postconditions: Returns m_size
// Required
template <class T>
int Lqueue<T>::GetSize() {return m_size;}


// Name: Find()
// Preconditions: Requires a lqueue
// Postconditions: Iterates and if it finds the thing, returns index, else -1
// Required
template <class T>
int Lqueue<T>::Find(T& data) {
  Node<T> *curr = m_head;
  int count = 0;

  //goes through linked list
  while(curr != nullptr) {
    //checks if data of current same as user data
    if (curr -> GetData() == data)
      return count;
    curr = curr -> GetNext();
    //holds index
    count++;
  }
  return -1;
}


// Name: Swap(int)
// Preconditions: Requires a lqueue
// Postconditions: Swaps the nodes at the index with the node prior to it.
// Required
template <class T>
void Lqueue<T>::Swap(int index) {
  int size = 2;//correlates with next
  Node<T> *curr = m_head;
  Node<T> *next = m_head -> GetNext();
  Node<T> *secondNext = next -> GetNext();

  //cannot swap if size or index is 1
  if (m_size == 1)
    cout << " not enough nodes to swap" << endl;
  if (index == 1)  
    cout << "no nodes prior" << endl;

  if (index == 2) {
    curr -> SetNext(secondNext);
    next -> SetNext(curr);
  }

  else {
    while(secondNext -> GetNext() != nullptr){

      if (size == index) {
	//connects all the nodes respectively
	next -> SetNext(secondNext -> GetNext());
	secondNext -> SetNext(next);
	curr -> SetNext(secondNext);
      }
      //continues traversing
      curr = curr -> GetNext();
      next = next -> GetNext();
      secondNext = next -> GetNext();
      size++;
    }
    
    //if wants to swap last element in list 
    if (index == m_size) {
      next -> SetNext(nullptr);
      secondNext -> SetNext(next);
      curr -> SetNext(secondNext);
    }
  }
}


// Name: Clear
// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
// Required
template <class T>
void Lqueue<T>::Clear() {
  Node<T> *curr = m_head;
  
  //iterates through and deletes node
  while(curr != nullptr) {
    m_head = curr;
    curr = curr -> GetNext();
    delete m_head;
  }

  //resets info
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}


// Name: At
// Precondition: Existing Lqueue
// Postcondition: Returns object from Lqueue at a specific location
// Desc: Iterates to node x and returns data from Lqueue
// Required
template <class T>
T Lqueue<T>::At(int x) {
  int count = 1;

  //if nodes exists
  if (m_size > 0) {
    
    Node<T> *curr = m_head;
    //iterates through until index the same as users input
    while(curr != nullptr) {
      if (x == count) 
	return curr -> GetData();
      curr = curr -> GetNext();

      count++;//counts the index
    }

    return m_head -> GetData();
  }
  else
    return nullptr;
}

#endif
