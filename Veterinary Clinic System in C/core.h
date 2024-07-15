// Copy the below commented "header" section to all your source code files!

/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Rohit Sivakumar
Student ID#: 104670229
Email      : rsivakumar8@myseneca.ca
Section    : NCC

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/
#ifndef CORE_H
#define CORE_H



//clear std input buffer
void clearInputBuffer(void);

//wait for user to input "enter" key to continue
void suspend(void);

//validate int input
int inputInt();

//validate pos int input
int inputIntPositive();

//validate int is between an inputted range
int inputIntRange(int lower, int upper);

//validate chars inputted 
char inputCharOption(const char* validChars);

//validate C string inputted
void inputCString(char* input, int minLength, int maxLength);

//display Formatted phone numbers if input is valid
void displayFormattedPhone(const char* phoneNumber);

//validate phone num input;
void inputPhoneValid(char* receive, int min, int max);

#endif // !CORE_H