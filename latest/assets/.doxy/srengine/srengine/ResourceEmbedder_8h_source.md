

# File ResourceEmbedder.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**ResourceEmbedder.h**](ResourceEmbedder_8h.md)

[Go to the documentation of this file](ResourceEmbedder_8h.md)


```C++
//
// Created by innerviewer on 2024-03-24.
//

#ifndef SR_ENGINE_RESOURCEEMBEDDER_H
#define SR_ENGINE_RESOURCEEMBEDDER_H

#include <Utils/stdInclude.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Map.h>

namespace SR_UTILS_NS {
    class ResourceEmbedder {
        struct Resource {
            std::string_view compressedHex;
            uint64_t decompressedSize = 0;
        };
    public:
        static ResourceEmbedder& Instance();

    public:
        template<class T> bool RegisterResource() {
            Resource resource;
            resource.compressedHex = std::string_view(T::data, T::compressedSize);
            resource.decompressedSize = T::decompressedSize;
            m_resources[T::path] = resource;
            return true;
        }

        bool ExportAllResources();
        bool ExportAllResources(const SR_UTILS_NS::Path& newDirectory);

        static bool ExportToFile(std::string_view path, const Resource& resource, const SR_UTILS_NS::Path& newDirectory);
        bool ExportToFile(const SR_UTILS_NS::Path& path);

        static bool ExportToMemory(std::string_view data);

    private:
        SR_NODISCARD static std::string HexToBytes(const std::string_view& hex);
        SR_NODISCARD static std::string Decompress(const Resource& resource);

    private:
        ska::flat_hash_map<std::string_view, Resource> m_resources;
    };
}

#endif //SR_ENGINE_RESOURCEEMBEDDER_H
```


