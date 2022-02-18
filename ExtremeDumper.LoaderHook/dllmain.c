#define WIN32_LEAN_AND_MEAN
#include "LoaderHook.h"

static LDHK_MONITOR_INFO info = { 0 };
static BOOL isInitialized = FALSE;

DWORD WINAPI RunMonitorLoop(LPVOID lpThreadParameter) {
	return LoaderHookMonitorLoop((PLDHK_MONITOR_INFO)lpThreadParameter);
}

VOID LoadIfAvailable() {
	if (isInitialized)
		return;

	WCHAR variable[20] = { 0 };
	GetEnvironmentVariable(L"EXTREMEDUMPER_MAGIC", variable, 20);
	if (wcscmp(variable, L"C41F3A60_DBG") == 0)
		goto exit;
	// If current dll is loaded in ExtremeDumper itself, don't initialize

	info.Sleep = 1;
	CreateThread(NULL, 0, RunMonitorLoop, &info, 0, NULL);
	// Create thread to run monitor loop

exit:
	isInitialized = TRUE;
	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		LoadIfAvailable();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
