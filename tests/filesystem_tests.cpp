#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/FileSystemManager.h"

TEST_CASE("File Creation and Deletion", "[filesystem]") {
    FileSystemManager fs;

    // Test file creation
    fs.createFile("test.txt");
    REQUIRE(fs.openFile("test.txt") != nullptr);

    // Test file cannot be created with duplicate name
    REQUIRE_THROWS_AS(fs.createFile("test.txt"), std::runtime_error);

    // Test file deletion
    fs.deleteFile("test.txt");
    REQUIRE_THROWS_AS(fs.openFile("test.txt"), std::runtime_error);

    // Test file deletion for non-existent file
    REQUIRE_THROWS_AS(fs.deleteFile("nonexistent.txt"), std::runtime_error);
}

TEST_CASE("File Reading and Writing", "[filesystem]") {
    FileSystemManager fs;
    fs.createFile("test.txt");
    auto fd = fs.openFile("test.txt");

    // Test writing to a file
    fs.writeFile(fd, "Hello, World!");
    fs.closeFile(fd);

    fd = fs.openFile("test.txt");
    REQUIRE(fs.readFile(fd, 50) == "Hello, World!");
    fs.closeFile(fd);

    // Test reading from a file not written to
    fs.createFile("empty.txt");
    fd = fs.openFile("empty.txt");
    REQUIRE(fs.readFile(fd, 50).empty());
    fs.closeFile(fd);
}

TEST_CASE("Directory Creation and Deletion", "[filesystem]") {
    FileSystemManager fs;

    // Test directory creation
    fs.createDirectory("testDir");
    fs.changeDirectory("testDir");
    REQUIRE(fs.getCurrentDirectoryPath() == "/testDir");

    fs.goBack();
    // Test directory cannot be created with duplicate name
    REQUIRE_THROWS_AS(fs.createDirectory("testDir"), std::runtime_error);

    // Test directory deletion
    fs.deleteDirectory("testDir");
    REQUIRE_THROWS_AS(fs.changeDirectory("testDir"), std::runtime_error);

    // Test directory deletion for non-existent directory
    REQUIRE_THROWS_AS(fs.deleteDirectory("nonexistentDir"), std::runtime_error);
}

TEST_CASE("Directory Navigation", "[filesystem]") {
    FileSystemManager fs;

    fs.createDirectory("testDir");
    fs.changeDirectory("testDir");
    REQUIRE(fs.getCurrentDirectoryPath() == "/testDir");

    fs.goBack();
    REQUIRE(fs.getCurrentDirectoryPath() == "/");

    // Test changing to non-existent directory
    REQUIRE_THROWS_AS(fs.changeDirectory("nonexistentDir"), std::runtime_error);
}

TEST_CASE("Listing Directory Contents", "[filesystem]") {
    FileSystemManager fs;
    fs.createFile("test.txt");

    // Write to file to update modification time
    auto fd = fs.openFile("test.txt");
    fs.writeFile(fd, "data");
    fs.closeFile(fd);

    auto contents = fs.listDirectoryWithDetails();
    REQUIRE(contents.size() == 1);

    auto [name, size, modified] = contents[0];
    REQUIRE(name == "test.txt");
    REQUIRE(size == 4); // "data" is 4 bytes
}
