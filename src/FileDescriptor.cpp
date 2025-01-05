#include "../include/FileDescriptor.h"

// Constructor for FileDescriptor
FileDescriptor::FileDescriptor(File* file): file(file), position(0) {
    // Nothing
}

// Current position getter
void FileDescriptor::seek(size_t pos) {
    position = pos;
}

// Read function to read data from the file
string FileDescriptor::read(size_t size) {
    string content = file->read();
    size_t endPos = min(position + size, content.size());
    string data = content.substr(position, endPos - position);
    position = endPos; // update the position
    return data;
}

// Write function to write data to the file
void FileDescriptor::write(const string& data) {
    string content = file->read();
    content.replace(position, data.size(), data);
    file->write(content);
    position += data.size(); // update the position
}

// Getter for the file
File* FileDescriptor::getFile() const {
    return file;
}
