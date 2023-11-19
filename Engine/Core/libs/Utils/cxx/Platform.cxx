#include <Utils/stdInclude.h>

#ifdef SR_LINUX
    #include "../../Utils/src/Utils/Platform/PlatformLinux.cpp"
    #include "../../Utils/src/Utils/Platform/StacktraceLinux.cpp"
#endif

#ifdef SR_WIN32
    #include "../../Utils/src/Utils/Platform/PlatformWindows.cpp"
    #include "../../Utils/src/Utils/Platform/StacktraceWindows.cpp"
#endif

#ifdef SR_ANDROID
    #include "../../Utils/src/Utils/Platform/StacktraceAndroid.cpp"
    #include "../../Utils/src/Utils/Platform/PlatformAndroid.cpp"
    #include "../../Utils/src/Utils/Platform/AndroidNativeAppGlue.c"
#endif