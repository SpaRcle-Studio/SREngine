//
// Created by Monika on 30.08.2023.
//

#include <Utils/SRLM/LogicalNodeManager.h>
#include <Utils/SRLM/DataTypeManager.h>
#include <Utils/SRLM/LogicalNodes.h>

namespace SR_SRLM_NS {
    template<typename T> void LogicalNodeManagerRegisterType(const std::vector<std::string>& category) {
        LogicalNodeManager::Instance().Register(T::HASH_NAME, []() -> LogicalNode* {
            auto&& pConstructorNode = new ConstructorNode();
            pConstructorNode->SetInitTypeHashName(T::HASH_NAME);
            return (LogicalNode*)pConstructorNode;
        }, category);
    }

    void LogicalNodeManager::InitializeTypes() {
        LogicalNodeManagerRegisterType<DataTypeInt8>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeInt16>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeInt32>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeInt64>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeUInt8>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeUInt16>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeUInt32>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeUInt64>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeFloat>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeDouble>({ "Math", "Types" });
        LogicalNodeManagerRegisterType<DataTypeString>({ "Base", "Types" });
        LogicalNodeManagerRegisterType<DataTypeBool>({ "Logic" });

        for (auto&& [hashName, pReflector] : SR_UTILS_NS::EnumReflectorManager::Instance().GetReflectors()) {
            LogicalNodeManager::Instance().Register(hashName, [hashName]() -> LogicalNode* {
                auto&& pConstructorNode = new ConstructorNode();
                pConstructorNode->SetInitTypeHashName(hashName);
                return (LogicalNode*)pConstructorNode;
            }, { "Enum" });
        }
    }

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