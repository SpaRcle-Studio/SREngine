

# File DefaultObjectMakers.inl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**DefaultObjectMakers.inl.h**](DefaultObjectMakers_8inl_8h.md)

[Go to the documentation of this file](DefaultObjectMakers_8inl_8h.md)


```C++
//
// Created by Monika on 17.10.2024.
//

template<typename T, typename Enable = void>
struct DefaultObjectMaker {
    static constexpr bool value = false;

    static void MakeDefault(T&) { }
};

template<class T>
struct DefaultObjectMaker<std::optional<T>>
{
    static constexpr bool value = true;

    static void MakeDefault(std::optional<T>& v) {
        v.reset();
    }
};

template<>
struct DefaultObjectMaker<std::string> {
    static constexpr bool value = true;

    static void MakeDefault(std::string& v) {
        v.clear();
    }
};

template<>
struct DefaultObjectMaker<SR_UTILS_NS::StringAtom> {
    static constexpr bool value = true;

    static void MakeDefault(SR_UTILS_NS::StringAtom& v) {
        v = {};
    }
};

template<class T, class... TOther>
struct DefaultObjectMaker<std::vector<T, TOther...>> {
    static constexpr bool value = true;

    static void MakeDefault(std::vector<T, TOther...>& v) {
        v.clear();
    }
};

template<typename T, typename U, typename Compare, typename Allocator>
struct DefaultObjectMaker<std::map<T, U, Compare, Allocator>> {
    static constexpr bool value = true;

    static void MakeDefault(std::map<T, U, Compare, Allocator>& v) {
        v.clear();
    }
};

template<typename T, typename Less, typename Allocator>
struct DefaultObjectMaker<std::set<T, Less, Allocator>> {
    static constexpr bool value = true;

    static void MakeDefault(std::set<T, Less, Allocator>& v) {
        v.clear();
    }
};

template<typename T, typename U, typename Hash, typename KeyEqual, typename Allocator>
struct DefaultObjectMaker<std::unordered_map<T, U, Hash, KeyEqual, Allocator>> {
    static constexpr bool value = true;

    static void MakeDefault(std::unordered_map<T, U, Hash, KeyEqual, Allocator>& v) {
        v.clear();
    }
};

template<class T>
struct DefaultObjectMaker<SR_HTYPES_NS::SharedPtr<T>> {
    static constexpr bool value = true;

    static void MakeDefault(SR_HTYPES_NS::SharedPtr<T>& v) {
        v = nullptr;
    }
};
```


