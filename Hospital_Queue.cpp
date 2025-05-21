#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Patient {
    string name;
    int age;
};

Patient queue[MAX];
int front = -1, rear = -1;

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return rear == MAX - 1;
}

void addPatient() {
    if (isFull()) {
        cout << "Queue is full! Cannot add more patients.\n";
        return;
    }
    if (isEmpty()) front = 0;

    rear++;
    cout << "Enter patient's name: ";
    cin.ignore();
    getline(cin, queue[rear].name);
    cout << "Enter age: ";
    cin >> queue[rear].age;

    cout << "Patient added to queue!\n";
}

void servePatient() {
    if (isEmpty()) {
        cout << "No patients in queue!\n";
        return;
    }
    cout << "Serving Patient: " << queue[front].name << ", Age: " << queue[front].age << endl;
    front++;

    if (front > rear) {
        front = rear = -1; // Reset queue
    }
}

void viewQueue() {
    if (isEmpty()) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << "\nCurrent Queue:\n";
    for (int i = front; i <= rear; i++) {
        cout << i - front + 1 << ". " << queue[i].name << " (Age: " << queue[i].age << ")\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Add Patient\n2. Serve Patient\n3. View Queue\n4. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addPatient(); break;
            case 2: servePatient(); break;
            case 3: viewQueue(); break;
            case 4: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
