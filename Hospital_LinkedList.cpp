
#include <iostream>
#include <string>
using namespace std;

struct Patient {
    int patient_id;
    string name;
    string dob;
    string gender;
    Patient* next;
};

struct Doctor {
    int doctor_id;
    string name;
    string specialization;
    Doctor* next;
};

struct Appointment {
    int appointment_id;
    int patient_id;
    int doctor_id;
    string appointment_date;
    Appointment* next;
};

Patient* patientsHead = nullptr;
Doctor* doctorsHead = nullptr;
Appointment* appointmentsHead = nullptr;

// Check for unique patient ID
bool patientExists(int id) {
    Patient* temp = patientsHead;
    while (temp) {
        if (temp->patient_id == id) return true;
        temp = temp->next;
    }
    return false;
}

// Check for unique doctor ID
bool doctorExists(int id) {
    Doctor* temp = doctorsHead;
    while (temp) {
        if (temp->doctor_id == id) return true;
        temp = temp->next;
    }
    return false;
}

// Check for unique appointment ID
bool appointmentExists(int id) {
    Appointment* temp = appointmentsHead;
    while (temp) {
        if (temp->appointment_id == id) return true;
        temp = temp->next;
    }
    return false;
}

// Register a patient
void registerPatient() {
    int id;
    string name, dob, gender;
    cout << "Enter Patient ID: ";
    cin >> id;
    if (patientExists(id)) {
        cout << "Patient ID already exists!\n";
        return;
    }
    cout << "Enter Name: ";
    cin >> ws; getline(cin, name);
    cout << "Enter DOB (dd-mm-yyyy): ";
    cin >> dob;
    cout << "Enter Gender: ";
    cin >> gender;

    Patient* newPatient = new Patient{id, name, dob, gender, patientsHead};
    patientsHead = newPatient;
    cout << "Patient registered successfully.\n";
}

// Register a doctor
void registerDoctor() {
    int id;
    string name, specialization;
    cout << "Enter Doctor ID: ";
    cin >> id;
    if (doctorExists(id)) {
        cout << "Doctor ID already exists!\n";
        return;
    }
    cout << "Enter Name: ";
    cin >> ws; getline(cin, name);
    cout << "Enter Specialization: ";
    cin >> specialization;

    Doctor* newDoctor = new Doctor{id, name, specialization, doctorsHead};
    doctorsHead = newDoctor;
    cout << "Doctor registered successfully.\n";
}

// Register an appointment
void registerAppointment() {
    int appointment_id, patient_id, doctor_id;
    string date;
    cout << "Enter Appointment ID: ";
    cin >> appointment_id;
    if (appointmentExists(appointment_id)) {
        cout << "Appointment ID already exists!\n";
        return;
    }
    cout << "Enter Patient ID: ";
    cin >> patient_id;
    cout << "Enter Doctor ID: ";
    cin >> doctor_id;

    if (!patientExists(patient_id) || !doctorExists(doctor_id)) {
        cout << "Patient or Doctor ID does not exist!\n";
        return;
    }

    cout << "Enter Appointment Date (dd-mm-yyyy): ";
    cin >> date;

    Appointment* newAppointment = new Appointment{appointment_id, patient_id, doctor_id, date, appointmentsHead};
    appointmentsHead = newAppointment;
    cout << "Appointment registered successfully.\n";
}

// Display patients
void displayPatients() {
    Patient* temp = patientsHead;
    while (temp) {
        cout << "ID: " << temp->patient_id << ", Name: " << temp->name
             << ", DOB: " << temp->dob << ", Gender: " << temp->gender << endl;
        temp = temp->next;
    }
}

// Display doctors
void displayDoctors() {
    Doctor* temp = doctorsHead;
    while (temp) {
        cout << "ID: " << temp->doctor_id << ", Name: " << temp->name
             << ", Specialization: " << temp->specialization << endl;
        temp = temp->next;
    }
}

// Display appointments
void displayAppointments() {
    Appointment* temp = appointmentsHead;
    while (temp) {
        cout << "Appointment ID: " << temp->appointment_id << ", Patient ID: " << temp->patient_id
             << ", Doctor ID: " << temp->doctor_id << ", Date: " << temp->appointment_date << endl;
        temp = temp->next;
    }
}

// Menu system
int main() {
    int choice;
    while (true) {
        cout << "\n--- RUHENGERI REFERRAL HOSPITAL SYSTEM ---\n";
        cout << "1. Register Patient\n2. Register Doctor\n3. Register Appointment\n";
        cout << "4. Display Patients\n5. Display Doctors\n6. Display Appointments\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerPatient(); break;
            case 2: registerDoctor(); break;
            case 3: registerAppointment(); break;
            case 4: displayPatients(); break;
            case 5: displayDoctors(); break;
            case 6: displayAppointments(); break;
            case 7: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
