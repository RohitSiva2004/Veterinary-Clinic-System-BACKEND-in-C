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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.
#ifndef CLINIC_H
#define CLINIC_H


//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

// Display formatting options (Provided to student)
// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10

// MS#3 Additional macro's:
// ToDo:
//cap on pets and appointments in system
#define PETS_CAP 20
#define APPOINTMENTS_CAP 20
//DATE CONSTRAINTS
#define MAX_YR 2027
#define MIN_YR 2024
#define MIN_DAY 1
//dont add max yr because leap years are taken into account(2024) and months have diff amt of days
#define MIN_MONTH 1
#define MAX_MONTH 12
//TIME CONSTRAINTS
#define MIN_HR 10
#define MAX_HR 14
#define MIN_INTERVAL_MIN 0
#define MIN_INTERVAL_MAX 30
//FMT all records or date specific
#define FMT_ALL_RECORDS 1
#define FMT_DATE_SPECIFIC 0




//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: Phone
// ToDo:
struct Phone {
    char description[PHONE_DESC_LEN + 1]; // C string for phone description
    char number[PHONE_LEN + 1]; // C string for phone number
};


// Data type: Patient 
// ToDo:
struct Patient {
    int patientNumber; // Unique patient number
    char name[NAME_LEN + 1]; // C string for patient's name
    struct Phone phone; // Phone type member for contact information
};

// ------------------- MS#3 -------------------

// Data type: Time
// ToDo:
struct Time {
    int hour;
    int min;
};

// Data type: Date
// ToDo:
struct Date {
    int year;
    int month;
    int day;
};

// Data type: Appointment
// ToDo:
struct Appointment {
    int patientNumber;
    struct Time time;
    struct Date date;
};

// ClinicData type: Provided to student
// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField);

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData* data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(const struct ClinicData* data);

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(const struct ClinicData* data);

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatient);

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatient);


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

//bubbleSort Date by order
void bubbleSort(struct Appointment appoints[], int max);

// Search and display patient record by patient number (form)
int searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone);

// Get user input for Date
void InputDate(struct Date* dt);

// Get user input for Time
void InputTime(struct Time* tm);

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max);

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max);


#endif // !CLINIC_H