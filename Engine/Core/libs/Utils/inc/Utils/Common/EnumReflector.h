//
// Created by Monika on 09.09.2022.
//

#ifndef SRENGINE_ENUMREFLECTOR_H
#define SRENGINE_ENUMREFLECTOR_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    class EnumReflector : public NonCopyable
    {
    public:
        template<typename Integral> EnumReflector(const Integral* values, size_t count, const char* name, const char* body);
        ~EnumReflector() override;

    public:
        template<typename EnumType> SR_NODISCARD static std::string ToString(EnumType value);
        template<typename EnumType> SR_NODISCARD static EnumType FromString(const std::string& value);

        template<typename EnumType> SR_NODISCARD static std::vector<std::string> GetNames();
        template<typename EnumType> SR_NODISCARD static std::vector<std::string> GetNamesFilter(const std::function<bool(EnumType)>& filter);

        template<typename EnumType> SR_NODISCARD static int64_t GetIndex(EnumType value);
        template<typename EnumType> SR_NODISCARD static EnumType At(int64_t index);

    private:
        SR_NODISCARD std::optional<std::string> ToStringInternal(int64_t value) const;
        SR_NODISCARD std::optional<int64_t> FromStringInternal(const std::string& name) const;
        SR_NODISCARD std::optional<int64_t> GetIndexInternal(int64_t value) const;
        SR_NODISCARD std::optional<int64_t> AtInternal(int64_t index) const;

        SR_NODISCARD uint64_t Count() const noexcept;

    private:
        static bool IsIdentChar(char c);

    private:
        struct Data
        {
            struct Enumerator
            {
                std::string name;
                int64_t hashName;
                int64_t value;
            };
            std::vector<Enumerator> values;
            std::vector<std::string> names;
            std::string enumName;
        }* m_data;
    };
}

namespace SR_UTILS_NS {
    template<typename Integral> EnumReflector::EnumReflector(const Integral *values, size_t count, const char *name, const char *body)
        : m_data(new Data())
    {
        m_data->enumName = name;
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
                        m_data->values[value_index].hashName = SR_UTILS_NS::HashCombine(m_data->values[value_index].name);

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

    template<typename EnumType> std::string EnumReflector::ToString(EnumType value) {
        if (auto&& result = _detail_reflector_(EnumType()).ToStringInternal(static_cast<int64_t>(value)); result.has_value()) {
            return result.value();
        }

        SRHalt("EnumReflector::ToString() : unknown type! Value: " + std::to_string(static_cast<int64_t>(value)));

        return std::string();
    }

    template<typename EnumType> EnumType EnumReflector::FromString(const std::string &value) {
        if (auto&& result = _detail_reflector_(EnumType()).FromStringInternal(value); result.has_value()) {
            return static_cast<EnumType>(result.value());
        }

        SRHalt("EnumReflector::FromString() : unknown type! Value: " + value);

        return static_cast<EnumType>(0);
    }

    template<typename EnumType> std::vector<std::string> EnumReflector::GetNames() {
        return _detail_reflector_(EnumType()).m_data->names;
    }

    template<typename EnumType> std::vector<std::string> EnumReflector::GetNamesFilter(const std::function<bool(EnumType)> &filter) {
        std::vector<std::string> names;

        auto&& data = _detail_reflector_(EnumType()).m_data;

        for (uint64_t i = 0; i < Count(); ++i) {
            if (filter(data->values[i])) {
                names.emplace_back(data->names[i]);
            }
        }

        return names;
    }

    template<typename EnumType> int64_t EnumReflector::GetIndex(EnumType value) {
        if (auto&& result = _detail_reflector_(EnumType()).GetIndexInternal(static_cast<int64_t>(value)); result.has_value()) {
            return result.value();
        }

        SRHalt("EnumReflector::GetIndex() : unknown type! Value: " + std::to_string(static_cast<int64_t>(value)));

        return SR_ID_INVALID;
    }

    template<typename EnumType> EnumType EnumReflector::At(int64_t index) {
        if (auto&& result = _detail_reflector_(EnumType()).AtInternal(index); result.has_value()) {
            return static_cast<EnumType>(result.value());
        }

        SRHalt("EnumReflector::At() : invalid index! Index: " + std::to_string(static_cast<int64_t>(index)));

        return EnumType();
    }

#define SR_ENUM_DETAIL_SPEC_namespace \
    extern "C"{/* Protection from being used inside a class body */} \
    SR_INLINE
#define SR_ENUM_DETAIL_SPEC_class friend
#define SR_ENUM_DETAIL_STR(x) #x
#define SR_ENUM_DETAIL_MAKE(enumClass, spec, enumName, integral, ...)                                                  \
    enumClass enumName : integral                                                                                      \
    {                                                                                                                  \
        __VA_ARGS__                                                                                                    \
    };                                                                                                                 \
    SR_ENUM_DETAIL_SPEC_##spec const SR_UTILS_NS::EnumReflector& _detail_reflector_(enumName)                          \
    {                                                                                                                  \
        static const SR_UTILS_NS::EnumReflector _reflector( []{                                                        \
            static integral _detail_sval;                                                                              \
            _detail_sval = 0;                                                                                          \
            struct _detail_val_t                                                                                       \
            {                                                                                                          \
                _detail_val_t(const _detail_val_t& rhs) : _val(rhs) { _detail_sval = _val + 1; }                       \
                _detail_val_t(integral val) /* NOLINT(google-explicit-constructor) */                                  \
                    : _val(val)                                                                                        \
                { _detail_sval = _val + 1; }                                                                           \
                                                                                                                       \
                _detail_val_t() : _val(_detail_sval){ _detail_sval = _val + 1; }                                       \
                                                                                                                       \
                _detail_val_t& operator=(const _detail_val_t&) { return *this; }                                       \
                _detail_val_t& operator=(integral) { return *this; }                                                   \
                operator integral() const { return _val; }                                                             \
                integral _val;                                                                                         \
            } __VA_ARGS__;                                                                                             \
            const integral _detail_vals[] = { __VA_ARGS__ };                                                           \
            return SR_UTILS_NS::EnumReflector( _detail_vals, sizeof(_detail_vals)/sizeof(integral),                    \
                    #enumName, SR_ENUM_DETAIL_STR((__VA_ARGS__))  );                                                   \
        }() );                                                                                                         \
        return _reflector;                                                                                             \
    }
}

#endif //SRENGINE_ENUMREFLECTOR_H
