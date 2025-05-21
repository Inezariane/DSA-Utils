#include <iostream>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string disease;
};

Patient patients[100];
int count = 0;

void addPatient() {
    cout << "Enter Patient ID: ";
    cin >> patients[count].id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, patients[count].name);
    cout << "Enter Age: ";
    cin >> patients[count].age;
    cin.ignore();
    cout << "Enter Disease: ";
    getline(cin, patients[count].disease);
    count++;
    cout << "Patient added successfully!\n";
}

void viewPatients() {
    if (count == 0) {
        cout << "No records available!\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        cout << "\nID: " << patients[i].id
             << "\nName: " << patients[i].name
             << "\nAge: " << patients[i].age
             << "\nDisease: " << patients[i].disease << endl;
    }
}

void searchPatient() {
    int searchID;
    cout << "Enter Patient ID to search: ";
    cin >> searchID;
    for (int i = 0; i < count; i++) {
        if (patients[i].id == searchID) {
            cout << "\nFound!\n";
            cout << "Name: " << patients[i].name << "\nAge: " << patients[i].age
                 << "\nDisease: " << patients[i].disease << endl;
            return;
        }
    }
    cout << "Patient not found!\n";
}

void deletePatient() {
    int deleteID;
    cout << "Enter Patient ID to delete: ";
    cin >> deleteID;
    for (int i = 0; i < count; i++) {
        if (patients[i].id == deleteID) {
            for (int j = i; j < count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            count--;
            cout << "Record deleted successfully!\n";
            return;
        }
    }
    cout << "Patient not found!\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- HOSPITAL MANAGEMENT SYSTEM ---\n";
        cout << "1. Add Patient\n2. View All Patients\n3. Search Patient\n4. Delete Patient\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
