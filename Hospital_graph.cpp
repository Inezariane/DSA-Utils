#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Hospital {
    int id;
    string name;
    string location;
    int patients;
};

struct Edge {
    int fromId;
    int toId;
    int distance;
};

vector<Hospital> hospitals;
vector<Edge> edges;
int nextHospitalId = 1;

Hospital* findHospitalById(int id) {
    for (auto& h : hospitals) {
        if (h.id == id) return &h;
    }
    return nullptr;
}

Hospital* findHospitalByName(const string& name) {
    for (auto& h : hospitals) {
        if (h.name == name) return &h;
    }
    return nullptr;
}

void saveHospitals() {
    ofstream file("hospitals.csv");
    for (auto& h : hospitals) {
        file << h.id << "," << h.name << "," << h.location << "," << h.patients << "\n";
    }
    file.close();
}

void saveEdges() {
    ofstream file("edges.csv");
    for (auto& e : edges) {
        file << e.fromId << "," << e.toId << "," << e.distance << "\n";
    }
    file.close();
}

void loadHospitals() {
    hospitals.clear();
    ifstream file("hospitals.csv");
    string line;
    int maxId = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, location, patientsStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, location, ',');
        getline(ss, patientsStr);
        int id = stoi(idStr);
        maxId = max(maxId, id);
        hospitals.push_back({id, name, location, stoi(patientsStr)});
    }
    file.close();
    nextHospitalId = maxId + 1;
}

void loadEdges() {
    edges.clear();
    ifstream file("edges.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fromStr, toStr, distanceStr;
        getline(ss, fromStr, ',');
        getline(ss, toStr, ',');
        getline(ss, distanceStr);
        edges.push_back({stoi(fromStr), stoi(toStr), stoi(distanceStr)});
    }
    file.close();
}

void viewHospitals() {
    cout << "\n Registered Hospitals:\n";
    for (auto& h : hospitals) {
        cout << h.id << ": " << h.name << " | Location: " << h.location << " | Patients: " << h.patients << "\n";
    }
}

void addHospital() {
    Hospital h;
    h.id = nextHospitalId++;
    cout << "\n Add New Hospital:\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, h.name);
    cout << "Location: ";
    getline(cin, h.location);
    cout << "Number of Patients: ";
    cin >> h.patients;
    hospitals.push_back(h);
    saveHospitals();
    cout << " Hospital added!\n";
}

void updateHospital() {
    int id;
    cout << "Enter hospital ID to update: ";
    cin >> id;
    Hospital* h = findHospitalById(id);
    if (h) {
        cout << "New Location: ";
        cin >> h->location;
        cout << "New Number of Patients: ";
        cin >> h->patients;
        saveHospitals();
        cout << " Hospital updated!\n";
    } else {
        cout << " Hospital not found.\n";
    }
}

void deleteHospital() {
    int id;
    cout << "Enter hospital ID to delete: ";
    cin >> id;
    auto it = remove_if(hospitals.begin(), hospitals.end(), [&](Hospital h) {
        return h.id == id;
    });
    if (it != hospitals.end()) {
        hospitals.erase(it, hospitals.end());
        edges.erase(remove_if(edges.begin(), edges.end(), [&](Edge e) {
            return e.fromId == id || e.toId == id;
        }), edges.end());
        saveHospitals();
        saveEdges();
        cout << " Hospital deleted!\n";
    } else {
        cout << " Hospital not found.\n";
    }
}

void linkHospitals() {
    int fromId, toId, distance;
    cout << "Link From (Hospital ID): ";
    cin >> fromId;
    cout << "Link To (Hospital ID): ";
    cin >> toId;
    if (!findHospitalById(fromId) || !findHospitalById(toId)) {
        cout << " One or both hospitals do not exist.\n";
        return;
    }
    cout << "Distance (in KM): ";
    cin >> distance;
    edges.push_back({fromId, toId, distance});
    saveEdges();
    cout << " Hospitals linked!\n";
}

void viewGraph() {
    cout << "\n Hospital Connections:\n";
    for (auto& e : edges) {
        Hospital* from = findHospitalById(e.fromId);
        Hospital* to = findHospitalById(e.toId);
        if (from && to)
            cout << from->name << " --- " << to->name << " : " << e.distance << "km\n";
    }
}

void visualizeGraph() {
    ofstream dotFile("graph.dot");
    dotFile << "graph HospitalNetwork {\n";
    dotFile << "  node [shape=circle, style=filled, color=lightblue];\n";

    for (const auto& e : edges) {
        Hospital* from = findHospitalById(e.fromId);
        Hospital* to = findHospitalById(e.toId);
        if (from && to)
            dotFile << "  \"" << from->name << "\" -- \"" << to->name << "\" [label=\"" << e.distance << "km\"];\n";
    }

    dotFile << "}\n";
    dotFile.close();

    int result = system("dot -Tpng graph.dot -o graph.png");
    if (result != 0) {
        cout << " Error: Graphviz 'dot' command not found. Make sure Graphviz is installed and 'dot' is in your PATH.\n";
        return;
    }

    cout << " Graph image 'graph.png' created!\n";

    #ifdef _WIN32
        system("start graph.png");
    #elif __APPLE__
        system("open graph.png");
    #else
        system("xdg-open graph.png");
    #endif
}

int main() {
    loadHospitals();
    loadEdges();

    int choice;
    do {
        cout << "\n Hospital Management Menu:\n";
        cout << "1. View Hospitals\n";
        cout << "2. Add Hospital\n";
        cout << "3. Update Hospital\n";
        cout << "4. Delete Hospital\n";
        cout << "5. Link Hospitals\n";
        cout << "6. View Hospital Graph (edges)\n";
        cout << "7. Visualize Hospital Graph (PNG)\n";
        cout << "8. Exit\n";
        cout << "Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewHospitals(); break;
            case 2: addHospital(); break;
            case 3: updateHospital(); break;
            case 4: deleteHospital(); break;
            case 5: linkHospitals(); break;
            case 6: viewGraph(); break;
            case 7: visualizeGraph(); break;
            case 8: cout << "Thank you for using our system.\n"; break;
            default: cout << " Invalid choice!\n"; break;
        }
    } while (choice != 8);

    return 0;
}
