struct DataSendDriver {
public:
	DataSendDriver(LPVOID pointerOne, LPVOID pointerTwo, DWORD idProcess) {
		_pointerOne = pointerOne;
		_pointerTwo = pointerTwo;
		_idProcess = idProcess;
	}
private:
	byte _unknownOne = 0x02;
	byte _nopOne[0x807] = { 0x00 };
	DWORD _idProcess;
	LPVOID _pointerOne;
	DWORD _unknownTwo = 4;
	byte _nopTwo[4] = { 0x00 };
	LPVOID _pointerTwo;
	byte _nopThree[4] = { 0x00 };
	byte _unknownThree[4] = { 0x00, 0x1C, 0x0B, 0x00 };
	DWORD _unknownFoure = 1;
};