/*****************************************
** File:    proj1.cpp
** Project: CMSC 202 Project 1, Fall 2021
** Author:  Leah Ball
** Date:    3/1/21
** Section: 10/12
** E-mail:  lball1@umbc.edu
**
**Project simulates wordle game. User most guess a randomly chosen word and is told whether or not letters in right spot or in the word.
********************************************/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

//defining functions
string chooseWord (int, string words[]);
bool checkInList(string, int);
string checkLetters(string, string);
void isCorrect(string, int);
void guessesLeft(int);

//symbols for wordle
const string CORRECT = "!";
const string INCORRECT = "_";
const string INWORD = "&";


int main () {
    //declaring variables
    string wordleWord;
    string words[2315] = { };
    string playAgain;
    int lenList = 2315;

    //choosing random word as key word
    wordleWord = chooseWord(lenList, words);

    //play game until user doesn't want to play again
    isCorrect(wordleWord, lenList);
    cout << "Would you like to play again?(y/n) " << endl;
    cin >> playAgain;

    while (playAgain == "y") {
        //chooses word again
        wordleWord = chooseWord(lenList, words);
        cout << wordleWord << endl;

        //checks if user has won until winner loses or wins
        isCorrect(wordleWord, lenList);
        cout << "Would you like to play again?(y/n) " << endl;
        cin >> playAgain;
    }
    return 0;
};


void isCorrect(string wordleWord, int lenList) {
    //defining variables
    string guess;
    string alreadyGuessed = "";
    bool win = false;
    int i = 0;
    //keep asking user what word is until winner gets it right or exceeds 6 tries
    do {
        cout << "What word would you like to guess?" << endl;
        cin >> guess;
        cout << "\n";

        //if word in list, prints out results of word guessed
        if (checkInList(guess, lenList)) {
            alreadyGuessed += checkLetters(guess, wordleWord);
            cout << alreadyGuessed;
            guessesLeft(i);
            ++i;
        }
        //if not in list
        if (!checkInList(guess, lenList)) {
            cout << "not in word list\n" << endl;
        }

        if (guess == wordleWord) {
            win = true;
        }
    }

    //end of do while loop
    while (win == false and i < 6);

    //results of do while loop
    if (win == true)
        cout << "Congratulations, you won!" << endl;
    if (win == false)
        cout << "Sorry, you lost\nThe correct word was: " << wordleWord << endl;
}


string chooseWord(int lenList, string words[2315]) {
    ifstream inputStream;
    //opens proj1_data file
    inputStream.open("C:\\Users\\leah1\\Downloads\\proj1_data.txt");

    // if it can't be opened
    if (!inputStream) {
        cout << "file cannot be opened" << endl;
        return 0;
    };
    //if file opened, put words into an array
    if (inputStream) {
        for (int i = 0; i < lenList; ++i)
            inputStream >> words[i];
    };
    inputStream.close();

    //randomly chooses and returns word for wordleWord
    srand(time(NULL));
    int i = rand();
    return words[(i % lenList)];
}


bool checkInList(string guess, int lenList) {
    ifstream inputStream;
    string words [2315];

    //open proj1data file
    inputStream.open("C:\\Users\\leah1\\Downloads\\proj1_data.txt");
    if (!inputStream) {
        cout << "file cannot be opened" << endl;
        return 0;
    };

    //checks if guessed word in the data file
    if (inputStream) {
        for (int i = 0; i < lenList; ++i) {
            inputStream >> words[i];
            if (guess == words[i]) {
                return 1;
            }
        }
    }
    inputStream.close();
    return 0;
};

string checkLetters(string guess, string wordleWord) {
    string correctLetters = guess + "\n";

    //goes through every letter of guessed word
    for (int i = 0; i < 5; ++i) {
        bool notInWord = true;

        //adds CORRECT symbol to final word if in the right spot
        if (guess[i] == wordleWord[i]) {
            correctLetters += CORRECT;
        }

        //checks if one letter of the guessed word anywhere in wordleWord
        for (int j = 0; j < 5; ++j) {
            //if it is in word, changes boolean
            if ((guess[i] == wordleWord[j]) && (guess[i] != wordleWord[i])){
                notInWord = false;
            }
        }
        //if notInWord, adds INCORRECT symbol
        if (notInWord == true and guess[i]!= wordleWord[i])
            correctLetters += INCORRECT;

        //if in word, adds INWORD symbol
        if (notInWord == false && guess[i] != wordleWord[i])
            correctLetters += INWORD;
    };
    correctLetters += "\n";
    return correctLetters;
};


void guessesLeft(int i) {
    string oneGuess = "-----\n";
    string repeat;

    //prints out the blank lines for every remaining guess
    for (i = 4 - i; i >= 0; --i) {
        repeat += oneGuess;
    }
    cout << repeat << endl;
}
