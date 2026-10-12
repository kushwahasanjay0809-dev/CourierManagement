// FileManager.h - the only class that reads and writes the data files.
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <vector>
#include "CourierSystem.h"
using namespace std;

class FileManager {
private:
    string folder;                                  // "Data"
    vector<string> splitLine(const string& line);   // "1|Asha|9876543210" -> {"1","Asha","9876543210"}
public:
    FileManager();
    void save(CourierSystem& system);               // write all records to the files
    void load(CourierSystem& system);               // read all records from the files
};

#endif
