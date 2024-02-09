//
// Created by Drakeme on 24/01/2024.
//

#ifndef SRENGINE_LOCALIZATIONMANAGER_H
#define SRENGINE_LOCALIZATIONMANAGER_H

///#include <Graphics/Font/ITextComponent.h>
#include <Utils/Types/UnicodeString.h>

namespace SR_CORE_NS {
    class Engine;
}

namespace SR_HTYPES_NS {
    class UnicodeString;
}

namespace SR_GTYPES_NS {
    class ITextComponent;
}

namespace SR_UTILS_NS::Localization {
    ///TODO: стоит ли Locale делать через enum или следует использовать коды типа "en"
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
        std::unordered_map<StringAtom, SR_HTYPES_NS::UnicodeString> m_locStrings = { }; ///first - id, second - UnicodeString for string itself
        ///TODO: Использование UnicodeString(u32string) является избыточным, можно продумать смену локали с UTF8
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
        ///using LocalizedTextComponent = SR_GTYPES_NS::ITextComponent*;
    public:
        ///void RegisterTextComponent(std::string& id, SR_GTYPES_NS::ITextComponent* textComponent);
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
        ///std::set<LocalizedTextComponent> m_textComponents = { };
        std::unordered_map<StringAtom, LocalizationFile> m_localizationFiles = { };
        std::unordered_map<StringAtom, std::vector<LocalizationFile*>> m_localizationGroups = { };
    };

}

#endif //SRENGINE_LOCALIZATIONMANAGER_H
