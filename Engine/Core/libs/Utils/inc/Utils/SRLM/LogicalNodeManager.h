//
// Created by Monika on 30.08.2023.
//

#ifndef SRENGINE_LOGICALNODEMANAGER_H
#define SRENGINE_LOGICALNODEMANAGER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Types/Function.h>

namespace SR_SRLM_NS {
    class LogicalNode;

    class LogicalNodeManager : public SR_UTILS_NS::Singleton<LogicalNodeManager> {
        friend class SR_UTILS_NS::Singleton<LogicalNodeManager>;
        using Hash = uint64_t;
        using NodeConstructors = std::unordered_map<Hash, SR_HTYPES_NS::Function<LogicalNode*()>>;
    public:
        SR_NODISCARD LogicalNode* CreateByName(Hash hashName);
        SR_NODISCARD LogicalNode* CreateByName(const std::string& name);

    private:
        NodeConstructors m_constructors;

    };
}

#endif //SRENGINE_LOGICALNODEMANAGER_H
