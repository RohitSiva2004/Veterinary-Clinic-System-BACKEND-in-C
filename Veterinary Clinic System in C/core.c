
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

void clearInputBuffer(void) {
    while (getchar() != '\n') {
        ;//do nothing
    }

}

void suspend(void) {
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
    

}


int inputInt() {
    int value;
    char newline;

    // Prompt for input until a valid integer is entered
    while (1) {
        
        if (scanf("%d%c", &value, &newline) != 2 || newline != '\n') {
            // Clear input buffer and display error message
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }

        else {
            // Valid input, return the integer value
            return value;
        }
    }
}

int inputIntPositive() {
    int value;
    char newline;

    // Prompt for input until a positive integer is entered
    while (1) {
        
        if (scanf("%d%c", &value, &newline) != 2 || newline != '\n') {
            // Clear input buffer and display error message
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (value <=0) {
            // Check if the value is within the specified range
            printf("ERROR! Value must be > 0: ");
        }
        else {
            // Valid input within range, return the integer value
            return value;
        }
    }
}

int inputIntRange(int lowerBound, int upperBound) {
    int value;
    char newline;

    // Prompt for input until a valid integer within the range is entered
    while (1) {
        
        if (scanf("%d%c", &value, &newline) != 2 || newline != '\n') {
            // Clear input buffer and display error message
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        else if (value < lowerBound || value > upperBound) {
            // Check if the value is within the specified range
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }

        else {
            // Valid input within range, return the integer value
            return value;
        }
    }
}

char inputCharOption(const char* validChars) {
    char inputChar;
    int isValid = 0;

    do {
        scanf(" %c", &inputChar);  // Add a space before %c to skip whitespace characters
        

        // Check if inputChar is in validChars
        const char* ptr = validChars;
        while (*ptr != '\0') {
            if (inputChar == *ptr) {
                isValid = 1;
                break; // Exit loop if valid character found
            }
            ptr++;
        }

        if (!isValid||getchar() != '\n') {
            printf("ERROR: Character must be one of [%s]: ", validChars);
            clearInputBuffer(); // Clear the input buffer if necessary
            isValid = 0;
            
        }
        
    } while (!isValid);

    return inputChar;
}




void inputCString(char* cstringPtr, int minLength, int maxLength) {
    char temp[101]; // Temporary storage including space for null terminator
    int length;
    int error = 0;
    do {
       
        scanf(" %[^\n]", temp); // Read input until newline character
        getchar();
        length = strlen(temp); // Calculate length excluding newline

        if (length > maxLength || length < minLength) {
            if (minLength == maxLength) {
                printf("ERROR: String length must be exactly %d characters.", maxLength);
            }
            else if(length>maxLength){
                printf("ERROR: String length must be no more than %d chars: ", maxLength);
                error = 1;
            }
            else {
                printf("ERROR: String length must be between %d and %d characters.", minLength, maxLength);
                
            }
        }
    } while (length < minLength || length > maxLength);
    if (error == 1) {
        printf("\n");
    }
    error = 0;
    strcpy(cstringPtr, temp); // Copy valid string to provided pointer
    
}



void inputPhoneValid(char* receive, int min, int max)
{
    int size;
    char input[1001]; // Increase buffer size by 1 for null terminator

    do {
        
        scanf("%1000s", input); // Limit input to prevent buffer overflow
        size = strlen(input);

        if (size < min || size > max) {
            printf("Invalid %02d-digit number! Number: ", min);
        }
    } while (size < min || size > max);

    strcpy(receive, input);
}





void displayFormattedPhone(const char* phoneNumber) {

    if (phoneNumber == NULL) {
        printf("(___)___-____");
        return;
    }
    int isValid = 1;
    int i = 0;

    // Validate the phoneNumber array
    for (i = 0; i < 10 && isValid; i++) {
        if (phoneNumber[i] < '0' || phoneNumber[i] > '9') {
            isValid = 0;
        }
    }
    if (i != 10 || phoneNumber[i] != '\0') {
        isValid = 0;
    }

    // Use flag to determine output
    if (isValid) {
        printf("(%c%c%c)%c%c%c-%c%c%c%c", phoneNumber[0], phoneNumber[1], phoneNumber[2],
            phoneNumber[3], phoneNumber[4], phoneNumber[5],
            phoneNumber[6], phoneNumber[7], phoneNumber[8],
            phoneNumber[9]);
    }
    else {
        printf("(___)___-____");
    }
}

