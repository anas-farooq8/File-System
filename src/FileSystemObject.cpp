#include "../include/FileSystemObject.h"

// Constructor for FileSystemObject
FileSystemObject::FileSystemObject(const string& name): name(name), lastModified(system_clock::now()) {
    // Nothing to do here
}

// Getters and Setters
string FileSystemObject::getName() const {
    return name;
}

system_clock::time_point FileSystemObject::getLastModified() const {
    return lastModified;
}

void FileSystemObject::setLastModified(system_clock::time_point time) {
    lastModified = time;
}
