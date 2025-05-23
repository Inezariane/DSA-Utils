#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct Hospital {
    string name;
    string location;
    int patients;
};

struct Edge {
    string from;
    string to;
    int distance;
};

vector<Hospital> hospitals;
vector<Edge> edges;

void saveHospitals() {
    ofstream file("hospitals.csv");
    for (auto& h : hospitals) {
        file << h.name << "," << h.location << "," << h.patients << "\n";
    }
    file.close();
}

void saveEdges() {
    ofstream file("edges.csv");
    for (auto& e : edges) {
        file << e.from << "," << e.to << "," << e.distance << "\n";
    }
    file.close();
}

void loadHospitals() {
    hospitals.clear();
    ifstream file("hospitals.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, location, patientsStr;
        getline(ss, name, ',');
        getline(ss, location, ',');
        getline(ss, patientsStr);
        hospitals.push_back({name, location, stoi(patientsStr)});
    }
    file.close();
}

void loadEdges() {
    edges.clear();
    ifstream file("edges.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string from, to, distanceStr;
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, distanceStr);
        edges.push_back({from, to, stoi(distanceStr)});
    }
    file.close();
}

void viewHospitals() {
    cout << "\n🩺 Registered Hospitals:\n";
    for (auto& h : hospitals) {
        cout << "- " << h.name << " | Location: " << h.location << " | Patients: " << h.patients << "\n";
    }
}

void addHospital() {
    Hospital h;
    cout << "\n Add New Hospital:\n";
    cout << "Name: ";
    cin >> h.name;
    cout << "Location: ";
    cin >> h.location;
    cout << "Number of Patients: ";
    cin >> h.patients;
    hospitals.push_back(h);
    saveHospitals();
    cout << " Hospital added!\n";
}

void updateHospital() {
    string name;
    cout << "Enter hospital name to update: ";
    cin >> name;
    for (auto& h : hospitals) {
        if (h.name == name) {
            cout << "New Location: ";
            cin >> h.location;
            cout << "New Number of Patients: ";
            cin >> h.patients;
            saveHospitals();
            cout << " Hospital updated!\n";
            return;
        }
    }
    cout << " Hospital not found.\n";
}

void deleteHospital() {
    string name;
    cout << "Enter hospital name to delete: ";
    cin >> name;
    auto it = remove_if(hospitals.begin(), hospitals.end(), [&](Hospital h) {
        return h.name == name;
    });
    if (it != hospitals.end()) {
        hospitals.erase(it, hospitals.end());
        saveHospitals();
        cout << " Hospital deleted!\n";
    } else {
        cout << " Hospital not found.\n";
    }
}

void linkHospitals() {
    string from, to;
    int distance;
    cout << "Link From (Hospital Name): ";
    cin >> from;
    cout << "Link To (Hospital Name): ";
    cin >> to;
    cout << "Distance (in KM): ";
    cin >> distance;
    edges.push_back({from, to, distance});
    saveEdges();
    cout << " Hospitals linked!\n";
}

void viewGraph() {
    cout << "\n Hospital Connections:\n";
    for (auto& e : edges) {
        cout << e.from << " --- " << e.to << " : " << e.distance << "km\n";
    }
}

void visualizeGraph(const vector<Edge>& edges) {
    ofstream dotFile("graph.dot");
    dotFile << "graph HospitalNetwork {\n";
    dotFile << "  node [shape=circle, style=filled, color=lightblue];\n";

    for (const auto& e : edges) {
        dotFile << "  \"" << e.from << "\" -- \"" << e.to << "\" [label=\"" << e.distance << "km\"];\n";
    }

    dotFile << "}\n";
    dotFile.close();

    system("dot -Tpng graph.dot -o graph.png");

    cout << "📸 Graph image 'graph.png' created!\n";

    // Auto open depending on OS
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
            case 7: visualizeGraph(edges); break;
            case 8: cout << "Thank you for using our system.\n"; break;
            default: cout << " Invalid choice!\n"; break;
        }
    } while (choice != 8);

    return 0;
}
