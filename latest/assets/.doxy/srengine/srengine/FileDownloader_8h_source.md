

# File FileDownloader.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Network**](dir_c7b83f1df097df65b63198ef53f0d275.md) **>** [**FileDownloader.h**](FileDownloader_8h.md)

[Go to the documentation of this file](FileDownloader_8h.md)


```C++
//
// Created by Monika on 31.03.2025.
//

#ifndef SR_ENGINE_UTILS_NETWORK_FILE_DOWNLOADER_H
#define SR_ENGINE_UTILS_NETWORK_FILE_DOWNLOADER_H

#include <Utils/Common/Singleton.h>

namespace SR_NETWORK_NS {
    class FileDownloader : public SR_UTILS_NS::Singleton<FileDownloader> {
        SR_REGISTER_SINGLETON(FileDownloader)
        using Super = SR_UTILS_NS::Singleton<FileDownloader>;
    public:
        SR_NODISCARD bool DownloadFile(const std::string& url, const SR_UTILS_NS::Path& filePath);

    };
}

#endif //SR_ENGINE_UTILS_NETWORK_FILE_DOWNLOADER_H
```


