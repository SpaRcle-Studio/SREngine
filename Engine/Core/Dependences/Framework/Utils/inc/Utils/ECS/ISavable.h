//
// Created by Monika on 21.09.2021.
//

#ifndef GAMEENGINE_ISAVABLE_H
#define GAMEENGINE_ISAVABLE_H

#include <Utils/Types/Marshal.h>
#include <Utils/Xml.h>

namespace SR_UTILS_NS {
    typedef uint64_t SavableFlags;

    enum SavableFlagBits {
        SAVABLE_FLAG_NONE = 1 << 0,
        SAVABLE_FLAG_ECS_NO_ID = 1 << 1,
    };

    class SR_DLL_EXPORT ISavable {
    protected:
        ISavable() = default;
        virtual ~ISavable() = default;

    public:
        SR_NODISCARD virtual SR_HTYPES_NS::Marshal Save(SavableFlags flags) const {
            return SR_HTYPES_NS::Marshal();
        }

    };
}

#endif //GAMEENGINE_ISAVABLE_H
