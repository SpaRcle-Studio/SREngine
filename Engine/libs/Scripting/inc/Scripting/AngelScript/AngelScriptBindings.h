//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BINDINGS_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BINDINGS_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/stdInclude.h>

#include <Utils/Reflection/Value.h>
#include <Utils/Reflection/ValuePool.h>
#include <Utils/Reflection/Method.h>
#include <Utils/Reflection/Property.h>
#include <Utils/Types/FlatHashMap.h>
#include <Utils/Types/SharedPtrDynamicData.h>
#include <Utils/Memory/Allocator.h>

#include <angelscript.h>

namespace SR_SCRIPTING_NS {
    class AngelScriptBindings;
    struct SR_SCRIPTING_DLL_API AngelScriptNativeObject {
        AngelScriptBindings* pBindings = nullptr;
        AngelScriptNativeObject* pAnchor = nullptr;
        SR_UTILS_NS::SRClass* pAllocation = nullptr;
        SR_UTILS_NS::Reflection::Value value;
        const SR_HTYPES_NS::SharedPtrDynamicData* pSharedControl = nullptr;
        const SR_UTILS_NS::SRClass* pIdentity = nullptr;
        uint32_t references = 1;

        explicit AngelScriptNativeObject(AngelScriptBindings* pBind);
        ~AngelScriptNativeObject();

        void AddRef();
        void Release();

        SR_NODISCARD bool IsAlive() const;
        SR_NODISCARD SR_UTILS_NS::SRClass* GetObject() const;
    };

    /// One runtime dispatcher for all factory types; no per-C++-type binding instantiations.
    class SR_SCRIPTING_DLL_API AngelScriptBindings : public asIStringFactory {
    public:
        static constexpr asPWORD NativeTypeUserData = 0x53524153;

        struct Type {
            SR_UTILS_NS::String name;
            int32_t scriptTypeId = 0;
            const SR_UTILS_NS::Reflection::TypeInfo* pTypeInfo = nullptr;
            const SR_UTILS_NS::SRClassMeta* pMeta = nullptr;
            bool isGeneratedVector = false;

            SR_NODISCARD bool IsValue() const {
                return pTypeInfo->IsMath() || pTypeInfo->IsString() ||
                    pTypeInfo->kind == SR_UTILS_NS::Reflection::TypeKind::Vector;
            }
        };

        struct Call {
            struct Frame {
                SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::Value> arguments;
                SR_UTILS_NS::Vector<void*> pointers;
                SR_UTILS_NS::Reflection::Value result;
            };

            Call() = default;

            explicit Call(SR_UTILS_NS::Reflection::Property initial)
                : method()
                , property(std::move(initial)) {
            }

            AngelScriptBindings* pBindings = nullptr;
            Type* pOwner = nullptr;
            SR_UTILS_NS::Reflection::Method method;
            SR_UTILS_NS::Reflection::Property property;
            const SR_UTILS_NS::Reflection::TypeInfo* pPropertyType = nullptr;
            bool propertyReference = false;
            uint32_t component = 0;
            SR_UTILS_NS::Vector<Frame*> frames;
            SR_UTILS_NS::Vector<bool> directArguments;
            bool directResult = false;
            uint32_t activeFrames = 0;
            SR_UTILS_NS::Reflection::ValuePool* pResultPool = nullptr;

            Frame* AddFrame();
            ~Call();
        };
    public:
        explicit AngelScriptBindings(asIScriptEngine* pEngine);
        ~AngelScriptBindings() override;

    public:
        bool RegisterFactory();
        SR_NODISCARD uint64_t GetStorageId() const {
            return m_storageId;
        }
        Type* ResolveVectorType(asITypeInfo* pScriptType);
        void ForgetType(int32_t typeId);

        SR_UTILS_NS::String Declaration(const SR_UTILS_NS::Reflection::TypeInfo& info) const;
        Type* FindType(int32_t typeId) const;
        Type* FindType(const SR_UTILS_NS::Reflection::TypeInfo& info) const;
        SR_UTILS_NS::Reflection::Value Read(asIScriptGeneric* pCall, uint32_t index, const SR_UTILS_NS::Reflection::TypeInfo& expected) const;
        bool ReadInto(asIScriptGeneric* pCall, uint32_t index, const SR_UTILS_NS::Reflection::TypeInfo& expected, SR_UTILS_NS::Reflection::Value& destination) const;
        void Return(asIScriptGeneric* pCall, SR_UTILS_NS::Reflection::Value value, AngelScriptNativeObject* pAnchor = nullptr) const;
        AngelScriptNativeObject* Wrap(SR_UTILS_NS::Reflection::Value value, AngelScriptNativeObject* pAnchor = nullptr) const;
        bool CopyTo(const SR_UTILS_NS::Reflection::Value& source, SR_UTILS_NS::Reflection::Value& destination) const;
        SR_UTILS_NS::Reflection::Value CopyValue(const SR_UTILS_NS::Reflection::Value& source) const;
        SR_UTILS_NS::Reflection::Value ReadProperty(asIScriptObject* pObject, uint32_t index) const;
        const SR_UTILS_NS::Vector<Type*>& GetTypes() const { return m_types; }
        bool WriteProperty(asIScriptObject* pObject, uint32_t index, const SR_UTILS_NS::Reflection::Value& value) const;

        SR_NODISCARD AngelScriptNativeObject* AllocateNativeObject() const;
        void Forget(AngelScriptNativeObject* pObject) const;

    public:
        const void* GetStringConstant(const char* pData, asUINT length) override;
        int32_t ReleaseStringConstant(const void* pString) override;
        int32_t GetRawStringData(const void* pString, char* pData, asUINT* pLength) const override;

    private:
        Type* Collect(const SR_UTILS_NS::Reflection::TypeInfo& info);
        bool RegisterType(Type& type);
        bool RegisterMembers(Type& type);
        bool Check(int32_t result, SR_UTILS_NS::StringView declaration) const;
        SR_UTILS_NS::String Argument(const SR_UTILS_NS::Reflection::TypeInfo& info) const;
        SR_UTILS_NS::Reflection::Value Convert(const SR_UTILS_NS::Reflection::Value& value, const SR_UTILS_NS::Reflection::TypeInfo& expected) const;

    private:
        asIScriptEngine* m_pEngine = nullptr;
        uint64_t m_storageId = 0;
        SR_UTILS_NS::Vector<Type*> m_types;
        SR_HTYPES_NS::FlatHashMap<int32_t, Type*> m_typesById;
        SR_HTYPES_NS::FlatHashMap<const SR_UTILS_NS::Reflection::TypeInfo*, Type*> m_typesByInfo;
        SR_UTILS_NS::Vector<Call*> m_calls;
        bool m_hasNameConflicts = false;
        mutable SR_HTYPES_NS::FlatHashMap<const SR_HTYPES_NS::SharedPtrDynamicData*, AngelScriptNativeObject*> m_sharedObjects;
        mutable SR_HTYPES_NS::FlatHashMap<const SR_UTILS_NS::SRClass*, AngelScriptNativeObject*> m_nativeObjects;
        SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::MonotonicAllocator> m_nativeObjectPoolAllocator;
        mutable SR_UTILS_NS::Vector<AngelScriptNativeObject*> m_freeNativeObjectPool;
        mutable SR_UTILS_NS::Vector<AngelScriptNativeObject*> m_allocatedNativeObjectPool;
    };
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BINDINGS_H
