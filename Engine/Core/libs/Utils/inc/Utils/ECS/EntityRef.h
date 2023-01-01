//
// Created by Monika on 26.11.2022.
//

#ifndef SRENGINE_ENTITYREF_H
#define SRENGINE_ENTITYREF_H

#include <Utils/ECS/EntityRefUtils.h>

namespace SR_UTILS_NS {
    class EntityRef {
    public:
        SR_ENUM_CLASS_T(Mode, uint8_t, Absolute, Relative);
    public:
        EntityRef();
        EntityRef(EntityRef&& other) noexcept;

    private:
        Mode m_mode = Mode::Absolute;

    };
}

#endif //SRENGINE_ENTITYREF_H
