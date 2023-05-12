#include <string>
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "classes.h"

using namespace std; 

int main(int argc, char* const argv[]) {
    // Create the EmployeeRelation file from Employee.csv
    StorageBufferManager manager("EmployeeRelation");
    manager.createFromFile("Employee.csv");

    // Loop to lookup IDs until user is ready to quit
    while (true) {
        // Get ID input from user
        cout << "Enter ID of employee to lookup (enter -1 to quit): ";
        int id;
        cin >> id;
        if (id == -1) {
            break;
        }
        
        // Find the record with the given ID
        Record record = manager.findRecordById(id);
        if (record.id == -1) {
            cout << "Record not found." << endl;
        }
        else {
            cout << "Found record:" << endl;
            record.print();
        }
    }

    return 0;
}
