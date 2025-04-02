

# File ResourceEmbedder.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Resources**](dir_324d400546bb3f221a744d7d2624d5c6.md) **>** [**ResourceEmbedder.h**](ResourceEmbedder_8h.md)

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
        static ResourceEmbedder& Instance() {
            static ResourceEmbedder instance;
            return instance;
        }

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


