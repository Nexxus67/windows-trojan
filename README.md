# windows-trojan

DISCLAIMER:

This code is for educational and research purposes only. The author does not condone or support the use of this code for any illegal or unethical activities. The author is not responsible for any harm caused by the use or misuse of this code.

By accessing and/or using this code, you agree to use it solely for educational and research purposes and to comply with all applicable laws and regulations. You assume full responsibility for any actions taken based on the information and code provided in this repository.

This code is provided as-is, without warranty of any kind, express or implied. The author disclaims any and all liability for any damages or losses arising from the use or inability to use this code.

The use of this code for any illegal or unethical activities is strictly prohibited. If you choose to use this code, you do so at your own risk and acknowledge that you may be subject to legal consequences.

The code defines a C program that includes a function called CreateRatFile which creates a remote administration tool (RAT) file by creating a new process and setting its parameters. The function takes two arguments: a HANDLE to a process and a char* that specifies the command-line arguments for the RAT file.

The main function includes an example usage of the CreateRatFile function that demonstrates how to call the function with the appropriate arguments.

To compile the program, you can use a C compiler such as GCC or Clang. Here's an example of how to compile the program using GCC on a Unix-like system:

gcc -o rat-file-creator rat-file-creator.c

This command will create an executable file called rat-file-creator in the current directory.

To run the program, you can simply execute the resulting executable file. Here's an example of how to run the program on a Unix-like system:

./rat-file-creator

Note that you'll need to replace "path/to/RAT/file.exe" in the main function with the actual path to the RAT file you want to create before compiling and running the program. Additionally, the program is currently set up to create a new console window when it creates the RAT process. If you don't want this behavior, you can change the CREATE_NEW_CONSOLE flag in the CreateProcessA call to 0 or CREATE_NO_WINDOW.
