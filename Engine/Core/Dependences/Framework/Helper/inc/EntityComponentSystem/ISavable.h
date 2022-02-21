//
// Created by Monika on 21.09.2021.
//

#ifndef GAMEENGINE_ISAVABLE_H
#define GAMEENGINE_ISAVABLE_H

#include <string>
#include <cctype>
#include <mutex>
#include <Xml.h>

namespace Framework::Helper {
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
        [[nodiscard]] virtual Xml::Document Save() const { return Xml::Document::New(); }

    };
}

#endif //GAMEENGINE_ISAVABLE_H
