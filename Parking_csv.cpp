#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>   // for file operations
#include <string>

using namespace std;

const int MAX_SPOTS = 10;
const int PRICE_PER_HOUR = 1000;

struct CarInfo {
    string owner;
    string plateNumber;
    int entryHour;
    int duration;
};

map<int, CarInfo> parkingSpots;

// Save car data to CSV
void saveCarToCSV(const CarInfo& car, int spot) {
    ofstream file("parking_data.csv", ios::app); // append mode
    if (file.is_open()) {
        // Format: spot,owner,plate,entryHour,duration
        file << spot << "," << car.owner << "," << car.plateNumber << "," << car.entryHour << "," << car.duration << "\n";
        file.close();
    } else {
        cout << " Warning: Could not open parking_data.csv to save data.\n";
    }
}

// Find first available spot
int assignParkingSpot() {
    for (int i = 1; i <= MAX_SPOTS; i++) {
        if (parkingSpots.find(i) == parkingSpots.end())
            return i;
    }
    return -1; // No spots available
}

void parkCar() {
    string owner, plate;
    int hour, duration;

    cout << "Owner's name: ";
    cin >> owner;
    cout << "Car plate number: ";
    cin >> plate;
    cout << "Entry hour (0-23): ";
    cin >> hour;
    cout << "Expected duration (hours): ";
    cin >> duration;

    int spot = assignParkingSpot();
    if (spot == -1) {
        cout << " Parking full!\n";
        return;
    }

    CarInfo car = {owner, plate, hour, duration};
    parkingSpots[spot] = car;

    // Save to CSV file here 
    saveCarToCSV(car, spot);

    cout << " Car parked at spot #" << spot << " for " << duration << " hour(s).\n";
}

void exitCar() {
    string plate;
    int currentHour;

    cout << "Enter car plate number: ";
    cin >> plate;
    cout << "Current hour (0-23): ";
    cin >> currentHour;

    bool found = false;

    for (auto it = parkingSpots.begin(); it != parkingSpots.end(); ++it) {
        if (it->second.plateNumber == plate) {
            int entryHour = it->second.entryHour;
            int hoursStayed = currentHour - entryHour;
            if (hoursStayed < 0) hoursStayed += 24;

            int payment = hoursStayed * PRICE_PER_HOUR;
            cout << fixed << setprecision(2);
            cout << " Owner: " << it->second.owner << "\n";
            cout << " Spot: " << it->first << "\n";
            cout << " Time Spent: " << hoursStayed << " hour(s)\n";
            cout << " Amount Due: " << payment << " RWF\n";

            parkingSpots.erase(it);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << " Car not found in parking.\n";
    }
}

void showParkedCars() {
    if (parkingSpots.empty()) {
        cout << " No cars in parking.\n";
        return;
    }

    cout << "\n Cars in Parking:\n";
    for (auto& [spot, car] : parkingSpots) {
        cout << "Spot #" << spot << ": " << car.owner << " (" << car.plateNumber << ") - "
             << "Entered at: " << car.entryHour << "h for " << car.duration << "h\n";
    }
}

void showHelp() {
    cout << "\n Commands:\n";
    cout << "1. park   - Park a new car\n";
    cout << "2. exit   - Register car exit\n";
    cout << "3. show   - Show cars in parking\n";
    cout << "4. help   - Show help info\n";
    cout << "5. quit   - Exit program\n\n";
}

int main() {
    string command;

    cout << " Welcome to Parking Manager 3000!\nType 'help' for commands.\n";

    while (true) {
        cout << "\n> ";
        cin >> command;

        for (auto& c : command) c = tolower(c);

        if (command == "park") {
            parkCar();
        } else if (command == "exit") {
            exitCar();
        } else if (command == "show") {
            showParkedCars();
        } else if (command == "help") {
            showHelp();
        } else if (command == "quit") {
            break;
        } else {
            cout << " Unknown command. Type 'help' for a list of valid commands.\n";
        }
    }

    return 0;
}
