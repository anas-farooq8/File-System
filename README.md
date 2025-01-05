
# File System

File System using c++, contains the basic functionalities for the user such as create, delete, write and read a file. Also create, navigate and remove directories. The program isn't persistence meaning the data is lost when the program finishes execution.

# Execution (Automated)
* Create a build Directoty.
* Navigate into it.
![Screenshot 2024-06-19 151641](https://github.com/someone20233/File-System/assets/128719291/a5a91388-9fc7-4f3a-acea-ce455f00fa3f)

* Generate the build files.
```bash
cmake ..
```
![Screenshot 2024-06-19 152118](https://github.com/someone20233/File-System/assets/128719291/50883d1f-d298-4a1e-9c1b-154977fcb308)


* Compile the Project.
```bash
cmake --build .
```
![Screenshot 2024-06-19 152146](https://github.com/someone20233/File-System/assets/128719291/1b2c6dcc-ddaa-428d-b202-5a70bb2da47b)


* Run the test cases.
```bash
.\Debug\filesystem_tests.exe
```
![Screenshot 2024-06-19 152251](https://github.com/someone20233/File-System/assets/128719291/cb127dee-dbdd-4a39-9368-ef654450d37c)
* Run the Program.
```bash
.\Debug\filesystem.exe
```

# Execution (Manual)
* Be on the src directory of the project; compile the program and run it.
```bash
cd src

g++ -o main main.cpp Directory.cpp File.cpp FileDescriptor.cpp FileSystemObject.cpp FileSystemManager.cpp

./main
```
![Screenshot 2024-06-19 152600](https://github.com/someone20233/File-System/assets/128719291/cd5d20f8-00db-4281-bd69-f33e09c5ccee)
