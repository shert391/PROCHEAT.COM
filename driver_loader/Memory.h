class Memory
{
public:
	DWORD GetProcessId(LPCSTR processNameWindow);
	DWORD GetProcessIdEx(const wchar_t* processName);
};
