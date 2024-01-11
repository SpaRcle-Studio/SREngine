//
// Created by Monika on 30.08.2023.
//

#ifndef SR_ENGINE_LOGICALNODEMANAGER_H
#define SR_ENGINE_LOGICALNODEMANAGER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Types/Function.h>

namespace SR_SRLM_NS {
    class ConstructorNode;
    class LogicalNode;

    class LogicalNodeManager : public SR_UTILS_NS::Singleton<LogicalNodeManager> {
        SR_REGISTER_SINGLETON(LogicalNodeManager)
        using Hash = uint64_t;
        using Constructor = SR_HTYPES_NS::Function<LogicalNode*()>;
        using Category = std::vector<std::string>;
        struct NodeInfo {
            Constructor constructor;
            Category category;
        };
        using NodeConstructors = std::unordered_map<Hash, NodeInfo>;
    public:
        SR_NODISCARD bool IsSingletonCanBeDestroyed() const override {
            return false;
        }

        SR_NODISCARD const NodeConstructors& GetNodeConstructors() { return m_constructors; }
        SR_NODISCARD LogicalNode* CreateByName(Hash hashName);
        SR_NODISCARD LogicalNode* CreateByName(const std::string& name);

        bool Register(Hash hashName, const Constructor& constructor, const Category& category);

        void InitializeTypes();

    private:
        NodeConstructors m_constructors;

    };
}

#endif //SR_ENGINE_LOGICALNODEMANAGER_H
