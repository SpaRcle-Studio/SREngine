

# File Compression.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**Compression.h**](Compression_8h.md)

[Go to the documentation of this file](Compression_8h.md)


```C++
//
// Created by innerviewer on 2024-04-10.
//
#ifndef SRCOMMON_COMPRESSION_H
#define SRCOMMON_COMPRESSION_H

#include <Utils/FileSystem/Path.h>

#include <zlib/zlib.h>
#include <zlib/contrib/minizip/unzip.h>

namespace SR_UTILS_NS {
    /*SR_ENUM_NS_CLASS_T(ArchiveFormat, uint8_t,
        z, zip);*/

    class Compression {
    public:
        Compression() = delete;
        ~Compression() = delete;

    public:
        /*static bool Create(const Path& source, const Path& destination) {
            return true;
        }

        static bool Unzip(const Path& source, const Path& destination) {
            if (!source.Exists() || !destination.Exists()) {
                SR_ERROR("Compression::Unzip() : either source or destination path does not exist.");
                return false;
            }

            auto&& zipFile = unzOpen(source.c_str());
            if (!zipFile) {
                SR_ERROR("Compression::Unzip() : failed to open zip file.");
                return false;
            }

            unz_global_info globalInfo;
            if (unzGetGlobalInfo(zipFile, &globalInfo) != UNZ_OK) {
                SR_ERROR("Compression::Unzip(): could not read file global info.");
                unzClose(zipFile);
                return false;
            }

            unzClose(zipFile);
            return true;
        }*/
    };
}

#endif //SRCOMMON_COMPRESSION_H
```


