// Patient.h
// Name: Isaac Husaiin
// Date: November 14, 2023
// Purpose: This program simulates a hospital triage system where patients
//          are prioritized based on their medical needs. It uses a
//          PatientPriorityQueue to manage the patients' priority order.

#ifndef P3_FILES_PATIENT_H
#define P3_FILES_PATIENT_H


#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Patient {
private:
    string name;
    string priorityCode;
    int arrivalOrder;
    int getPriorityRank(const string& priority) const;

public:
    // Constructor
    Patient(const string &name);

    // Getter for patient name
    string getName() const;

    // Overloaded operator < for comparing patients
    bool operator<(const Patient &other) const;

    // Overloaded operator > for comparing patients
    bool operator>(const Patient &other) const;

    // Overloaded operator == for comparing patients
    bool operator==(const Patient &other) const;

    // Convert the patient object to a string representation
    string to_string() const;

    void setPriorityCode (const string& Code);
    string getPriorityCode();
    void setArrivalOrder (const int& order);
    int getArrivalOrder();
};




// Constructor
Patient::Patient(const string &n) {
    name = n;

}

// Getter for patient name
string Patient::getName() const {
    return name;
}



// Overloaded operator < for comparing patients
// Overload the < operator implementation
bool Patient::operator<(const Patient& other) const {
    int thisPriority = getPriorityRank(priorityCode);
    int otherPriority = getPriorityRank(other.priorityCode);

    if (thisPriority == otherPriority) {
        return arrivalOrder > other.arrivalOrder;
    }
    return thisPriority < otherPriority;
}



bool Patient::operator>(const Patient& other) const {
    int thisPriority = getPriorityRank(priorityCode);
    int otherPriority = getPriorityRank(other.priorityCode);

    if (thisPriority == otherPriority) {
        return arrivalOrder < other.arrivalOrder;
    }
    return thisPriority > otherPriority;
}
// Private helper function to convert priorityCode to rank.
int Patient::getPriorityRank(const string& priority) const {
    if (priority == "immediate") return 4;
    if (priority == "emergency") return 3;
    if (priority == "urgent") return 2;
    if (priority == "routine") return 1;
    return 0; // Default rank if unknown priority
}



// Overloaded operator == for comparing patients
bool Patient::operator==(const Patient &other) const {
    // Compare based on both name and priority code
    return (name == other.name && priorityCode == other.priorityCode);
}

// Convert the patient object to a string representation
string Patient::to_string() const {
    stringstream ss;
    ss << left << setw(14) << setfill(' ') <<arrivalOrder
       << setw(15) << setfill(' ') << priorityCode
       << setw(20) << setfill(' ') <<name;
    return ss.str();
}


// Setter for priorityCode
// Sets the priority code for the patient
void Patient:: setPriorityCode (const string& Code )
{
    priorityCode = Code;
}

// Setter for arrivalOrder
// Sets the arrival order for the patient
void Patient::setArrivalOrder(const int& order) {
    arrivalOrder = order;
}

// Getter for priorityCode
// Returns the priority code of the patient
string Patient::getPriorityCode() {
    return priorityCode;
}

// Getter for arrivalOrder
// Returns the arrival order of the patient
int Patient::getArrivalOrder() {
    return arrivalOrder;
}

#endif //P3_FILES_PATIENT_H