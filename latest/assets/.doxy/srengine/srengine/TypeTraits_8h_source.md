

# File TypeTraits.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**TypeTraits.h**](TypeTraits_8h.md)

[Go to the documentation of this file](TypeTraits_8h.md)


```C++
//
// Created by Monika on 16.10.2024.
//

#ifndef SR_COMMON_TYPE_TRAITS_H
#define SR_COMMON_TYPE_TRAITS_H

#include <Utils/Common/Hashes.h>
#include <Utils/Common/EnumReflector.h>

#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>
#include <Utils/Math/Vector6.h>

namespace SR_UTILS_NS {
    struct SerializationId {
        SR_CONSTEXPR SerializationId() noexcept = default;

        SR_CONSTEXPR ~SerializationId() noexcept = default;

        template<uint64_t S> static constexpr SerializationId Create(const char (&text)[S]) noexcept {
            SerializationId id;
            for (uint64_t i = 0; i < S - 1; ++i) {
                id.name[i] = text[i];
            }
            id.name[S - 1] = '\0';
            id.hash = ComputeHashConstexpr(text);
            return id;
        }

        static SerializationId CreateFromCStr(const char* text) noexcept {
            SerializationId id;
            SR_STRNCPY(id.name, text, MaxNameLength - 1);
            id.name[MaxNameLength - 1] = '\0';
            id.hash = ComputeHash(text);
            return id;
        }

        static SerializationId CreateFromString(const std::string_view text) noexcept {
            SerializationId id;
            SR_STRNCPY(id.name, text.data(), std::min(text.size(), MaxNameLength - 1));
            id.name[MaxNameLength - 1] = '\0';
            id.hash = ComputeHash(text);
            return id;
        }

        SR_NODISCARD SR_INLINE  const char* GetName() const noexcept { return name; }
        SR_NODISCARD SR_INLINE  uint64_t GetHash() const noexcept { return hash; }

    private:
        static constexpr uint64_t MaxNameLength = 256;
        uint64_t hash = 0;
        char name[MaxNameLength]{};
    };

    template <typename T, typename = void>
    struct IsCompleteType : std::false_type {};

    template <typename T>
    struct IsCompleteType<T, std::void_t<decltype(sizeof(T))>> : std::true_type {};

    template <typename T>
    constexpr bool IsCompleteTypeV = IsCompleteType<T>::value;

    template<template<typename, size_t> typename Tmpl1>
    struct IsStdArrayTemplate : std::false_type
    {};

    template<>
    struct IsStdArrayTemplate<std::array> : std::true_type
    {};

    template<template<typename, size_t> typename Tmpl>
    SR_INLINE constexpr bool IsStdArrayTemplateV = IsStdArrayTemplate<Tmpl>::value;

    template<typename T>
    struct IsTypeFromStdArrayTemplate : std::false_type
    {};

    template<typename T, size_t N>
    struct IsTypeFromStdArrayTemplate<std::array<T, N>> : std::true_type
    {};

    template<typename T>
    SR_INLINE constexpr bool IsTypeFromStdArrayTemplateV = IsTypeFromStdArrayTemplate<T>::value;

    namespace Details
    {
        template<class Default, class AlwaysVoid, template<class...> class Op, class... Args>
        struct Detector {
            using value_t = std::false_type;
            using type = Default;
        };

        template<class Default, template<class...> class Op, class... Args>
        struct Detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
            using value_t = std::true_type;
            using type = Op<Args...>;
        };

        struct Empty {};

        template<size_t I, class T, class... Types>
        struct GetPromPack {
            using type = typename GetPromPack<I - 1, Types...>::type;
        };

        template<class T, class... Types>
        struct GetPromPack<0, T, Types...> {
            using type = T;
        };

        template<size_t Index, class... Types>
        auto GetFromPackResolver()
        {
            if constexpr (Index < sizeof...(Types)) {
                return GetPromPack<Index, Types...>();
            }
            else {
                return GetPromPack<0, Empty>();
            }
        }
    }

    template<typename T> struct InnerType {
        using type = T;
    };

    template<typename T, typename Alloc> struct InnerType<std::vector<T, Alloc>> {
        using type = typename InnerType<T>::type;
    };

    /*template<typename T, size_t N> struct InnerType<std::array<T, N>> {
        using type = typename InnerType<T>::type;
    };

    template<typename T> struct InnerType<std::set<T>> {
        using type = typename InnerType<T>::type;
    };

    template<typename T> struct InnerType<std::unordered_set<T>> {
        using type = typename InnerType<T>::type;
    };

    template<typename T> struct InnerType<std::list<T>> {
        using type = typename InnerType<T>::type;
    };

    template<typename Key, typename Value, typename Hash, typename KeyEqual, typename Alloc>
    struct InnerType<std::unordered_map<Key, Value, Hash, KeyEqual, Alloc>> {
        using type = typename InnerType<Value>::type;
    };

    template<typename Key, typename Value, typename Compare, typename Alloc>
    struct InnerType<std::map<Key, Value, Compare, Alloc>> {
        using type = typename InnerType<Value>::type;
    };*/

    template<typename T> using InnerTypeT = typename InnerType<RemoveQualifiersT<T>>::type;

    template<typename T>
    struct IsStdVector : std::false_type {};

    template<typename T, typename Alloc>
    struct IsStdVector<std::vector<T, Alloc>> : std::true_type {};

    template<typename T>
    constexpr bool IsStdVectorV = IsStdVector<RemoveQualifiersT<T>>::value;

    template<typename T>
    struct IsStdSet : std::false_type {};

    template<typename T, typename Compare, typename Alloc>
    struct IsStdSet<std::set<T, Compare, Alloc>> : std::true_type {};

    template<typename T>
    constexpr bool IsStdSetV = IsStdSet<RemoveQualifiersT<T>>::value;

    template<typename T>
    struct IsStdMap : std::false_type {};

    template<typename Key, typename Value, typename Compare, typename Alloc>
    struct IsStdMap<std::map<Key, Value, Compare, Alloc>> : std::true_type {};

    template<typename T>
    constexpr bool IsStdMapV = IsStdMap<RemoveQualifiersT<T>>::value;

    template<template<class...> class Op, class... Args>
    struct IsDetected : Details::Detector<Details::Empty, void, Op, Args...>::value_t
    {};

    template<template<class...> class Op, class... Args>
    inline constexpr bool IsDetectedV = IsDetected<Op, Args...>::value;

    template<template<class...> class Op, class... Args>
    using DetectedT = typename Details::Detector<Details::Empty, void, Op, Args...>::type;

    template <typename T>
    using HasNullptrComparison = decltype(std::declval<const T>() == nullptr);

    template <typename T>
    struct SupportsNullptrComparison : std::bool_constant<IsDetectedV<HasNullptrComparison, T>> {};

    template <typename T> struct SupportsNullptrComparison<SR_MATH_NS::Vector2<T>> : std::false_type {};
    template <typename T> struct SupportsNullptrComparison<SR_MATH_NS::Vector3<T>> : std::false_type {};
    template <typename T> struct SupportsNullptrComparison<SR_MATH_NS::Vector4<T>> : std::false_type {};
    template <typename T> struct SupportsNullptrComparison<SR_MATH_NS::Vector6<T>> : std::false_type {};

    template <> struct SupportsNullptrComparison<SR_UTILS_NS::StringAtom> : std::false_type {};

    template<class T>
    inline constexpr bool SupportsNullptrComparisonV = SupportsNullptrComparison<T>::value;

    template<class Default, template<class...> class Op, class... Args>
    struct DetectedOr : Details::Detector<Default, void, Op, Args...>
    {};

    template<class Default, template<class...> class Op, class... Args>
    using DetectedOrT = typename DetectedOr<Default, Op, Args...>::type;

    template<class Expected, template<class...> class Op, class... Args>
    struct IsDetectedExact : std::is_same<Expected, DetectedT<Op, Args...>>
    {};

    template<class Expected, template<class...> class Op, class... Args>
    inline constexpr bool IsDetectedExactV = IsDetectedExact<Expected, Op, Args...>::value;

    template<class To, template<class...> class Op, class... Args>
    struct IsDetectedConvertible : std::is_convertible<DetectedT<Op, Args...>, To>
    {};

    template<class To, template<class...> class Op, class... Args>
    inline constexpr bool IsDetectedConvertibleV = IsDetectedConvertible<To, Op, Args...>::value;

    template<typename>
    struct IsTemplateClass : std::false_type
    {};

    template<template<typename...> typename Tmpl, typename... Args>
    struct IsTemplateClass<Tmpl<Args...>> : std::true_type
    {};

    template<class T>
    inline constexpr bool IsTemplateClassV = IsTemplateClass<T>::value;

    template<template<typename...> typename Tmpl1, template<typename...> typename Tmpl2>
    struct IsSameClassTemplate : std::false_type
    {};

    template<template<typename...> typename Tmpl>
    struct IsSameClassTemplate<Tmpl, Tmpl> : std::true_type
    {};

    template<template<typename...> typename Tmpl1, template<typename...> typename Tmpl2>
    inline constexpr bool IsSameClassTemplateV = IsSameClassTemplate<Tmpl1, Tmpl2>::value;

    template<typename, template<typename...> typename>
    struct IsTypeFromClassTemplate : std::false_type
    {};

    template<template<typename...> typename Tmpl, typename... Args>
    struct IsTypeFromClassTemplate<Tmpl<Args...>, Tmpl> : std::true_type
    {};

    template<typename T, template<typename...> typename Tmpl>
    inline constexpr bool IsTypeFromClassTemplateV = IsTypeFromClassTemplate<T, Tmpl>::value;

    template<class T> struct IsEnum {
        using Type = SR_UTILS_NS::RemoveQualifiersT<T>;

        static constexpr bool IsEnumType() {
            if constexpr (std::is_enum_v<Type>) {
                return true;
            }
            else {
                return false;
            }
        }

        static constexpr bool value = IsEnum::IsEnumType();
    };

    template<class T>
    inline constexpr bool IsEnumV = IsEnum<T>::value;

    template<class T> struct IsSREnum {
        using Type = SR_UTILS_NS::RemoveQualifiersT<T>;

        static constexpr bool IsEnumType() {
            if constexpr (IsEnumV<Type>) {
                return SR_UTILS_NS::EnumTraits<Type>::IsEnum;
            }
            else {
                return false;
            }
        }

        static constexpr bool value = IsSREnum::IsEnumType();
    };

    template<class T>
    inline constexpr bool IsSREnumV = IsSREnum<T>::value;

    template<size_t Index, class... Types>
    using GetPromPackT = typename decltype(Details::GetFromPackResolver<Index, Types...>())::type;

    template<class T, class... Types>
    inline constexpr bool HasTypeInPackV = std::disjunction_v<std::is_same<T, Types>...>;

    template<class T, class... Types>
    inline constexpr bool PackOfSameTypeV = std::conjunction_v<std::is_same<T, Types>...>;

    template<class T, class... Types>
    inline constexpr bool NoTypeInPackV = std::conjunction_v<std::negation<std::is_same<T, Types>>...>;

    template<class T, auto val>
    struct TypeValuePair
    {
        using type = T;
        static SR_INLINE constexpr auto value = val;
    };

    template<class T, auto val>
    inline constexpr auto TypeValuePairV = TypeValuePair<T, val>::value;

    template<class T, auto val>
    using TypeValuePairT = typename TypeValuePair<T, val>::type;

    // Предназначено в основном для использования в static_assert, чтобы сделать его зависимым от T
    template<class T>
    inline constexpr bool AlwaysFalseV = std::is_same_v<std::decay_t<T>, std::add_cv_t<std::decay_t<T>>>;

    template<class T>
    struct GetFirstOfTypeFromSequenceAssert
    {
        static_assert(AlwaysFalseV<T>, "There's no same type for T in sequence!");
        static SR_INLINE constexpr auto value = 0;
    };

    template<class T, class Pair, class... Pairs>
    struct GetFirstOfTypeFromSequence
    {
        static SR_INLINE constexpr auto value = std::conditional_t<std::is_same_v<T, typename Pair::type>, Pair, GetFirstOfTypeFromSequence<T, Pairs...>>::value;
    };

    template<class T, class Pair>
    struct GetFirstOfTypeFromSequence<T, Pair>
    {
        static SR_INLINE constexpr auto value = std::conditional_t<std::is_same_v<T, typename Pair::type>, Pair, GetFirstOfTypeFromSequenceAssert<T>>::value;
    };

    template<class T, class... Pairs>
    inline constexpr auto GetFirstOfTypeFromSequenceV = GetFirstOfTypeFromSequence<T, Pairs...>::value;

    template<class T>
    struct RemoveCVRef
    {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };

    template<class T>
    using RemoveCVRefT = typename RemoveCVRef<T>::type;

    template<class X, class Y>
    using CheckerEqualityComparable = decltype(std::declval<const X>() == std::declval<const Y>());

    template<class X, class Y>
    using CheckerOperatorMinus = decltype(std::declval<const X>() - std::declval<const Y>());

    /*template<template<class...> class Op, class X, class Y>
    struct CheckOperatorUsable : IsDetected<Op, X, Y>
    {};

    template<typename T>
    struct CheckOperatorUsable<CheckerEqualityComparable, std::optional<T>, std::optional<T>> : std::false_type
    {};*/

    template <template<class...> class Op, class X, class Y, typename = void>
    struct CheckOperatorUsable : IsDetected<Op, X, Y> {};

    template <template<class...> class Op, class X, class Y>
    struct CheckOperatorUsable<Op, X, Y, std::enable_if_t<std::is_same_v<Y, std::nullptr_t> && !SupportsNullptrComparisonV<X>>> : std::false_type {};

    template <typename T>
    struct CheckOperatorUsable<CheckerEqualityComparable, std::optional<T>, std::optional<T>> : std::false_type {};

    template <template<class...> class Op, class X, class Y>
    constexpr bool CheckOperatorUsableV = CheckOperatorUsable<Op, X, Y>::value;

    template<typename T> SR_UTILS_NS::StringAtom GetEnumReflectorName() {
        using Type = SR_UTILS_NS::RemoveQualifiersT<T>;
        if constexpr (SR_UTILS_NS::IsSREnumV<Type>) {
            return SR_UTILS_NS::EnumReflector::GetName<Type>();
        }
        return SR_UTILS_NS::StringAtom();
    }

}

#endif //SR_COMMON_TYPE_TRAITS_H
```


