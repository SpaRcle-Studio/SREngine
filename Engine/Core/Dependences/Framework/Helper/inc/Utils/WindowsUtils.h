//
// Created by Monika on 15.12.2021.
//

#ifndef SRENGINE_WINDOWSUTILS_H
#define SRENGINE_WINDOWSUTILS_H

#include <macros.h>

#ifdef SR_WIN32

#include <Windows.h>
#include <SetupApi.h>
#include <cfgmgr32.h> // MAX_DEVICE_ID_LEN
#include <iostream>
#include <vector>
#include <string>
#include <map>

#pragma comment(lib, "setupapi.lib")

namespace Framework::Helper {
    /*typedef std::map<std::wstring, std::wstring> DevNameToDevId; // DeviceName -> DeviceId
    typedef std::map<std::wstring, std::pair<int, int> > PhyMonitorSizes; // DeviceId -> (width, height)

    // Helper function that finds the monitor sizes in millimeter using the SetupAPI and the EDID data in the registry.
    // This function may return more monitors than actually connected to the computer, these will
    // be filtered out later when matching the device ids.
    static PhyMonitorSizes findMonitorSizesFromEDID() {
        PhyMonitorSizes screenSizes;

        const GUID GUID_DEVINTERFACE_MONITOR = { 0xe6f07b5f, 0xee97, 0x4a90, 0xb0, 0x76, 0x33, 0xf5, 0x7b, 0xf4, 0xea, 0xa7 };
        const HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_MONITOR, NULL, NULL, DIGCF_DEVICEINTERFACE);

        // Instead of creating a buffer in each iteration and calling SetupDiGetDeviceInterfaceDetail
        // twice (once to find required buffer size and once to actually get the data), we create a
        // buffer up front with the maximum size it can have.
        // The 128 contant comes from the fact that the DeviceId parameter in DISPLAY_DEVICE is
        // at most 128 characters and we will be looking for a match with this id later.
        // Note that the buffer is slightly larger than it has to be (as "sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA)"
        // was used instead of "offsetof(SP_DEVICE_INTERFACE_DETAIL_DATA, DevicePath)").
        wchar_t devPathBuffer[sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W) + (128 * sizeof(wchar_t))];

        // Loop over the device interfaces using the SetupAPI
        DWORD monitorIndex = 0;
        SP_DEVICE_INTERFACE_DATA devInfo;
        devInfo.cbSize = sizeof(devInfo);
        while (SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &GUID_DEVINTERFACE_MONITOR, monitorIndex, &devInfo))
        {
            ++monitorIndex;

            // Retrieve the id of the device interface
            SP_DEVICE_INTERFACE_DETAIL_DATA_W* devPathData = (SP_DEVICE_INTERFACE_DETAIL_DATA_W*)devPathBuffer;
            devPathData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);
            SP_DEVINFO_DATA devInfoData;
            memset(&devInfoData, 0, sizeof(devInfoData));
            devInfoData.cbSize = sizeof(devInfoData);
            if (!SetupDiGetDeviceInterfaceDetailW(hDevInfo, &devInfo, devPathData, sizeof(devPathBuffer), NULL, &devInfoData))
                continue; // Error

            // We now have the device id that we will use to match this device on other places later.
            const std::wstring deviceId = devPathData->DevicePath;

            // Find the instance id of the device to look up the EDID in the registry
            wchar_t instanceId[MAX_DEVICE_ID_LEN];
            if (!SetupDiGetDeviceInstanceIdW(hDevInfo, &devInfoData, instanceId, MAX_PATH, NULL))
                continue; // Error

            // Find the EDID registry key
            HKEY hEDIDRegKey = SetupDiOpenDevRegKey(hDevInfo, &devInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
            if (!hEDIDRegKey || (hEDIDRegKey == INVALID_HANDLE_VALUE))
                continue; // Error

            // Read the EDID data from the registry
            BYTE dataEDID[1024];
            DWORD sizeOfDataEDID = sizeof(dataEDID);
            if (ERROR_SUCCESS == RegQueryValueExW(hEDIDRegKey, L"EDID", NULL, NULL, dataEDID, &sizeOfDataEDID))
            {
                // Extract the width and height of the monitor from the EDID
                int WidthMm = ((dataEDID[68] & 0xF0) << 4) + dataEDID[66];
                int HeightMm = ((dataEDID[68] & 0x0F) << 8) + dataEDID[67];
                screenSizes[deviceId] = std::make_pair(WidthMm, HeightMm);
            }

            RegCloseKey(hEDIDRegKey);
        }

        return screenSizes;
    }


    // Helper function that creates a mapping between device names and ids.
    static DevNameToDevId getDeviceNamesToIdMap()
    {
        DevNameToDevId namesToIdMap;

        // Query how many display paths there are
        UINT32 nrPaths;
        UINT32 nrModes;
        GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &nrPaths, &nrModes);

        // Retrieve the active display paths.
        // Although we don't need the modes, documentation of QueryDisplayConfig says we can't use NULL for them.
        std::vector<DISPLAYCONFIG_PATH_INFO> paths(nrPaths);
        std::vector<DISPLAYCONFIG_MODE_INFO> modes(nrModes);
        QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &nrPaths, &paths[0], &nrModes, &modes[0], NULL);

        // Loop over the display paths and map the device name to the unique id that we will use
        for (unsigned int i = 0; i < paths.size(); ++i)
        {
            DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
            sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
            sourceName.header.size = sizeof(sourceName);
            sourceName.header.adapterId = paths[i].sourceInfo.adapterId;
            sourceName.header.id = paths[i].sourceInfo.id;
            DisplayConfigGetDeviceInfo(&sourceName.header);

            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName;
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = sizeof(targetName);
            targetName.header.adapterId = paths[i].sourceInfo.adapterId;
            targetName.header.id = paths[i].targetInfo.id;
            DisplayConfigGetDeviceInfo(&targetName.header);

            namesToIdMap[sourceName.viewGdiDeviceName] = targetName.monitorDevicePath;
        }

        return namesToIdMap;
    }

    // Helper function for a case-insensitive string comparison.
    // This isn't the best nor the fastest method, but it is simple and gets the job done.
    static bool caseInsensitiveComparison(const std::wstring& Str1, const std::wstring& Str2)
    {
        if (Str1.length() != Str2.length())
            return false;

        for (unsigned i = 0; i < Str1.length(); ++i)
        {
            if (Str1[i] == Str2[i])
                continue;
            if ((Str1[i] >= L'A') && (Str1[i] <= L'Z') && ((Str1[i] - (L'A' - L'a')) == Str2[i]))
                continue;
            if ((Str2[i] >= L'A') && (Str2[i] <= L'Z') && ((Str2[i] - (L'A' - L'a')) == Str1[i]))
                continue;

            return false;
        }

        return true;
    }

    // The actual function that takes the HMONITOR as input and has the screen size as output.
    static std::pair<int, int> getMonitorSizeInMillimeter(HMONITOR hMonitor)
    {
        const PhyMonitorSizes& sizesById = findMonitorSizesFromEDID();
        const DevNameToDevId& deviceIdsByName = getDeviceNamesToIdMap();

        // Find the device name from the HMONITOR
        MONITORINFOEXW monInfo;
        monInfo.cbSize = sizeof(monInfo);
        if (!GetMonitorInfoW(hMonitor, &monInfo))
            return {}; // Error

        // Find the device id belonging to that name
        auto deviceIdIt = deviceIdsByName.find(monInfo.szDevice);
        if (deviceIdIt == deviceIdsByName.end())
            return {}; // Error

        const std::wstring& deviceId = deviceIdIt->second;

        // We now need to loop over the data returned from FindMonitorSizesFromEDID
        // and do a case-insensitive comparison because the device id from
        // FindMonitorSizesFromEDID seems to be in lowercase.
        for (auto it = sizesById.begin(); it != sizesById.end(); ++it)
        {
            const std::wstring& devId = it->first;
            const std::pair<int, int>& size = it->second;
            if (!caseInsensitiveComparison(deviceId, devId))
                continue;

            // We matched the device id from the HMONITOR with the one from SetupAPI, so we now have its size.
            // Keep in mind that the size is independent of the orientation of the monitor. You may still want
            // to add code that swaps the width and height in case the monitor is rotated (which could easily
            // be detected: if the monitor has a larger width in pixels then it must also have a larger width in mm).
            const int phyWidthMm = size.first;
            const int phyHeightMm = size.second;
            return std::make_pair(phyWidthMm, phyHeightMm);
        }

        // If we pass here then we didn't find a match and we couldn't get the size of
        // this monitor.
        return {};
    }*/

    static BOOL CALLBACK MonitorVectorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
        auto* monitors = (std::vector<HMONITOR>*)dwData;
        monitors->emplace_back(hMonitor);
        return TRUE;
    }

    static std::vector<HMONITOR> GetAllMonitors() {
        std::vector<HMONITOR> monitors;
        if (EnumDisplayMonitors(NULL, NULL, MonitorVectorEnumProc, (LPARAM)&monitors))
            return monitors;

        return {};
    }
}

#endif

#endif //SRENGINE_WINDOWSUTILS_H
