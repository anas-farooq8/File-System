#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FileSystemObject.h"
#include <vector>
#include <memory>
#include <unordered_map>
using namespace std;

// Directory class, derived from FileSystemObject
class Directory : public FileSystemObject {
private:
    /* When a unique_ptr goes out of scope, the destructor of unique_ptr is called,
       which automatically deletes the owned object. This helps prevent memory leaks.
    */
    unordered_map<string, unique_ptr<FileSystemObject>> contents; // Map of string and Vector of unique pointers to FileSystemObject
    Directory* parent;  // Parent directory reference

public:
    Directory(const std::string& name, Directory* parent = nullptr);
    void addObject(unique_ptr<FileSystemObject> obj); // Add object to directory
    void removeObject(const string& name); // Remove object from directory
    FileSystemObject* getObject(const std::string& name) const; // Get object by name
    vector<string> listContents() const; // List names of objects in directory
    Directory* getParent() const; // Getter for parent
    size_t getTotalSize() const; // Get total size of all items in the directory
};

#endif // DIRECTORY_H
