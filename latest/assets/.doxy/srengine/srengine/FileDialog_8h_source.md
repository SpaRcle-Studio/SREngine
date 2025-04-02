

# File FileDialog.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**FileSystem**](dir_7528bfd63282bb3e25ecf9b22e573ae4.md) **>** [**FileDialog.h**](FileDialog_8h.md)

[Go to the documentation of this file](FileDialog_8h.md)


```C++
#ifndef SR_ENGINE_UTILS_FILE_DIALOG_H
#define SR_ENGINE_UTILS_FILE_DIALOG_H

#include <Utils/FileSystem/Path.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT FileDialog : public Singleton<FileDialog> {
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


