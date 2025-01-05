#include "../include/File.h"
#include "../include/Directory.h"
#include <stdexcept>

// Constructor
Directory::Directory(const string& name, Directory* parent): FileSystemObject(name), parent(parent) {
    // Nothing to do here
}

// Add object to directory
void Directory::addObject(unique_ptr<FileSystemObject> obj) {
    // Check if object is already in directory
    contents[obj->getName()] = move(obj);
}

// Remove object from directory
void Directory::removeObject(const string& name) {
    contents.erase(name);
}

// Get object by name
FileSystemObject* Directory::getObject(const string& name) const {
    // Find object by name
    auto it = contents.find(name);
    // Return object if found, otherwise return nullptr
    return (it != contents.end()) ? it->second.get() : nullptr;
}

// List names of objects in directory
vector<string> Directory::listContents() const {
    vector<string> names;
    for (const auto& pair : contents) {
        names.push_back(pair.first);
    }
    return names;
}

// Getter for parent
Directory* Directory::getParent() const {
    return parent;
}

// Get total size of all items in the directory
size_t Directory::getTotalSize() const {
    size_t totalSize = 0;
    for (const auto& pair : contents) {
        if (File* file = dynamic_cast<File*>(pair.second.get())) {
            totalSize += file->read().size();
        } else if (Directory* dir = dynamic_cast<Directory*>(pair.second.get())) {
            totalSize += dir->getTotalSize();
        }
    }
    return totalSize;
}