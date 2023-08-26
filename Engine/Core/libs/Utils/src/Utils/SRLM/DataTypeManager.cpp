//
// Created by Monika on 26.08.2023.
//

#include <Utils/SRLM/DataTypeManager.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Xml.h>

namespace SR_SRLM_NS {
    DataType* DataTypeManager::CreateByName(uint64_t hashName) {
        SR_LOCK_GUARD;

        SRAssert(hashName != DataTypeStruct::HASH_NAME);

        if (auto&& pData = DataTypeAllocator::Instance().Allocate(hashName)) {
            return pData;
        }

        if (auto&& pIt = m_structs.find(hashName); pIt != m_structs.end()) {
            return pIt->second->Copy();
        }

        if (auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(hashName)) {
            return new DataTypeEnum(0, pReflector);
        }

        if (auto&& pIt = m_strings.find(hashName); pIt != m_strings.end()) {
            SR_ERROR("DataTypeManager::CreateByName() : failed to create \"" + pIt->second + "\"!");
        }
        else {
            SRHalt("Type by hash \"" + SR_UTILS_NS::ToString(hashName) + "\" not found!");
        }

        return nullptr;
    }

    const std::string& DataTypeManager::HashToString(uint64_t hash) const {
        SR_LOCK_GUARD;
        static std::string gDefault;
        if (auto&& pIt = m_strings.find(hash); pIt != m_strings.end()) {
            return pIt->second;
        }
        return gDefault;
    }

    void DataTypeManager::Clear() {
        SR_LOCK_GUARD;

        m_strings.clear();

        for (auto&& [hash, pData] : m_structs) {
            delete pData;
        }
        m_structs.clear();
    }

    void DataTypeManager::ReloadSettings() {
        SR_LOCK_GUARD;

        auto&& xmlDocument = SR_XML_NS::Document::Load(m_watcher->GetPath());
        if (!xmlDocument.Valid()) {
            SR_ERROR("DataTypeManager::ReloadSettings() : failed to read xml!\n\tPath: " + m_watcher->GetPath().ToStringRef());
            return;
        }

        auto&& xmlRoot = xmlDocument.Root();

        for (auto&& xmlStruct : xmlRoot.GetNodes("Struct")) {
            auto&& structHash = SR_HASH_STR(xmlStruct.Name());
            m_strings[structHash] = xmlStruct.Name();

            auto&& pStruct = m_structs[structHash] = new DataTypeStruct(structHash);

            for (auto&& xmlVar : xmlStruct.GetNodes()) {
                auto&& varName = xmlVar.GetAttribute("Name");

                auto&& nameHash = SR_HASH_STR(varName.ToString());
                m_strings[nameHash] = varName.ToString();

                auto&& typeHash = SR_HASH_STR(xmlVar.Name());
                m_strings[typeHash] = xmlVar.Name();

                if (auto&& pData = CreateByName(typeHash)) {
                    pStruct->AddVariable(nameHash, pData);
                }
            }
        }
    }

    void DataTypeManager::OnSingletonDestroy() {
        Singleton::OnSingletonDestroy();

        if (m_watcher) {
            m_watcher->Stop();
        }
    }

    void DataTypeManager::InitSingleton() {
        Singleton::InitSingleton();

        m_watcher = SR_UTILS_NS::ResourceManager::Instance().StartWatch(
                SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Configs/SRLMTypes.xml")
        );

        m_watcher->SetCallBack([this](FileWatcher* pWatcher) {
            ReloadSettings();
        });
    }
}