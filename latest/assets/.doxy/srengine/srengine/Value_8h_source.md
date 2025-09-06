

# File Value.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Reflection**](dir_b9e652b456a4d9b315741a759a2b0c5c.md) **>** [**Value.h**](Value_8h.md)

[Go to the documentation of this file](Value_8h.md)


```C++
//
// Created by Monika on 20.01.2025.
//

#ifndef SR_UTILS_TYPE_TRAITS_VALUE_H
#define SR_UTILS_TYPE_TRAITS_VALUE_H

#include <Utils/Reflection/ValueImpl.h>
#include <Utils/Types/SharedPtr.h>

#include <entt/entt.hpp>

namespace SR_UTILS_NS::Reflection {
    class Value;
    class ValueSequenceContainer;
    class ValueAssociativeContainer;

    class ValueSequenceContainerIterator {
        friend ValueSequenceContainer;
    private:
        explicit ValueSequenceContainerIterator(entt::meta_sequence_container::iterator&& iterator)
            : m_iterator(std::move(iterator))
        { }

    public:
        ValueSequenceContainerIterator& operator++() noexcept { ++m_iterator; return *this; }
        ValueSequenceContainerIterator& operator--() noexcept { --m_iterator; return *this; }

        ValueSequenceContainerIterator operator++(int32_t value) noexcept {
            ValueSequenceContainerIterator orig = *this;
            ++m_iterator;
            return orig;
        }

        ValueSequenceContainerIterator operator--(int32_t value) noexcept {
            ValueSequenceContainerIterator orig = *this;
            --m_iterator;
            return orig;
        }

        SR_NODISCARD Value operator*() const;
        SR_NODISCARD InputIteratorPointer<Value> operator->() const;

        SR_NODISCARD operator bool() const noexcept { return static_cast<bool>(m_iterator); } 

        SR_NODISCARD bool operator==(const ValueSequenceContainerIterator& other) const noexcept {
            return m_iterator == other.m_iterator;
        }

        SR_NODISCARD bool operator!=(const ValueSequenceContainerIterator& other) const noexcept {
            return !(*this == other);
        }

    private:
        entt::meta_sequence_container::iterator m_iterator;

    };

    class ValueAssociativeContainerIterator {
        friend ValueAssociativeContainer;
    private:
        explicit ValueAssociativeContainerIterator(entt::meta_associative_container::iterator&& iterator)
            : m_iterator(std::move(iterator))
        { }

    public:
        ValueAssociativeContainerIterator& operator++() noexcept { ++m_iterator; return *this; }

        ValueAssociativeContainerIterator operator++(int32_t value) noexcept {
            ValueAssociativeContainerIterator orig = *this;
            ++m_iterator;
            return orig;
        }

        SR_NODISCARD Value First() const;
        SR_NODISCARD Value Second() const;

        SR_NODISCARD operator bool() const noexcept { return static_cast<bool>(m_iterator); } 

        SR_NODISCARD bool operator==(const ValueAssociativeContainerIterator& other) const noexcept {
            return m_iterator == other.m_iterator;
        }

        SR_NODISCARD bool operator!=(const ValueAssociativeContainerIterator& other) const noexcept {
            return !(*this == other);
        }

    private:
        entt::meta_associative_container::iterator m_iterator;

    };

    class SR_COMMON_DLL_API SR_NODISCARD ValueAssociativeContainer {
        friend Value;
    private:
        explicit ValueAssociativeContainer(entt::meta_associative_container&& storage)
            : m_storage(storage)
        { }

    public:
        SR_NODISCARD ValueAssociativeContainerIterator begin() { return ValueAssociativeContainerIterator(m_storage.begin()); }
        SR_NODISCARD ValueAssociativeContainerIterator end() { return ValueAssociativeContainerIterator(m_storage.end()); }

        void Clear();
        void Reserve(uint64_t size);

        void Erase(const Value& key);

        SR_NODISCARD Value GetKeyType() const;
        SR_NODISCARD Value GetValueType() const;
        SR_NODISCARD Value GetMappedType() const;

        SR_NODISCARD uint64_t Size() const { return m_storage.size(); }
        SR_NODISCARD bool Empty() const { return Size() == 0; }

        bool Insert(const Value& key, const Value& value);

    private:
        entt::meta_associative_container m_storage;
    };

    class SR_COMMON_DLL_API SR_NODISCARD ValueSequenceContainer {
        friend Value;
    private:
        explicit ValueSequenceContainer(entt::meta_sequence_container&& storage)
            : m_storage(storage)
        { }

    public:
        SR_NODISCARD ValueSequenceContainerIterator begin() { return ValueSequenceContainerIterator(m_storage.begin()); }
        SR_NODISCARD ValueSequenceContainerIterator end() { return ValueSequenceContainerIterator(m_storage.end()); }

        void Clear();
        void Resize(uint64_t size);
        void Reserve(uint64_t size);

        ValueSequenceContainerIterator Erase(ValueSequenceContainerIterator it) {
            return ValueSequenceContainerIterator(m_storage.erase(it.m_iterator));
        }

        ValueSequenceContainerIterator Insert(ValueSequenceContainerIterator it, Value value);

        SR_NODISCARD uint64_t Size() const { return m_storage.size(); }
        SR_NODISCARD bool Empty() const { return Size() == 0; }

    private:
        entt::meta_sequence_container m_storage;
    };


    class SR_COMMON_DLL_API SR_NODISCARD Value {
        friend ValueSequenceContainerIterator;
        friend ValueAssociativeContainerIterator;
        friend ValueAssociativeContainer;
        friend ValueSequenceContainer;
        using SRClassGetterFn = SRClass*(*)(const Value&);
        using SRClassSetterFn = void(*)(Value&, SRClass*);
    private:
        explicit Value(entt::meta_any&& storage);

    public:
        Value();
        Value(const Value& other);
        Value& operator=(const Value& other) noexcept;
        Value& operator=(Value&& other) noexcept;
        ~Value();

        template<typename T> static Value Create(T&& value);
        template<typename T> static Value CreateRef(T& value);
        template<typename T> static Value CreateCRef(const T& value);

        template<typename T> const T* TryCast() const { return m_storage.try_cast<T>(); }
        template<typename T> T* TryCast() { return m_storage.try_cast<T>(); }

        Value& Detach();
        Value& DetachIfConst();

        SR_NODISCARD ValueSequenceContainer AsSequenceContainer();
        SR_NODISCARD ValueSequenceContainer AsSequenceContainer() const;

        SR_NODISCARD ValueAssociativeContainer AsAssociativeContainer();
        SR_NODISCARD ValueAssociativeContainer AsAssociativeContainer() const;

        SR_NODISCARD Value Ref();
        SR_NODISCARD Value Copy() const;

        SR_NODISCARD bool IsRef() const;
        SR_NODISCARD bool IsConst() const;
        SR_NODISCARD bool IsEmbedded() const;
        SR_NODISCARD bool IsDynamic() const;

        SR_NODISCARD bool IsSequenceContainer() const;
        SR_NODISCARD bool IsAssociativeContainer() const;
        SR_NODISCARD bool IsBitMap() const;

        SR_NODISCARD bool IsSmartPtr() const;
        SR_NODISCARD bool IsPointer() const;
        SR_NODISCARD bool IsString() const;
        SR_NODISCARD bool IsStringView() const;
        SR_NODISCARD bool IsStringAtom() const;
        SR_NODISCARD bool IsUnicodeString() const;
        SR_NODISCARD bool IsPath() const;
        SR_NODISCARD bool IsRect() const;
        SR_NODISCARD bool IsFColor() const;
        SR_NODISCARD bool IsMathVector() const;
        SR_NODISCARD bool IsMathSize() const;
        SR_NODISCARD bool IsBool() const;
        SR_NODISCARD bool IsArithmetic() const;
        SR_NODISCARD bool IsOptional() const;
        SR_NODISCARD bool IsClass() const;
        SR_NODISCARD bool IsTemplate() const;
        SR_NODISCARD bool IsIntegral() const;
        SR_NODISCARD bool IsSigned() const;
        SR_NODISCARD bool IsEnum() const;
        SR_NODISCARD std::string_view GetTypeName() const;
        SR_NODISCARD std::string_view GetSharedPtrType() const;
        SR_NODISCARD uint64_t SizeOf() const;
        SR_NODISCARD void* Data();
        SR_NODISCARD const void* Data() const;
        SR_NODISCARD std::string_view GetEnumType() const;
        SR_NODISCARD SRClass* GetSRClass() const;
        SR_NODISCARD SR_HTYPES_NS::SharedPtrBase* GetSharedPtrBase() const;

        SR_NODISCARD operator bool() const noexcept; 

    //private:
    //    template<typename T> static void InitBase(Value& value);

    private:
        entt::meta_any m_storage;

    };


    //template<typename T> void Value::InitBase(Value& value) {
        /*if constexpr (IsSharedPointerV<T>) {
            value.m_SRClassGetter = [](const Value& value) -> SRClass* {
                if (auto&& pData = value.TryCast<T>()) {
                    return const_cast<SRClass*>(dynamic_cast<const SRClass*>((*pData).Get()));
                }
                return nullptr;
            };

            if constexpr (!std::is_abstract_v<T>) {
                value.m_SRClassSetter = [](Value& value, SRClass* pSRClass) {
                    value.m_storage = entt::meta_any(*(dynamic_cast<T*>(pSRClass)));
                };
            }
        }
        else if constexpr (std::is_base_of_v<SRClass, T> || std::is_same_v<SRClass, T>) {
            value.m_SRClassGetter = [](const Value& value) -> SRClass* {
                if (auto&& pData = value.TryCast<T>()) {
                    return const_cast<SRClass*>(dynamic_cast<const SRClass*>(pData));
                }
                return nullptr;
            };
        }*/
    //}

    template<typename T> Value Value::Create(T&& value) {
        return Value(entt::meta_any(std::forward<T>(value)));
        //auto&& reflected = Value(entt::meta_any(std::forward<T>(value)));
        //InitBase<T>(reflected);
        //return std::move(reflected);
    }

    template<typename T> Value Value::CreateRef(T& value) {
        return Value(entt::meta_any::create_ref(value));
        //auto&& reflected = Value(entt::meta_any::create_ref(value));
        //InitBase<T>(reflected);
        //return std::move(reflected);
    }

    template<typename T> Value Value::CreateCRef(const T& value) {
        return Value(entt::meta_any::create_cref(value));
        //auto&& reflected = Value(entt::meta_any::create_cref(value));
        //InitBase<T>(reflected);
        //return std::move(reflected);
    }
}

#endif //SR_UTILS_TYPE_TRAITS_VALUE_H
```


