#define _WIN32_WINNT _WIN32_WINNT_WIN10
#include <initguid.h>
#include <windows.h>
#include <appmodel.h>
#include <shobjidl.h>

static IPackageDebugSettings *pPackageDebugSettings = NULL;

static void AppPolicySetLifecycleManagementUnmanaged(PCWSTR packageFamilyName)
{
    UINT32 count = 0, bufferLength = 0;
    if (GetPackagesByPackageFamily(packageFamilyName, &count, NULL, &bufferLength, NULL) != ERROR_INSUFFICIENT_BUFFER)
        return;

    PWSTR *packageFullNames = HeapAlloc(GetProcessHeap(), 0, sizeof(PWSTR) * count),
          buffer = HeapAlloc(GetProcessHeap(), 0, sizeof(WCHAR) * bufferLength);

    GetPackagesByPackageFamily(packageFamilyName, &count, packageFullNames, &bufferLength, buffer);
    pPackageDebugSettings->lpVtbl->EnableDebugging(pPackageDebugSettings, packageFullNames[0], NULL, NULL);
}

int WinMainCRTStartup()
{
    CoInitialize(NULL);
    CoCreateInstance(&CLSID_PackageDebugSettings, NULL, CLSCTX_INPROC_SERVER, &IID_IPackageDebugSettings,
                     (LPVOID *)&pPackageDebugSettings);
    AppPolicySetLifecycleManagementUnmanaged(L"Microsoft.MinecraftUWP_8wekyb3d8bbwe");
    AppPolicySetLifecycleManagementUnmanaged(L"Microsoft.MinecraftWindowsBeta_8wekyb3d8bbwe");
    pPackageDebugSettings->lpVtbl->Release(pPackageDebugSettings);
    CoUninitialize();
    ExitProcess(0);
    return 0;
}