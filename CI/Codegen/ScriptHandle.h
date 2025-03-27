#ifdef _MSVC_LANG
    #pragma pack(push, 1) // MSVC: Remove padding
#endif

#ifndef SR_ENGINE_SCRIPT_API_SCRIPT_HANDLE_INCLUDE_GUARD
#define SR_ENGINE_SCRIPT_API_SCRIPT_HANDLE_INCLUDE_GUARD
extern "C" {
    struct ScriptHandle {
        void* pData = nullptr;
        uint32_t* pRefCount = nullptr;
        bool isDestructible = false;
    }
    #if defined(__GNUC__) || defined(__clang__)
        __attribute__((packed)); // GCC/Clang: Remove padding
    #else
        ;
    #endif
}
#endif /// SR_ENGINE_SCRIPT_API_SCRIPT_HANDLE_INCLUDE_GUARD

#ifdef _MSVC_LANG
    #pragma pack(pop) // MSVC: Restore pack settings
#endif