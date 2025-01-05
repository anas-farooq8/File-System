#ifndef FILESYSTEMOBJECT_H
#define FILESYSTEMOBJECT_H

#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

// Base class for all filesystem objects
class FileSystemObject {
protected:
    string name;    // Name of the object
    system_clock::time_point lastModified;  // Last modified time of the object

public:
    // Constructor
    FileSystemObject(const string& name);
    // Destructor
    virtual ~FileSystemObject() = default;
    // Getters and Setters
    string getName() const;
    system_clock::time_point getLastModified() const;
    void setLastModified(system_clock::time_point time);
};

#endif // FILESYSTEMOBJECT_H
