#include "includes.h"

void Utilits::SetColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Utilits::SetTitleConsole() {
	static const char rnum[] = "0123456789" "qwertyuiopasdfghjklzxcvbnm" "QWERTYUIOPASDFGHJKLZXCVBNM";
	wchar_t RandomTitle[40] = { 0x00 };
	srand(time(0));
	for (unsigned int i = 0; i < 30; ++i) {

		RandomTitle[i] = (char)rnum[rand() % (sizeof(rnum) - 1)];
	}
	SetConsoleTitle(RandomTitle);
}
	