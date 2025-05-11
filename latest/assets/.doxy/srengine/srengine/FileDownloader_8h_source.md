

# File FileDownloader.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Network**](dir_fcfa5bace1b3a12e3000ff4cad4809c8.md) **>** [**FileDownloader.h**](FileDownloader_8h.md)

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


