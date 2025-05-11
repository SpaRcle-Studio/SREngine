

# File LogicalNodeManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**SRLM**](dir_a6f28b551a04c8f6c9ec3f9b059c2feb.md) **>** [**LogicalNodeManager.h**](LogicalNodeManager_8h.md)

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


