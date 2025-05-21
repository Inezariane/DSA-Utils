#include <iostream>
#include <string>
using namespace std;

struct Account {
    int accNo;
    string name;
    float balance;
};

Account accounts[100];
int totalAccs = 0;

void createAccount() {
    cout << "Enter Account Number: ";
    cin >> accounts[totalAccs].accNo;
    cin.ignore();
    cout << "Enter your Name: ";
    getline(cin, accounts[totalAccs].name);
    cout << "Enter Initial Balance: ";
    cin >> accounts[totalAccs].balance;
    totalAccs++;
    cout << "Account created successfully!\n";
}

void displayAccounts() {
    for (int i = 0; i < totalAccs; i++) {
        cout << "Acc No: " << accounts[i].accNo
             << ", Name: " << accounts[i].name
             << ", Balance: " << accounts[i].balance << endl;
    }
}

int findAccount(int accNo) {
    for (int i = 0; i < totalAccs; i++) {
        if (accounts[i].accNo == accNo)
            return i;
    }
    return -1;
}

void deposit(int accNo) {
    int index = findAccount(accNo);
    if (index != -1) {
        float amt;
        cout << "Enter amount to deposit: ";
        cin >> amt;
        accounts[index].balance += amt;
        cout << "Deposited! New Balance: " << accounts[index].balance << endl;
    } else {
        cout << "Account not found!\n";
    }
}

void withdraw(int accNo) {
    int index = findAccount(accNo);
    if (index != -1) {
        float amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;
        if (accounts[index].balance >= amt) {
            accounts[index].balance -= amt;
            cout << "Withdrawn! New Balance: " << accounts[index].balance << endl;
        } else {
            cout << "Insufficient balance!\n";
        }
    } else {
        cout << "Account not found!\n";
    }
}

void showBalance(int accNo) {
    int index = findAccount(accNo);
    if (index != -1) {
        cout << "Current Balance: " << accounts[index].balance << endl;
    } else {
        cout << "Account not found!\n";
    }
}

int main() {
    int choice, accNo;
    while (true) {
        cout << "\n1. Create Account\n2. Display All Accounts\n3. Deposit\n4. Withdraw\n5. Show Balance\n6. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: cout << "Enter Account Number: "; cin >> accNo; deposit(accNo); break;
            case 4: cout << "Enter Account Number: "; cin >> accNo; withdraw(accNo); break;
            case 5: cout << "Enter Account Number: "; cin >> accNo; showBalance(accNo); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
