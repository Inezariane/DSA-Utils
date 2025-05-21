#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

// Struct to store item info
struct Item {
    string id, name, regDate;
    int quantity;
};

// Convert string to lowercase
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Add item to CSV
void addItem(const string& id, const string& name, int quantity, const string& regDate) {
    ofstream file("inventory.csv", ios::app);
    if (file.is_open()) {
        file << id << "," << name << "," << quantity << "," << regDate << "\n";
        file.close();
        cout << " Item added successfully!\n";
    } else {
        cout << "Failed to open inventory file.\n";
    }
}

//  List all items in alphabetical order
void listItems() {
    ifstream file("inventory.csv");
    string line;
    vector<Item> items;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, quantityStr, regDate;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, quantityStr, ',');
        getline(ss, regDate, ',');

        items.push_back({id, name, regDate, stoi(quantityStr)});
    }
    file.close();

    // Sort by item name
    sort(items.begin(), items.end(), [](Item a, Item b) {
        return toLower(a.name) < toLower(b.name);
    });

    // Display items
    cout << " Items in inventory:\n";
    for (auto& item : items) {
        cout << "ID: " << item.id << ", Name: " << item.name
             << ", Quantity: " << item.quantity << ", Date: " << item.regDate << "\n";
    }
    if (items.empty()) {
        cout << " No items in inventory.\n";
    }
}

//  Help info
void showHelp() {
    cout << "\n Commands:\n";
    cout << "  itemadd <id> <name> <quantity> <date>   : Add a new item to inventory\n";
    cout << " itemslist                              : List all items in stock (alphabetically)\n";
    cout << " help                                   : Show help info\n";
    cout << "  exit                                   : Exit the program\n\n";
}

//  Main loop
int main() {
    string commandLine;
    cout << " Welcome to Inventory Manager! Type 'help' for commands.\n";

    while (true) {
        cout << "\n> ";
        getline(cin, commandLine);
        stringstream ss(commandLine);
        string cmd;
        ss >> cmd;
        cmd = toLower(cmd);

        if (cmd == "itemadd") {
            string id, name, regDate;
            int qty;
            ss >> id >> name >> qty >> regDate;

            if (id.empty() || name.empty() || regDate.empty() || ss.fail()) {
                cout << " Usage: itemadd <id> <name> <quantity> <date>\n";
            } else {
                addItem(id, name, qty, regDate);
            }

        } else if (cmd == "itemslist") {
            listItems();

        } else if (cmd == "help") {
            showHelp();

        } else if (cmd == "exit") {
            break;

        } else {
            cout << "Unknown command! Type 'help' for a list of commands.\n";
        }
    }

    return 0;
}
