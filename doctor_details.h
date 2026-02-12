#pragma once
#include <string>
#include <iostream>
using namespace std;

class Doctor {
    int DoctID;
    string DocName;
    string Specialization;
    bool IsAvailable;

public:
    Doctor() : DoctID(-999), DocName("N/A"), Specialization("N/A"), IsAvailable(false) {}
    Doctor(int id, string name, string specs, bool avail) {
        DoctID = id;
        DocName = name;
        Specialization = specs;
        IsAvailable = avail;
    }

    int getDocID() const { return DoctID; }
    string getDocName() const { return DocName; }
    string getDocSpecialization() const { return Specialization; }
    bool getAvailability() const { return IsAvailable; }

    void setDocID(int ID) { DoctID = ID; }
    void setDocName(string name) { DocName = name; }
    void setDocSpecialization(string specs) { Specialization = specs; }
    void setAvailability(bool availability) { IsAvailable = availability; }
};

struct DocNode {
    Doctor D1;
    DocNode* next;
   
    DocNode(int ID, string name, string specs, bool availability) {
        D1.setDocID(ID);
        D1.setDocName(name);
        D1.setDocSpecialization(specs);
        D1.setAvailability(availability);
        next = nullptr;
    }
};

class DocLinkedList {
    DocNode* head;
    DocNode* tail;
public:
    DocLinkedList() { head = tail = nullptr; }

    DocNode* getHead() { return head; }
    
    void insertDoctor(int ID, string name, string specs, bool availability) {
        DocNode* newNode = new DocNode(ID, name, specs, availability);
        if (head == nullptr) {
            head = tail = newNode;
            cout << "New doctor inserted" << endl;
            return;
        }
        tail->next = newNode;
        tail = newNode;
        cout << "New doctor inserted" << endl;
    }

    //linear search for doctor
    DocNode* searchDoctor(int id) {
        DocNode* curr = head;
        while (curr != nullptr) {
            if (curr->D1.getDocID() == id) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    bool deleteDoctor(int ID) {
        if (head == nullptr) return false;

        DocNode* temp = head;
        DocNode* prev = nullptr;

        // Case 1: Head is the node to delete
        if (temp->D1.getDocID() == ID) {
            head = head->next;
            if (head == nullptr) tail = nullptr;
            delete temp;
            cout << "Doctor with ID: " << ID << " has been deleted" << endl;
            return true;
        }

        //Case2; traverse to find node
        prev = temp;
        temp = temp->next;

        while (temp != nullptr) {
            if (temp->D1.getDocID() == ID) {
                prev->next = temp->next;
                if (temp == tail) tail = prev;
                delete temp;
                cout << "Doctor with ID: " << ID << " has been deleted" << endl;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    void viewDoctor(int ID) const {
        DocNode* temp = head;
        while (temp != nullptr) {
            if (temp->D1.getDocID() == ID) {
                cout << "Doctor's ID: " << ID << endl;
                cout << "Doctor's Name: " << temp->D1.getDocName() << endl;
                cout << "Doctor's Specialization: " << temp->D1.getDocSpecialization() << endl;
                cout << "Doctor's Availability: " << (temp->D1.getAvailability() ? "Yes" : "No") << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "No such Doctor exists" << endl;
    }

    void updateDoctor(int ID, string name, string specs, bool availability) {
        DocNode* temp = head;
        while (temp != nullptr) {
            if (temp->D1.getDocID() == ID) {
                temp->D1.setDocName(name);
                temp->D1.setDocSpecialization(specs);
                temp->D1.setAvailability(availability);
                cout << "Doctor's details updated!" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "No such Doctor exists" << endl;
    }
};
