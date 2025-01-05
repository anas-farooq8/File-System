#include "../include/FileSystemManager.h"
#include <sstream>
#include <regex>
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
using namespace chrono;

// Constructor
FileSystemManager::FileSystemManager(): root(make_unique<Directory>("", nullptr)), currentDirectory(root.get()) {
    // Nothing
}

// Helper function to navigate to a directory
Directory* FileSystemManager::navigateToDirectory(const string& path) {
    Directory* current = (path.empty() || path == "/") ? root.get() : currentDirectory;
    istringstream stream(path);
    string token;
    
    while (getline(stream, token, '/')) {
        if (!token.empty()) {
            FileSystemObject* obj = current->getObject(token);
            current = dynamic_cast<Directory*>(obj);
            if (!current) {
                return nullptr; // path is invalid
            }
        }
    }
    return current;
}

// Function to create a file
void FileSystemManager::createFile(const string& name) {
        // Check if the name contains at least one dot followed by one or more characters
        regex fileExtensionRegex(R"((.+)\.(.+))");
        if (!regex_match(name, fileExtensionRegex)) {
            throw runtime_error("Error: Invalid file name. File name must end with an extension.");
        }
        
        if (currentDirectory->getObject(name)) {
            throw runtime_error("Error: File with the same name already exists.");
        }
        currentDirectory->addObject(make_unique<File>(name));
}

// Function to delete a file
void FileSystemManager::deleteFile(const string& name) {
    if (currentDirectory->getObject(name)) {
        currentDirectory->removeObject(name);
    } else {
        throw runtime_error("Error: File not found.");
    }
}

// Function to open a file
FileDescriptor* FileSystemManager::openFile(const string& name) {
    FileSystemObject* obj = currentDirectory->getObject(name);
    File* file = dynamic_cast<File*>(obj);
    if (file) {
        auto fd = make_unique<FileDescriptor>(file);
        FileDescriptor* fdPtr = fd.get();
        fileDescriptors[name] = move(fd);
        return fdPtr;
    } else {
        throw runtime_error("Error: File not found.");
    }
}

// Function to close a file
void FileSystemManager::closeFile(FileDescriptor* fd) {
    for (auto it = fileDescriptors.begin(); it != fileDescriptors.end(); ++it) {
        if (it->second.get() == fd) {
            fileDescriptors.erase(it);
            return;
        }
    }
}

// Function to write to a file
void FileSystemManager::writeFile(FileDescriptor* fd, const string& content) {
    fd->write(content);
}

// Function to read from a file
string FileSystemManager::readFile(FileDescriptor* fd, size_t size) {
    return fd->read(size);
}

// Function to list all files in the current directory
void FileSystemManager::createDirectory(const string& name) {
    if (currentDirectory->getObject(name)) {
        throw runtime_error("Error: Directory with the same name already exists.");
    }
    currentDirectory->addObject(make_unique<Directory>(name, currentDirectory));
}

// Function to delete a directory
void FileSystemManager::deleteDirectory(const string& name) {
    FileSystemObject* obj = currentDirectory->getObject(name);
    Directory* dir = dynamic_cast<Directory*>(obj);
    if (dir && dir != currentDirectory) {
        currentDirectory->removeObject(name);
    } else if (dir == currentDirectory) {
        throw runtime_error("Error: Cannot delete the current directory.");
    } else {
        throw runtime_error("Error: Directory not found.");
    }
}

// Function to list all files in the current directory
vector<tuple<string, size_t, string>> FileSystemManager::listDirectoryWithDetails() const {
    vector<tuple<string, size_t, string>> contentsWithDetails;
    for (const auto& name : currentDirectory->listContents()) {
        FileSystemObject* obj = currentDirectory->getObject(name);
        
        // Get last modified time as a string
        ostringstream dateStream;
        auto time = system_clock::to_time_t(obj->getLastModified());
        dateStream << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
        
        // Get size
        size_t size = 0;
        if (File* file = dynamic_cast<File*>(obj)) {
            size = file->read().size();
        } else if (Directory* dir = dynamic_cast<Directory*>(obj)) {
            size = dir->getTotalSize();
        }
        
        contentsWithDetails.emplace_back(name, size, dateStream.str());
    }
    return contentsWithDetails;
}

// Function to change the current directory
void FileSystemManager::changeDirectory(const string& path) {
    Directory* newDir = navigateToDirectory(path);
    if (newDir) {
        directoryStack.push(currentDirectory);
        currentDirectory = newDir;
    } else {
        throw runtime_error("Error: Directory not found.");
    }
}

// Function to navigate to the parent directory
void FileSystemManager::goBack() {
    if (!directoryStack.empty()) {
        currentDirectory = directoryStack.top();
        directoryStack.pop();
    } else {
        throw runtime_error("Error: No previous directory to go back to.");
    }
}

// Function to get the current directory path
string FileSystemManager::getCurrentDirectoryPath() const {
    string path;
    const Directory* dir = currentDirectory;

    while (dir != nullptr && dir != root.get()) {
        string dirName = dir->getName();
        path = "/" + dirName + path;
        dir = dir->getParent();
    }

    return path.empty() ? "/" : path; // Ensuring root path remains "/"
}
