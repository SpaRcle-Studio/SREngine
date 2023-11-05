#include <Utils/stdInclude.h>

#ifdef SR_LINUX
#include "../../Utils/src/Utils/Platform/PlatformLinux.cpp"
#endif

#ifdef SR_WIN32
#include "../../Utils/src/Utils/Platform/PlatformWindows.cpp"
#endif

#ifdef SR_ANDROID
#include "../../Utils/src/Utils/Platform/PlatformAndroid.cpp"
#include "../../Utils/src/Utils/Platform/AndroidNativeAppGlue.c"
#endif