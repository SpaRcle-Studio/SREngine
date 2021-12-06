//
// Created by Monika on 21.09.2021.
//

#ifndef GAMEENGINE_ISAVABLE_H
#define GAMEENGINE_ISAVABLE_H

#include <set>
#include <string>
#include <cctype>
#include <mutex>
#include <Types/SafePointer.h>
#include <Xml.h>

namespace Framework::Helper {
    class ISavable {
    protected:
        ISavable();
        ~ISavable();
    private:
        static std::set<uint64_t> g_entities;
        static std::mutex g_mutex;
    private:
        /// этот флаг означает, чтобыхотя-бы раз сохраняли этот объект
        bool m_onceSaved  = false;
        /// true - объект был загружен из-файла, false - объект был создан средствами движка
        bool m_isLoaded   = false;
        bool m_hasChanges = false;
        uint64_t m_id     = 0;
    public:
        virtual Xml::Document Save() = 0;
        virtual bool Load(const Xml::Document& xml) = 0;
    };
}

#endif //GAMEENGINE_ISAVABLE_H
