//
// Created by Monika on 25.08.2023.
//

#ifndef SR_ENGINE_SRLM_UTILS_H
#define SR_ENGINE_SRLM_UTILS_H

#include <Utils/Common/HashManager.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/Function.h>
#include <Utils/ResourceManager/FileWatcher.h>

#define SR_LM_REGISTER_BASE(className, name)                                                                            \
        SR_INLINE_STATIC const std::string NAME = #name; /** NOLINT*/                                                   \
        SR_INLINE_STATIC const uint64_t HASH_NAME = SR_HASH_STR_REGISTER(#name); /** NOLINT*/                           \
        static className* AllocateNew() { return new className(); }                                                     \
            static DataType* AllocateBase() { return (DataType*)new className(); }                                          \
        SR_INLINE_STATIC const bool REGISTER_STATUS = SR_SRLM_NS::DataTypeAllocator::Instance().Register( /** NOLINT*/  \
            DataTypeClass::name, HASH_NAME, []() -> DataType* { return AllocateBase(); }                                \
        );                                                                                                              \
        SR_NODISCARD DataTypeClass GetClass() const noexcept override { return DataTypeClass::name; }                   \

#define SR_LM_REGISTER_TYPE_NO_META(className, name)                                                                    \
    public:                                                                                                             \
        SR_NODISCARD std::string GetName() const noexcept override { return #name; }                                    \
        SR_NODISCARD Hash GetHashName() const noexcept override { return HASH_NAME; }                                   \
        SR_LM_REGISTER_BASE(className, name)                                                                            \

/// --------------------------------------------------------------------------------------------------------------------

#define SR_LM_REGISTER_TYPE(className, name)                                                                            \
    public:                                                                                                             \
        SR_LM_REGISTER_TYPE_NO_META(className, name)                                                                    \
        SR_NODISCARD Meta GetMeta() const noexcept override {                                                           \
            Hash hash = GetHashName();                                                                                  \
            for (auto&& pData : GetMetaData()) { hash = SR_COMBINE_HASHES(hash, pData->GetMeta()); }                    \
            return hash;                                                                                                \
        }                                                                                                               \

/// --------------------------------------------------------------------------------------------------------------------

#define SR_LM_REGISTER_TYPE_GETTER_SETTER(className, name, type)                                                        \
    public:                                                                                                             \
        SR_LM_REGISTER_TYPE(className, name)                                                                            \
        SR_NODISCARD type GetValue() const noexcept { return m_value; }                                                 \
        void SetValue(const type& value) { m_value = value; }                                                           \
        SR_NODISCARD void* GetRawValue() const noexcept override { return const_cast<void*>((const void*)&m_value); }   \
        DataType* SetRawValue(void* pValue) override { m_value = *(type*)pValue; return (DataType*)this; }              \

/// --------------------------------------------------------------------------------------------------------------------

#define SR_LM_REGISTER_TYPE_SG_COPY(className, base, name, type)                                                        \
        SR_LM_REGISTER_TYPE_GETTER_SETTER(className, name, type)                                                        \
        SR_NODISCARD DataType* Copy() const override {                                                                  \
            return new className(m_value);                                                                              \
        }                                                                                                               \
        void CopyTo(DataType* pData) const override { pData->SetCustomValue(*(type*)GetRawValue()); }                   \

/// --------------------------------------------------------------------------------------------------------------------

#define SR_LM_REGISTER_TYPE_FULL(className, base, name, type, defValue)                                                 \
        SR_LM_REGISTER_TYPE_SG_COPY(className, base, name, type)                                                        \
        className() = default;                                                                                          \
        explicit className(const type& value)                                                                           \
            : base()                                                                                                    \
            , m_value(value)                                                                                            \
        { }                                                                                                             \
        void Reset() override { m_value = defValue; }                                                                   \
protected:                                                                                                              \
        type m_value = defValue;                                                                                        \

/// --------------------------------------------------------------------------------------------------------------------

#define SR_LM_REGISTER_TYPE_FULL_MOVE(className, base, name, type, defValue)                                            \
        SR_LM_REGISTER_TYPE_SG_COPY(className, base, name, type)                                                        \
        className() = default;                                                                                          \
        explicit className(type value)                                                                                  \
            : base()                                                                                                    \
            , m_value(std::move(value))                                                                                 \
        { }                                                                                                             \
        void Reset() override { m_value = defValue; }                                                                   \
    protected:                                                                                                          \
        type m_value = defValue;                                                                                        \

/// --------------------------------------------------------------------------------------------------------------------

#define SR_INIT_LOGICAL_NODE(className, name)                                                                           \
public:                                                                                                                 \
        SR_INLINE_STATIC const uint64_t HASH_NAME = SR_HASH_STR_REGISTER(#name); /** NOLINT*/                           \
        SR_NODISCARD std::string GetNodeName() const noexcept override { return #name; }                                \
        SR_NODISCARD Hash GetNodeHashName() const noexcept override { return HASH_NAME; }                               \
        static SR_SRLM_NS::LogicalNode* AllocateNew() { return (new className())->GetBaseLogicalNode(); }               \

#define SR_REGISTER_LOGICAL_NODE(className, name, category)                                                             \
public:                                                                                                                 \
        SR_INIT_LOGICAL_NODE(className, name)                                                                           \
        SR_INLINE_STATIC const bool REGISTER_STATUS = SR_SRLM_NS::LogicalNodeManager::Instance().Register( /** NOLINT*/ \
            HASH_NAME, []() -> SR_SRLM_NS::LogicalNode* {                                                               \
                return AllocateNew();                                                                                   \
            }, std::vector<std::string> category                                                                        \
        );                                                                                                              \

#endif //SR_ENGINE_SRLM_UTILS_H
