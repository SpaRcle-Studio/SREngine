//
// Created by Monika on 21.09.2021.
//

#ifndef GAMEENGINE_ISAVABLE_H
#define GAMEENGINE_ISAVABLE_H

#include <string>
#include <cctype>
#include <mutex>

#include <Xml.h>
#include <Types/Marshal.h>

namespace Framework::Helper {
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
        [[nodiscard]] virtual MarshalEncodeNode Save(SavableFlags flags) const {
            return MarshalEncodeNode();
        }

    };
}

#endif //GAMEENGINE_ISAVABLE_H
