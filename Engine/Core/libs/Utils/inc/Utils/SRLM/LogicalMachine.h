//
// Created by Monika on 15.08.2023.
//

#ifndef SRENGINE_LOGICALMACHINE_H
#define SRENGINE_LOGICALMACHINE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Hashes.h>
#include <Utils/ResourceManager/IResource.h>
#include <Utils/ResourceManager/FileWatcher.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/SRLM/LogicalNode.h>
#include <Utils/Xml.h>

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

        pResource->SetId(path, false);

        if (!pResource->Reload()) {
            SR_ERROR("LogicalMachine::Load() : failed to load!");
            pResource->DeleteResource();
            return nullptr;
        }

        resourceManager.RegisterResource(pResource);

        return pResource;
    }
}

#endif //SRENGINE_LOGICALMACHINE_H
