

# File StoreUtils.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**StoreUtils.h**](StoreUtils_8h.md)

[Go to the documentation of this file](StoreUtils_8h.md)


```C++
//
// Created by Monika on 02.02.2025.
//

#ifndef SR_ENGINE_UTILS_STORE_UTILS_H
#define SR_ENGINE_UTILS_STORE_UTILS_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>
#include <Utils/TypeTraits/TypeTraits.h>

namespace SR_UTILS_NS::StoreUtils {
    class Storage : public Singleton<Storage> {
        SR_REGISTER_SINGLETON(Storage)
    public:
        enum class StorageType {
            Temp, User
        };
        enum class ValueType {
            AnyType,
            Float,
            Int,
            Bool,
            String
        };
    private:
        union Value {
            float_t f;
            bool b;
            int64_t i;
            std::string* s;
        };

        template<typename T> static T& VisitValue(Value& value) {
            using Type = SR_UTILS_NS::RemoveQualifiersT<T>;

            if constexpr (std::is_same_v<Type, float_t>) {
                return value.f;
            }
            else if constexpr (std::is_same_v<Type, int64_t>) {
                return value.i;
            }
            else if constexpr (std::is_same_v<Type, bool>) {
                return value.b;
            }
            else if constexpr (std::is_same_v<Type, std::string>) {
                if (!value.s) {
                    value.s = new std::string();
                }
                return *value.s;
            }
            else {
                static_assert(SR_UTILS_NS::AlwaysFalseV<T>, "Unsupported type!");
            }
        }

        struct ValueHolder {
            Value value;
            ValueType type;

            ValueHolder();
            ValueHolder(Value val, ValueType type);
            ValueHolder(const ValueHolder& other);
            ValueHolder(ValueHolder&& other) noexcept;
            ValueHolder& operator=(const ValueHolder& other);
            ValueHolder& operator=(ValueHolder&& other) noexcept;
            ~ValueHolder();
        };
    public:
        void Clear() { m_storage.clear(); }
        void Save();
        void Load();

        SR_NODISCARD bool Has(StorageType storageTepe, ValueType valueType, SR_UTILS_NS::StringAtom key);
        bool Drop(StorageType storageTepe, SR_UTILS_NS::StringAtom key);

        template<typename T> SR_NODISCARD T Get(StorageType storageTepe, ValueType valueType, SR_UTILS_NS::StringAtom key, const std::optional<T>& def = std::nullopt);
        template<typename T> void Set(StorageType storageTepe, ValueType valueType, SR_UTILS_NS::StringAtom key, T value);

    private:
        SR_NODISCARD Value GetImpl(StorageType storageTepe, ValueType valueType, SR_UTILS_NS::StringAtom key, const std::optional<Value>& def);
        void SetImpl(StorageType storageTepe, ValueType valueType, SR_UTILS_NS::StringAtom key, Value value);

    private:
        std::map<StorageType, std::unordered_map<SR_UTILS_NS::StringAtom, ValueHolder>> m_storage;

    };

    template <typename T> T Storage::Get(const StorageType storageTepe, const ValueType valueType, const StringAtom key, const std::optional<T>& def) {
        if (!def) {
            Value result = GetImpl(storageTepe, valueType, key, std::nullopt);
            return VisitValue<T>(result);
        }

        Value valueDef{};
        VisitValue<T>(valueDef) = def.value();

        Value result = GetImpl(storageTepe, valueType, key, valueDef);
        return VisitValue<T>(result);
    }

    template <typename T> void Storage::Set(const StorageType storageTepe, const ValueType valueType, const StringAtom key, T value) {
        Value val{};
        VisitValue<T>(val) = value;
        SetImpl(storageTepe, valueType, key, val);
    }

    template<Storage::StorageType storeType> class Template {
    public:
        Template() = delete;
        ~Template() = delete;

    public:
        SR_NODISCARD static bool Has(SR_UTILS_NS::StringAtom key, Storage::ValueType type = Storage::ValueType::AnyType) {
            return Storage::Instance().Has(storeType, type, key);
        }


        SR_NODISCARD static bool HasFloat(SR_UTILS_NS::StringAtom key) { return Has(key, Storage::ValueType::Float); }
        SR_NODISCARD static float_t GetFloat(SR_UTILS_NS::StringAtom key, const std::optional<float_t>& def = std::nullopt) {
            return Storage::Instance().Get<float_t>(storeType, Storage::ValueType::Float, key, def);
        }
        static void SetFloat(SR_UTILS_NS::StringAtom key, float_t value) {
            Storage::Instance().Set(storeType, Storage::ValueType::Float, key, value);
        }


        SR_NODISCARD static bool HasBool(SR_UTILS_NS::StringAtom key) { return Has(key, Storage::ValueType::Bool); }
        SR_NODISCARD static bool GetBool(SR_UTILS_NS::StringAtom key, const std::optional<bool>& def = std::nullopt) {
            return Storage::Instance().Get<bool>(storeType, Storage::ValueType::Bool, key, def);
        }
        static void SetBool(SR_UTILS_NS::StringAtom key, bool value) {
            Storage::Instance().Set(storeType, Storage::ValueType::Bool, key, value);
        }


        SR_NODISCARD static bool HasInt(SR_UTILS_NS::StringAtom key) { return Has(key, Storage::ValueType::Int); }
        SR_NODISCARD static int64_t GetInt(SR_UTILS_NS::StringAtom key, const std::optional<int64_t>& def = std::nullopt) {
            return Storage::Instance().Get<int64_t>(storeType, Storage::ValueType::Int, key, def);
        }
        static void SetInt(SR_UTILS_NS::StringAtom key, int64_t value) {
            Storage::Instance().Set(storeType, Storage::ValueType::Int, key, value);
        }


        SR_NODISCARD static bool HasString(SR_UTILS_NS::StringAtom key) { return Has(key, Storage::ValueType::String); }
        SR_NODISCARD static std::string GetString(SR_UTILS_NS::StringAtom key, const std::optional<std::string>& def = std::nullopt) {
            return Storage::Instance().Get<std::string>(storeType, Storage::ValueType::String, key, def);
        }
        static void SetString(SR_UTILS_NS::StringAtom key, const std::string& value) {
            Storage::Instance().Set(storeType, Storage::ValueType::String, key, value);
        }

    };

    using Temp = Template<Storage::StorageType::Temp>;
    using User = Template<Storage::StorageType::User>;
}

#endif //SR_ENGINE_UTILS_STORE_UTILS_H
```


