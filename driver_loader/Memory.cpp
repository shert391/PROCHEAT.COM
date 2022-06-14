#include "Includes.h"

DWORD Memory::GetProcessId(LPCSTR processNameWindow)
{
	HWND hwnd = FindWindowA(NULL, processNameWindow);

	DWORD procId; 

	GetWindowThreadProcessId(hwnd, &procId); 

    return procId;
}

DWORD Memory::GetProcessIdEx(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry{};
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
	return procId;
}
