

# File FileDialog.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**FileSystem**](dir_4f99f6be72c0abf8a55fac20395de74b.md) **>** [**FileDialog.h**](FileDialog_8h.md)

[Go to the documentation of this file](FileDialog_8h.md)


```C++
#ifndef SR_ENGINE_UTILS_FILE_DIALOG_H
#define SR_ENGINE_UTILS_FILE_DIALOG_H

#include <Utils/FileSystem/Path.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API FileDialog : public Singleton<FileDialog> {
        SR_REGISTER_SINGLETON(FileDialog)
        using Filter = std::vector<std::pair<StringAtom, StringAtom>>;
    protected:
        ~FileDialog() override = default;

    public:
        SR_NODISCARD Path OpenDialog(const Path& defaultPath, const Filter& filter) const;
        SR_NODISCARD Path SaveDialog(const Path& defaultPath, const Filter& filter) const;
        SR_NODISCARD Path PickFolder(const Path& defaultPath) const;

    protected:
        void InitSingleton() override;
        void OnSingletonDestroy() override;

    };
}

#endif // SR_ENGINE_UTILS_FILE_DIALOG_H
```


