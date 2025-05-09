

# File Value.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Reflection**](dir_a5a26934b95143030003946f011a899c.md) **>** [**Value.h**](Value_8h.md)

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

        SR_NODISCARD uint64_t Size() const { return m_storage.size(); }
        SR_NODISCARD bool Empty() const { return Size() == 0; }

    private:
        entt::meta_sequence_container m_storage;
    };


    class SR_COMMON_DLL_API SR_NODISCARD Value {
        friend ValueSequenceContainerIterator;
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

        SR_NODISCARD Value Ref();
        SR_NODISCARD Value Copy() const;

        SR_NODISCARD bool IsRef() const;
        SR_NODISCARD bool IsConst() const;

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
        SR_NODISCARD bool IsMathVector() const;
        SR_NODISCARD bool IsMathSize() const;
        SR_NODISCARD bool IsBool() const;
        SR_NODISCARD bool IsArithmetic() const;
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

    private:
        template<typename T> static void InitBase(Value& value);

    private:
        entt::meta_any m_storage;

    };


    template<typename T> void Value::InitBase(Value& value) {
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
    }

    template<typename T> Value Value::Create(T&& value) {
        auto&& reflected = Value(entt::meta_any(std::forward<T>(value)));
        InitBase<T>(reflected);
        return std::move(reflected);
    }

    template<typename T> Value Value::CreateRef(T& value) {
        auto&& reflected = Value(entt::meta_any::create_ref(value));
        InitBase<T>(reflected);
        return std::move(reflected);
    }

    template<typename T> Value Value::CreateCRef(const T& value) {
        auto&& reflected = Value(entt::meta_any::create_cref(value));
        InitBase<T>(reflected);
        return std::move(reflected);
    }
}

#endif //SR_UTILS_TYPE_TRAITS_VALUE_H
```


