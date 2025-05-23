#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct Vehicle {
    string id;
    string plateNumber;
};

struct Parking {
    string id;
    string name;
    vector<Vehicle> vehicles;
};

struct Edge {
    string fromId;
    string toId;
};

vector<Parking> parkings;
vector<Edge> edges;

// Utility
bool parkingExists(const string& id) {
    return any_of(parkings.begin(), parkings.end(), [&](const Parking& p) { return p.id == id; });
}

Parking* getParkingById(const string& id) {
    for (auto& p : parkings) if (p.id == id) return &p;
    return nullptr;
}

// Save and Load
void saveData() {
    ofstream pf("parkings.csv"), ef("edges.csv"), vf("vehicles.csv");

    for (auto& p : parkings) {
        pf << p.id << "," << p.name << "\n";
        for (auto& v : p.vehicles) {
            vf << p.id << "," << v.id << "," << v.plateNumber << "\n";
        }
    }

    for (auto& e : edges) {
        ef << e.fromId << "," << e.toId << "\n";
    }

    pf.close(); ef.close(); vf.close();
}

void loadData() {
    parkings.clear(); edges.clear();
    ifstream pf("parkings.csv"), ef("edges.csv"), vf("vehicles.csv");
    string line;

    while (getline(pf, line)) {
        stringstream ss(line);
        string id, name;
        getline(ss, id, ','); getline(ss, name);
        parkings.push_back({id, name});
    }
    pf.close();

    while (getline(vf, line)) {
        stringstream ss(line);
        string pid, vid, plate;
        getline(ss, pid, ','); getline(ss, vid, ','); getline(ss, plate);
        if (auto* p = getParkingById(pid)) {
            p->vehicles.push_back({vid, plate});
        }
    }
    vf.close();

    while (getline(ef, line)) {
        stringstream ss(line);
        string from, to;
        getline(ss, from, ','); getline(ss, to);
        edges.push_back({from, to});
    }
    ef.close();
}

// Core Features
void addParking() {
    Parking p;
    cout << "Enter Parking ID: "; cin >> p.id;
    if (parkingExists(p.id)) { cout << "Already exists!\n"; return; }
    cout << "Enter Parking Name: "; cin >> p.name;
    parkings.push_back(p);
    saveData();
    cout << "Parking added!\n";
}

void deleteParking() {
    string id; cout << "Enter Parking ID to delete: "; cin >> id;
    auto it = remove_if(parkings.begin(), parkings.end(), [&](Parking p) { return p.id == id; });
    if (it != parkings.end()) {
        parkings.erase(it, parkings.end());
        edges.erase(remove_if(edges.begin(), edges.end(), [&](Edge e) { return e.fromId == id || e.toId == id; }), edges.end());
        saveData();
        cout << "Parking deleted.\n";
    } else cout << "Not found.\n";
}

void linkParkings() {
    string from, to;
    cout << "Link From (ID): "; cin >> from;
    cout << "Link To (ID): "; cin >> to;
    if (!parkingExists(from) || !parkingExists(to)) { cout << "One of the IDs doesn't exist.\n"; return; }
    edges.push_back({from, to});
    saveData(); cout << "Linked.\n";
}

void addVehicle() {
    string pid; cout << "Parking ID: "; cin >> pid;
    if (!parkingExists(pid)) { cout << "Invalid parking.\n"; return; }
    Vehicle v; cout << "Vehicle ID: "; cin >> v.id;
    cout << "Plate Number: "; cin >> v.plateNumber;
    getParkingById(pid)->vehicles.push_back(v);
    saveData(); cout << "Vehicle added.\n";
}

void displaceVehicle() {
    string vid, fromId, toId;
    cout << "Vehicle ID: "; cin >> vid;
    cout << "From Parking ID: "; cin >> fromId;
    cout << "To Parking ID: "; cin >> toId;
    if (!parkingExists(fromId) || !parkingExists(toId)) { cout << "Invalid IDs.\n"; return; }

    Parking* from = getParkingById(fromId);
    Parking* to = getParkingById(toId);
    auto it = find_if(from->vehicles.begin(), from->vehicles.end(), [&](Vehicle v){ return v.id == vid; });
    if (it != from->vehicles.end()) {
        to->vehicles.push_back(*it);
        from->vehicles.erase(it);
        saveData(); cout << "Vehicle moved.\n";
    } else cout << "Vehicle not found in source.\n";
}

// New View Functions
void viewParkings() {
    cout << "\n All Parkings:\n";
    for (auto& p : parkings) {
        cout << "- ID: " << p.id << ", Name: " << p.name << "\n";
    }
}

void viewVehicles() {
    cout << "\n All Vehicles by Parking:\n";
    for (auto& p : parkings) {
        cout << "Parking " << p.name << " (" << p.id << "):\n";
        for (auto& v : p.vehicles) {
            cout << "  • Vehicle ID: " << v.id << ", Plate: " << v.plateNumber << "\n";
        }
        if (p.vehicles.empty()) cout << "  (No vehicles)\n";
    }
}

void viewLinks() {
    cout << "\n Parking Links:\n";
    for (auto& e : edges) {
        cout << "- " << e.fromId << " <--> " << e.toId << "\n";
    }
    if (edges.empty()) cout << "(No links)\n";
}

void visualizeGraph() {
    ofstream dot("graph.dot");
    dot << "graph ParkingGraph {\n";
    dot << "  node [shape=rectangle, style=filled, color=lightgrey];\n";

    for (auto& p : parkings) {
        dot << "  \"" << p.id << "\" [label=\"" << p.name << "\"];\n";
        for (auto& v : p.vehicles) {
            dot << "  \"" << v.id << "\" [label=\"" << v.plateNumber << "\", shape=circle, color=lightblue];\n";
            dot << "  \"" << p.id << "\" -- \"" << v.id << "\";\n";
        }
    }
    for (auto& e : edges) {
        dot << "  \"" << e.fromId << "\" -- \"" << e.toId << "\";\n";
    }
    dot << "}\n";
    dot.close();

    system("\"C:/Program Files/Graphviz/bin/dot.exe\" -Tpng graph.dot -o graph.png");
    system("start graph.png");
}

void menu() {
    int c;
    do {
        cout << "\n--- Parking Management ---\n";
        cout << "1. Add Parking\n";
        cout << "2. Delete Parking\n";
        cout << "3. Link Parkings\n";
        cout << "4. Add Vehicle\n";
        cout << "5. Displace Vehicle\n";
        cout << "6. View Parkings\n";
        cout << "7. View Vehicles\n";
        cout << "8. View Links\n";
        cout << "9. Visualize\n";
        cout << "10. Exit\n";
        cout << "Your choice: ";
        cin >> c;
        switch(c) {
            case 1: addParking(); break;
            case 2: deleteParking(); break;
            case 3: linkParkings(); break;
            case 4: addVehicle(); break;
            case 5: displaceVehicle(); break;
            case 6: viewParkings(); break;
            case 7: viewVehicles(); break;
            case 8: viewLinks(); break;
            case 9: visualizeGraph(); break;
            case 10: break;
            default: cout << "Invalid.\n";
        }
    } while (c != 10);
}

int main() {
    loadData();
    menu();
    return 0;
}
