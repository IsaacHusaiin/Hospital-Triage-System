// PatientPriorityQueuex.h
// Name: Isaac Husaiin
// Date: November 14, 2023
// Purpose: This program simulates a hospital triage system where patients
//          are prioritized based on their medical needs. It uses a
//          PatientPriorityQueuex to manage the patients' priority order.

#ifndef P3_FILES_PATIENTPRIORITYQUEUE_H
#define P3_FILES_PATIENTPRIORITYQUEUE_H

#include "Patient.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class PatientPriorityQueuex {
private:
    vector<Patient> patients;
    int nextPatientNumber;

    // Helper function to maintain heap order (upward)
    void heapifyUp(int index);

    // Helper function to maintain heap order (downward)
    void heapifyDown(int index);

public:
    // Constructor
    PatientPriorityQueuex();

    // Add the patient to the priority queue
    void add(Patient patient, string priority);

    // Peek at the highest priority patient without removing it
    Patient peek() const;

    // Remove and return the highest priority patient
    Patient remove();

    // Get the number of patients still waiting
    int size() const;

    // Convert the priority queue object to a string representation
    string to_string() const;

    // Change a patient's priority
    string changePriority(int arrivalID, const string &newPriority);

    // Save patient information to a file
    void saveToFile(const string &fileName) const;
};

// Constructor
PatientPriorityQueuex::PatientPriorityQueuex() : nextPatientNumber(1) {}

// Helper function to maintain heap order (upward)
void PatientPriorityQueuex::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (patients[index] > patients[parentIndex]) {
            swap(patients[index], patients[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

// Helper function to maintain heap order (downward)
void PatientPriorityQueuex::heapifyDown(int index) {
    size_t leftChildIndex = 2 * index + 1;
    size_t rightChildIndex = 2 * index + 2;
    size_t largestIndex = static_cast<size_t>(index);

    if (leftChildIndex < patients.size() &&
        patients[leftChildIndex] > patients[largestIndex]) {
        largestIndex = leftChildIndex;
    }
    if (rightChildIndex < patients.size() &&
        patients[rightChildIndex] > patients[largestIndex]) {
        largestIndex = rightChildIndex;
    }

    if (largestIndex != static_cast<size_t>(index)) {
        swap(patients[index], patients[largestIndex]);
        heapifyDown(static_cast<int>(largestIndex));
    }
}

// Add the patient to the priority queue
void PatientPriorityQueuex::add(Patient patient, string priority) {
    patient.setArrivalOrder(nextPatientNumber++);
    patient.setPriorityCode(priority);
    patients.push_back(patient);
    heapifyUp(patients.size() - 1);
}

// Peek at the highest priority patient without removing it
Patient PatientPriorityQueuex::peek() const {
    if (patients.empty()) {
        throw runtime_error("The queue is empty.");
    }
    return patients[0];
}

// Remove and return the highest priority patient
Patient PatientPriorityQueuex::remove() {
    if (patients.empty()) {
        throw runtime_error("The queue is empty.");
    }

    Patient highestPriority = patients[0];
    patients[0] = patients.back();
    patients.pop_back();
    heapifyDown(0);

    return highestPriority;
}

// Get the number of patients still waiting
int PatientPriorityQueuex::size() const {
    return patients.size();
}

// Convert the priority queue object to a string representation
string PatientPriorityQueuex::to_string() const {
    stringstream ss;
    ss << "\n";
    for (const Patient &patient: patients) {
        ss << patient.to_string() << "\n";
    }
    return ss.str();
}

// Change a patient's priority
string PatientPriorityQueuex::changePriority(int arrivalID,
                                             const string &newPriority) {
    int size = (int) patients.size();

    for (int i = 0; i < size; i++) {
        Patient updatedPatient = patients[i];
        if (updatedPatient.getArrivalOrder() == arrivalID) {
            updatedPatient.setPriorityCode(newPriority);
            patients[i] = updatedPatient;
            heapifyUp(i);
            heapifyDown(i);
            return updatedPatient.getName();
        }
    }

    throw runtime_error("No patient with the given ID was found");
}

// Save patient information to a file
void PatientPriorityQueuex::saveToFile(const string &fileName) const {
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        throw runtime_error("Unable to open the file for saving.");
    }

    for (Patient patient: patients) {
        outputFile << "add" << " " << patient.getPriorityCode() << " "
                   << patient.getName() << endl;
    }

    outputFile.close();
    cout << "Saved " << patients.size() << " patients to file " << fileName
         << endl;
}

#endif //P3_FILES_PATIENTPRIORITYQUEUE_H
