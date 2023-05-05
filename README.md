
# Copying-Files-with-Memory-Usage-Tracking

This is a simple employee management system that allows you to store employee records and retrieve them by ID. The system consists of two classes: "Record" and "StorageBufferManager".

# Record

The Record class represents a single employee record and has the following attributes:

1. id (integer): the ID of the employee
2. name (string): the name of the employee
3. bio (string): a brief biography of the employee
4. manager_id (integer): the ID of the employee's manager

The class also has a print method that prints out the record to the console.

# StorageBufferManager

The StorageBufferManager class manages the storage and retrieval of employee records. It has the following methods:

1. StorageBufferManager(fileName): constructor that initializes the object with a given filename.
2. createFromFile(csvFName): reads in employee records from a CSV file and writes them to the storage file.
3. findRecordById(id): finds a record with a given ID and returns it.
