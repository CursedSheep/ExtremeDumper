#include "LoaderHook.h"
#include "../Libraries/Detours/src/detours.h"

VOID SetHookMscorwks() {
	DetourCreateProcessWithDll(NULL, NULL, NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL, NULL, NULL);
}

_Success_(return != FALSE)
BOOL WINAPI LoaderHookReadMonitorInfoFile(_In_ LPCWSTR pFilePath, _Out_ PLDHK_MONITOR_INFO pInfo) {
	return FALSE;
}

_Success_(return != FALSE)
BOOL WINAPI LoaderHookMonitorLoop(_In_ PLDHK_MONITOR_INFO pInfo) {
	if (pInfo == NULL)
		return FALSE;

	BYTE foundModules = 0;
	while (foundModules != (pInfo->Flags & LDHK_MONITOR_MODULE_MASK)) {
		HINSTANCE hModule;
		if ((pInfo->Flags & LDHK_MONITOR_MSCORWKS) && !(foundModules & LDHK_MONITOR_MSCORWKS) && (hModule = GetModuleHandle(L"mscorwks.dll"))) {
			foundModules &= LDHK_MONITOR_MSCORWKS;
		}
		Sleep(pInfo->Sleep);
	}

	return TRUE;
}
