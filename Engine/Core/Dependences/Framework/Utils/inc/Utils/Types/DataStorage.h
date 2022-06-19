//
// Created by Monika on 21.02.2022.
//

#ifndef SRENGINE_DATASTORAGE_H
#define SRENGINE_DATASTORAGE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Debug.h>

namespace SR_HTYPES_NS {
    class SR_DLL_EXPORT DataStorage : public NonCopyable {
    public:
        using Ptr = DataStorage*;

        ~DataStorage() override = default;

    public:
        template<typename T> void SetPointer(const std::string& name, T* pointer) {
            if (!(m_pointers[name] = reinterpret_cast<void*>(pointer))) {
                SR_ERROR("DataStorage::SetPointer() : invalid pointer! Name: " + name);
            }
        }

        template<typename T> void SetPointer(T* pointer) {
            SetPointer(typeid(T).name(), pointer);
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

        template<typename T> T* GetPointer() const {
            return GetPointer<T>(typeid(T).name());
        }

        void Clear() {
            m_pointers.clear();
        }

    private:
        std::unordered_map<std::string, void*> m_pointers;

    };
}

#endif //SRENGINE_DATASTORAGE_H
