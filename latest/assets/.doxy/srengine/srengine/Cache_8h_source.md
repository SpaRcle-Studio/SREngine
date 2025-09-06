

# File Cache.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**Cache.h**](Cache_8h.md)

[Go to the documentation of this file](Cache_8h.md)


```C++
//
// Created by Monika on 05.09.2025.
//

#ifndef SR_ENGINE_GRAPHICS_SRSL_SHADER_CACHE_H
#define SR_ENGINE_GRAPHICS_SRSL_SHADER_CACHE_H

#include <Graphics/macros.h>

#include <Utils/FileSystem/Path.h>

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_HTYPES_NS {
    class Marshal;
}

namespace SR_SRSL_NS {
    class SRSLShader;

    class SRSLShaderCache : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::NonMovable {
    public:
        SRSLShaderCache() = delete;

    public:
        static void SaveShaderToCache(const SR_UTILS_NS::Path& cachePath, const SR_SRSL_NS::SRSLShader* pShader);
        static bool LoadShaderFromCache(const SR_UTILS_NS::Path &cachePath, SR_SRSL_NS::SRSLShader* pShader);

    };
}

namespace SR_GRAPH_NS {
    namespace Memory {
        struct ShaderUBOBlock;
    }

    class ShaderCache : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::NonMovable {
    public:
        ShaderCache() = delete;

    public:
        static void SaveShaderToCache(const SR_UTILS_NS::Path& cachePath, const  SR_GTYPES_NS::Shader* pShader);
        static bool LoadShaderFromCache(const SR_UTILS_NS::Path &cachePath,  SR_GTYPES_NS::Shader* pShader);

    private:
        static uint64_t GetVersion();

        static void SaveUBOBlock(SR_HTYPES_NS::Marshal& marshal, const Memory::ShaderUBOBlock& block);
        static void LoadUBOBlock(SR_HTYPES_NS::Marshal& marshal, Memory::ShaderUBOBlock& block);

    };
}

#endif //SR_ENGINE_GRAPHICS_SRSL_SHADER_CACHE_H
```


