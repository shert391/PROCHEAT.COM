#include "Includes.h"

byte* Binary::Open(const char* pathFile)
{
	ifstream stream(pathFile, ios::binary);
	if (!stream.is_open()) {
		Utilits::SetColor(12);
		printf("[-] %s not found!", pathFile);
		Sleep(3000);
		exit(-1);
	}
	stream.seekg(0, stream.end);
	int lenght = stream.tellg();
	stream.seekg(0, stream.beg);
	byte* result = new byte[lenght];
	stream.read((char*)result, lenght);
	stream.close();
	return result;
}
