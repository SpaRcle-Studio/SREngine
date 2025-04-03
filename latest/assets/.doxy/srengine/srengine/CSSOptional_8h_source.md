

# File CSSOptional.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Web**](dir_70f8c8659136766207f9e88b26ae6fb0.md) **>** [**CSS**](dir_c67fdec84752b754610b5eee0005e4af.md) **>** [**CSSOptional.h**](CSSOptional_8h.md)

[Go to the documentation of this file](CSSOptional_8h.md)


```C++
//
// Created by Monika on 20.08.2024.
//

#ifndef SR_COMMON_WEB_CSS_OPTIONAL_H
#define SR_COMMON_WEB_CSS_OPTIONAL_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS::Web {
    template<class T> class CSSOptional : public T {
    public:
        CSSOptional() = default;
        CSSOptional(const T& value) : T(value), m_isDefault(false) { } 
        CSSOptional(const T&& value) : T(value), m_isDefault(false) { } 
    public:
        template<typename Y> static CSSOptional CreateDefault(Y value) {
            CSSOptional<Y> result(value);
            result.SetAsDefault();
            return result;
        }

    public:
        SR_NODISCARD bool IsDefault() const { return m_isDefault; }
        void SetAsDefault() { m_isDefault = true; }

        SR_NODISCARD bool operator==(const CSSOptional& other) const {
            return static_cast<const T&>(*this) == static_cast<const T&>(other);
        }
        SR_NODISCARD bool operator!=(const CSSOptional& other) const {
            return static_cast<const T&>(*this) != static_cast<const T&>(other);
        }
        SR_NODISCARD bool operator==(const T& other) const {
            return static_cast<const T&>(*this) == other;
        }
        SR_NODISCARD bool operator!=(const T& other) const {
            return static_cast<const T&>(*this) != other;
        }

        SR_NODISCARD operator T() const { return static_cast<const T&>(*this); }

    protected:
        void OnChanged() final { m_isDefault = false; }

    private:
        bool m_isDefault = true;

    };

    template<typename T> class CSSOptionalEnumContainer {
    public:
        CSSOptionalEnumContainer() = default;
        CSSOptionalEnumContainer(const T& value) : value(value) { } 
        CSSOptionalEnumContainer(const T&& value) : value(value) { } 
        CSSOptionalEnumContainer(const CSSOptionalEnumContainer& other) : value(other.value) { }
        CSSOptionalEnumContainer(CSSOptionalEnumContainer&& other) noexcept : value(SR_EXCHANGE(other.value, { })) { }



        CSSOptionalEnumContainer& operator=(const CSSOptionalEnumContainer& other) {
            value = other.value;
            return *this;
        }

        CSSOptionalEnumContainer& operator=(CSSOptionalEnumContainer&& other) noexcept {
            value = SR_EXCHANGE(other.value, {});
            return *this;
        }

        CSSOptionalEnumContainer& operator=(const T& value) {
            this->value = value;
            return *this;
        }

        CSSOptionalEnumContainer& operator=(const T&& value) {
            this->value = value;
            return *this;
        }

        virtual ~CSSOptionalEnumContainer() = default;

        virtual void OnChanged() { }

    public:
        T value;

    };

    template<typename T> class CSSOptionalEnum : public CSSOptional<CSSOptionalEnumContainer<T>> {
        using ContainerT = CSSOptionalEnumContainer<T>;
        using Super = CSSOptional<ContainerT>;
    public:
        CSSOptionalEnum() = default;

        CSSOptionalEnum(const T& value) : Super(ContainerT(value)) { 
            static_cast<ContainerT&>(*this).OnChanged();
        }
        CSSOptionalEnum(const T&& value) : Super(ContainerT(value)) {  
            static_cast<ContainerT&>(*this).OnChanged();
        }

        CSSOptionalEnum(const CSSOptionalEnum& other) {
            static_cast<ContainerT&>(*this).value = other.value;
        }
        CSSOptionalEnum(CSSOptionalEnum&& other) noexcept {
            static_cast<ContainerT&>(*this).value = SR_EXCHANGE(other.value, {});
        }

        CSSOptionalEnum& operator=(const CSSOptionalEnum& other) {
            static_cast<ContainerT&>(*this).value = other.value;
            return *this;
        }
        CSSOptionalEnum& operator=(CSSOptionalEnum&& other) noexcept {
            static_cast<ContainerT&>(*this).value = SR_EXCHANGE(other.value, {});
            return *this;
        }

        CSSOptionalEnum& operator=(const T& value) {
            static_cast<ContainerT&>(*this).value = value;
            static_cast<ContainerT&>(*this).OnChanged();
            return *this;
        }

        CSSOptionalEnum& operator=(const T&& value) {
            static_cast<ContainerT&>(*this).value = value;
            static_cast<ContainerT&>(*this).OnChanged();
            return *this;
        }

        template<typename Y> static CSSOptionalEnum CreateDefault(Y value) {
            CSSOptionalEnum<Y> result(value);
            result.SetAsDefault();
            return result;
        }

        SR_NODISCARD bool operator==(const CSSOptionalEnum& other) const {
            return static_cast<const ContainerT&>(*this).value == static_cast<const ContainerT&>(other.value);
        }
        SR_NODISCARD bool operator!=(const CSSOptionalEnum& other) const {
            return static_cast<const ContainerT&>(*this).value != static_cast<const ContainerT&>(other.value);
        }
        SR_NODISCARD bool operator==(const T& other) const {
            return static_cast<const ContainerT&>(*this).value == other;
        }
        SR_NODISCARD bool operator!=(const T& other) const {
            return static_cast<const ContainerT&>(*this).value != other;
        }

        SR_NODISCARD operator T() const { return static_cast<const ContainerT&>(*this).value; }
    };
}

#endif //SR_COMMON_WEB_CSS_OPTIONAL_H
```


