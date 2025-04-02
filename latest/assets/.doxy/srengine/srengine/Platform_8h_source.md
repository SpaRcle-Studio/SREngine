

# File Platform.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Platform**](dir_dff07e13fcd57a959fed4d2a16791af6.md) **>** [**Platform.h**](Platform_8h.md)

[Go to the documentation of this file](Platform_8h.md)


```C++
//
// Created by Monika on 17.03.2022.
//

#ifndef SR_ENGINE_UTILS_PLATFORM_H
#define SR_ENGINE_UTILS_PLATFORM_H

#include <Utils/Math/Vector2.h>
#include <Utils/Common/ThreadUtils.h>
#include <Utils/FileSystem/Path.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(PlatformType, uint8_t,
        Unknown, Windows, Linux, Android, MacOS, Emscripten
    );
}

namespace SR_UTILS_NS::Platform {
    struct FileMetadata {
        uint64_t lastWriteTime = SR_UINT64_MAX;
    };

    struct MouseState {
        SR_MATH_NS::FVector2 position;
        bool buttonStates[5] { false, false, false, false, false };
    };

    extern std::mutex g_platformLogMutex;

    SR_NORETURN SR_DLL_EXPORT extern void Terminate();

    SR_DLL_EXPORT extern void InitializePlatform();
    SR_DLL_EXPORT extern void InitSegmentationHandler();
    SR_DLL_EXPORT extern void SetInstance(void* pInstance);
    SR_DLL_EXPORT extern void* GetInstance();
    SR_DLL_EXPORT extern PlatformType GetType();

    SR_DLL_EXPORT extern void SetEnvironmentVar(const std::string_view& name, const std::string_view& value);
    SR_DLL_EXPORT extern std::optional<std::string> ReadFile(const Path& path);
    SR_DLL_EXPORT extern void TextToClipboard(const std::string& text);
    SR_DLL_EXPORT extern void CopyFilesToClipboard(std::list<SR_UTILS_NS::Path> paths);
    SR_DLL_EXPORT extern void SetCurrentProcessDirectory(const SR_UTILS_NS::Path& directory);
    SR_DLL_EXPORT extern void PasteFilesFromClipboard(const SR_UTILS_NS::Path& topath);
    SR_DLL_EXPORT extern void ClearClipboard();
    SR_DLL_EXPORT extern void Sleep(uint64_t milliseconds);
    SR_DLL_EXPORT extern void WriteConsoleLog(const std::string& msg);
    SR_DLL_EXPORT extern void WriteConsoleError(const std::string& msg);
    SR_DLL_EXPORT extern void WriteConsoleWarn(const std::string& msg);
    SR_DLL_EXPORT extern void SelfOpen();
    SR_DLL_EXPORT extern void OpenFile(const SR_UTILS_NS::Path& path, const std::string& args);
    SR_DLL_EXPORT extern void Unzip(const SR_UTILS_NS::Path& source, const SR_UTILS_NS::Path& destination, bool replace = true);
    SR_DLL_EXPORT extern void OpenWithAssociatedApp(const Path& filepath);
    SR_DLL_EXPORT extern bool CreateFolder(const std::string& path);
    SR_DLL_EXPORT extern bool Copy(const Path& from, const Path& to);
    SR_DLL_EXPORT extern bool Delete(const Path& path);
    SR_DLL_EXPORT extern bool WaitAndDelete(const Path& path);
    SR_DLL_EXPORT extern bool IsConsoleFocused();

    SR_DLL_EXPORT extern uint64_t GetProcessUsedMemory();
    SR_DLL_EXPORT extern uint16_t GetCurrentProcessId();
    SR_DLL_EXPORT extern SR_MATH_NS::FVector2 GetMousePos();
    SR_DLL_EXPORT extern MouseState GetMouseState();
    SR_DLL_EXPORT extern bool GetSystemKeyboardState(uint8_t* pKeyCodes);
    SR_DLL_EXPORT extern std::string GetClipboardText();
    SR_DLL_EXPORT extern Path GetApplicationPath();
    SR_DLL_EXPORT extern Path GetApplicationDirectory();
    SR_DLL_EXPORT extern Path GetApplicationName();
    SR_DLL_EXPORT extern std::list<Path> GetInDirectory(const Path& dir, Path::Type type);
    SR_DLL_EXPORT extern std::list<Path> GetAllInDirectory(const Path& dir);
    SR_DLL_EXPORT extern FileMetadata GetFileMetadata(const Path& file);
    SR_DLL_EXPORT extern SR_MATH_NS::UVector2 GetScreenResolution();
    SR_DLL_EXPORT extern double_t GetScreenDPI();
    SR_DLL_EXPORT extern std::vector<SR_MATH_NS::UVector2> GetScreenResolutions();
    SR_DLL_EXPORT extern bool FileIsHidden(const Path& path);
    SR_DLL_EXPORT extern bool IsExists(const Path& path);
    SR_DLL_EXPORT extern bool IsAbsolutePath(const Path& path);
    SR_DLL_EXPORT extern bool IsRunningUnderDebugger();
    SR_DLL_EXPORT extern bool IsFileDeletable(const SR_UTILS_NS::Path& path);

    SR_DLL_EXPORT extern void SetMousePos(const SR_MATH_NS::IVector2& pos);
    SR_DLL_EXPORT extern void SetCursorVisible(bool isVisible);
    SR_DLL_EXPORT extern void ConfineCursor(); // TODO: add ability to confine cursor to a specific window
    SR_DLL_EXPORT extern void ReleaseCursorConfinement(); // TODO: add ability to confine cursor to a specific window
    SR_DLL_EXPORT extern void SetThreadPriority(void* nativeHandle, ThreadPriority priority);
    SR_DLL_EXPORT extern void CopyPermissions(const SR_UTILS_NS::Path& source, const SR_UTILS_NS::Path& destination);

}
#endif //SR_ENGINE_UTILS_PLATFORM_H
```


