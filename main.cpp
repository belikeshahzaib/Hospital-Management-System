#include <iostream>
#include <string>
#include <limits>
#include "hospital_management.h"

using namespace std;

//helper to clean buffer
void flushInput() {
    if (cin.peek() == '\n') cin.get();
}

int main() {
    RecordManager rm;
    rm.loadallData();
    cout << "Loaded saved data.\n";

    bool running = true;
    while (running) {
        cout << "\n========== Hospital Management ==========\n";
        cout << "1) Doctor menu\n2) Patient menu\n3) Appointments menu\n4) Save data\n0) Exit\nOption: ";

        int mainChoice;
        if (!(cin >> mainChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (mainChoice) {
            case 1: { //doctor
                int opt = -1;
                while (opt != 0) {
                    cout << "\n[1] Add [2] View [3] Update [4] Delete [0] Back: ";
                    cin >> opt;
                    if (opt == 1) {
                        flushInput();
                        string name, spec;
                        int avail;
                        cout << "Name: "; getline(cin, name);
                        cout << "Spec: "; getline(cin, spec);
                        cout << "Avail (1/0): "; cin >> avail;
                        rm.addDoctor(name, spec, avail);
                    } else if (opt == 2) {
                        int id; 
						cout << "ID: ";
						cin >> id;
                        rm.viewDoctor(id);
                    } else if (opt == 3) {
                        int id, avail; string name, spec;
                        cout << "ID to update: "; cin >> id; flushInput();
                        cout << "New Name: "; getline(cin, name);
                        cout << "New Spec: "; getline(cin, spec);
                        cout << "New Avail: "; cin >> avail;
                        rm.updateDoctor(id, name, spec, avail);
                    } else if (opt == 4) {
                        int id; cout << "ID to delete: "; cin >> id;
                        rm.deleteDoctor(id);
                    }
                }
                break;
            }
            case 2: { //patient
                int opt = -1;
                while (opt != 0) {
                    cout << "\n[1] Add [2] View [3] Delete [0] Back: ";
                    cin >> opt;
                    if (opt == 1) {
                        flushInput();
                        string name, dis; int age;
                        cout << "Name: "; getline(cin, name);
                        cout << "Age: "; cin >> age; flushInput();
                        cout << "Disease: "; getline(cin, dis);
                        rm.addPatient(name, age, dis);
                    } else if (opt == 2) {
                        int id; cout << "ID: "; cin >> id;
                        rm.viewPatient(id);
                    } else if (opt == 3) {
                        int id; cout << "ID: "; cin >> id;
                        rm.deletePatient(id);
                    }
                }
                break;
            }
            case 3: { //appointmnts
                int opt = -1;
                while (opt != 0) {
                    cout << "\n[1] Book [2] View All [3] Process Next [0] Back: ";
                    cin >> opt;
                    if (opt == 1) {
                        int pID, dID; string date;
                        cout << "Pat ID: "; cin >> pID;
                        cout << "Doc ID: "; cin >> dID; flushInput();
                        cout << "Date: "; getline(cin, date);
                        rm.bookAppointment(pID, dID, date);
                    } else if (opt == 2) rm.viewAppointments();
                    else if (opt == 3) rm.processNextAppointment();
                }
                break;
            }
            case 4: rm.saveallData(); break;
            case 0: rm.saveallData(); running = false; break;
        }
    }
    return 0;
}
