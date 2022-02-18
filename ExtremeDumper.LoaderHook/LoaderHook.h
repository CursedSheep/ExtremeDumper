#pragma once

#include <windows.h>

#define LDHK_MONITOR_MSCORWKS    0x01
#define LDHK_MONITOR_CLR         0x02
#define LDHK_MONITOR_CORECLR     0x04
#define LDHK_MONITOR_MODULE_MASK 0x07

typedef struct LDHK_MONITOR_INFO {
	BYTE Sleep;
	BYTE Flags;
} LDHK_MONITOR_INFO, * PLDHK_MONITOR_INFO;

#ifdef __cplusplus
extern "C" {
#endif
	// Read config from file
	_Success_(return != FALSE)
	BOOL WINAPI LoaderHookReadMonitorInfoFile(_In_ LPCWSTR pFilePath, _Out_ PLDHK_MONITOR_INFO pInfo);

	// Run loop to monitor clr modules loading and hook it
	_Success_(return != FALSE)
	BOOL WINAPI LoaderHookMonitorLoop(_In_ PLDHK_MONITOR_INFO pInfo);
#ifdef __cplusplus
}
#endif
