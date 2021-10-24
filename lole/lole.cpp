#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <string>

using namespace std;

#ifdef _WIN32
#define WINPAUSE system("pause");
#endif

uintptr_t moduleBaseAddress(DWORD ProcessID, const wchar_t* name)
{
    uintptr_t modBaseAddr = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);

    if (snapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(snapshot, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, name))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(snapshot, &modEntry));
        }
    }
    CloseHandle(snapshot);
    return modBaseAddr;
}

HWND findHWND(string title)
{
    return FindWindowA(NULL, title.c_str());
}

int main()
{
    cout << "Welcome to skootersnese.tk for Leaf Blower Revolution..." << endl;
    HWND processHandle;
    DWORD pid;
    uintptr_t moduleBase;

    processHandle = findHWND("Leaf Blower Revolution");
    cout << "Getting process handle..." << endl;

    if (processHandle != NULL) {
        cout << "Successfully obtained window handle at -> " << &processHandle << endl;

        GetWindowThreadProcessId(processHandle, &pid);

        if (pid != NULL)
            cout << "Successfully obtained process ID: " << pid << endl;

        moduleBase = moduleBaseAddress(pid, L"Leaf Blower Revolution");

        if (&moduleBase != NULL)
            cout << "Successfully obtained module base address at -> " << &moduleBase << endl;
    }
    else
    {
        cout << "Invalid window handle! Please make sure the game is opened" << endl;
    }

    WINPAUSE;

    return 420;
}