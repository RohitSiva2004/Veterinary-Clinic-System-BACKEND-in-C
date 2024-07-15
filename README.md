# Veterinary Clinic System

Welcome to the Veterinary Clinic System! This program manages patient and appointment records for a veterinary clinic, importing data from text files upon startup.

## Overview

The Veterinary Clinic System provides functionalities for managing both patient and appointment records through an intuitive menu-driven interface. It allows you to:

- Import patient and appointment records from text files.
- Navigate between Patient Management and Appointment Management systems.
- Perform operations such as viewing, searching, adding, editing, and removing records.

## Main Menu

Upon starting the program, you are presented with a main menu where you can choose between accessing the Patient Management System, Appointment Management System, or exiting the program:

1. **Patient Management System**
   - View all patient records imported from the text file.
   - Search for a patient by patient number or phone number.
   - Add a new patient to the records with auto-generated patient number.
   - Edit existing patient information by patient number or phone number.
   - Remove a patient from the records by patient number or phone number.

2. **Appointment Management System**
   - View all current appointments including patient details like name, number, day, time, and phone number.
   - View appointments scheduled on a specific date.
   - Add a new appointment to the records by patient number.
   - Remove an appointment from the records by patient number.

0. **Exit**
   - Exit the Veterinary Clinic System.

## Usage

### Patient Management System Options

- **1**: View all patient records.
- **2**: Search for a patient (by patient number or phone number).
- **3**: Add a new patient to the records.
- **4**: Edit an existing patient's information.
- **5**: Remove a patient from the records.
- **0**: Return to the main menu.

### Appointment Management System Options

- **1**: View all appointments.
- **2**: View appointments by date.
- **3**: Add a new appointment.
- **4**: Remove an appointment.
- **0**: Return to the main menu.

## Implementation Details

The system utilizes text files for storing and managing patient and appointment records. Upon starting the program, data is imported from these files, allowing seamless access and manipulation through menu-driven options.

### Sorting Algorithm

Appointments are sorted by date using the bubble sort algorithm, ensuring chronological display and efficient management of scheduled appointments.

## Requirements

- C++ compiler
- Text files containing patient and appointment data in specified formats

## Getting Started

1. Clone the repository.
2. Compile the source code.
3. Run the executable.
4. Follow the on-screen prompts to navigate through the menu options and manage patient and appointment records.

## Future Improvements

- Implement graphical user interface (GUI) using JavaFX or similar technology for enhanced user experience.
- Incorporate database integration for scalable and efficient data management.
- Enhance error handling and input validation to improve system robustness.

## Contributing

Contributions are welcome! Fork the repository, make your improvements, and submit a pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
