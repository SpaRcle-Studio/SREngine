

# File LogicalNodeManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**SRLM**](dir_ccfa529a2c413666958bcf1b1fc32cf9.md) **>** [**LogicalNodeManager.h**](LogicalNodeManager_8h.md)

[Go to the documentation of this file](LogicalNodeManager_8h.md)


```C++
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
```


