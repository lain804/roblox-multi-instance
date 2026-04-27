#include <windows.h>
#include <cstdio>
#include <TlHelp32.h>

const wchar_t ROBLOX_EXECUTABLE_NAME[] = L"RobloxPlayerBeta.exe";
const wchar_t ROBLOX_MUTEX_NAME[] = L"ROBLOX_singletonEvent";

void KillAllRoblox() {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32W pe{};
	pe.dwSize = sizeof(pe);

	BOOL ok = Process32FirstW(hSnapshot, &pe);

	DWORD returnVal = 0;

	while (ok) {
		if (wcscmp(pe.szExeFile, ROBLOX_EXECUTABLE_NAME) == 0) {
			HANDLE hRoblox = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, FALSE, pe.th32ProcessID);
			TerminateProcess(hRoblox, NULL);
			WaitForSingleObject(hRoblox, INFINITE);
			CloseHandle(hRoblox);
		}
		ok = Process32NextW(hSnapshot, &pe);
	}

	CloseHandle(hSnapshot);
}

int main() {
	KillAllRoblox();

	HANDLE hMutex = CreateMutexW(NULL, TRUE, ROBLOX_MUTEX_NAME);

	printf("Roblox multi instance Active, close to disable\n");

	while (true) {
		Sleep(INFINITE);
	}

}
