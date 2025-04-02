

# Namespace SR\_UTILS\_NS::Platform



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Platform**](namespaceSR__UTILS__NS_1_1Platform.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**FileMetadata**](structSR__UTILS__NS_1_1Platform_1_1FileMetadata.md) <br> |
| struct | [**MouseState**](structSR__UTILS__NS_1_1Platform_1_1MouseState.md) <br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::mutex | [**g\_platformLogMutex**](#variable-g_platformlogmutex)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_DLL\_EXPORT void | [**ClearClipboard**](#function-clearclipboard) () <br> |
|  SR\_DLL\_EXPORT void | [**ConfineCursor**](#function-confinecursor) () <br> |
|  SR\_DLL\_EXPORT bool | [**Copy**](#function-copy) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & from, const [**Path**](classSR__UTILS__NS_1_1Path.md) & to) <br> |
|  SR\_DLL\_EXPORT void | [**CopyFilesToClipboard**](#function-copyfilestoclipboard) (std::list&lt; [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) &gt; paths) <br> |
|  SR\_DLL\_EXPORT void | [**CopyPermissions**](#function-copypermissions) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & source, const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & destination) <br> |
|  SR\_DLL\_EXPORT bool | [**CreateFolder**](#function-createfolder) (const std::string & path) <br> |
|  SR\_DLL\_EXPORT bool | [**Delete**](#function-delete) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_DLL\_EXPORT bool | [**FileIsHidden**](#function-fileishidden) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_DLL\_EXPORT std::list&lt; [**Path**](classSR__UTILS__NS_1_1Path.md) &gt; | [**GetAllInDirectory**](#function-getallindirectory) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & dir) <br> |
|  SR\_DLL\_EXPORT [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetApplicationDirectory**](#function-getapplicationdirectory) () <br> |
|  SR\_DLL\_EXPORT [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetApplicationName**](#function-getapplicationname) () <br> |
|  SR\_DLL\_EXPORT [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetApplicationPath**](#function-getapplicationpath) () <br> |
|  SR\_DLL\_EXPORT std::string | [**GetClipboardText**](#function-getclipboardtext) () <br> |
|  SR\_DLL\_EXPORT uint16\_t | [**GetCurrentProcessId**](#function-getcurrentprocessid) () <br> |
|  SR\_DLL\_EXPORT [**FileMetadata**](structSR__UTILS__NS_1_1Platform_1_1FileMetadata.md) | [**GetFileMetadata**](#function-getfilemetadata) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & file) <br> |
|  SR\_DLL\_EXPORT std::list&lt; [**Path**](classSR__UTILS__NS_1_1Path.md) &gt; | [**GetInDirectory**](#function-getindirectory) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & dir, Path::Type type) <br> |
|  SR\_DLL\_EXPORT void \* | [**GetInstance**](#function-getinstance) () <br> |
|  SR\_DLL\_EXPORT SR\_MATH\_NS::FVector2 | [**GetMousePos**](#function-getmousepos) () <br> |
|  SR\_DLL\_EXPORT [**MouseState**](structSR__UTILS__NS_1_1Platform_1_1MouseState.md) | [**GetMouseState**](#function-getmousestate) () <br> |
|  SR\_DLL\_EXPORT uint64\_t | [**GetProcessUsedMemory**](#function-getprocessusedmemory) () <br> |
|  SR\_DLL\_EXPORT double\_t | [**GetScreenDPI**](#function-getscreendpi) () <br> |
|  SR\_DLL\_EXPORT SR\_MATH\_NS::UVector2 | [**GetScreenResolution**](#function-getscreenresolution) () <br> |
|  SR\_DLL\_EXPORT std::vector&lt; SR\_MATH\_NS::UVector2 &gt; | [**GetScreenResolutions**](#function-getscreenresolutions) () <br> |
|  SR\_DLL\_EXPORT bool | [**GetSystemKeyboardState**](#function-getsystemkeyboardstate) (uint8\_t \* pKeyCodes) <br> |
|  SR\_DLL\_EXPORT PlatformType | [**GetType**](#function-gettype) () <br> |
|  SR\_DLL\_EXPORT void | [**InitSegmentationHandler**](#function-initsegmentationhandler) () <br> |
|  SR\_DLL\_EXPORT void | [**InitializePlatform**](#function-initializeplatform) () <br> |
|  SR\_DLL\_EXPORT bool | [**IsAbsolutePath**](#function-isabsolutepath) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_DLL\_EXPORT bool | [**IsConsoleFocused**](#function-isconsolefocused) () <br> |
|  SR\_DLL\_EXPORT bool | [**IsExists**](#function-isexists) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_DLL\_EXPORT bool | [**IsFileDeletable**](#function-isfiledeletable) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_DLL\_EXPORT bool | [**IsRunningUnderDebugger**](#function-isrunningunderdebugger) () <br> |
|  SR\_DLL\_EXPORT void | [**OpenFile**](#function-openfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, const std::string & args) <br> |
|  SR\_DLL\_EXPORT void | [**OpenWithAssociatedApp**](#function-openwithassociatedapp) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & filepath) <br> |
|  SR\_DLL\_EXPORT void | [**PasteFilesFromClipboard**](#function-pastefilesfromclipboard) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & topath) <br> |
|  SR\_DLL\_EXPORT std::optional&lt; std::string &gt; | [**ReadFile**](#function-readfile) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_DLL\_EXPORT void | [**ReleaseCursorConfinement**](#function-releasecursorconfinement) () <br> |
|  SR\_DLL\_EXPORT void | [**SelfOpen**](#function-selfopen) () <br> |
|  SR\_DLL\_EXPORT void | [**SetCurrentProcessDirectory**](#function-setcurrentprocessdirectory) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & directory) <br> |
|  SR\_DLL\_EXPORT void | [**SetCursorVisible**](#function-setcursorvisible) (bool isVisible) <br> |
|  SR\_DLL\_EXPORT void | [**SetEnvironmentVar**](#function-setenvironmentvar) (const std::string\_view & name, const std::string\_view & value) <br> |
|  SR\_DLL\_EXPORT void | [**SetInstance**](#function-setinstance) (void \* pInstance) <br> |
|  SR\_DLL\_EXPORT void | [**SetMousePos**](#function-setmousepos) (const SR\_MATH\_NS::IVector2 & pos) <br> |
|  SR\_DLL\_EXPORT void | [**SetThreadPriority**](#function-setthreadpriority) (void \* nativeHandle, ThreadPriority priority) <br> |
|  SR\_DLL\_EXPORT void | [**Sleep**](#function-sleep) (uint64\_t milliseconds) <br> |
|  SR\_NORETURN SR\_DLL\_EXPORT void | [**Terminate**](#function-terminate) () <br> |
|  SR\_DLL\_EXPORT void | [**TextToClipboard**](#function-texttoclipboard) (const std::string & text) <br> |
|  SR\_DLL\_EXPORT void | [**Unzip**](#function-unzip) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & source, const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & destination, bool replace=true) <br> |
|  SR\_DLL\_EXPORT bool | [**WaitAndDelete**](#function-waitanddelete) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_DLL\_EXPORT void | [**WriteConsoleError**](#function-writeconsoleerror) (const std::string & msg) <br> |
|  SR\_DLL\_EXPORT void | [**WriteConsoleLog**](#function-writeconsolelog) (const std::string & msg) <br> |
|  SR\_DLL\_EXPORT void | [**WriteConsoleWarn**](#function-writeconsolewarn) (const std::string & msg) <br> |




























## Public Attributes Documentation




### variable g\_platformLogMutex 

```C++
std::mutex SR_UTILS_NS::Platform::g_platformLogMutex;
```




<hr>
## Public Functions Documentation




### function ClearClipboard 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::ClearClipboard () 
```




<hr>



### function ConfineCursor 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::ConfineCursor () 
```




<hr>



### function Copy 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::Copy (
    const Path & from,
    const Path & to
) 
```




<hr>



### function CopyFilesToClipboard 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::CopyFilesToClipboard (
    std::list< SR_UTILS_NS::Path > paths
) 
```




<hr>



### function CopyPermissions 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::CopyPermissions (
    const SR_UTILS_NS::Path & source,
    const SR_UTILS_NS::Path & destination
) 
```




<hr>



### function CreateFolder 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::CreateFolder (
    const std::string & path
) 
```




<hr>



### function Delete 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::Delete (
    const Path & path
) 
```




<hr>



### function FileIsHidden 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::FileIsHidden (
    const Path & path
) 
```




<hr>



### function GetAllInDirectory 

```C++
SR_DLL_EXPORT std::list< Path > SR_UTILS_NS::Platform::GetAllInDirectory (
    const Path & dir
) 
```




<hr>



### function GetApplicationDirectory 

```C++
SR_DLL_EXPORT Path SR_UTILS_NS::Platform::GetApplicationDirectory () 
```




<hr>



### function GetApplicationName 

```C++
SR_DLL_EXPORT Path SR_UTILS_NS::Platform::GetApplicationName () 
```




<hr>



### function GetApplicationPath 

```C++
SR_DLL_EXPORT Path SR_UTILS_NS::Platform::GetApplicationPath () 
```




<hr>



### function GetClipboardText 

```C++
SR_DLL_EXPORT std::string SR_UTILS_NS::Platform::GetClipboardText () 
```




<hr>



### function GetCurrentProcessId 

```C++
SR_DLL_EXPORT uint16_t SR_UTILS_NS::Platform::GetCurrentProcessId () 
```




<hr>



### function GetFileMetadata 

```C++
SR_DLL_EXPORT FileMetadata SR_UTILS_NS::Platform::GetFileMetadata (
    const Path & file
) 
```




<hr>



### function GetInDirectory 

```C++
SR_DLL_EXPORT std::list< Path > SR_UTILS_NS::Platform::GetInDirectory (
    const Path & dir,
    Path::Type type
) 
```




<hr>



### function GetInstance 

```C++
SR_DLL_EXPORT void * SR_UTILS_NS::Platform::GetInstance () 
```




<hr>



### function GetMousePos 

```C++
SR_DLL_EXPORT SR_MATH_NS::FVector2 SR_UTILS_NS::Platform::GetMousePos () 
```




<hr>



### function GetMouseState 

```C++
SR_DLL_EXPORT MouseState SR_UTILS_NS::Platform::GetMouseState () 
```




<hr>



### function GetProcessUsedMemory 

```C++
SR_DLL_EXPORT uint64_t SR_UTILS_NS::Platform::GetProcessUsedMemory () 
```




<hr>



### function GetScreenDPI 

```C++
SR_DLL_EXPORT double_t SR_UTILS_NS::Platform::GetScreenDPI () 
```




<hr>



### function GetScreenResolution 

```C++
SR_DLL_EXPORT SR_MATH_NS::UVector2 SR_UTILS_NS::Platform::GetScreenResolution () 
```




<hr>



### function GetScreenResolutions 

```C++
SR_DLL_EXPORT std::vector< SR_MATH_NS::UVector2 > SR_UTILS_NS::Platform::GetScreenResolutions () 
```




<hr>



### function GetSystemKeyboardState 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::GetSystemKeyboardState (
    uint8_t * pKeyCodes
) 
```




<hr>



### function GetType 

```C++
SR_DLL_EXPORT PlatformType SR_UTILS_NS::Platform::GetType () 
```




<hr>



### function InitSegmentationHandler 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::InitSegmentationHandler () 
```




<hr>



### function InitializePlatform 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::InitializePlatform () 
```




<hr>



### function IsAbsolutePath 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::IsAbsolutePath (
    const Path & path
) 
```




<hr>



### function IsConsoleFocused 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::IsConsoleFocused () 
```




<hr>



### function IsExists 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::IsExists (
    const Path & path
) 
```




<hr>



### function IsFileDeletable 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::IsFileDeletable (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function IsRunningUnderDebugger 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::IsRunningUnderDebugger () 
```




<hr>



### function OpenFile 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::OpenFile (
    const SR_UTILS_NS::Path & path,
    const std::string & args
) 
```




<hr>



### function OpenWithAssociatedApp 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::OpenWithAssociatedApp (
    const Path & filepath
) 
```




<hr>



### function PasteFilesFromClipboard 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::PasteFilesFromClipboard (
    const SR_UTILS_NS::Path & topath
) 
```




<hr>



### function ReadFile 

```C++
SR_DLL_EXPORT std::optional< std::string > SR_UTILS_NS::Platform::ReadFile (
    const Path & path
) 
```




<hr>



### function ReleaseCursorConfinement 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::ReleaseCursorConfinement () 
```




<hr>



### function SelfOpen 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::SelfOpen () 
```




<hr>



### function SetCurrentProcessDirectory 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::SetCurrentProcessDirectory (
    const SR_UTILS_NS::Path & directory
) 
```




<hr>



### function SetCursorVisible 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::SetCursorVisible (
    bool isVisible
) 
```




<hr>



### function SetEnvironmentVar 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::SetEnvironmentVar (
    const std::string_view & name,
    const std::string_view & value
) 
```




<hr>



### function SetInstance 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::SetInstance (
    void * pInstance
) 
```




<hr>



### function SetMousePos 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::SetMousePos (
    const SR_MATH_NS::IVector2 & pos
) 
```




<hr>



### function SetThreadPriority 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::SetThreadPriority (
    void * nativeHandle,
    ThreadPriority priority
) 
```




<hr>



### function Sleep 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::Sleep (
    uint64_t milliseconds
) 
```




<hr>



### function Terminate 

```C++
SR_NORETURN SR_DLL_EXPORT void SR_UTILS_NS::Platform::Terminate () 
```




<hr>



### function TextToClipboard 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::TextToClipboard (
    const std::string & text
) 
```




<hr>



### function Unzip 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::Unzip (
    const SR_UTILS_NS::Path & source,
    const SR_UTILS_NS::Path & destination,
    bool replace=true
) 
```




<hr>



### function WaitAndDelete 

```C++
SR_DLL_EXPORT bool SR_UTILS_NS::Platform::WaitAndDelete (
    const Path & path
) 
```




<hr>



### function WriteConsoleError 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::WriteConsoleError (
    const std::string & msg
) 
```




<hr>



### function WriteConsoleLog 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::WriteConsoleLog (
    const std::string & msg
) 
```




<hr>



### function WriteConsoleWarn 

```C++
SR_DLL_EXPORT void SR_UTILS_NS::Platform::WriteConsoleWarn (
    const std::string & msg
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Platform/Platform.h`

