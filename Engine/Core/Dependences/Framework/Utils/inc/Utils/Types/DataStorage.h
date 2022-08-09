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

        DataStorage() = default;
        ~DataStorage() override = default;

        DataStorage(DataStorage &&data) noexcept {
            m_pointers = std::exchange(data.m_pointers, {});
            m_values = std::exchange(data.m_values, {});
        }

        DataStorage &operator=(DataStorage &&data) noexcept {
            m_pointers = std::exchange(data.m_pointers, {});
            m_values = std::exchange(data.m_values, {});
            return *this;
        }

    public:
        template<typename T> void SetPointer(const std::string& name, T* pointer);
        template<typename T> void SetPointer(T* pointer);

        template<typename T> void SetValue(const std::string& name, const T& value);
        template<typename T> void SetValue(const T& value);

        template<typename T> T* GetPointer(const std::string& name) const;
        template<typename T> T* GetPointer() const;

        template<typename T> T* GetPointerDef(const std::string& name, T* def) const;
        template<typename T> T* GetPointerDef(T* def) const;

        template<typename T> T GetValue(const std::string& name) const;
        template<typename T> T GetValue() const;

        template<typename T> T GetValueDef(const std::string& name, const T& def) const;
        template<typename T> T GetValueDef(const T& def) const;

        template<typename T> bool RemoveValue(const std::string& name);
        template<typename T> bool RemoveValue();

        void Clear() {
            m_pointers.clear();
            m_values.clear();
        }

    private:
        std::unordered_map<std::string, void*> m_pointers;
        std::unordered_map<std::string, std::any> m_values;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    template<typename T> void DataStorage::SetPointer(const std::string &name, T *pointer) {
        if (!(m_pointers[name] = reinterpret_cast<void*>(pointer))) {
            SR_ERROR("DataStorage::SetPointer() : invalid pointer! Name: " + name);
        }
    }

    template<typename T> void DataStorage::SetPointer(T *pointer) {
        SetPointer(typeid(T).name(), pointer);
    }

    template<typename T> T *DataStorage::GetPointer(const std::string &name) const  {
        if (m_pointers.count(name) == 0) {
            SRHalt("DataStorage::GetPointer() : pointer not found! Name: " + name);
            return nullptr;
        }

        if (T* ptr = reinterpret_cast<T*>(m_pointers.at(name)))
            return ptr;

        SRHalt("DataStorage::GetPointer() : invalid pointer! Name: " + name);

        return nullptr;
    }

    template<typename T> T *DataStorage::GetPointer() const {
        return GetPointer<T>(typeid(T).name());
    }

    template<typename T> void DataStorage::SetValue(const std::string &name, const T &value) {
        m_values[name] = value;
    }

    template<typename T> void DataStorage::SetValue(const T &value) {
        SetValue(typeid(T).name(), value);
    }

    template<typename T> T DataStorage::GetValue(const std::string &name) const {
        if (m_values.count(name) == 0) {
            SRHalt("DataStorage::GetValue() : value not found! Name: " + name);
            return T();
        }

        try {
            return std::any_cast<T>(m_values.at(name));
        }
        catch (const std::bad_any_cast& e) {
            SRHalt("DataStorage::GetValue() : bad cast! Name: " + name);
            return T();
        }
    }

    template<typename T> T DataStorage::GetValue() const {
        return GetValue<T>(typeid(T).name());
    }

    template<typename T> T DataStorage::GetValueDef(const std::string &name, const T& def) const {
        if (m_values.count(name) == 0) {
            return def;
        }

        try {
            return std::any_cast<T>(m_values.at(name));
        }
        catch (const std::bad_any_cast& e) {
            SRHalt("DataStorage::GetValue() : bad cast! Name: " + name);
            return def;
        }
    }

    template<typename T> T DataStorage::GetValueDef(const T& def) const {
        return GetValueDef<T>(typeid(T).name(), def);
    }

    template<typename T> bool DataStorage::RemoveValue(const std::string &name) {
        if (m_values.count(name) == 0) {
            return false;
        }

        m_values.erase(name);

        return true;
    }

    template<typename T> bool DataStorage::RemoveValue() {
        return RemoveValue<T>(typeid(T).name());
    }

    template<typename T> T *DataStorage::GetPointerDef(const std::string &name, T *def) const {
        if (m_pointers.count(name) == 0) {
            return def;
        }

        if (T* ptr = reinterpret_cast<T*>(m_pointers.at(name)))
            return ptr;

        SR_ERROR("DataStorage::GetPointerDef() : invalid pointer! Name: " + name);

        return def;
    }

    template<typename T> T *DataStorage::GetPointerDef(T *def) const {
        return GetPointerDef<T>(typeid(T).name(), def);
    }
}

#endif //SRENGINE_DATASTORAGE_H
