

# File LogicalMachine.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**SRLM**](dir_ccfa529a2c413666958bcf1b1fc32cf9.md) **>** [**LogicalMachine.h**](LogicalMachine_8h.md)

[Go to the documentation of this file](LogicalMachine_8h.md)


```C++
//
// Created by Monika on 15.08.2023.
//

#ifndef SR_ENGINE_LOGICALMACHINE_H
#define SR_ENGINE_LOGICALMACHINE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Resources/IResource.h>
#include <Utils/Resources/FileWatcher.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/SRLM/LogicalNode.h>
#include <Utils/Resources/Xml.h>

namespace SR_SRLM_NS {
    class DataType;
    class DataTypeStruct;

    class LogicalMachine : public SR_UTILS_NS::IResource {
        using Super = SR_UTILS_NS::IResource;
    public:
        SR_INLINE_STATIC uint16_t VERSION = 1000;

    public:
        LogicalMachine();
        ~LogicalMachine() override;

    public:
        template<class T = LogicalMachine> SR_NODISCARD static LogicalMachine* Load(const SR_UTILS_NS::Path& rawPath);

        bool Init();
        virtual void UpdateMachine(float_t dt);

    private:
        SR_NODISCARD IResource* CopyResource(SR_UTILS_NS::IResource* pDestination) const override;

        bool Execute(float_t dt);
        void AddNode(LogicalNode* pNode);
        void Optimize();
        bool ProcessExecutable(float_t dt);
        bool ProcessReset(float_t dt);

        void SetCurrentNode(LogicalNode* pNode, LogicalNode::NodePin* pFromPin);

        SR_NODISCARD LogicalNode* GetCurrentNode() const;
        SR_NODISCARD LogicalNode::NodePin* GetCurrentPin() const;

        bool Load() override;
        bool Unload() override;

        void Clear();

    private:
        std::vector<LogicalNode*> m_nodes;

        struct ActiveNodeInfo {
            LogicalNode* pNode = nullptr;
            LogicalNode::NodePin* pFromPin = nullptr;
        };

        std::vector<ActiveNodeInfo> m_active;

        uint32_t m_currentNode = 0;

        std::map<std::string, LogicalNode*> m_entryPoints;

    };

    template<class T> LogicalMachine* LogicalMachine::Load(const Path& rawPath) {
        if (!rawPath.Exists()) {
            SR_ERROR("LogicalMachine::Load() : file not exists! Path: " + rawPath.ToStringRef());
            return nullptr;
        }

        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();
        SR_UTILS_NS::Path&& path = rawPath.RemoveSubPath(resourceManager.GetResPath());

        auto&& pResource = new T();

        pResource->SetId(path.ToStringRef(), false);

        if (!pResource->Reload()) {
            SR_ERROR("LogicalMachine::Load() : failed to load!");
            pResource->DeleteResource();
            return nullptr;
        }

        resourceManager.RegisterResource(pResource);

        return pResource;
    }
}

#endif //SR_ENGINE_LOGICALMACHINE_H
```


