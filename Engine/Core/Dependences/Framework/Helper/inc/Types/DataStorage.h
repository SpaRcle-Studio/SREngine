//
// Created by Monika on 21.02.2022.
//

#ifndef SRENGINE_DATASTORAGE_H
#define SRENGINE_DATASTORAGE_H

#include <string>
#include <unordered_map>

#include <Debug.h>
#include <Utils/NonCopyable.h>

namespace Framework::Helper::Types {
    class DataStorage : public NonCopyable {
    public:
        ~DataStorage() override = default;

    public:
        template<typename T> void SetPointer(const std::string& name, T* pointer) {
            if (!(m_pointers[name] = reinterpret_cast<void*>(pointer))) {
                SR_ERROR("DataStorage::SetPointer() : invalid pointer! Name: " + name);
            }
        }

        template<typename T> T* GetPointer(const std::string& name) const {
            if (m_pointers.count(name) == 0) {
                SR_ERROR("DataStorage::GetPointer() : pointer not found! Name: " + name);
                return nullptr;
            }

            if (T* ptr = reinterpret_cast<T*>(m_pointers.at(name)))
                return ptr;

            SR_ERROR("DataStorage::GetPointer() : invalid pointer! Name: " + name);

            return nullptr;
        }

        void Clear() {
            m_pointers.clear();
        }

    private:
        std::unordered_map<std::string, void*> m_pointers;

    };
}

#endif //SRENGINE_DATASTORAGE_H
