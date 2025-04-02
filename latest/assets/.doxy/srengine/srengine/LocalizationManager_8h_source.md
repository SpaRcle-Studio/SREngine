

# File LocalizationManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Localization**](dir_a49f0db6b4130ce5cf0adc29f1f90718.md) **>** [**LocalizationManager.h**](LocalizationManager_8h.md)

[Go to the documentation of this file](LocalizationManager_8h.md)


```C++
//
// Created by innerviewer on 2024-03-17.
//
#ifndef SR_ENGINE_LOCALIZATIONMANAGER_H
#define SR_ENGINE_LOCALIZATIONMANAGER_H

#include <Utils/Types/UnicodeString.h>
#include <Utils/Resources/FileWatcher.h>

namespace SR_CORE_NS {
    class Engine;
}

namespace SR_HTYPES_NS {
    class UnicodeString;
}

namespace SR_GTYPES_NS {
    //class ITextComponent;
}

namespace SR_UTILS_NS::Localization {
    using Locale = std::string;
    /*SR_ENUM_NS_CLASS(Locale,
                     None,
                     English,
                     Russian)*/

    class LocalizationFile {
    public:
        LocalizationFile() = default;
        ~LocalizationFile();
        LocalizationFile(const std::unordered_map<Locale, Path>& localePaths, const Locale& languageToLoad);
        void SwitchFileByLocale(const Locale& newLocale);
        void LoadLocalizationStrings(const Path& filePath);
        SR_HTYPES_NS::UnicodeString GetStringById(const StringAtom& id);
    private:
        std::unordered_map<Locale, Path> m_localePaths = { };
        FileWatcher::Ptr m_watchedFile = nullptr;
        std::unordered_map<StringAtom, SR_HTYPES_NS::UnicodeString> m_locStrings = { }; 
    };

    /*class LocalizationGroup {
    public:
        LocalizationGroup() = default;
        ~LocalizationGroup();
        explicit LocalizationGroup(const std::list<LocalizationFile>& locFiles);
        void ChangeLocale(Locale newLocale);
        void AddLocFile(const LocalizationFile& locFile);
        void RemoveLocFile(const StringAtom& id);
    private:
        std::list<LocalizationFile> m_locFiles = { };
    };*/

    class LocalizationManager {
    public:
        StringAtom MakeLocFile(const std::unordered_map<Locale, Path>& localePaths, const Locale& languageToLoad, StringAtom fileId);
        void MakeLocGroup(std::unordered_map<StringAtom, LocalizationFile>& locFiles, const StringAtom& groupId);
        void RegisterLocGroup(const std::vector<StringAtom>& locFileIds, const StringAtom& groupId);
        void RemoveLocGroup(const StringAtom& groupId);
        void RemoveLocFileFromGroup(const StringAtom& fileId, const StringAtom& groupId);
        void AddLocFileIntoGroup(const StringAtom& fileId, const StringAtom& groupId);
        void ChangeLocGroupLocale(const StringAtom& id, const Locale& newLocale);
        std::vector<StringAtom> GetLocGroupsIds();

        void SaveInfoAsConfigFile(const SR_UTILS_NS::Path& filePath);
        void LoadInfoAsConfigFile(const SR_UTILS_NS::Path& filePath);

    private:
        std::unordered_map<StringAtom, LocalizationFile> m_localizationFiles = { };
        std::unordered_map<StringAtom, std::vector<LocalizationFile*>> m_localizationGroups = { };
    };

}

#endif //SR_ENGINE_LOCALIZATIONMANAGER_H
```


