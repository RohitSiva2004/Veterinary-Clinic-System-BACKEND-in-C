

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"
int i = 0;
int apt = 0;

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("\nClinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            
            break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  
            suspend();
            break;
        }
    } while (selection);
}



void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    int found = 0; // Flag to indicate if any records are found

    // Display table header based on the format
    if (fmt == FMT_TABLE) {
        displayPatientTableHeader();
    }

    // Iterate through the patient array and display each patient record
    for (i = 0; i < max; ++i) {
        if (patient[i].patientNumber != 0) { // Check if patient number is not zero
            displayPatientData(&patient[i], fmt); // Display patient record
            found = 1; // Set flag to indicate record found
        }
    }
    printf("\n");

    // If no records found, print "*** No records found ***"
    if (!found) {
        printf("*** No records found ***\n");
    }
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max) {
    int choice;

    while (1) {
        // Display menu
        printf("Search Options\n==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        choice = inputIntRange(0, 2);
        printf("\n");

        // Check the user's choice
        if (choice == 1) {
            searchPatientByPatientNumber(patient, max);
            
            suspend();
            
        }
        else if (choice == 2) {
            searchPatientByPhoneNumber(patient, max);
            
            suspend();
            
        }
        else if (choice == 0) {
            return; // Return to previous menu
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max) {
    int index = -1; // Index to store the new record
    int foundFreeElement = 0; // Flag to indicate if a free element is found

    // Find a free element for a new record
    for (i = 0; i < max && !foundFreeElement; ++i) {
        if (patient[i].patientNumber == 0) {
            index = i;
            foundFreeElement = 1; // Set flag to true
        }
    }

    // If no free element found, display error message and return
    if (!foundFreeElement) {
        printf("ERROR: Patient listing is FULL!\n\n");
        return;
    }

    // Get the next unique patient number
    int newPatientNumber = nextPatientNumber(patient, max);

    // Assign the new patient number to the element at the index
    patient[index].patientNumber = newPatientNumber;
    
    // Get user input for the new record
    inputPatient(&patient[index]);
  

    // Display confirmation message
    printf("*** New patient record added ***\n\n");
    clearInputBuffer();

}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max) {
    int patientNumber;
    int index = -1;

    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();
    printf("\n");
    

    // Find the index of the patient record by patient number
    index = findPatientIndexByPatientNum(patientNumber, patient, max);

    // If the patient record exists, call menuPatientEdit for editing options
    if (index != -1) {
        
        menuPatientEdit(&patient[index]);
    }
    else {
        // If the patient record does not exist, display an error message
        printf("ERROR: Patient record not found!\n");
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max) {
    int patientNumber;
    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();
    

    // Find the index of the patient record by patient number
    int index = findPatientIndexByPatientNum(patientNumber, patient, max);

    // If the patient record exists, display the record and prompt for confirmation
    if (index != -1) {
        printf("\n");
        displayPatientData(&patient[index], FMT_FORM); // Display patient record in "form" format

        // Prompt for confirmation to remove the record
        char confirmation;
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        confirmation = inputCharOption("yn");

        // If user confirms to remove the record, set patient information to safe empty state
        if (confirmation == 'y' || confirmation == 'Y') {
            // Set patient information to safe empty state
            patient[index].patientNumber = 0;
            patient[index].name[0] = '\0';
            patient[index].phone.description[0] = '\0';
            patient[index].phone.number[0] = '\0';
            printf("Patient record has been removed!\n\n");
        }
        else {
            printf("Operation aborted.\n\n");
        }
    }
    else {
        // If the patient record does not exist, display an error message
        printf("\nERROR: Patient record not found!\n\n");
        
    }
    

}


// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* data)
{
    // Display table header for all appointments
    displayScheduleTableHeader(&data->appointments->date, FMT_ALL_RECORDS); // Passing NULL to indicate all records

    // Sort appointments by date
    bubbleSort(data->appointments, APPOINTMENTS_CAP);

    // Iterate through all appointments
    for (int i = 0; i < APPOINTMENTS_CAP; i++)
    {
        // Check if the appointment date is valid (not empty)
        if (data->appointments[i].date.year != 0)
        {
            // Find the patient associated with the current appointment
            int patientIndex = -1;
            for (int j = 0; j < PETS_CAP; j++)
            {
                if (data->patients[j].patientNumber == data->appointments[i].patientNumber)
                {
                    patientIndex = j;
                    break; // Found the patient, no need to continue searching
                }
            }

            // If patient is found, display the appointment data
            if (patientIndex != -1)
            {
                displayScheduleData(&data->patients[patientIndex], &data->appointments[i], FMT_ALL_RECORDS); // Passing 1 to include the date field
            }
        }
    }
    printf("\n");
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data)
{
    struct Date Date;

    // Input the date for which to view the appointment schedule
    InputDate(&Date);

    // Display table header for the specific appointment schedule
    displayScheduleTableHeader(&Date, FMT_DATE_SPECIFIC);

    // Sort appointments by date
    bubbleSort(data->appointments, APPOINTMENTS_CAP);

    // Iterate through all appointments
    for (int i = 0; i < APPOINTMENTS_CAP; i++)
    {
        // Check if the appointment date matches the input date
        if (Date.year == data->appointments[i].date.year &&
            Date.month == data->appointments[i].date.month &&
            Date.day == data->appointments[i].date.day)
        {
            // Find the patient associated with the current appointment
            int patientIndex = -1; // Initialize to -1 (not found)
            for (int j = 0; j < PETS_CAP; j++)
            {
                if (data->patients[j].patientNumber == data->appointments[i].patientNumber)
                {
                    patientIndex = j; // Store the index of the patient
                    break; // Exit the loop once found
                }
            }

            // Check if the patient is found
            if (patientIndex != -1)
            {
                // Display the appointment data for the specific date
                displayScheduleData(&data->patients[patientIndex], &data->appointments[i], FMT_DATE_SPECIFIC);
            }
        }
    }

    printf("\n");
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatients)
{
    struct Date Date;
    struct Time Time;
    int patientIndex = -1;
    int vacantSlotIndex = -1;
    int index = 0;
    int scheduled = 0;

    // Get the patient's index
    apt = 1;
    index=searchPatientByPatientNumber(patients, maxPatients);

    // If the patient exists, proceed to schedule the appointment
    if (index != -1)
    {
        do {
            // Input the date and time for the appointment
            InputDate(&Date);
            InputTime(&Time);

            // Check appointment availability
            int slotAvailable = 1;
            for (int i = 0; i < maxAppointments; i++)
            {
                if (appointments[i].date.year == Date.year &&
                    appointments[i].date.month == Date.month &&
                    appointments[i].date.day == Date.day &&
                    appointments[i].time.hour == Time.hour &&
                    appointments[i].time.min == Time.min)
                {
                    // Appointment slot is not available
                    slotAvailable = 0;
                    break;
                }
            }

            // If the appointment slot is available, find a vacant slot
            if (slotAvailable)
            {
                for (int j = 0; j < maxAppointments; j++)
                {
                    if (appointments[j].date.year == 0)
                    {
                        // Found a vacant slot
                        vacantSlotIndex = j;
                        break;
                    }
                }

                // If a vacant slot is found, schedule the appointment
                if (vacantSlotIndex != -1)
                {
                    // Set the patient's index
                    patientIndex = index;

                    // Assign appointment details
                    appointments[vacantSlotIndex].date = Date;
                    appointments[vacantSlotIndex].time = Time;
                    appointments[vacantSlotIndex].patientNumber = patients[patientIndex].patientNumber;

                    // Appointment scheduled successfully
                    printf("\n*** Appointment scheduled! ***\n\n");
                    scheduled = 1;
                    
                }
                else
                {
                    // No vacant slot available
                    printf("\nERROR: Appointment listing is FULL!\n");
                }
            }
            else
            {
                // Appointment slot is not available
                printf("\nERROR: Appointment timeslot is not available!\n\n");

            }
        } while (scheduled!=1);
    }
    apt = 0;
   
}


// Remove an appointment record from the appointment array

void removeAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatients)
{
    apt = 2;
    int patientIndex = searchPatientByPatientNumber(patients, maxPatients);
  

    if (patientIndex != -1)
    {
        struct Date Date;
        InputDate(&Date);
        printf("\n");

        int found = 0;
        int appointmentIndex = -1;

        for (int i = 0; i < maxAppointments; i++)
        {
            if (appointments[i].patientNumber == patients[patientIndex].patientNumber &&
                appointments[i].date.year == Date.year &&
                appointments[i].date.month == Date.month &&
                appointments[i].date.day == Date.day)
            {
                found = 1;
                appointmentIndex = i;
                break;
            }
        }

        if (found)
        {
            displayPatientData(&patients[patientIndex], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y/n): ");
            int selection = inputCharOption("yn");
            if (selection == 'y')
            {
                appointments[appointmentIndex].patientNumber = 0;
                appointments[appointmentIndex].date = (struct Date){ 0 };
                appointments[appointmentIndex].time = (struct Time){ 0 };

                printf("\nAppointment record has been removed!\n\n");
            }
            else
            {
                printf("\nOperation aborted.\n\n");
            }
        }
        
    }
    apt = 0;
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
int searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int patientNumber;
    if (apt == 0) {
        printf("Search by patient number: ");
    }
    else {
        printf("Patient Number: ");
        
    }
    patientNumber = inputIntPositive();

    // Find the index of the patient record by patient number
    int index = findPatientIndexByPatientNum(patientNumber, patient, max);

    // If the patient record exists, display the record in "form" format
    if (index != -1 && apt ==0) {
        printf("\n");
        
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
        return index;
        
    }
    else if (apt==0) {
        // If the patient record does not exist, display a message indicating no records found
        printf("\n*** No records found ***\n\n");
       
    }
    else if (apt==2 && index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    
   }
    return index;
    
}

void bubbleSort(struct Appointment appoints[], int max)
{
    for (int i = 0; i < max - 1; i++)
    {
        for (int j = 0; j < max - i - 1; j++)
        {
            // Compare appointment dates
            if (appoints[j].date.year > appoints[j + 1].date.year ||
                (appoints[j].date.year == appoints[j + 1].date.year &&
                    (appoints[j].date.month > appoints[j + 1].date.month ||
                        (appoints[j].date.month == appoints[j + 1].date.month &&
                            (appoints[j].date.day > appoints[j + 1].date.day ||
                                (appoints[j].date.day == appoints[j + 1].date.day &&
                                    (appoints[j].time.hour > appoints[j + 1].time.hour ||
                                        (appoints[j].time.hour == appoints[j + 1].time.hour &&
                                            appoints[j].time.min > appoints[j + 1].time.min))))))))
            {
                // Swap appointments
                struct Appointment temp = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = temp;
            }
        }
    }
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    char phoneNumber[10 + 1];
    printf("Search by phone number: ");
    inputCString(phoneNumber, PHONE_LEN, PHONE_LEN);
    printf("\n");
    
    // Flag to indicate if any records were found
    int found = 0;
    displayPatientTableHeader();
    
    // Iterate through the patient array to search for matches on the entered phone number
    for (i = 0; i < max; ++i) {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0) {
            // If a match is found, display the patient record in "tabular" format
           
            
            displayPatientData(&patient[i], FMT_TABLE);
            
            found = 1; // Set flag to indicate record found
        }
    }
    printf("\n");

    // If no records match the entered phone number, display a message indicating no records found
    if (!found) {
        printf("*** No records found ***\n\n");
    }
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max) {
    int maxPatientNumber = 0;

    // Iterate through the patient array to find the largest patient number
    for (i = 0; i < max; ++i) {
        if (patient[i].patientNumber > maxPatientNumber) {
            maxPatientNumber = patient[i].patientNumber;
        }
    }

    // Increment the largest patient number to get the next patient number
    return maxPatientNumber + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max) {
    // Iterate through the patient array
    for (i = 0; i < max; ++i) {
        // Check if the patient number matches the given patientNumber argument
        if (patient[i].patientNumber == patientNumber) {
            // Return the index position of the matched element
            return i;
        }
    }

    // If the record cannot be located, return -1
    return -1;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
// 
// Get user input for Date
void InputDate(struct Date* date) {
    do {
        printf("Year        : ");
        date->year = inputIntRange(MIN_YR, MAX_YR);

        printf("Month (%d-%d): ", MIN_MONTH, MAX_MONTH);
        date->month = inputIntRange(MIN_MONTH, MAX_MONTH);

        // Determine the maximum number of days based on the month and year
        int maxDays = 31;
        if (date->month == 2)
        {
            if (date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0))
            {
                // Leap year
                maxDays = 29;
            }
            else
            {
                maxDays = 28;
            }
        }
        else if (date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11)
        {
            maxDays = 30;
        }

        printf("Day (%d-%d)  : ", MIN_DAY, maxDays);
        date->day = inputIntRange(MIN_DAY, maxDays);

    } while (!(date->year && date->month && date->day));
}

// Get user input for Time
void InputTime(struct Time* Time) {
    int done = 0;

    do {
        printf("Hour (0-23)  : ");
        Time->hour = inputIntRange(0, 23);

        printf("Minute (0-59): ");
        Time->min = inputIntRange(0, 59);

        if (Time->hour < MIN_HR || Time->hour > MAX_HR ||
            (Time->min % MIN_INTERVAL_MAX != 0) ||
            (Time->hour == MAX_HR && Time->min == MIN_INTERVAL_MAX))
        {
            printf("ERROR: Time must be between %02d:%02d and %02d:%02d in %02d minute intervals.\n\n", MIN_HR, 0, MAX_HR, 59, MIN_INTERVAL_MAX);
        }
        else
        {
            done = 1;
        }

    } while (!done);

}

// Get user input for a new patient record
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n");
    printf("------------------\n");

    // Display patient number
    printf("Number: %05d\n", patient->patientNumber);

    // Prompt for patient name
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);

    // Input phone information
    
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone) {
    int choice;
    int isTBD = 0; // Flag to indicate if TBD option is selected
    

    // Display menu for phone description selection
    printf("Phone Information\n-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    choice = inputIntRange(1, 4);


    // Assign phone description based on user choice
    if (choice == 1) {
        strcpy(phone->description, "CELL");
    }
    else if (choice == 2) {
        strcpy(phone->description, "HOME");
    }
    else if (choice == 3) {
        strcpy(phone->description, "WORK");
    }
    else if (choice == 4) {
        strcpy(phone->description, "TBD");
        isTBD = 1; // Set flag for TBD option
    }

    // If the choice is not TBD, prompt for phone number
    if (!isTBD) {
       
        printf("\nContact: %s\n", phone->description);
        printf("Number : ");
        inputPhoneValid(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
	


    }
    else {
        // Set number to empty state for TBD
        strcpy(phone->number, "");
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)

int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* fp = fopen(datafile, "r");
    int i = 0;

    if (datafile != NULL)
    {
        for (i = 0; i < max && !feof(fp); i++)
        {
            fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number);
        }
        fclose(fp);
        fp = NULL;
    }
    else
    {
        puts("ERROR: Failed to access file!");
    }

    return i;
}




// Import appointment data from file into an Appointment array (returns # of records read)

int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    FILE* fp = fopen(datafile, "r");
    int count = 0;

    if (fp != NULL)
    {
        while (count < max && fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[count].patientNumber, &appoints[count].date.year, &appoints[count].date.month, &appoints[count].date.day, &appoints[count].time.hour, &appoints[count].time.min) == 6)
        {
            count++;
        }
        fclose(fp);
    }
    else
    {
        puts("ERROR: Failed to access file!");
    }

    return count;

}