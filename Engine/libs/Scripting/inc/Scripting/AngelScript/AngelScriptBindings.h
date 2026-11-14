//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BINDINGS_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BINDINGS_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/stdInclude.h>

#include <Utils/Reflection/Value.h>
#include <Utils/Reflection/Method.h>
#include <Utils/Reflection/Property.h>
#include <Utils/Types/FlatHashMap.h>
#include <Utils/Types/SharedPtrDynamicData.h>

#include <angelscript.h>

namespace SR_SCRIPTING_NS {
    class AngelScriptBindings;
    struct SR_SCRIPTING_DLL_API AngelScriptNativeObject {
        SR_UTILS_NS::Reflection::Value value;
        AngelScriptNativeObject* pAnchor = nullptr;
        SR_UTILS_NS::SRClass* pAllocation = nullptr;
        AngelScriptBindings* pBindings = nullptr;
        const SR_HTYPES_NS::SharedPtrDynamicData* pSharedControl = nullptr;
        uint32_t references = 1;

        ~AngelScriptNativeObject();
        void AddRef();
        void Release();
        bool IsAlive() const;
        SR_UTILS_NS::SRClass* GetObject() const;
    };

    /// One runtime dispatcher for all factory types; no per-C++-type binding instantiations.
    class SR_SCRIPTING_DLL_API AngelScriptBindings : public asIStringFactory {
    public:
        static constexpr asPWORD NativeTypeUserData = 0x53524153;

        struct Type {
            SR_UTILS_NS::String name;
            int32_t scriptTypeId = 0;
            SR_UTILS_NS::Reflection::TypeInfo* pTypeInfo = nullptr;
            const SR_UTILS_NS::SRClassMeta* pMeta = nullptr;

            ~Type();
        };

        struct Call {
            struct Frame {
                SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::Value> arguments;
                SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::Value*> pointers;
            };

            Call() = default;
            explicit Call(const SR_UTILS_NS::Reflection::Property& initial)
                : property(initial)
            { }

            AngelScriptBindings* pBindings = nullptr;
            Type* pOwner = nullptr;
            SR_UTILS_NS::Reflection::Method method;
            SR_UTILS_NS::Reflection::Property property;
            SR_UTILS_NS::Reflection::TypeInfo* pPropertyType = nullptr;
            uint32_t component = 0;
            SR_UTILS_NS::Vector<Frame*> frames;
            uint32_t activeFrames = 0;

            Frame* AddFrame();
            ~Call();
        };

        explicit AngelScriptBindings(asIScriptEngine* pEngine);
        ~AngelScriptBindings() override;
        bool RegisterFactory();

    public:
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
        bool WriteProperty(asIScriptObject* pObject, uint32_t index, const SR_UTILS_NS::Reflection::Value& value) const;
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
        SR_UTILS_NS::Vector<Type*> m_types;
        SR_UTILS_NS::Vector<Call*> m_calls;
        bool m_hasNameConflicts = false;
        mutable SR_HTYPES_NS::FlatHashMap<const SR_HTYPES_NS::SharedPtrDynamicData*, AngelScriptNativeObject*> m_sharedObjects;
    };
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_BINDINGS_H
