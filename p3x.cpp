// p3x.cpp
// Name: Isaac Husaiin
// Date: November 14, 2023
// Purpose: This program simulates a hospital triage system where patients
//          are prioritized based on their medical needs. It uses a
//          PatientPriorityQueuex to manage the patients' priority order.

#include "PatientPriorityQueuex.h"
#include "Patient.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Function declarations
void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueuex &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueuex &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueuex &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueuex &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueuex &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueuex &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.

void execSaveCmd(string, PatientPriorityQueuex &);

int main() {
    // declare variables
    string line;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueuex priQueue;
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}

void changePatientCmd(string line, PatientPriorityQueuex &priQueue) {
    int arrivalID;
    string newPriority;

    string id = delimitBySpace(line);
    stringstream(id) >> arrivalID;

    if (id.empty() || arrivalID <= 0) {
        cout << "Error: No patient id provided\n";
        return;
    }

    newPriority = delimitBySpace(line);

    if (newPriority != "immediate" && newPriority != "minimal" &&
        newPriority != "urgent" && newPriority != "emergency") {
        cout << "No priority code given.\n";
        return;
    }

    try {
        string name = priQueue.changePriority(arrivalID, newPriority);
        cout << "Changed patient \"" << name << "\" 's priority to "
             << newPriority << endl;
    } catch (const exception &e) {
        cout << "Error: " << e.what() << ". Try again.\n";
    }
}

bool processLine(string line, PatientPriorityQueuex &priQueue) {
    string cmd = delimitBySpace(line);
    if (cmd.empty()) {
        cout << "Error: no command given." << endl;
        return true;
    }

    if (cmd == "help") {
        help();
    } else if (cmd == "add") {
        addPatientCmd(line, priQueue);
    } else if (cmd == "peek") {
        peekNextCmd(priQueue);
    } else if (cmd == "next") {
        removePatientCmd(priQueue);
    } else if (cmd == "list") {
        showPatientListCmd(priQueue);
    } else if (cmd == "load") {
        execCommandsFromFileCmd(line, priQueue);
    } else if (cmd == "quit") {
        return false;
    } else if (cmd == "change") {
        changePatientCmd(line, priQueue);
    } else if (cmd == "save") {
        execSaveCmd(line, priQueue);
    } else {
        cout << "Error: unrecognized command: " << cmd << endl;
    }

    return true;
}

void addPatientCmd(string line, PatientPriorityQueuex &priQueue) {
    string priority, name;

    // get priority and name
    priority = delimitBySpace(line);
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }
    name = line;
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    // Create a Patient object and add it to the priority queue
    Patient patient(name);
    priQueue.add(patient, priority);

    // Print a message to indicate that the patient has been added
    cout << "Added patient \"" << name << "\" to the priority system\n";
}

void peekNextCmd(PatientPriorityQueuex &priQueue) {

    if (priQueue.size() == 0) {
        cout << "There are no patients in the waiting area.\n";
        return;
    }

    // Get the next patient (highest priority) without removing them
    Patient nextPatient = priQueue.peek();

    // Print the next patient's information
    cout << "Highest priority patient to be called next: "
         << nextPatient.getName() << endl;
}

void removePatientCmd(PatientPriorityQueuex &priQueue) {

    if (priQueue.size() == 0) {
        cout << "There are no patients in the waiting area.\n";
        return;
    }

    // Remove and get the next patient (highest priority)
    Patient nextPatient = priQueue.remove();

    // Print the next patient's information
    cout << "This patient will now be seen: " << nextPatient.getName() << endl;
}

void showPatientListCmd(PatientPriorityQueuex &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+";
    // Iterate through the priority queue and print patient details
    string patientList = priQueue.to_string();
    cout << patientList;
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueuex &priQueue) {
    ifstream infile;
    string line;

    // open and read from file
    infile.open(filename);
    if (infile) {
        while (getline(infile, line)) {
            cout << "\ntriage> " << line;
            // process file input
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

string delimitBySpace(string &s) {
    unsigned pos = 0;
    char delimiter = ' ';
    string result = "";

    pos = s.find(delimiter);
    if (pos != string::npos) {
        result = s.substr(0, pos);
        s.erase(0, pos + 1);
    }
    return result;
}

void welcome() {
    cout << " Welcome to the hospital triage system. " << endl;
}

void goodbye() {
    cout << "Thank you for using hospital triage System" << endl;
    cout << "Bye!" << endl;
}

void help() {
    cout << "add <priority-code> <patient-name>\n"
         << "   Adds the patient to the triage system.\n"
         << "   <priority-code> must be one of the 4 accepted priority codes:\n"
         << "   1. immediate 2. emergency 3. urgent 4. minimal\n"
         << "  <patient-name>: patient's full legal name (may contain spaces)\n"
         << "next:      Announces the patient to be seen next.\n"
            "           Takes into account the type of emergency and the\n"
            "           patient's arrival order.\n"
         << "peek:      Displays the patient that is next in line, \n"
            "           but keeps in queue\n"
         << "list:      Displays the list of all patients that are still\n"
            "           waiting in the order that they have arrived.\n"
         << "load:      Reads the file and executes the command on each line\n"
         << "help:      Displays this menu\n"
         << "quit:      Exits the program\n";
}

void execSaveCmd(string line, PatientPriorityQueuex &pq) {
    string fileName = delimitBySpace(line);
    pq.saveToFile(fileName);
    cout << "" << endl;
}
