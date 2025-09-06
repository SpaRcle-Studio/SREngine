

# File DataStorage.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**DataStorage.h**](DataStorage_8h.md)

[Go to the documentation of this file](DataStorage_8h.md)


```C++
//
// Created by Monika on 21.02.2022.
//

#ifndef SR_ENGINE_DATASTORAGE_H
#define SR_ENGINE_DATASTORAGE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/HashManager.h>
#include <Utils/Debug.h>

namespace SR_HTYPES_NS {
    class SR_COMMON_DLL_API DataStorage : public NonCopyable {
    public:
        using Ptr = DataStorage*;

        DataStorage();
        ~DataStorage() override;

        DataStorage(DataStorage &&data) noexcept;
        DataStorage &operator=(DataStorage &&data) noexcept;

    public:
        template<typename T> void SetPointer(const std::string& name, T* pointer);
        template<typename T> void SetPointer(T* pointer);

        template<typename T> void SetValue(const std::string& name, const T& value);
        template<typename T> void SetValue(const T& value);

        template<typename T> T* GetPointer(const std::string& name) const;
        template<typename T> T* GetPointer() const;

        template<typename T> T* GetPointerDef(const std::string& name, T* def) const;
        template<typename T> T* GetPointerDef(T* def) const;

        template<typename T> T GetValue(const char* name) const;

        template<typename T> T GetValue(const std::string& name) const;
        template<typename T> T GetValue() const;

        template<typename T> T GetValueDef(const std::string& name, const T& def) const;
        template<typename T> T GetValueDef(const T& def) const;

        template<typename T> bool RemovePointer();
        template<typename T> bool RemovePointer(const std::string& name);

        template<typename T> bool RemoveValue();
        template<typename T> bool RemoveValue(const std::string& name);

        template<typename T> std::vector<std::pair<std::string, T>> GetValues();

        void Clear();

    private:
        template<typename T> void SetPointer(uint64_t hashCode, T* pointer);
        template<typename T> void SetValue(uint64_t hashCode, const T& value);

        template<typename T> T* GetPointer(uint64_t hashCode) const;
        template<typename T> T* GetPointerDef(uint64_t hashCode, T* def) const;

        template<typename T> T GetValue(uint64_t hashCode) const;
        template<typename T> T GetValueDef(uint64_t hashCode, const T& def) const;

        template<typename T> bool RemovePointer(uint64_t hashCode);
        template<typename T> bool RemoveValue(uint64_t hashCode);

    private:
        std::map<uint64_t, void*> m_pointers;
        std::map<uint64_t, std::any> m_values;

    };


    template<typename T> void DataStorage::SetPointer(const std::string& name, T* pPointer) {
        SR_TRACY_ZONE;
        SetPointer(SR_HASH_STR_REGISTER(name), pPointer);
    }

    template<typename T> void DataStorage::SetPointer(T* pPointer) {
        SR_TRACY_ZONE;
        SetPointer(SR_HASH_TYPE_NAME_STR_REGISTER(T), pPointer);
    }

    template<typename T> T *DataStorage::GetPointer(const std::string& name) const  {
        SR_TRACY_ZONE;
        return GetPointer<T>(SR_HASH_STR_REGISTER(name));
    }

    template<typename T> T *DataStorage::GetPointer() const {
        SR_TRACY_ZONE;
        return GetPointer<T>(SR_HASH_TYPE_NAME_STR_REGISTER(T));
    }

    template<typename T> void DataStorage::SetValue(const std::string &name, const T &value) {
        SR_TRACY_ZONE;
        SetValue(SR_HASH_STR_REGISTER(name), value);
    }

    template<typename T> void DataStorage::SetValue(const T &value) {
        SR_TRACY_ZONE;
        SetValue(SR_HASH_TYPE_NAME_STR_REGISTER(T), value);
    }

    template<typename T> T DataStorage::GetValue(const char* name) const {
        SR_TRACY_ZONE;
        return GetValue<T>(SR_HASH_STR_REGISTER(name));
    }

    template<typename T> T DataStorage::GetValue(const std::string& name) const {
        SR_TRACY_ZONE;
        return GetValue<T>(SR_HASH_STR_REGISTER(name));
    }

    template<typename T> T DataStorage::GetValue() const {
        SR_TRACY_ZONE;
        return GetValue<T>(SR_HASH_TYPE_NAME_STR_REGISTER(T));
    }

    template<typename T> T DataStorage::GetValueDef(const std::string& name, const T& def) const {
        SR_TRACY_ZONE;
        return GetValueDef<T>(SR_HASH_STR_REGISTER(name), def);
    }

    template<typename T> T DataStorage::GetValueDef(const T& def) const {
        SR_TRACY_ZONE;
        return GetValueDef<T>(SR_HASH_TYPE_NAME_STR_REGISTER(T), def);
    }

    template<typename T> T *DataStorage::GetPointerDef(const std::string& name, T *def) const {
        SR_TRACY_ZONE;
        return GetPointerDef<T>(SR_HASH_STR_REGISTER(name), def);
    }

    template<typename T> T *DataStorage::GetPointerDef(T *def) const {
        SR_TRACY_ZONE;
        return GetPointerDef<T>(SR_HASH_TYPE_NAME_STR_REGISTER(T), def);
    }

    template<typename T> bool DataStorage::RemovePointer() {
        SR_TRACY_ZONE;
        return RemovePointer<T>(SR_HASH_TYPE_NAME_STR_REGISTER(T));
    }

    template<typename T> bool DataStorage::RemovePointer(const std::string& name) {
        SR_TRACY_ZONE;
        return RemovePointer<T>(SR_HASH_STR_REGISTER(name));
    }

    template<typename T> bool DataStorage::RemoveValue(const std::string& name) {
        SR_TRACY_ZONE;
        return RemoveValue<T>(SR_HASH_STR_REGISTER(name));
    }

    template<typename T> bool DataStorage::RemoveValue() {
        SR_TRACY_ZONE;
        return RemoveValue<T>(SR_HASH_TYPE_NAME_STR_REGISTER(T));
    }


    template<typename T> void DataStorage::SetPointer(uint64_t hashCore, T *pointer) {
        if (!(m_pointers[hashCore] = reinterpret_cast<void*>(pointer))) {
            SR_ERROR("DataStorage::SetPointer() : invalid pointer!");
        }
    }

    template<typename T> void DataStorage::SetValue(uint64_t hashCode, const T &value) {
        m_values[hashCode] = value;
    }

    template<typename T> T *DataStorage::GetPointer(uint64_t hashCode) const {
        if (m_pointers.count(hashCode) == 0) {
            SRHalt("DataStorage::GetPointer() : pointer not found!");
            return nullptr;
        }

        if (T* ptr = reinterpret_cast<T*>(m_pointers.at(hashCode))) {
            return ptr;
        }

        SRHalt("DataStorage::GetPointer() : invalid pointer!");

        return nullptr;
    }

    template<typename T> T *DataStorage::GetPointerDef(uint64_t hashCode, T *def) const {
        if (m_pointers.count(hashCode) == 0) {
            return def;
        }

        if (T* ptr = reinterpret_cast<T*>(m_pointers.at(hashCode)))
            return ptr;

        SR_ERROR("DataStorage::GetPointerDef() : invalid pointer!");

        return def;
    }

    template<typename T> T DataStorage::GetValue(uint64_t hashCode) const {
        if (m_values.count(hashCode) == 0) {
            SRHalt("DataStorage::GetValue() : value not found!");
            return T();
        }

        try {
            return std::any_cast<T>(m_values.at(hashCode));
        }
        catch (const std::bad_any_cast& e) {
            SRHalt("DataStorage::GetValue() : bad cast!");
            return T();
        }
    }

    template<typename T> T DataStorage::GetValueDef(uint64_t hashCode, const T &def) const {
        if (m_values.count(hashCode) == 0) {
            return def;
        }

        try {
            return std::any_cast<T>(m_values.at(hashCode));
        }
        catch (const std::bad_any_cast& e) {
            SRHalt("DataStorage::GetValueDef() : bad cast!");
            return def;
        }

    }

    template<typename T> bool DataStorage::RemovePointer(uint64_t hashCode) {
        if (m_pointers.count(hashCode) == 0) {
            return false;
        }

        m_pointers.erase(hashCode);

        return true;
    }

    template<typename T> bool DataStorage::RemoveValue(uint64_t hashCode) {
        if (m_values.count(hashCode) == 0) {
            return false;
        }

        m_values.erase(hashCode);

        return true;
    }

    template<typename T> std::vector<std::pair<std::string, T>> DataStorage::GetValues() {
        std::vector<std::pair<std::string, T>> values;

        for (auto&& [hash, any] : m_values) {
            try {
                auto&& type = std::any_cast<T>(any);
                values.emplace_back(std::make_pair(SR_HASH_TO_STR(hash), type));
            }
            catch (const std::bad_any_cast& e) {
                continue;
            }
        }

        return values;
    }
}

#endif //SR_ENGINE_DATASTORAGE_H
```


