//
// Created by Monika on 30.08.2023.
//

#include <Utils/SRLM/LogicalNodeManager.h>

namespace SR_SRLM_NS {
    LogicalNode* LogicalNodeManager::CreateByName(LogicalNodeManager::Hash hashName) {
        if (auto&& pIt = m_constructors.find(hashName); pIt != m_constructors.end()) {
            return pIt->second.constructor();
        }

        SRHalt("Node not found! Hash name: \"" + SR_UTILS_NS::ToString(hashName) + "\"");
        return nullptr;
    }

    LogicalNode* LogicalNodeManager::CreateByName(const std::string& name) {
        return CreateByName(SR_HASH_STR_REGISTER(name));
    }

    bool LogicalNodeManager::Register(Hash hashName, const Constructor& constructor, const Category& category) {
        auto&& info = m_constructors[hashName];
        info.constructor = constructor;
        info.category = category;
        return true;
    }
}