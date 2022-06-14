#include "Includes.h"

void Driver::Load()
{
	HMODULE ntdll = GetModuleHandleA("ntdll.dll");

	*(FARPROC*)&RtlInitUnicodeString = GetProcAddress(ntdll, "RtlInitUnicodeString");
	*(FARPROC*)&NtLoadDriver = GetProcAddress(ntdll, "NtLoadDriver");
	*(FARPROC*)&NtUnloadDriver = GetProcAddress(ntdll, "NtUnloadDriver");
	*(FARPROC*)&NtCreateKey = GetProcAddress(ntdll, "NtCreateKey");
	*(FARPROC*)&NtSetValueKey = GetProcAddress(ntdll, "NtSetValueKey");

	EnablePrivilege(L"SeLoadDriverPrivilege");

	RtlInitUnicodeString(&reestrPath, REESTR_PATH);

	CreateRegedit();

	Unload();
	
	if (NtLoadDriver(&reestrPath) == STATUS_SUCCESS) {
		Utilits::SetColor(10);
		printf("[+] Driver loaded!\n");
		driverHandle = CreateFileA("\\\\.\\driver", GENERIC_WRITE | GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (driverHandle == NULL) {
			Utilits::SetColor(12);
			printf("[-] driver.sys not found!");
			Sleep(3000);
			exit(-1);
		}
		Sleep(500);
	}
	else {
		Utilits::SetColor(12);
		printf("[-] Driver loading error!");
		Sleep(3000);
		exit(-1);
	}
}

void Driver::Unload() {
	if (NtUnloadDriver(&reestrPath) == STATUS_SUCCESS) {
		Utilits::SetColor(10);
		printf("[+] Driver unloaded!\n");
		Sleep(500);
	}
}

void Driver::Send(DataSendDriver* data){
	DWORD result;
	DeviceIoControl(driverHandle, 0x0397C898, data, 0x828, 0, 0, &result, 0);
	Utilits::SetColor(10);
	printf("[+] Cheat loaded!\n");
}

void Driver::EnablePrivilege(LPCWSTR lpPrivilegeName)
{
	TOKEN_PRIVILEGES privilege{};
	DWORD dwErrorCode = 0;
	HANDLE hToken;

	privilege.PrivilegeCount = 1;
	privilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	LookupPrivilegeValueW(NULL, lpPrivilegeName, &privilege.Privileges[0].Luid);

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);

	AdjustTokenPrivileges(hToken, FALSE, &privilege, sizeof(privilege), NULL, NULL);

	CloseHandle(hToken);
}

void Driver::CreateRegedit()
{
	OBJECT_ATTRIBUTES objectAttributes = { 0 };

	objectAttributes.Length = sizeof(objectAttributes);
	objectAttributes.ObjectName = &reestrPath;

	DWORD typeStartValue = 1;

	HANDLE keyHandle = NULL;

	NTSTATUS result = NtCreateKey(&keyHandle, KEY_ALL_ACCESS, &objectAttributes, 0, NULL, REG_OPTION_NON_VOLATILE, NULL);

	if (result != STATUS_SUCCESS) {
		Utilits::SetColor(12);
		printf("[-] NtCreateKey error: 0x%X\n", result);
		Sleep(3000);
		exit(-1);
	}

	UNICODE_STRING errorKey;

	RtlInitUnicodeString(&errorKey, L"Type");

	UNICODE_STRING pathKey{};

	RtlInitUnicodeString(&pathKey, L"ImagePath");

	NtSetValueKey(keyHandle, &errorKey, 0, REG_DWORD, &typeStartValue, sizeof(typeStartValue));

	wchar_t sol[MAX_PATH] = L"\\??\\";

	wchar_t pathCurrentDir[MAX_PATH]{};

	wchar_t driverName[] = L"\\driver.sys";

	DWORD countPath = GetCurrentDirectory(sizeof(pathCurrentDir), pathCurrentDir);

	wcsncat(sol, pathCurrentDir, sizeof(sol) - countPath);

	wcsncat(sol, driverName, sizeof(driverName));

	SIZE_T pathCurrentDirSize = ((((DWORD)lstrlenW(sol) + 1)) * 2);

	NtSetValueKey(keyHandle, &pathKey, 0, REG_SZ, (LPVOID)sol, pathCurrentDirSize);

	CloseHandle(keyHandle);
}
