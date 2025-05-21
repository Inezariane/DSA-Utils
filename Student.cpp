#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

Student students[100];
int total = 0;

void addStudent() {
    cout << "Enter Roll Number: ";
    cin >> students[total].rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, students[total].name);
    cout << "Enter Marks: ";
    cin >> students[total].marks;
    total++;
}

void displayStudents() {
    for (int i = 0; i < total; i++) {
        cout << "Roll No: " << students[i].rollNo
             << ", Name: " << students[i].name
             << ", Marks: " << students[i].marks << endl;
    }
}

void searchStudent(int rollNo) {
    for (int i = 0; i < total; i++) {
        if (students[i].rollNo == rollNo) {
            cout << "Found: " << students[i].name << ", Marks: " << students[i].marks << endl;
            return;
        }
    }
    cout << "Student not found!\n";
}

void updateMarks(int rollNo) {
    for (int i = 0; i < total; i++) {
        if (students[i].rollNo == rollNo) {
            cout << "Enter new marks: ";
            cin >> students[i].marks;
            cout << "Marks updated!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void deleteStudent(int rollNo) {
    for (int i = 0; i < total; i++) {
        if (students[i].rollNo == rollNo) {
            for (int j = i; j < total - 1; j++) {
                students[j] = students[j + 1];
            }
            total--;
            cout << "Student deleted!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

int main() {
    int choice, rollNo;
    while (true) {
        cout << "\n1. Add Student\n2. Display Students\n3. Search Student\n4. Update Marks\n5. Delete Student\n6. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: cout << "Enter Roll Number: "; cin >> rollNo; searchStudent(rollNo); break;
            case 4: cout << "Enter Roll Number: "; cin >> rollNo; updateMarks(rollNo); break;
            case 5: cout << "Enter Roll Number: "; cin >> rollNo; deleteStudent(rollNo); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
