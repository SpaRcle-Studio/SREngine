

# File DefaultCheckers.inl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**DefaultCheckers.inl.h**](DefaultCheckers_8inl_8h.md)

[Go to the documentation of this file](DefaultCheckers_8inl_8h.md)


```C++
//
// Created by Monika on 17.10.2024.
//

template<class T> struct DefaultChecker<T, typename std::enable_if_t<std::is_default_constructible_v<T> && CheckOperatorUsableV<CheckerEqualityComparable, T, T> && !SerializationTraits<T>::HasEmpty && !std::is_same_v<T, SR_UTILS_NS::StringAtom>>> {
    static bool IsDefault(const T& value) {
        return SR_EQUALS(value, T {});
    }
};

template<> struct DefaultChecker<SR_UTILS_NS::StringAtom> {
    static bool IsDefault(const SR_UTILS_NS::StringAtom& value) {
        return value.Empty();
    }
};

template<class T> struct DefaultChecker<std::optional<T>> {
    static bool IsDefault(const std::optional<T>& value) {
        return !value.is_initialized();
    }
};

template<class T>
struct DefaultChecker<T, std::enable_if_t<SerializationTraits<T>::HasEmpty && !IsTypeFromStdArrayTemplateV<T>>> {
    static bool IsDefault(const T& value) {
        return value.empty();
    }
};

template<class T, size_t N>
struct DefaultChecker<std::array<T, N>> {
    using IsAlwaysFalse = std::bool_constant<(N > 0)>;

    static constexpr bool IsDefault(const std::array<T, N>& value) {
        return value.empty();
    }
};
```


