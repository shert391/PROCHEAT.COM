class Driver
{
public:
	void Load();
	void Unload();
	void Send(DataSendDriver* data);
private:
	HANDLE driverHandle = NULL;

	const NTSTATUS STATUS_SUCCESS = 0x0;
	const PCWSTR REESTR_PATH = L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\PhoenixKernel";

	UNICODE_STRING reestrPath;

	NTSTATUS(NTAPI* NtLoadDriver)(IN PUNICODE_STRING DriverServiceName);
	NTSTATUS(NTAPI* NtUnloadDriver)(IN PUNICODE_STRING DriverServiceName);
	VOID(NTAPI* RtlInitUnicodeString)(PUNICODE_STRING DestinationString, PCWSTR SourceString);
	NTSTATUS (NTAPI* NtCreateKey)(OUT PHANDLE pKeyHandle, IN ACCESS_MASK DesiredAccess, IN POBJECT_ATTRIBUTES ObjectAttributes, IN ULONG TitleIndex, IN PUNICODE_STRING Class OPTIONAL, IN ULONG CreateOptions, OUT PULONG Disposition OPTIONAL);
	NTSTATUS(NTAPI* NtSetValueKey)(IN HANDLE KeyHandle, IN PUNICODE_STRING ValueName, IN ULONG TitleIndex OPTIONAL, IN ULONG Type, IN PVOID Data, IN ULONG DataSize);

	void EnablePrivilege(LPCWSTR lpPrivilegeName);
	void CreateRegedit();
};