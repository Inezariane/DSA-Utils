#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
};

Book library[100];
int count = 0;

void addBook() {
    cout << "Enter Book ID: ";
    cin >> library[count].id;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, library[count].title);
    cout << "Enter Book Author: ";
    getline(cin, library[count].author);
    count++;
}

void displayBooks() {
    for (int i = 0; i < count; i++) {
        cout << "ID: " << library[i].id << ", Title: " << library[i].title << ", Author: " << library[i].author << endl;
    }
}

void searchBook(int id) {
    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            cout << "Found: " << library[i].title << " by " << library[i].author << endl;
            return;
        }
    }
    cout << "Book not found!\n";
}

void deleteBook(int id) {
    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                library[j] = library[j + 1];
            }
            count--;
            cout << "Book deleted!\n";
            return;
        }
    }
    cout << "Book not found!\n";
}

int main() {
    int choice, id;
    while (true) {
        cout << "\n1. Add Book\n2. Display Books\n3. Search Book\n4. Delete Book\n5. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: cout << "Enter ID: "; cin >> id; searchBook(id); break;
            case 4: cout << "Enter ID: "; cin >> id; deleteBook(id); break;
            case 5: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
