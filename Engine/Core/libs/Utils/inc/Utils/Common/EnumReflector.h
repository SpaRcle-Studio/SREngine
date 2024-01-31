//
// Created by Monika on 09.09.2022.
//

#ifndef SR_ENGINE_ENUMREFLECTOR_H
#define SR_ENGINE_ENUMREFLECTOR_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/HashManager.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/StringAtom.h>

namespace SR_UTILS_NS {
    class EnumReflector;

    class IEnumStructBase { };

    class SR_DLL_EXPORT EnumReflectorManager : public SR_UTILS_NS::Singleton<EnumReflectorManager> {
        SR_REGISTER_SINGLETON(EnumReflectorManager);
        using Reflectors = ska::flat_hash_map<uint64_t, EnumReflector*>;
    public:
        SR_NODISCARD bool IsSingletonCanBeDestroyed() const override {
            return false;
        }

        bool RegisterReflector(EnumReflector* pReflector);

        SR_NODISCARD EnumReflector* GetReflector(const SR_UTILS_NS::StringAtom& name) const;
        SR_NODISCARD EnumReflector* GetReflector(uint64_t hashName) const;
        SR_NODISCARD const Reflectors& GetReflectors() const noexcept { return m_reflectors; }

    private:
        Reflectors m_reflectors;

    };

    class SR_DLL_EXPORT EnumReflector : public NonCopyable
    {
    public:
        template<typename Integral> EnumReflector(const Integral* values, size_t count, const char* name, const char* body);
        ~EnumReflector() override;

    public:
        template<typename EnumType> SR_NODISCARD static EnumReflector* GetReflector();
        template<typename EnumType> SR_NODISCARD static uint64_t Count();
        template<typename EnumType> SR_NODISCARD static SR_UTILS_NS::StringAtom ToStringAtom(EnumType value);
        template<typename EnumType> SR_NODISCARD static SR_UTILS_NS::StringAtom ToStringAtom(int64_t value);
        template<typename EnumType> SR_NODISCARD static EnumType FromString(const SR_UTILS_NS::StringAtom& value);

        template<typename EnumType> SR_NODISCARD static const std::vector<SR_UTILS_NS::StringAtom>& GetNames();
        template<typename EnumType> SR_NODISCARD static std::vector<SR_UTILS_NS::StringAtom> GetNamesFilter(const std::function<bool(EnumType)>& filter);

        template<typename EnumType> SR_NODISCARD static int64_t GetIndex(EnumType value);
        template<typename EnumType> SR_NODISCARD static int64_t GetIndex(int64_t value);
        template<typename EnumType> SR_NODISCARD static EnumType At(int64_t index);
        template<typename EnumType> SR_NODISCARD static int64_t AtAsInt(int64_t index);

        SR_NODISCARD SR_MAYBE_UNUSED std::optional<SR_UTILS_NS::StringAtom> ToStringInternal(int64_t value) const;
        SR_NODISCARD SR_MAYBE_UNUSED std::optional<int64_t> FromStringInternal(const SR_UTILS_NS::StringAtom& name) const;
        SR_NODISCARD SR_MAYBE_UNUSED std::optional<int64_t> GetIndexInternal(int64_t value) const;
        SR_NODISCARD SR_MAYBE_UNUSED std::optional<int64_t> AtInternal(int64_t index) const;
        SR_NODISCARD SR_MAYBE_UNUSED const std::vector<SR_UTILS_NS::StringAtom>& GetNamesInternal() const { return m_data->names; }
        SR_NODISCARD SR_MAYBE_UNUSED const SR_UTILS_NS::StringAtom& GetNameInternal() const { return m_data->enumName; }
        SR_NODISCARD SR_MAYBE_UNUSED uint64_t GetHashNameInternal() const { return m_data->hashName; }

    private:
        static bool IsIdentChar(char c);
        static void ErrorInternal(const std::string& msg);

    private:
        struct Data
        {
            struct Enumerator
            {
                SR_UTILS_NS::StringAtom name;
                uint64_t hashName;
                int64_t value;
            };
            std::vector<Enumerator> values;
            std::vector<SR_UTILS_NS::StringAtom> names;
            SR_UTILS_NS::StringAtom enumName;
            uint64_t hashName;
        }* m_data;
    };
}

namespace SR_UTILS_NS {
    template<typename Integral> EnumReflector::EnumReflector(const Integral *values, size_t count, const char *name, const char *body)
        : m_data(new Data())
    {
        m_data->enumName = name;
        m_data->hashName = SR_HASH_STR_REGISTER(name);
        m_data->values.resize(count);
        m_data->names.resize(count);

        enum states
        {
            state_start, // Before identifier
            state_ident, // In identifier
            state_skip, // Looking for separator comma
        } state = state_start;

        assert(*body == '(');
        ++body;
        const char* ident_start = nullptr;
        int value_index = 0;
        int level = 0;
        for (;;)
        {
            assert(*body);
            switch (state)
            {
                case state_start:
                    if (IsIdentChar(*body))
                    {
                        state = state_ident;
                        ident_start = body;
                    }
                    ++body;
                    break;
                case state_ident:
                    if (!IsIdentChar(*body))
                    {
                        state = state_skip;
                        assert(value_index < count);

                        m_data->values[value_index].name = std::string(ident_start, body - ident_start);
                        m_data->values[value_index].value = static_cast<int64_t>(values[value_index]);
                        m_data->values[value_index].hashName = m_data->values[value_index].name.GetHash();

                        m_data->names[value_index] = m_data->values[value_index].name;

                        ++value_index;
                    }
                    else
                    {
                        ++body;
                    }
                    break;
                case state_skip:
                    if (*body == '(')
                    {
                        ++level;
                    }
                    else if (*body == ')')
                    {
                        if (level == 0)
                        {
                            assert(value_index == count);
                            return;
                        }
                        --level;
                    }
                    else if (level == 0 && *body == ',')
                    {
                        state = state_start;
                    }
                    ++body;
            }
        }
    }

    template<typename EnumType> SR_UTILS_NS::StringAtom EnumReflector::ToStringAtom(EnumType value) {
        if (auto&& result = GetReflector<EnumType>()->ToStringInternal(static_cast<int64_t>(value)); result.has_value()) {
            return result.value();
        }

        ErrorInternal("EnumReflector::ToStringAtom() : unknown type! Value: " + std::to_string(static_cast<int64_t>(value)));

        return SR_UTILS_NS::StringAtom(); /// NOLINT
    }

    template<typename EnumType> SR_UTILS_NS::StringAtom EnumReflector::ToStringAtom(int64_t value) {
        if (auto&& result = GetReflector<EnumType>()->ToStringInternal(value); result.has_value()) {
            return result.value();
        }

        ErrorInternal("EnumReflector::ToStringAtom() : unknown type! Value: " + std::to_string(value));

        return SR_UTILS_NS::StringAtom(); /// NOLINT
    }

    template<typename EnumType> EnumType EnumReflector::FromString(const SR_UTILS_NS::StringAtom& value) {
        if (auto&& result = GetReflector<EnumType>()->FromStringInternal(value); result.has_value()) {
            return static_cast<EnumType>(result.value());
        }

        ErrorInternal("EnumReflector::FromString() : unknown type! Value: " + value.ToStringRef());

        return static_cast<EnumType>(0);
    }

    template<typename EnumType> const std::vector<SR_UTILS_NS::StringAtom>& EnumReflector::GetNames() {
        return GetReflector<EnumType>()->m_data->names;
    }

    template<typename EnumType> std::vector<SR_UTILS_NS::StringAtom> EnumReflector::GetNamesFilter(const std::function<bool(EnumType)> &filter) {
        std::vector<SR_UTILS_NS::StringAtom> names;

        auto&& data = GetReflector<EnumType>()->m_data;

        for (uint64_t i = 0; i < Count<EnumType>(); ++i) {
            if (filter(data->values[i])) {
                names.emplace_back(data->names[i]);
            }
        }

        return names;
    }

    template<typename EnumType> int64_t EnumReflector::GetIndex(EnumType value) {
        return GetIndex<EnumType>(static_cast<int64_t>(value));
    }

    template<typename EnumType> int64_t EnumReflector::GetIndex(int64_t value) {
        if (auto&& result = GetReflector<EnumType>()->GetIndexInternal(value); result.has_value()) {
            return result.value();
        }

        ErrorInternal("EnumReflector::GetIndex() : unknown type! Value: " + std::to_string(static_cast<int64_t>(value)));

        return SR_ID_INVALID;
    }

    template<typename EnumType> EnumType EnumReflector::At(int64_t index) {
        return static_cast<EnumType>(AtAsInt<EnumType>(index));
    }

    template<typename EnumType> int64_t EnumReflector::AtAsInt(int64_t index) {
        if (auto&& result = GetReflector<EnumType>()->AtInternal(index); result.has_value()) {
            return result.value();
        }

        ErrorInternal("EnumReflector::At() : invalid index! Index: " + std::to_string(static_cast<int64_t>(index)));

        return 0;
    }

    template<typename EnumType> uint64_t EnumReflector::Count() {
        return GetReflector<EnumType>()->m_data->values.size();
    }

    template<typename EnumType> EnumReflector* EnumReflector::GetReflector() {
        if constexpr (std::is_class_v<EnumType>) {
            if constexpr (std::is_enum_v<EnumType>) {
                return const_cast<EnumReflector*>(&_detail_reflector_(EnumType()));
            }
            else {
                return const_cast<EnumReflector*>(&_detail_reflector_(EnumType::TypeT()));
            }
        }
        else {
            return const_cast<EnumReflector*>(&_detail_reflector_(EnumType()));
        }

        return nullptr;
    }
}

#define SR_ENUM_DETAIL_SPEC_namespace \
    extern "C"{/* Protection from being used inside a class body */} \
    SR_INLINE
#define SR_ENUM_DETAIL_SPEC_class friend
#define SR_ENUM_DETAIL_STR(x) #x
#define SR_ENUM_DETAIL_MAKE(enumClass, spec, enumName, enumNameStr, integral, ...)                                      \
    enumClass enumName : integral                                                                                       \
    {                                                                                                                   \
        __VA_ARGS__, SR_MACRO_CONCAT(enumName, MAX)                                                                     \
    };                                                                                                                  \
    SR_ENUM_DETAIL_SPEC_##spec const SR_UTILS_NS::EnumReflector& _detail_reflector_(enumName)                           \
    {                                                                                                                   \
        static const SR_UTILS_NS::EnumReflector _reflector( []{                                                         \
            static integral _detail_sval;                                                                               \
            _detail_sval = 0;                                                                                           \
            struct _detail_val_t                                                                                        \
            {                                                                                                           \
                _detail_val_t(const _detail_val_t& rhs) : _val(rhs) { _detail_sval = _val + 1; }                        \
                _detail_val_t(integral val) /** NOLINT(google-explicit-constructor) */                                  \
                    : _val(val)                                                                                         \
                { _detail_sval = _val + 1; }                                                                            \
                                                                                                                        \
                _detail_val_t() : _val(_detail_sval){ _detail_sval = _val + 1; }                                        \
                                                                                                                        \
                _detail_val_t& operator=(const _detail_val_t&) { return *this; }                                        \
                _detail_val_t& operator=(integral) { return *this; }                                                    \
                operator integral() const { return _val; }                                                              \
                integral _val;                                                                                          \
            } __VA_ARGS__;                                                                                              \
            const integral _detail_vals[] = { __VA_ARGS__ };                                                            \
            return SR_UTILS_NS::EnumReflector( _detail_vals, sizeof(_detail_vals) / sizeof(integral),                   \
                    enumNameStr, SR_ENUM_DETAIL_STR((__VA_ARGS__)));                                                    \
        }());                                                                                                           \
        return _reflector;                                                                                              \
    }                                                                                                                   \
    SR_INLINE_STATIC const bool SR_MACRO_CONCAT(enumName, RegistrationCodegenResult) =                    /** NOLINT */ \
        SR_UTILS_NS::EnumReflectorManager::Instance()                                                     /** NOLINT */ \
            .RegisterReflector(const_cast<SR_UTILS_NS::EnumReflector*>(&_detail_reflector_(enumName()))); /** NOLINT */ \

#endif //SR_ENGINE_ENUMREFLECTOR_H
