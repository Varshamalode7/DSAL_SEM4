// Implementation of a direct access file -Insertion and deletion of a
// record from a Direct Access File.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class HashTable
{
    int address[10];

public:
    HashTable()
    {
        for (int i = 0; i < 10; i++)
        {
            address[i] = -1;
        }
    }
    friend class Employee;
};

class Employee
{
    int id;
    string salary;
    string name;
    string experience;

public:
    HashTable table;
    void addRecord()
    {
        int n, location, index;
        cout << "Enter number of records: ";
        cin >> n;

        ofstream fout;
        fout.open("DirectAccessFile.txt", ios::out);

        for (int i = 0; i < n; i++)
        {
            cout << "Enter Employee id: ";
            cin >> id;

            cout << "Enter Employee name: ";
            cin >> name;

            cout << "Enter Employee salary: ";
            cin >> salary;

            cout << "Enter Employee experience: ";
            cin >> experience;

            location = fout.tellp();
            index = id % 10;
            table.address[index] = location;
            fout << id << " " << name << " " << salary << " " << experience << endl;
        }
        fout.close();
    }

    void displayRecord()
    {
        char buffer[40];
        int count = 0;

        ifstream fin;
        fin.open("DirectAccessFile.txt", ios::in);

        while (!fin.eof())
        {
            fin.getline(buffer, 40);
            count++;
            cout << "Record " << count << endl;
            cout << buffer << endl;
        }
    }

    void searchRecord(int id)
    {
        int index, location;

        index = id % 10;
        location = table.address[index];

        ifstream fin;
        fin.open("DirectAccessFile.txt", ios::in);

        fin.seekg(location, ios::beg);

        char buffer[40];
        fin.getline(buffer, 40);
        cout << "Record found: " << buffer << endl;
    }

    void deleteRecord(int id)
    {
        int index, location;
        string tempArray[10];
        int count;
        char buffer[40];

        index = id % 10;
        location = table.address[index];

        ifstream fin;
        fin.open("DirectAccessFile.txt", ios::in);

        for (int i = 0; i < 10; i++)
        {
            if (table.address[i] != -1 && table.address[i] != location)
            {
                fin.seekg(table.address[i], ios::beg);
                fin.getline(buffer, 40);
                tempArray[i] = buffer;
                count++;
            }
        }

        fin.close();

        ofstream fout;
        fout.open("DirectAccessFile.txt", ios::out);

        for (int i = 0; i < 10; i++)
        {
            table.address[i] = -1;
        }

        for (int i = 0; i < 10; i++)
        {
            if (tempArray[i] != "")
            {
                location = fout.tellp();
                table.address[i] = location;
                fout << tempArray[i] << endl;
            }
        }

        fout.close();
    }
};

int main()
{
    Employee e;
    int choice, id;
    while (true)
    {
        cout << "MNEU" << endl;
        cout << "1.Add records" << endl;
        cout << "2.Display Records" << endl;
        cout << "3.Search record" << endl;
        cout << "4.Delete record" << endl;
        cout << "5.Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            e.addRecord();
            break;
        case 2:
            e.displayRecord();
            break;
        case 3:
            cout << "Enter id to be searched: ";
            cin >> id;
            e.searchRecord(id);
            break;
        case 4:
            cout << "Enter id to be deleted: ";
            cin >> id;
            e.deleteRecord(id);
            break;
        case 5:
            exit(0);
        default:
            cout << "Enter valid option" << endl;
            break;
        }
    }
}
