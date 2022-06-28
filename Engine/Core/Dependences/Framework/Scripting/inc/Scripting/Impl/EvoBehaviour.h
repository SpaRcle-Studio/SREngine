//
// Created by Monika on 24.05.2022.
//

#ifndef SRENGINE_EVOBEHAVIOUR_H
#define SRENGINE_EVOBEHAVIOUR_H

#include <Scripting/Base/Behaviour.h>

namespace SR_SCRIPTING_NS {
    class EvoBehaviour : public SR_SCRIPTING_NS::Behaviour {
        using Properties = std::vector<std::string>;
    private:
        ~EvoBehaviour() override = default;

    public:
        Properties GetProperties() const override;
        std::any GetProperty(const std::string& id) const override;
        void SetProperty(const std::string& id, const std::any& val) override;

    protected:
        bool Load() override;
        bool Unload() override;
        SR_NODISCARD uint64_t GetFileHash() const override;

    private:
        void InitHooks();

    private:
        EvoScript::Script* m_script = nullptr;

        EvoScript::Typedefs::InitBehaviourFnPtr m_initBehaviour = nullptr;
        EvoScript::Typedefs::ReleaseBehaviourFnPtr m_releaseBehaviour = nullptr;
        EvoScript::Typedefs::GetPropertiesFnPtr m_getProperties = nullptr;
        EvoScript::Typedefs::GetPropertyFnPtr m_getProperty = nullptr;
        EvoScript::Typedefs::SetPropertyFnPtr m_setProperty = nullptr;

    };
}

#endif //SRENGINE_EVOBEHAVIOUR_H
