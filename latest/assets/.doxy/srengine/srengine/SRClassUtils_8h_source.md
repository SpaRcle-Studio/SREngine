

# File SRClassUtils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Reflection**](dir_b9e652b456a4d9b315741a759a2b0c5c.md) **>** [**SRClassUtils.h**](SRClassUtils_8h.md)

[Go to the documentation of this file](SRClassUtils_8h.md)


```C++
//
// Created by Monika on 16.07.2025.
//

#ifndef SR_ENGINE_COMMON_REFLECTION_SR_CLASS_UTILS_H
#define SR_ENGINE_COMMON_REFLECTION_SR_CLASS_UTILS_H

#include <Utils/Serialization/Serializable.h>
#include <Utils/Reflection/Property.h>
#include <Utils/TypeTraits/SRClass.h>

namespace SR_UTILS_NS::Reflection {
    /*static void ForEachSRClass(const SR_UTILS_NS::Reflection::Value& value, const SR_HTYPES_NS::Function<void(SRClass&)>& callback) {
        if (value.IsClass()) {
            if (auto&& pSRClass = value.GetSRClass()) {
                callback(*pSRClass);
                pSRClass->GetMeta()->ForEachProperty([&callback, pSRClass](const SR_UTILS_NS::Reflection::Property& property, uint64_t index) {
                    ForEachSRClass(property.Get(pSRClass), callback);
                });
                return;
            }
        }

        if (value.IsSequenceContainer()) {
            auto&& container = value.AsSequenceContainer();
            for (auto&& pIt = container.begin(); pIt != container.end(); ++pIt) {
                ForEachSRClass(*pIt, callback);
            }
        }
    }*/

    template<typename T> SR_INLINE void CloneTo(const T& from, T& to) {
        if constexpr (IsSRClassV<T>) {
            from.CloneTo(to);
        }
        else if constexpr (IsSharedPointerV<T>) {
            if (from) {
                auto&& pClone = SR_UTILS_NS::Factory::Instance().Create<InnerTypeT<T>>(from->GetMeta()->GetFactoryName());
                from->CloneTo(*pClone);
                to = std::move(pClone);
            }
        }
        else if constexpr (IsStdVectorV<T> && ContainsSRClassV<T>) {
            to.resize(from.size());
            for (size_t i = 0; i < from.size(); ++i) {
                CloneTo(from[i], to[i]);
            }
        }
        else if constexpr (IsStdSetV<T> && ContainsSRClassV<T>) {
            to.clear();
            for (auto&& item : from) {
                InnerTypeT<T> cloneValue;
                CloneTo(item, cloneValue);
                to.insert(std::move(cloneValue));
            }
        }
        else if constexpr (IsStdMapV<T> && ContainsSRClassV<T>) {
            to.clear();
            for (auto&& [key, value] : from) {
                InnerTypeT<T> cloneValue;
                CloneTo(value, cloneValue);
                to.emplace(key, std::move(cloneValue));
            }
        }
        else {
            to = from;
        }
    }

    template<typename T> SR_INLINE void ForEachSRClass(T&& object, const auto& func) {
        if constexpr (IsSRClassV<T>) {
            func(object);
        }
        else if constexpr ((IsStdVectorV<T> || IsStdSetV<T>)) {
            if constexpr (ContainsSRClassV<T>) {
                for (auto&& item : object) {
                    ForEachSRClass(item, func);
                }
            }
        }
        //else if constexpr (IsStdMapV<T>) {
        //    for (auto&& [key, value] : object) {
        //        ForEachSRClass(value, func);
        //    }
        //}
        else if constexpr (IsSharedPointerV<T>) {
            if constexpr (IsSRClassV<typename RemoveQualifiersT<T>::SharedPointerType>) {
                if (object) {
                    func(*object);
                }
            }
        }
    }
}

#endif //SR_ENGINE_COMMON_REFLECTION_SERIALIZABLE_UTILS_H
```


