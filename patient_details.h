#pragma once
#include <string>
#include <iostream>
using namespace std; 

class Patient {
private:
    int PatientID;
    string PatName;
    int Age;
    string Disease;

public:
    Patient() : PatientID(-999), PatName("N/A"), Age(0), Disease("N/A") {}

    Patient(int id, string name, int age, string disease) {
        PatientID = id;
        PatName = name;
        Age = age;
        Disease = disease;
    }
    
    string getPatientName() const { return PatName; }
    int getPatientAge() const { return Age; }
    string getPatientDisease() const { return Disease; }
    int getPatientID() const { return PatientID; }

    void setPatientID(int newID) { PatientID = newID; }
    void setPatientName(string name) { PatName = name; }
    void setPatientAge(int age) { Age = age; }
    void setPatientDisease(string disease) { Disease = disease; }
};
