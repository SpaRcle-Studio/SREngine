//
// Created by Monika on 30.08.2023.
//

#include <Utils/SRLM/LogicalNodeManager.h>

namespace SR_SRLM_NS {
    LogicalNode* LogicalNodeManager::CreateByName(LogicalNodeManager::Hash hashName) {
        return nullptr;
    }

    LogicalNode* LogicalNodeManager::CreateByName(const std::string& name) {
        return nullptr;
    }

    bool LogicalNodeManager::Register(Hash hashName, const Constructor& constructor, const Category& category) {
        auto&& info = m_constructors[hashName];
        info.constructor = constructor;
        info.category = category;
        return true;
    }
}