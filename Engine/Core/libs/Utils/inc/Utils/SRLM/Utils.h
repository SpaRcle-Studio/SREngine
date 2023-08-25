//
// Created by Monika on 25.08.2023.
//

#ifndef SRENGINE_SRLM_UTILS_H
#define SRENGINE_SRLM_UTILS_H

#include <Utils/Common/Hashes.h>

#define SR_LM_REGISTER_TYPE(name)                                                                                   \
    public:                                                                                                         \
        SR_INLINE_STATIC const uint64_t HASH_NAME = SR_HASH_STR(#name); /** NOLINT*/                                \
        SR_NODISCARD Meta GetMeta() const noexcept override {                                                       \
            return 0;                                                                                               \
        }                                                                                                           \
        SR_NODISCARD std::string GetName() const noexcept override { return #name; }                                \

#define SR_LM_REGISTER_TYPE_GETTER_SETTER(name, type)                                                               \
    public:                                                                                                         \
        SR_LM_REGISTER_TYPE(name)                                                                                   \
        SR_NODISCARD type GetValue() const noexcept { return m_value; }                                             \
        void SetValue(const type& value) { m_value = value; }                                                       \

#define SR_LM_REGISTER_TYPE_SG_COPY(className, base, name, type)                                                    \
        SR_LM_REGISTER_TYPE_GETTER_SETTER(name, type)                                                               \
        SR_NODISCARD DataType* Copy() const override {                                                              \
            return new className(m_value);                                                                          \
        }                                                                                                           \

#define SR_LM_REGISTER_TYPE_FULL(className, base, name, type, defValue)                                             \
        SR_LM_REGISTER_TYPE_SG_COPY(className, base, name, type)                                                    \
        className() = default;                                                                                      \
        explicit className(const type& value)                                                                       \
            : base()                                                                                                \
            , m_value(value)                                                                                        \
        { }                                                                                                         \
    protected:                                                                                                      \
        type m_value = defValue;                                                                                    \

#define SR_LM_REGISTER_TYPE_FULL_MOVE(className, base, name, type, defValue)                                        \
        SR_LM_REGISTER_TYPE_SG_COPY(className, base, name, type)                                                    \
        className() = default;                                                                                      \
        explicit className(type value)                                                                              \
            : base()                                                                                                \
            , m_value(std::move(value))                                                                             \
        { }                                                                                                         \
    protected:                                                                                                      \
        type m_value = defValue;                                                                                    \

#endif //SRENGINE_SRLM_UTILS_H
