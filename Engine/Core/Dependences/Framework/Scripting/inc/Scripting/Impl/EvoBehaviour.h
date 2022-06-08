//
// Created by Monika on 24.05.2022.
//

#ifndef SRENGINE_EVOBEHAVIOUR_H
#define SRENGINE_EVOBEHAVIOUR_H

#include <Scripting/Base/Behaviour.h>

namespace SR_SCRIPTING_NS {
    class EvoBehaviour : public SR_SCRIPTING_NS::Behaviour {
    private:
        ~EvoBehaviour() override = default;

    protected:
        bool Load() override;
        bool Unload() override;
        SR_NODISCARD uint64_t GetFileHash() const override;

    private:
        EvoScript::Script* m_script = nullptr;

    };
}

#endif //SRENGINE_EVOBEHAVIOUR_H
