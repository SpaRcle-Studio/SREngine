

# File SaveCheckers.inl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**SaveCheckers.inl.h**](SaveCheckers_8inl_8h.md)

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


