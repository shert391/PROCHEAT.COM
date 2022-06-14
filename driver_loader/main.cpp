#include "Includes.h"

int main()
{
	Utilits::SetTitleConsole();

	Sleep(300);
	Utilits::SetColor(11);
	printf("[~] Cracked by Shert :-)\n\n");
	Sleep(500);


	Binary binary;

	byte* systemOne = binary.Open("system_one.bin");
	byte* systemTwo = binary.Open("system_two.bin");

	Memory memory;

	DWORD processId = memory.GetProcessIdEx(L"csgo.exe");

	if (processId == 0xcccccccc || processId == NULL) {
		Utilits::SetColor(12);
		printf("[-] Could not find csgo!");
		Sleep(3000);
		exit(-1);
	}

	Utilits::SetColor(10);
	printf("[+] csgo.exe(PID: %i) found!\n", processId);
	Sleep(500);

	Driver driver{};
	driver.Load();

	DataSendDriver dataSend(systemOne, systemTwo, processId);
	driver.Send(&dataSend);

	Sleep(5000);

	return 0;
}