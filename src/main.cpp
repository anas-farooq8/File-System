#include <iostream>
#include <string>
#include <iomanip>
#include "../include/FileSystemManager.h"

using namespace std;

void showMenu(const string& currentDirectory) {
    cout << "Filesystem CLI - Current Directory: " << currentDirectory << "\n";
    cout << "1. Create File\n";
    cout << "2. Delete File\n";
    cout << "3. Write to File\n";
    cout << "4. Read from File\n";
    cout << "5. Create Directory\n";
    cout << "6. List Directory\n";
    cout << "7. Change Directory\n";
    cout << "8. Go Back\n";
    cout << "9. Delete Directory\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    FileSystemManager fs;
    int choice;
    string name, content;
    size_t size;
    
    while (true) {
        showMenu(fs.getCurrentDirectoryPath());
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush input
        
        try {
            switch (choice) {
                case 1:
                    cout << "Enter file name (with extension): ";
                    getline(cin, name);
                    fs.createFile(name);
                    cout << "File created.\n";
                    break;
                case 2:
                    cout << "Enter file name: ";
                    getline(cin, name);
                    fs.deleteFile(name);
                    cout << "File deleted.\n";
                    break;
                case 3:
                    cout << "Enter file name: ";
                    getline(cin, name);
                    if (FileDescriptor* fd = fs.openFile(name)) {
                        cout << "Enter content to write: ";
                        getline(cin, content);
                        fs.writeFile(fd, content);
                        fs.closeFile(fd);
                        cout << "File written.\n";
                    } else {
                        cout << "File not found.\n";
                    }
                    break;
                case 4:
                    cout << "Enter file name: ";
                    getline(cin, name);
                    cout << "Enter number of bytes to read: ";
                    cin >> size;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush input
                    if (FileDescriptor* fd = fs.openFile(name)) {
                        string data = fs.readFile(fd, size);
                        fs.closeFile(fd);
                        cout << "Data read from file: " << data << "\n";
                    } else {
                        cout << "File not found.\n";
                    }
                    break;
                case 5:
                    cout << "Enter directory name: ";
                    getline(cin, name);
                    fs.createDirectory(name);
                    cout << "Directory created.\n";
                    break;
                case 6:
                    for (const auto& [entry, size, date] : fs.listDirectoryWithDetails()) {
                        cout << setw(20) << left << entry 
                                  << setw(10) << right << size 
                                  << setw(25) << right << date << "\n";
                    }
                    break;
                case 7:
                    cout << "Enter directory path: ";
                    getline(cin, name);
                    fs.changeDirectory(name);
                    break;
                case 8:
                    fs.goBack();
                    break;
                case 9:
                    cout << "Enter directory name: ";
                    getline(cin, name);
                    fs.deleteDirectory(name);
                    cout << "Directory deleted.\n";
                    break;
                case 10:
                    cout << "Exiting.\n";
                    return 0;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& e) {
            cerr << e.what() << "\n";
        }
    }
}
