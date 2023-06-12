#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
private:
    string rollNumber;
    string name;
    string division;
    string address;

public:
    // Parameterized constructor
    Student(const string& roll, const string& studentName, const string& div, const string& addr)
        : rollNumber(roll), name(studentName), division(div), address(addr) {}

    // Getter methods
    string getRollNumber() const { return rollNumber; }
    string getName() const { return name; }
    string getDivision() const { return division; }
    string getAddress() const { return address; }

    // Overloading the << operator for displaying student details
    friend ostream& operator<<(ostream& out, const Student& student) {
        out << "Roll Number: " << student.rollNumber << endl;
        out << "Name: " << student.name << endl;
        out << "Division: " << student.division << endl;
        out << "Address: " << student.address << endl;
        return out;
    }
};

// Function to add a student's information
void addStudent() {
    ofstream file("student_info.txt", ios::app);

    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    string roll, name, division, address;
    cout << "Enter Roll Number: ";
    getline(cin, roll);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Division: ";
    getline(cin, division);
    cout << "Enter Address: ";
    getline(cin, address);

    Student student(roll, name, division, address);

    file << student.getRollNumber() << "," << student.getName() << "," << student.getDivision() << ","
         << student.getAddress() << endl;

    file.close();

    cout << "Student information added successfully!" << endl;
}

// Function to display the details of a particular student
void displayStudent() {
    string rollNumber;
    cout << "Enter Roll Number of the student to display: ";
    getline(cin, rollNumber);

    ifstream file("student_info.txt");

    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find(rollNumber + ",") == 0) {
            found = true;
            string roll, name, division, address;
            size_t pos = line.find(",");
            roll = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            division = line.substr(0, pos);
            line.erase(0, pos + 1);

            address = line;

            Student student(roll, name, division, address);
            cout<< student; // Displaying student details using operator overload
            break;
        }
    }

    if (!found) {
        cout << "Student record not found!" << endl;
    }

    file.close();
}
void deleteStudent() {
    string rollNumber;
    cout << "Enter Roll Number of the student to delete: ";
    getline(cin, rollNumber);

    ifstream inputFile("student_info.txt");
    ofstream outputFile("temp.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Failed to open file!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        if (line.find(rollNumber + ",") == 0) {
            found = true;
            cout << "Deleting the following student record:" << endl;
            cout << line << endl;
            continue;
        }
        outputFile << line << endl;
    }

    inputFile.close();
    outputFile.close();

    if (found) {
        remove("student_info.txt");
        rename("temp.txt", "student_info.txt");
        cout << "Student record deleted successfully!" << endl;
    } else {
        remove("temp.txt");
        cout << "Student record not found!" << endl;
    }
}

// Main program loop
int main() {
    while (true) {
        cout << "\n===== Student Information System =====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student Details" << endl;
        cout << "4. Exit" << endl;

        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent() ;
                break;
            case 3:
                displayStudent();
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

