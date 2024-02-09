//
// Created by Drakeme on 24/01/2024.
//

#include <Utils/Localization/LocalizationManager.h>
#include <rapidyaml/src/ryml.hpp>
#include <rapidyaml/src/ryml_std.hpp> ///needed to use rapidyaml with std containers
#include <utility>

namespace SR_UTILS_NS::Localization {

    LocalizationFile::LocalizationFile(const std::unordered_map<Locale, Path>& localePaths, const Locale& languageToLoad) {
        m_localePaths = localePaths;
        LoadLocalizationStrings(m_localePaths[languageToLoad]);

        //localizationStrings.insert();
    }

    LocalizationFile::~LocalizationFile() {
        //m_watchedFile ///TODO: Что делать с FileWatcher
    }

    void LocalizationFile::LoadLocalizationStrings(const Path& filePath) {
        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();
        m_watchedFile = resourceManager.StartWatch(filePath);
        std::string fileContents = FileSystem::ReadAllText(filePath.ToString());
        ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(fileContents));
        ryml::ConstNodeRef root = tree.crootref();
        for (auto&& n : root.children()) {
            std::string id; ///это должен был быть StringAtom
            std::string str; ///это должен был быть UnicodeString
            n >> ryml::key(id); ///deserialize key
            n >> str; ///deserialize value
            m_locStrings[id] = str; ///но операторы десериализации делают всё сложнее
            ///альтернативой десериализации может быть закидывание в конструктор std::string двух указателей на начало и конец val() или key() или что-то в подобном роде
            ///пример auto id = std::string(locFile.key().data(), locFile.key().end());
        }
    }

    void LocalizationFile::SwitchFileByLocale(const Locale& newLocale) {
        if (m_localePaths.contains(newLocale)) {
            LoadLocalizationStrings(m_localePaths[newLocale]);
        }
        else {
            SR_WARN("LocalizationFile::SwitchFileByLocale() : Chosen locale is not supported by file! Locale code: %i"); ///TODO: SR_FORMAT locale code
        }
    }

    SR_HTYPES_NS::UnicodeString LocalizationFile::GetStringById(const StringAtom &id) {
        return m_locStrings[id];
    }

    /*LocalizationGroup::LocalizationGroup(const std::list<LocalizationFile>& locFiles) :
        m_locFiles(locFiles)
    { }

    void LocalizationGroup::AddLocFile(const LocalizationFile& locFile) {
        m_locFiles.emplace_back(locFile);
    }

    void LocalizationGroup::ChangeLocale(Locale newLocale) {
        for (auto&& locFile : m_locFiles) {
            locFile.SwitchFileByLocale(newLocale);
        }
    }

    LocalizationGroup::~LocalizationGroup() {
        ///
    } */

    void LocalizationManager::MakeLocGroup(std::unordered_map<StringAtom, LocalizationFile>& locFiles,
                                           const StringAtom& groupId) {
        std::vector<LocalizationFile*> localizationGroup;
        localizationGroup.reserve(locFiles.size());
        for (auto&& file : locFiles) {
            localizationGroup.emplace_back(&file.second);
            m_localizationFiles.insert(std::move(file));
        }
        m_localizationGroups[groupId] = std::move(localizationGroup);
    }

    void LocalizationManager::RegisterLocGroup(const std::vector<StringAtom> &locFileIds, const StringAtom &groupId) {
        std::vector<LocalizationFile*> locFiles = { };
        locFiles.reserve(locFileIds.size());
        for (auto&& id : locFileIds) {
            locFiles.emplace_back(&m_localizationFiles[id]);
        }
        m_localizationGroups[groupId] = std::move(locFiles);
    }

    void LocalizationManager::RemoveLocGroup(const StringAtom& id) {
        m_localizationGroups.erase(id);
        ///TODO: что делать с файлами в m_localizationGroups
    }

    void LocalizationManager::ChangeLocGroupLocale(const StringAtom& id, const Locale& newLocale) {
        for (auto&& file : m_localizationGroups[id]) {
            file->SwitchFileByLocale(newLocale);
        }
    }

    void LocalizationManager::AddLocFileIntoGroup(const StringAtom &fileId, const StringAtom &groupId) {

    }

    void LocalizationManager::RemoveLocFileFromGroup(const StringAtom &fileId, const StringAtom &groupId) {

    }

    StringAtom LocalizationManager::MakeLocFile(const std::unordered_map<Locale, Path>& localePaths,
                                                const Locale& languageToLoad,
                                                StringAtom fileId) {
        LocalizationFile locFile = LocalizationFile(localePaths, languageToLoad);
        m_localizationFiles[fileId] = locFile;
        return fileId;
    }

    void LocalizationManager::LoadInfoAsConfigFile(const SpaRcle::Utils::Path &filePath) {
        Path resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        std::string fileContents = FileSystem::ReadAllText(filePath.ToString());
        ryml::Tree tree = ryml::parse_in_place(fileContents.data());
        ryml::ConstNodeRef root = tree.crootref();

        for (auto&& locGroup : root.children()) {
            std::vector<StringAtom> locFileIds;
            locFileIds.reserve(locGroup.num_children());

            for (auto&& locFile : locGroup.children()) {
                Locale languageToLoad;
                locFile[0] >> ryml::key(languageToLoad);
                std::unordered_map<Locale, Path> localePaths;

                for (auto&& localePath : locFile) {
                    std::string path;
                    std::string locale;
                    localePath >> path;
                    localePath >> ryml::key(locale);
                    localePaths[locale] = resourcesFolder.Concat(path);
                }

                std::string id = std::string(locFile.key().data(), locFile.key().end());
                locFileIds.emplace_back(MakeLocFile(localePaths, languageToLoad, id));
            }

            RegisterLocGroup(locFileIds, locGroup.key().data());
        }
    }

    //void LocalizationManager::RegisterTextComponent(std::string &id,
    //                                                SR_GTYPES_NS::ITextComponent *textComponent) {
    //    m_textComponents.insert(textComponent);
    //}
}
