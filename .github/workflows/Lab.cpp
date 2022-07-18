#include "Lab.h"
#include "Substance.h"
#include "Chemist.h"

void Lab::LoadSusbstances() {
  // Name: LoadSubstances
  // Desc - Loads each substance into m_substances from file
  //        The loads all substances from m_substances into m_myChemist's substance array
  // Preconditions - Requires file with valid substance data
  // Postconditions - m_substance is populated with substance structs
    string m_name, m_type, m_formula, m_substance1, m_substance2;
    ifstream inputStream;
    if (inputStream.open(PROJ2_DATA))
        for (int i = 0; i < PROJ2_SIZE; ++i) {
            getline(inputStream, m_name, ',');
            getline(inputStream, m_type, ',');
            getline(inputStream, m_formula, ',');
            getline(inputStream, m_susbstance1, ',');
            getline(inputStream, m_susbstance2);
            Substance newSub(m_name, m_type, m_formula, m_substance1, m_substance2, 0);
            m_substances[i] = newSub;

        }
}


void Lab::StartLab(){
  // Name: StartLab()
  // 1. Displays Lab Title (as implemented below)
  // 2. Loads all substances and their recipes into m_substances (Load Substances)
  // 3. Asks user for their chemist's name (store in m_myChemist as m_myName)
  // 4. Copies all substances from m_substances into the chemist's substance array
  // 5. Manages the game itself including win conditions continually calling the main menu
  // Preconditions - None
  // Postconditions - m_substances and m_myChemist's substances populated
    int userInput = 0;
    string name;
    //loads substance and gets substances
    Lab.LabTitle();
    Lab.LoadSubstances();
    //gets name
    cout << "What is your Chemist's name?" << endl;
    getline(cin, name, '\n');
    m_myChemist.SetName(name);
    //loads individual substances into actual chemist
    for (int i = 0; i < PROJ2_SIZE; ++i)
        m_myChemist.AddSubstance(m_substances[i]);
    //implements functions based on user output
    userInput = lab.MainMenu();
    while (Lab.MainMenu() != 5)
        if (userInput == 1)
            Lab.DisplaySubstances();
        else if (userInput == 2)
            Lab.SearchSubstances();
        else if (userInput == 3)
            Lab.MergeSubstances();
        else if (userInput == 4)
            Lab.CalcScore();
        else if (userInput < 1 || userInput > 5)
            cout << "Not an option(must be between 1 and 5)" << endl;
        userInput = Lab.MainMenu();
}

void Lab::DisplaySubstances() {
  // Name: DisplayMySubstances()
  // Desc - Iterates over m_myChemist's substances
  // Preconditions - Player's chemist has substances
  // Postconditions - Displays a numbered list of substances
    for (int i = 0; i < PROJ2_SIZE; ++i) {
        cout << i + 1 << " ";
        cout << m_myChemist.m_mySubstances.m_name << " ";
        cout << m_myChemist.m_mySubstances.m_formula << " ";
        cout << m_myChemist.m_mySubstances.m_quantity << endl;
        }
}

int Lab::MainMenu() {
  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - Player has an Chemist
  // Postconditions - Returns number including exit
    int userInput = 0;
    cout << "What would you like to do?\n1. Display the Chemist's substances?\n2. Search elements\n3. Attempt to Merge Substances\n4. See Score\n5. Quit" << endl;
    cin >> userInput;
    return userInput;
}

void Lab::SearchSubstances() {
  // Name: SearchSubstances()
  // Desc - Attempts to search for raw substances (must be type "element")
  // Preconditions - Raw substances loaded
  // Postconditions - Increases quantity in Chemist's possession of substances
    srand(time(NULL));
    int i = rand();
    Substance element;
    //return substance at specific index
    element[i] = m_myChemist.GetSubstance(i % 40);
    if (m_myChemist.CheckSubstance(element) == -1)
        cout << "Element does not exist" << endl;
    else if (Chemist.CheckSubstance(element) > -1)
        m_myChemist.IncrementQuantity(element[i]);
}

void Lab::CombineSubstances() {
  // Name: CombineSubstances()
  // Desc - Attempts to combine known substances. If combined, quantity of substance decreased
  // 1. Requests user to choose two substances (RequestSubstance)
  // 2. Checks to see if formula exists for combining two chosen substances
  //     (checks sub1, sub2 and sub2, sub1) using SearchFormula
  // 3. If there is an available formula for two chosen substances, checks
  //     quantity for two chosen substance.
  // If no quantity for two substances, tells user that there is no available quantity
  // If quantity is available, decreases quantity for two chosen substances
  //     from the chemist then increases new substance
  // 4. If there is no available formula, tells user that nothing happens when you try and merge two chosen substances
  // Preconditions - Chemist is populated with substances
  // Postconditions - Increments quantity of substance "made", decreases quantity of source items
    int element1, element2;
    Substance substance1, substance2;
    int numSubstance;
    //returns integer of substance selected by user
    RequestSubstance(&element1);
    RequestSubstance(&element2);
    //returns substance at specifix index
    substance1 = m_myChemist.GetSubstance(element1);
    substance2 = m_myChemist.GetSubstance(element2);
    //returns index of matching formula
    numSubstance = SearchFormulas(substance1, substance2);
    //if no matching formula
    if (numSubstance == -1)
        cout << "no available formula" << endl;
    //if matching formula
    else if (numSubstance > -1)
        //if enough of both
        if (m_myChemist.CheckQuantity(substance1, substance2) == true)
            m_myChemist.DecrementQuantity(m_myChemist.m_mySubstances);
            m_myChemist.DecrementQuantity(m_myChemist.m_mySubstances);
            m_myChemist.IncrementQuantity(m_myChemist.m_mySubstances);
        //if not enough
        else if (m_myChemist.CheckQuantity(substance1, substance2) == false)
            cout << "quantity not enough" << endl;
}

void Lab::RequestSubstance(int &choice) {
  // Name: RequestSubstance()
  // Desc - Allows the user to choose a substance to try and merge.
  //        Returns the index of chosen substance
  // Preconditions - Chemist has substances to try and merge
  // Postconditions - Returns integer of substance selected by user
    cout << "Which substances would you like to combine?\nTo list known substances enter -1" << endl;
    cin >> choice;
    while (choice < 0 && choice > PROJ2_SIZE)
        cout << "Element not available for combining" << endl;
        Lab.DisplaySubstances();
        cout << "Which substances would you like to combine?\nTo list known substances enter -1" << endl;
        cin >> choice;
}

int Lab::SearchFormulas(string substance1, string substance2) {
  // Name: SearchFormula()
  // Desc - Searches formulas for two strings (name of item)
  // Preconditions - m_substances is populated
  // Postconditions - Returns int index of matching formula
    for (int i = 0; i < PROJ2_SIZE; ++i){
        if (m_myChemist.m_mySubstances[i].m_substance1 == substance1 && m_myChemist.m_mySubstances[i].substance2 == substance2)
            return i;
        if (m_myChemist.m_mySubstances[i].m_substance1 == substance2 && m_myChemist.m_mySubstances[i].m_substance2 == substance1)
            return i;
        else
            return -1;
    }
}

void Lab::CalcScore() {
  // Name: CalcScore()
  // Desc - Displays current score for Chemist
  // Preconditions - Chemist is populated with substances
  // Postconditions - Displays total number of substances found. Displays
  //        percentange found as number found divided by total available
    double score = 0;
    for (int i = 0; i < PROJ2_SIZE; ++i){
        if (m_myChemist.m_mySubstances[i].m_quantity > 0)
            score += 1
    }
    cout << "The Great Chemist" << m_myChemist.m_myName << endl;
    cout << "There are 283 substances found" << endl;
    cout << "You have found " << score << "substances" << endl;
    cout << "This is " << score/PROJ2_SIZE << "%" << endl;
}



