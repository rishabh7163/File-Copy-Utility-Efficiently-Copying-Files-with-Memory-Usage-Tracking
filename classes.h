#include <string>
#include <vector>
#include <iostream> 
#include <sstream>
#include <fstream>
#include <sys/resource.h>

class Record {
public:
    int id, manager_id;
    std::string bio, name;
    
    Record(const std::vector<std::string>& fields) {
        id = std::stoi(fields[0]);
        name = fields[1];
        bio = fields[2];
        manager_id = std::stoi(fields[3]);
    }
    
    void print() const {
        std::cout << "\tID: " << id << "\n";
        std::cout << "\tNAME: " << name << "\n";
        std::cout << "\tBIO: " << bio << "\n";
        std::cout << "\tMANAGER_ID: " << manager_id << "\n";
    }
};


class StorageBufferManager {
private:
    const int PAGE_SIZE = 1; // Each line is a page
    int numRecords;
    std::string fileName;
    std::ofstream output_file;
    int recordsWrittenToPage;

    void writeRecordToFile(const Record& record) {
        output_file << record.id << "," << record.name << "," << record.bio << "," << record.manager_id << "\n";
        recordsWrittenToPage++;
    }

public:

    StorageBufferManager(const std::string& newFileName) {
        fileName = newFileName + ".csv";
        numRecords = 0;
        recordsWrittenToPage = 0;
        output_file.open(fileName, std::ios::out);
        std::ifstream input_file("EmployeeRelation.csv");
        std::string header;
        getline(input_file, header); // read the header line from the input file
        output_file << header << "\n"; // write the header line to the output file
        input_file.close();
    }
    
    
    ~StorageBufferManager() {
        output_file.close();
    }
    
    void createFromFile(const std::string& csvFName) {
        std::ifstream input_file(csvFName);
        std::string line;
        getline(input_file, line); // read and ignore the header line
        
        // Check memory usage
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        std::cout << "Memory Usage: " << usage.ru_maxrss << " KB\n";

        while (getline(input_file, line)) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;
            
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            
            Record record(fields);
            
            writeRecordToFile(record);
            
            numRecords++;
            
            if (recordsWrittenToPage >= PAGE_SIZE) {
                output_file.close();
                output_file.open(fileName, std::ios::app);
                recordsWrittenToPage = 0;
            }
        }
        
        input_file.close();
    }
    
    Record findRecordById(int id) const {
    std::ifstream input_file(fileName);
    std::string line;
    getline(input_file, line); // read and ignore the header line

    int numLines = 1;
    while (getline(input_file, line)) {
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        Record record(fields);

        if (record.id == id) {
            input_file.close();
            return record;
        }

        numLines++;

        // Get the current position in the file
        std::streampos currentPos = input_file.tellg();

        // Move to the beginning of the file to count the number of lines read so far
        input_file.seekg(0, std::ios::beg);
        for (int i = 0; i < numLines; i++) {
            getline(input_file, line);
        }

        // Get the current position in the file again
        std::streampos newPos = input_file.tellg();

        // Calculate the size of the read so far
        int sizeRead = newPos - currentPos;

        if (sizeRead >= PAGE_SIZE) {
            input_file.close();
            throw std::invalid_argument("Record not found!");
        }
    }

    input_file.close();
    throw std::invalid_argument("Record not found!");
}


};
