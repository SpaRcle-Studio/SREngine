//
// Created by Monika on 15.08.2023.
//

#ifndef SRENGINE_LOGICALMACHINE_H
#define SRENGINE_LOGICALMACHINE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Common/Hashes.h>
#include <Utils/ResourceManager/FileWatcher.h>

namespace SR_SRLM_NS {
    class LogicalNode;
    class DataType;
    class DataTypeStruct;

    class LogicalMachine : public SR_UTILS_NS::NonCopyable {
    public:
        SR_INLINE_STATIC uint16_t VERSION = 1000;

    public:
        bool Init();
        void Update(float_t dt);

    private:
        bool Execute(LogicalNode*& pNode, float_t dt);

    private:
        std::vector<LogicalNode*> m_nodes;
        std::vector<LogicalNode*> m_active;

        uint32_t m_currentNode = 0;

        std::map<std::string, LogicalNode*> m_entryPoints;
        std::map<std::string, std::pair<DataType*, std::vector<LogicalNode*>>> m_variables;

    };
}

#endif //SRENGINE_LOGICALMACHINE_H
