

# File SaveCheckers.inl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**SaveCheckers.inl.h**](SaveCheckers_8inl_8h.md)

[Go to the documentation of this file](SaveCheckers_8inl_8h.md)


```C++
//
// Created by Monika on 01.03.2025.
//

template<typename T, typename Enable = void>
struct SaveChecker {
    static bool CanBeSaved(const T& value) {
        return true;
    }
};


template<typename T>
struct SaveChecker<T, typename std::enable_if<SerializationTraits<T>::IsSerializable>::type> {
    static bool CanBeSaved(const T& value) {
        return !value.HasSerializationFlags(SR_UTILS_NS::SerializationFlags::DontSave);
    }
};

template<typename T>
struct SaveChecker<SR_HTYPES_NS::SharedPtr<T>, std::enable_if_t<SerializationTraits<T>::IsSerializable>> {
    static bool CanBeSaved(const SR_HTYPES_NS::SharedPtr<T>& value) {
        return !value || SaveChecker<T>().CanBeSaved(*value);
    }
};
```


