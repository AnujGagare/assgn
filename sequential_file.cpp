#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Record {
    int rollNo, div;
    string name, address;

public:
    Record() {}

    Record(int roll, string title, string path, int division) {
        this->name = title;
        this->address = path;
        this->rollNo = roll;
        this->div = division;
    }

    friend class File;
};

class File {
    string fileName;
    fstream file; //object of fstream class

public:
    File(string title) {
        fileName = title;
    }

    void writeRecord(Record *r, int num) {
        file.open(fileName, ios::out); 
        for (int i = 0; i < num; i++) {
            file << r[i].rollNo << "," << r[i].name << ",SE-" << r[i].div << "," << r[i].address << endl;
        }
        file.close();
    }

    void printRecord() {
        file.open(fileName, ios::in);
        string record;
        while (getline(file, record)) {
            cout << record << endl;
        }
        file.close();
    }

    void searchRecord(int r) {
        file.open(fileName, ios::in);
        bool isFound = false;
        string record;
        while (getline(file, record)) { //it reads lines.so 1st read honar mag if condition mag 2nd read
            if (stoi(record.substr(0, record.find(','))) == r) { //0 to first comma paryant string access 
                                                                //karnar ani tyala integer madhe convert
                cout << "Record found" << endl;            
                cout << record << endl;
                cout << endl;
                isFound = true;
                break;
            }
        }
        file.close();
        if (!isFound) {
            cout << "Record not found...." << endl;
        }
    }

    void deleteRecord(int r) {
        file.open(fileName, ios::in);
        vector<string> lines;

        string record;
        while (getline(file, record)) {
            if (stoi(record.substr(0, record.find(','))) != r) {
                lines.push_back(record);  //adds the current value of record 
                                        // to the end of the lines vector.
            }
        }
        file.close();

        file.open(fileName, ios::out);
        for (int i = 0; i < lines.size(); i++) {
            file << lines[i] << endl;
        }
        file.close();
    }
};

int main() {
    File F("sample.txt");
    int numRecords;
    cout << "Enter the number of records: ";
    cin >> numRecords;
    Record *record = new Record[numRecords];

    for (int i = 0; i < numRecords; i++) {
        int rollNo, div;
        string name, address;

        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore(); // to consume the newline character. to clear any remaining characters, 
                      //including the newline character, from the input buffer before calling getline
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Division: ";
        cin >> div;

        record[i] = Record(rollNo, name, address, div);
    }

    F.writeRecord(record, numRecords);

    //delete[] record;

    int choice;
    int rollNo;
    bool exit = false;

    while (!exit) {
        cout << "Menu:" << endl;
        cout << "1. Display all records" << endl;
        cout << "2. Search record" << endl;
        cout << "3. Delete record" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                F.printRecord();
                break;
            case 2:
                cout << "Enter roll number to search: ";
                cin >> rollNo;
                F.searchRecord(rollNo);
                break;
            case 3:
                cout << "Enter roll number to delete: ";
                cin >> rollNo;
                F.deleteRecord(rollNo);
                cout << "Record deleted successfully!" << endl;
                break;
            case 4:
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}
