/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Leah Ball
 ** Date:    04/05/2022
 ** Email:   lball1@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};

//**********Implement Trivia Class Here***********
// Name: Default Constructor
// Desc: Displays the title, Loads Questions and calls menu
// Indicates if the file was not loaded.
// Precondition: None
// Postcondition: User is prompted with assignment menus
template <class T>
Trivia<T>::Trivia(string filename) {
  DisplayTitle();
  int choice = 0;
  
  //initializes m_questions
  m_questions = new Lqueue<Question<T>* >();

  if (LoadQuestions(filename) == true) {
    MainMenu();
    cin >> choice;
    
    //continues to ask until user quits
    while(choice != 3) {

      if (choice == 1)
	DisplaySubjects();

      //way to play trivia
      else if (choice == 2)
	StartSubject();

      else
	cout << "Choose an option between 1 and 3" << endl;

      MainMenu();
      cin >> choice;
    }
  }
  cout << "Thank you for trying UMBC Trivia" << endl;
}


// Name: Destructor
// Desc: Deallocates memory allocated for the Questions and
// resets all variables.
// Precondition: A Trivia exists.
// Postcondition: All dynamically allocated memory in Trivia is deleted.
template <class T>
Trivia<T>::~Trivia() {
  //deletes every question then clears
  for (int i = 0; i < m_questions -> GetSize(); i++) {
    delete m_questions -> At(i);
    m_questions -> Clear();
  }
  
  //new initialization to delete
  m_questions = new Lqueue<Question<T>* >();
  delete m_questions;
  m_questions = nullptr;
};


// Name: LoadQuestions
// Desc: Each input file will be for a specific type of question (int, double, string)
//       Reads in Questions from a file and stores them in anLqueue.
//       An input file will be for exactly one type of question (int, double, string)
// Precondition: None.
// Postcondition: Returns true if file was read. Otherwise, it returns false.
template <class T>
bool Trivia<T>::LoadQuestions(string filename){
  ifstream newFile;
  string subject,question,datatype, difficulty, newLines;
  T answer;
  
  newFile.open(filename);
  if (newFile.is_open()) {

    //continues getting info until end of file
    while (getline(newFile, subject, DELIMITER)) {
      getline(newFile, question, DELIMITER);
      getline(newFile, datatype, DELIMITER);
      getline(newFile, difficulty, DELIMITER);
      //so that can be of type T
      newFile >> answer;

      int intDifficulty = stoi(difficulty);
      Question<T> *newQuestion = new Question<T>(subject, question, datatype, intDifficulty, answer);

      //inserts question into queue
      m_questions -> Push(newQuestion);
      AddSubject(subject);
      //for extra indent after last element
      getline(newFile, newLines);
    }    
    newFile.close();
    return true;
  }
  
  else {
    cout << "File could not be opened" << endl;
    return false;
  }
}


// Name: MainMenu
// Desc: Presents user with menu options for showing subjects and allowing
// user to work on a subject.
// Precondition: None.
// Postcondition: The main menu is presented.
  template <class T>
  void Trivia<T>::MainMenu() {
    cout << "Choose an option" << endl;
    cout << "1. Display Subjects" << endl;
    cout << "2. Start Subject" << endl;
    cout << "3. Quit" << endl;
  };


// Name: DisplaySubjects
// Desc: Presents all Subjects with corresponding numerical identifiers.
// Precondition: Subjects have been added.
// Postcondition: All assignments are printed to the screen.
template <class T>
void Trivia<T>::DisplaySubjects() {
  cout << "Possible Subjects:" << endl;
  
  //iterates through all subjects in vector
  for (unsigned int i = 0; i < m_subjects.size(); i++) {
    cout << i + 1 << ". " << m_subjects[i] << endl;
  }
}


// Name: StartSubject
// Desc: Starts working on a selected Subject.
// Displays the number of questions in subject.
// Starts at beginning and goes through each question.
// After all questions have been answered:
//       displays total correct, incorrect, and percentage correct
// Precondition: m_questions has been populated
// Postcondition: Returns to main menu
  template <class T>
  void Trivia<T>::StartSubject() {
    int questionChoice;
    int correct = 0;
    int totalQuestions = 1;
    int subjectChoice = ChooseSubject();
    double percentage = 0.0;
    T answer;

    //calls function to get number of questions with same subject
    questionChoice = QuestionsPerSubject(m_subjects[subjectChoice]);
    cout << "There are " << questionChoice << " in this subject" << endl;

    for (int i = 0; i < m_questions -> GetSize(); i++) {

      //if the subject of question equals chosen subject
      if (m_questions -> At(i) -> m_subject == m_subjects[subjectChoice]) {

	//gives question and type
	cout << totalQuestions << ". " << m_questions -> At(i) -> m_question << endl;
	cout << "Please answer with a " << m_questions -> At(i) -> m_datatype << endl;

	cin >> answer;
	cout << endl;
	
	//if answer correct
	if (m_questions -> At(i) -> CheckAnswer(answer)) {
	  cout << "Correct" << endl;
	  correct++;
	}

	else
	  cout << "Incorrect" << endl;

	totalQuestions++;
      }
    }

    //calculates percentage of correct over total questions in subject
    percentage = ((double)correct/(double)questionChoice) * 100;
    
    cout << "You got " << correct << " correct" << endl;
    cout << "You got " << questionChoice - correct << " incorrect" << endl;
    cout << "Which is " << percentage << "%" << endl;
  }


  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
    template <class T>
    void Trivia<T>::AddSubject(string subject) {
      bool flag = true;
      
      //checks to see if subject in list
      for (unsigned int i = 0; i < m_subjects.size(); i++) {
	if (m_subjects[i] == subject) {
	  flag = false;
	}
      }

      //if not adds to subject vector
      if (flag == true)
	m_subjects.push_back(subject);
    }


// Name: ChooseSubject
// Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
// in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
// Precondition: A Subject exists.
// Postcondition: Returns value entered minus one
template <class T>
int Trivia<T>::ChooseSubject() {
  int choice;
  cout << "What subject would you like to try? " << endl;
  DisplaySubjects();
  cin >> choice;
  return (choice - 1);
}


// Name: QuestionsPerSubject
// Desc: Iterates over m_questions and counts how many questions match the subject
// passed into function
// Precondition: A Subject exists.
// Postcondition: Returns number of questions of a particular subject
template <class T>
int Trivia<T>::QuestionsPerSubject(string subject){
  int count = 0;
  for (int i = 0; i < m_questions -> GetSize(); i++){

    //if subject the same as chosen user subject
    if (m_questions -> At(i) -> m_subject == subject)
      count++;
  }
  return count;
}


// Name: DisplayTitle
// Desc: Displays opening Welcome message
// Precondition: None.
// Postcondition: Title is displayed.
template <class T>
void Trivia<T>::DisplayTitle(){cout << "Welcome to UMBC Trivia!" << endl;}


#endif
