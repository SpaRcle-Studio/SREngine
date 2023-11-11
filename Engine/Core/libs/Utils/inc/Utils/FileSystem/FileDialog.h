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