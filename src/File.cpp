#include "../include/File.h"
using namespace chrono;

// Constructor for File
File::File(const string& name): FileSystemObject(name), size(0), content("") {
    // Nothing to do here
}

// Write function to write data to the file
void File::write(const string& data) {
    // Updating the info of the file
    content = data;
    size = data.size();
    setLastModified(system_clock::now());
}

// Read function to read data from the file
string File::read() const {
    return content;
}

// Resets file by making the content of the file to null
void File::deleteContent() {
    content.clear();
    size = 0;
    setLastModified(system_clock::now());
}
