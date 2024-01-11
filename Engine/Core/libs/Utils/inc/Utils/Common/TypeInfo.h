//
// Created by Monika on 29.06.2022.
//

#ifndef SR_ENGINE_TYPEINFO_H
#define SR_ENGINE_TYPEINFO_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Common/AnyVisitor.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>
#include <Utils/Math/Vector6.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(StandardType, uint16_t,
        Unknown,
        Bool,
        Int8,
        UInt8,
        Int16,
        UInt16,
        Int32,
        UInt32,
        Int64,
        UInt64,
        Float,
        Double,

        String,
        StringAtom,

        Enum,
        Class,

        Path,

        FVector2, FVector3, FVector4, FVector5, FVector6,
        IVector2, IVector3, IVector4, IVector5, IVector6,
        UVector2, UVector3, UVector4, UVector5, UVector6,
        BVector2, BVector3, BVector4, BVector5, BVector6
    );

    union StandardData {
        bool m_bool;
        int8_t m_int8;
        uint8_t m_uint8;
        int16_t m_int16;
        uint16_t m_uint16;
        int32_t m_int32;
        uint32_t m_uint32;
        int64_t m_int64;
        uint64_t m_uint64;
        float_t m_float;
        double_t m_double;
    };

    template<typename Any> static StandardType GetStandardType(const Any& any) {
        StandardType type = StandardType::Unknown;

        auto&& visitor = SR_UTILS_NS::Overloaded {
                [&type](bool)               { type = StandardType::Bool; },
                [&type](char)               { type = StandardType::Int8; },
                [&type](unsigned char)      { type = StandardType::UInt8; },
                [&type](short)              { type = StandardType::Int16; },
                [&type](unsigned short)     { type = StandardType::UInt16; },
                [&type](int)                { type = StandardType::Int32; },
                [&type](unsigned int)       { type = StandardType::UInt32; },
                [&type](long long)          { type = StandardType::Int64; },
                [&type](unsigned long long) { type = StandardType::UInt64; },
                [&type](float)              { type = StandardType::Float; },
                [&type](double)             { type = StandardType::Double; },
                [&type](const std::string&) { type = StandardType::String; }, /// TODO: maybe not working
                [&type](auto&&)             { type = StandardType::Unknown; }
        };

        SR_UTILS_NS::AnyVisitor<bool, char, unsigned char, short, unsigned short, int, unsigned int, long long, unsigned long long, float, double, std::string>{}(any, visitor);

        return type;
    }

    template<typename T> constexpr StandardType GetStandardType() {
        if constexpr (std::is_same<T, bool>()) {
            return StandardType::Bool;
        }
        else if constexpr (std::is_same<T, int8_t>() || std::is_same<T, char>()) {
            return StandardType::Int8;
        }
        else if constexpr (std::is_same<T, uint8_t>() || std::is_same<T, unsigned char>()) {
            return StandardType::UInt8;
        }
        else if constexpr (std::is_same<T, int16_t>() || std::is_same<T, short>()) {
            return StandardType::Int16;
        }
        else if constexpr (std::is_same<T, uint16_t>() || std::is_same<T, unsigned short>()) {
            return StandardType::UInt16;
        }
        else if constexpr (std::is_same<T, int32_t>() || std::is_same<T, int>()) {
            return StandardType::Int32;
        }
        else if constexpr (std::is_same<T, uint32_t>() || std::is_same<T, unsigned int>()) {
            return StandardType::UInt32;
        }
        else if constexpr (std::is_same<T, int64_t>() || std::is_same<T, long long>()) {
            return StandardType::Int64;
        }
        else if constexpr (std::is_same<T, uint64_t>() || std::is_same<T, unsigned long long>()) {
            return StandardType::UInt64;
        }
        else if constexpr (std::is_same<T, float_t>() || std::is_same<T, float>()) {
            return StandardType::Float;
        }
        else if constexpr (std::is_same<T, double_t>() || std::is_same<T, double>()) {
            return StandardType::Double;
        }
        else if constexpr (std::is_same<T, std::string>() || std::is_same<T, const char*>()) {
            return StandardType::String;
        }
        else if constexpr (std::is_same<T, std::string>() || std::is_same<T, const char*>()) {
            return StandardType::String;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::FVector2>() || std::is_same<T, SR_MATH_NS::Vector2<float>>() || std::is_same<T, SR_MATH_NS::Vector2<float_t>>()) {
            return StandardType::FVector2;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::FVector3>() || std::is_same<T, SR_MATH_NS::Vector3<float>>() || std::is_same<T, SR_MATH_NS::Vector3<float_t>>()) {
            return StandardType::FVector3;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::FVector4>() || std::is_same<T, SR_MATH_NS::Vector4<float>>() || std::is_same<T, SR_MATH_NS::Vector4<float_t>>()) {
            return StandardType::FVector4;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::FVector6>() || std::is_same<T, SR_MATH_NS::Vector6<float>>() || std::is_same<T, SR_MATH_NS::Vector6<float_t>>()) {
            return StandardType::FVector6;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::BVector3>() || std::is_same<T, SR_MATH_NS::Vector3<bool>>()) {
            return StandardType::BVector3;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::IVector2>() || std::is_same<T, SR_MATH_NS::Vector2<int>>()|| std::is_same<T, SR_MATH_NS::Vector2<int32_t>>()) {
            return StandardType::IVector2;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::IVector3>() || std::is_same<T, SR_MATH_NS::Vector3<int>>()|| std::is_same<T, SR_MATH_NS::Vector3<int32_t>>()) {
            return StandardType::IVector3;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::IVector4>() || std::is_same<T, SR_MATH_NS::Vector4<int>>()|| std::is_same<T, SR_MATH_NS::Vector4<int32_t>>()) {
            return StandardType::IVector4;
        }
        else if constexpr (std::is_same<T, SR_MATH_NS::IVector6>() || std::is_same<T, SR_MATH_NS::Vector6<int>>()|| std::is_same<T, SR_MATH_NS::Vector6<int32_t>>()) {
            return StandardType::IVector6;
        }
        else if constexpr (std::is_class_v<T>) {
            return StandardType::Class;
        }
        else if constexpr (std::is_enum_v<T>) {
            return StandardType::Enum;
        }
        else
            return StandardType::Unknown;
    }

    SR_MAYBE_UNUSED static uint64_t GetTypeSize(const StandardType& type) {
        switch (type) {
            case StandardType::Bool: return sizeof(bool);
            case StandardType::Int8: return sizeof(int8_t);
            case StandardType::UInt8: return sizeof(uint8_t);
            case StandardType::Int16: return sizeof(int16_t);
            case StandardType::UInt16: return sizeof(uint16_t);
            case StandardType::Int32: return sizeof(int32_t);
            case StandardType::UInt32: return sizeof(uint32_t);
            case StandardType::Int64: return sizeof(int64_t);
            case StandardType::UInt64: return sizeof(uint64_t);
            case StandardType::Float: return sizeof(float_t);
            case StandardType::Double: return sizeof(double_t);
            default:
                return 0;
        }
    }

    SR_MAYBE_UNUSED static bool IsNumber(const StandardType& type) {
        switch (type) {
            case StandardType::Int8:
            case StandardType::UInt8:
            case StandardType::Int16:
            case StandardType::UInt16:
            case StandardType::Int32:
            case StandardType::UInt32:
            case StandardType::Int64:
            case StandardType::UInt64:
            case StandardType::Float:
            case StandardType::Double:
                return true;
            default:
                return false;
        }
    }

    //specialize a type for all of the STL containers.
    namespace is_stl_container_impl{
        template <typename T>       struct is_stl_vector:std::false_type{};
        template <typename... Args> struct is_stl_vector<std::vector<Args...>>:std::true_type{};

        template <typename T>       struct is_stl_container:std::false_type{};
        template <typename T, std::size_t N> struct is_stl_container<std::array    <T,N>>    :std::true_type{};
        template <typename... Args> struct is_stl_container<std::vector            <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::deque             <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::list              <Args...>>:std::true_type{};
#if !defined(SR_ANDROID) && defined(SR_CXX_20)
        template <typename... Args> struct is_stl_container<std::forward_list      <Args...>>:std::true_type{};
#endif
        template <typename... Args> struct is_stl_container<std::set               <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::multiset          <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::map               <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::multimap          <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::unordered_set     <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::unordered_multiset<Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::unordered_map     <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::unordered_multimap<Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::stack             <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::queue             <Args...>>:std::true_type{};
        template <typename... Args> struct is_stl_container<std::priority_queue    <Args...>>:std::true_type{};
    }

    /// type trait to utilize the implementation type traits as well as decay the type
    template <typename T> struct IsSTLContainer {
        static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
    };

    template <typename T> constexpr bool IsSTLVector() {
        return is_stl_container_impl::is_stl_vector<std::decay_t<T>>::value;
    }
}

#endif //SR_ENGINE_TYPEINFO_H
