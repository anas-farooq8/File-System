#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H

#include "Directory.h"
#include "FileDescriptor.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <stack>
#include <stdexcept>

// The FileSystemManager class is responsible for managing the file system operations.
class FileSystemManager {
private:
    unique_ptr<Directory> root; // Represents the root directory
    Directory* currentDirectory;    // Represents the current directory
    stack<Directory*> directoryStack;   // Stack to keep track of the directory navigation
    unordered_map<string, unique_ptr<FileDescriptor>> fileDescriptors;  // Map of string and Vector of unique pointers to FileDescriptor

    // Helper function to navigate to a directory
    Directory* navigateToDirectory(const string& path);

public:
    // Constructor
    FileSystemManager();
    // Function to create a file
    void createFile(const string& name);
    // Function to delete a file
    void deleteFile(const string& name);
    // Function to open a file
    FileDescriptor* openFile(const string& name);
    // Function to close a file
    void closeFile(FileDescriptor* fd);
    // Function to write to a file
    void writeFile(FileDescriptor* fd, const string& content);
    // Function to read from a file
    string readFile(FileDescriptor* fd, size_t size);
    // Function to list all files in the current directory
    void createDirectory(const string& name);
    // Function to delete a directory
    void deleteDirectory(const string& name);
    // Function to list all files in the current directory
    vector<tuple<string, size_t, string>> listDirectoryWithDetails() const;

// Function to change the current directory
    void changeDirectory(const string& path);
// Function to navigate to the parent directory
    void goBack();
// Function to get the current directory path
    string getCurrentDirectoryPath() const;
};

#endif // FILESYSTEMMANAGER_H
