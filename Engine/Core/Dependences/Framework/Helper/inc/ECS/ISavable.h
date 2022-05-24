//
// Created by Monika on 21.09.2021.
//

#ifndef GAMEENGINE_ISAVABLE_H
#define GAMEENGINE_ISAVABLE_H

#include <Types/Marshal.h>
#include <Xml.h>

namespace SR_UTILS_NS {
    typedef uint64_t SavableFlags;

    enum SavableFlagBits {
        SAVABLE_FLAG_NONE = 1 << 0,
        SAVABLE_FLAG_ECS_NO_ID = 1 << 1,
    };

    class ISavable {
    protected:
        ISavable();
        virtual ~ISavable();

    private:
        /// этот флаг означает, чтобыхотя-бы раз сохраняли этот объект
        bool m_onceSaved  = false;
        /// true - объект был загружен из-файла, false - объект был создан средствами движка
        bool m_isLoaded   = false;

    public:
        SR_NODISCARD virtual SR_HTYPES_NS::Marshal Save(SavableFlags flags) const {
            return SR_HTYPES_NS::Marshal();
        }

    };
}

#endif //GAMEENGINE_ISAVABLE_H
