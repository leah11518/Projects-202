#include "Chemist.h"
#include "Substance.h"
#include "Lab.h"


Chemist::Chemist() {
  // Name: Chemist() - Default Constructor
  // Desc: Used to build a new Chemist
  // Preconditions - Requires default values
  // Postconditions - Creates a new Chemist (with a default name of "Beaker" and
  //       m_numSubstances = 0
  m_myName = "Beaker";
  m_numSubstances = 0;
	}

Chemist::Chemist(string name) {
  // Name: Chemist(name) - Overloaded constructor
  // Desc - Used to build a new Chemist
  // Preconditions - Requires name
  // Postconditions - Creates a new Chemist (with passed name and m_numSubstance = 0)
  m_myName = GetName();
  m_numSubstances = 0;
}

string Chemist::GetName() {
  // Name: GetName()
  // Desc - Getter for Chemist name
  // Preconditions - Chemist exists
  // Postconditions - Returns the name of the Chemist
  return m_myName;
}

void Chemist::SetName(string name){
  // Name: SetName(string)
  // Desc - Allows the user to change the name of the Chemist
  // Preconditions - Chemist exists
  // Postconditions - Sets name of Chemist
  m_myName = name;
}

int Chemist::CheckSubstance(Substance substance) {
  // Name: CheckSubstance(Substance)
  // Desc - Checks to see if the Chemist has a substance if so, returns
  //        the index where it exists, if not returns -1
  // Preconditions - Chemist already has substance
  // Postconditions - Returns index of substance if Chemist has it else -1
  for (int i = 0; i < PROJ2_SIZE; ++i) {
    if (m_mySubstances[i].m_name == substance.m_name)
      return i;
  }
  return -1;
}

void Chemist::AddSubstance(Substance substance) {
  // Name: AddSubstance(string)
  // Desc - Inserts a material into the Chemist's list of substances. Has
  //        to see if it exists in m_mySubstances first to find location.
  //        Then adds substance and increments m_numSubstances
  // Preconditions - Chemist exists
  // Postconditions - Add a substances to the Chemist's m_mySubstances with a quantity of 0
  for (int i = 0; i < PROJ2_SIZE; ++i) {
    m_mySubstances[i].m_name = substance.m_name;
    m_mySubstances[i].m_type = substance.m_type;
    m_mySubstances[i].m_formula = substance.m_formula;
    m_mySubstances[i].m_substance1 = substance.m_substance1;
    m_mySubstances[i].m_substance2 = substance.m_substance2;
    m_mySubstances[i].m_quantity = substance.m_quantity;
  }
}


void Chemist::IncrementQuantity(Substance substance) {
  // Name: IncrementQuantity(Substance)
  // Desc - Adds quantity to list of substances the chemist knows.
  //        Has to find location in array first. Then increments quantity
  // Preconditions - Chemist exists
  // Postconditions - Increases quantity of material for chemist
  int index = CheckSubstance(substance);
  if (index == -1) {
    m_mySubstances[m_numSubstances] = substance;
  m_numSubstances++;
  }
  else
    m_mySubstances[index].m_quantity++;
}


bool Chemist::DecrementQuantity(Substance substance) {
  // Name: DecrementQuantity(Substance)
  // Desc - Reduces quantity from chemist's inventory with true, if no quantity false
  // Preconditions - Chemist exists
  // Postconditions - Reduces quantity of substance for chemist
  int index = CheckSubstance(substance);
  if (index == -1) {
    m_mySubstances[m_numSubstances] = substance;
  m_numSubstances++;
  }
  else
    m_mySubstances[index].m_quantity++;
  return true;
}


bool Chemist::CheckQuantity(Substance substance1, Substance substance2) {
  // Name: CheckQuantity(Substance)
  // Desc - Checks to see if quantity of two merge substances is greater than one.
  //        if the quantity of substance 1 is greater than one and the
  //        quantity of substance two is greater than one, returns true else false
  // Preconditions - Chemist exists with substances
  // Postconditions - Returns true if both are available
  int index1 = CheckSubstance(substance1);
  int index2 = CheckSubstance(substance2);
  if (index1 == -1 || index2 == -1)
    return false;
  else
    return true;
}


Substance Chemist::GetSubstance(int num) {
  // Name: GetSubstance(int)
  // Desc - Returns a substance at at specific index
  // Preconditions - Chemist already has substances
  // Postconditions - Returns substance at specific index
  return m_mySubstances[num];
}


int Chemist::GetTotalSubstances() {
  // Name: GetTotalSubstances
  // Desc - Iterates over m_mySubstances and counts each substance with a quantity higher than 0
  // Preconditions - Chemist may have no substances
  // Postconditions - Returns number of substances with a quantity greater than 0
  int numSubstances = 0;
  for (int i = 0; i < PROJ2_SIZE; ++i) {
    if (m_mySubstances[i].m_quantity > 0)
      numSubstances += m_mySubstances[i].m_quantity;
  }
  return numSubstances;
}
