#include <stdio.h>
#include <windows.h>

// Function to create RAT file
void CreateRatFile(HANDLE hProcess, char* szCmdLine)
{
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi = { 0 };

    ZeroMemory(&pi, sizeof(pi));

    // Create a new process for the RAT file and set its parameters.
    if (!CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        printf("Error creating process for RAT file: %lu\n", GetLastError());
        return;
    }

    // Wait for the RAT process to become active.
    DWORD dwExitCode;
    if (WaitForInputIdle(pi.hProcess, 5000) == WAIT_FAILED)
    {
        printf("Error waiting for RAT process to become active: %lu\n", GetLastError());
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return;
    }

    printf("RAT process created successfully (PID: %lu)\n", pi.dwProcessId);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main()
{
    // Example usage of the CreateRatFile function
    HANDLE hProcess = GetCurrentProcess();
    char* szCmdLine = "path/to/RAT/file.exe";
    CreateRatFile(hProcess, szCmdLine);

    return 0;
}
