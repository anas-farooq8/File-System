
# File System

File System using c++, contains the basic functionalities for the user such as create, delete, write and read a file. Also create, navigate and remove directories. The program isn't persistence meaning the data is lost when the program finishes execution.

## Execution (Automated)
* Create a build Directoty.
* Navigate into it.
![1](https://github.com/user-attachments/assets/fe9ee87f-4ab5-4118-ade7-879281040e25)

* Generate the build files.
```bash
cmake ..
```
![2](https://github.com/user-attachments/assets/00ef2c70-e691-488f-a040-615596e12229)

* Compile the Project.
```bash
cmake --build .
```
![3](https://github.com/user-attachments/assets/05922017-f757-4273-bdd5-f19edc92a7a6)

* Run the test cases.
```bash
.\Debug\filesystem_tests.exe
```
![4](https://github.com/user-attachments/assets/3f20ba89-f59e-45ae-a67b-d8cd13ad9455)

* Run the Program.
```bash
.\Debug\filesystem.exe
```

## Execution (Manual)
* Be on the src directory of the project; compile the program and run it.
```bash
cd src

g++ -o main main.cpp Directory.cpp File.cpp FileDescriptor.cpp FileSystemObject.cpp FileSystemManager.cpp

./main
```
![5](https://github.com/user-attachments/assets/8ea92b95-699e-4bb1-9594-7bca0005162f)

## Video Demo
https://github.com/user-attachments/assets/cbe2aee6-d403-4fa1-aee2-e9d80c6b0b7f

