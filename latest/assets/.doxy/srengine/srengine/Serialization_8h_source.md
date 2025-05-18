

# File Serialization.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**Serialization.h**](Serialization_8h.md)

[Go to the documentation of this file](Serialization_8h.md)


```C++
//
// Created by Monika on 16.10.2024.
//

#ifndef SR_COMMON_TYPE_TRAITS_SERIALIZATION_H
#define SR_COMMON_TYPE_TRAITS_SERIALIZATION_H

#include <Utils/Serialization/Serializer.h>
#include <Utils/Serialization/Deserializer.h>
#include <Utils/Serialization/ObjectDataAccessor.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/Types/UnicodeString.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Math/Size.h>
#include <Utils/Math/Rect.h>
#include <Utils/Common/StringAtomLiterals.h>

#include <Codegen/Enums.generated.hpp>

namespace SR_UTILS_NS {
    class Serializable;

    template<class T>
    using HasMethodEmptyT = decltype(std::declval<const T&>().empty());

    template<typename T>
    struct SerializationTraits
    {
        static constexpr bool HasEmpty = IsDetectedV<HasMethodEmptyT, T>;
        static constexpr bool IsSerializable = std::is_base_of_v<SR_UTILS_NS::Serializable, T>;
    };

    template<typename T, typename Enable = void> struct DefaultChecker {
        using IsAlwaysFalse = std::true_type;

        static bool IsDefault(const T&) { return false; }
    };

    namespace Details {
        template<typename T>
        using IsDefaultCheckerAlwaysFalseT = typename DefaultChecker<T>::IsAlwaysFalse;

        template<typename T>
        using ReserveMethodT = decltype(std::declval<T>().reserve(size_t()));
    }

    template<typename T> SR_INLINE bool IsDefault(const T& value) {
        return DefaultChecker<T>::IsDefault(value);
    }

    template<typename T>
    SR_INLINE constexpr bool IsDefaultCheckerAlwaysFalse = DetectedOrT<std::false_type, Details::IsDefaultCheckerAlwaysFalseT, T>::value;


    #include <Utils/Serialization/DefaultObjectMakers.inl.h>

    #include <Utils/Serialization/SaveCheckers.inl.h>

    namespace Serialization {
        template<typename T> bool IsValidValue(const T& value) {
            if constexpr (CheckOperatorUsableV<CheckerEqualityComparable, T, std::nullptr_t>) {
                return value != nullptr;
            }
            else {
                SR_IGNORE_UNUSED(value);
                return true;
            }
        }

        template<typename T> bool CanBeSaved(const T& value) {
            return SR_UTILS_NS::SaveChecker<T>::CanBeSaved(value);
        }

        template<typename T> void Save(ISerializer& serializer, const T& value, const SerializationId& key) {
            if (!CanBeSaved(value)) {
                return;
            }
            SR_UTILS_NS::ObjectDataAccessor<T>::Save(serializer, value, key);
        }

        template<typename T> void SaveCheckDefault(ISerializer& serializer, const T& value, const SerializationId& key) {
            if (!serializer.IsWriteDefaults() && IsDefault(value)) {
                return;
            }
            Save(serializer, value, key);
        }

        template<typename T> bool Load(IDeserializer& deserializer, T& value, const SerializationId& key) {
            if (!deserializer.IsDefault(key)) {
                ObjectDataAccessor<T>::Load(deserializer, value, key);
                return true;
            }

            if constexpr (DefaultObjectMaker<T>::value) {
                if (deserializer.ShouldSetDefaults(key)) {
                    DefaultObjectMaker<T>::MakeDefault(value);
                }
            }
            return false;
        }
    }


    #include <Utils/Serialization/DefaultCheckers.inl.h>


    #include <Utils/Serialization/ObjectDataAccessors.inl.h>
}

#endif //SR_COMMON_TYPE_TRAITS_SERIALIZATION_H
```


