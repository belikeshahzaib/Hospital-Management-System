#pragma once
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <queue>
#include "doctor_details.h"
#include "patient_details.h"

using namespace std;

struct Appointment{
    int doctorID;
    int patientID;
    string date;
    Appointment(int docId, int patId, const string &dt) {
        doctorID = docId;
        patientID = patId;
        date = dt;
    }
};

class RecordManager {
    DocLinkedList doctors;
    unordered_map<int, Patient> PatientTable;
    queue<Appointment> appointments;

    int nextDoctorID = 1;
    int nextPatientID = 1000;

public:
    RecordManager() {
        nextDoctorID = 1;
        nextPatientID = 1000;
    }

    void addDoctor(string name, string specs, bool avail) {
        int id = nextDoctorID++;
        doctors.insertDoctor(id, name, specs, avail);
    }
    void deleteDoctor(int id) {
        if (!doctors.deleteDoctor(id)) cout << "Doctor not found" << endl;
    }
    void updateDoctor(int id, string name, string specs, bool avail) {
        doctors.updateDoctor(id, name, specs, avail);
    }
    void viewDoctor(int id) {
        doctors.viewDoctor(id);
    }

    //Patient Functions 
    int addPatient(string name, int age, string disease) {
        int id = nextPatientID++;
        Patient P(id, name, age, disease);
        PatientTable[id] = P;
        cout << "Patient added successfully. ID No. " << id << endl;
        return id;
    }

    void viewPatient(int ID) const {
        if (PatientTable.count(ID) > 0) {
            Patient p = PatientTable.at(ID);
            cout << "Patient ID : " << p.getPatientID() << endl;
            cout << "Name       : " << p.getPatientName() << endl;
            cout << "Age        : " << p.getPatientAge() << endl;
            cout << "Disease    : " << p.getPatientDisease() << endl;
        } else {
            cout << "Patient with ID " << ID << " not found." << endl;
        }
    }

    void deletePatient(int id) {
        if (PatientTable.erase(id)) {
            cout << "Patient with ID " << id << " deleted successfully!" << endl;
        } else {
            cout << "Patient with ID " << id << " not found." << endl;
        }
    }

    //apointment functions
    void bookAppointment(int patientID, int doctorID, string date) {
        if (PatientTable.count(patientID) == 0) {
            cout << "Patient not found! " << endl;
            return;
        }
        DocNode* d = doctors.searchDoctor(doctorID);
        if (d == nullptr) {
            cout << "Doctor not found! " << endl;
            return;
        }
        if (!d->D1.getAvailability()) {
            cout << "Doctor is not available right now!" << endl;
            return;
        }
        Appointment A(doctorID, patientID, date);
        appointments.push(A);
        cout << "Appointment booked successfully!" << endl;
    }

    void viewAppointments() {
        if (appointments.empty()) {
            cout << "No pending appointments.\n";
            return;
        }
        queue<Appointment> temp = appointments;
        cout << "Appointment Queue: \n" << endl;
        while (!temp.empty()) {
            Appointment A = temp.front();
            temp.pop();
            cout << "Doctor ID: " << A.doctorID
                 << " | Patient ID: " << A.patientID
                 << " | Date: " << A.date << endl;
        }
        cout << endl;
    }

    void processNextAppointment() {
        if (appointments.empty()) {
            cout << "No appointments in queue." << endl;
            return;
        }
        Appointment A = appointments.front();
        appointments.pop();
        cout << "Processing Appointment -> Doctor: " << A.doctorID << " | Patient: " << A.patientID << endl;
    }

    void saveallData() {
        ofstream Docfile("Doctors.txt");
        if (Docfile.is_open()) {
            DocNode* temp = doctors.getHead();
            while (temp != nullptr) {
                Docfile << temp->D1.getDocID() << "," << temp->D1.getDocName() << ","
                        << temp->D1.getDocSpecialization() << "," << temp->D1.getAvailability() << "\n";
                temp = temp->next;
            }
            Docfile.close();
        }

        ofstream PatientFile("Patients.txt");
        if (PatientFile.is_open()) {
            for (auto& p : PatientTable) {
                Patient x = p.second;
                PatientFile << x.getPatientID() << "," << x.getPatientName() << ","
                            << x.getPatientAge() << "," << x.getPatientDisease() << "\n";
            }
            PatientFile.close();
        }

        ofstream IDfile("nextIDs.txt");
        if (IDfile.is_open()) {
            IDfile << nextDoctorID << "\n" << nextPatientID << "\n";
            IDfile.close();
        }

        ofstream AppFile("Appointments.txt");
        if (AppFile.is_open()) {
            queue<Appointment> tempQ = appointments;
            while (!tempQ.empty()) {
                Appointment A = tempQ.front();
                tempQ.pop();
                AppFile << A.patientID << " " << A.doctorID << " " << A.date << endl;
            }
            AppFile.close();
        }
    }

    void loadallData() {
        ifstream idFile("nextIDs.txt");
        if (idFile.is_open()) {
            idFile >> nextDoctorID >> nextPatientID;
            idFile.close();
        }

        ifstream pFile("Patients.txt");
        string line;
        while (getline(pFile, line)) {
            stringstream ss(line);
            string idStr, name, ageStr, disease;
            getline(ss, idStr, ','); getline(ss, name, ',');
            getline(ss, ageStr, ','); getline(ss, disease, ',');
            if(!idStr.empty()) PatientTable[stoi(idStr)] = Patient(stoi(idStr), name, stoi(ageStr), disease);
        }
        pFile.close();

        ifstream dFile("Doctors.txt");
        while (getline(dFile, line)) {
            stringstream ss(line);
            string idStr, name, spec, availStr;
            getline(ss, idStr, ','); getline(ss, name, ',');
            getline(ss, spec, ','); getline(ss, availStr, ',');
            if(!idStr.empty()) doctors.insertDoctor(stoi(idStr), name, spec, (stoi(availStr) != 0));
        }
        dFile.close();

        ifstream AppFile("Appointments.txt");
        if (AppFile.is_open()) {
            while (getline(AppFile, line)) {
                stringstream ss(line);
                string dID, pID, date;
                ss >> pID >> dID >> date; 
                if(!pID.empty()) appointments.push(Appointment(stoi(dID), stoi(pID), date));
            }
            AppFile.close();
        }
    }
};
