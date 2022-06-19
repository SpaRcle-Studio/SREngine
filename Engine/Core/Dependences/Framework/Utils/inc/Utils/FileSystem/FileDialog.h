#ifndef UTILS_DILEDIALOG_H
#define UTILS_DILEDIALOG_H

#include <Utils/FileSystem/Path.h>
#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT FileDialog : public Singleton<FileDialog> {
        friend class Singleton<FileDialog>;
        using Filter = std::vector<std::pair<std::string, std::string>>;
    protected:
        ~FileDialog() override = default;

    public:
        SR_NODISCARD Path OpenDialog(const Path& defaultPath, const Filter& filter) const;
        SR_NODISCARD Path SaveDialog(const Path& defaultPath, const Filter& filter) const;

    protected:
        void InitSingleton() override;
        void OnSingletonDestroy() override;

    };
}

#endif // UTILS_DILEDIALOG