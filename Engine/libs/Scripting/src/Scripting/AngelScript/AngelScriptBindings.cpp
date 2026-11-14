//
// Created by Codex on 13.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptBindings.h>
#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>
#include <Scripting/AngelScript/AngelScriptMathHelpers.h>
#include <Scripting/Base/ScriptSystem.h>

#include <Utils/TypeTraits/Factory.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Reflection/TypeInfoSerialization.h>
#include <Utils/Common/EnumReflector.h>
#include <Utils/Memory/Allocator.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Types/UnicodeString.h>
#include <Utils/Localization/UTF.h>
#include <Utils/Common/Singleton.h>

namespace SR_SCRIPTING_NS {
    AngelScriptNativeObject::~AngelScriptNativeObject() {
        if (pBindings) {
            pBindings->Forget(this);
        }

        value = {};
        delete pAllocation;

        if (pAnchor) {
            pAnchor->Release();
        }
    }

    void AngelScriptNativeObject::AddRef() {
        ++references;
    }

    void AngelScriptNativeObject::Release() {
        if (--references == 0) {
            delete this;
        }
    }

    bool AngelScriptNativeObject::IsAlive() const {
        if (auto&& pPointer = value.GetSharedPtrBase(); pPointer && !pPointer->Valid()) {
            return false;
        }
        return !pAnchor || pAnchor->IsAlive();
    }

    SR_UTILS_NS::SRClass* AngelScriptNativeObject::GetObject() const {
        if (!IsAlive()) {
            return nullptr;
        }
        return value.GetSRClass();
    }

    AngelScriptBindings::Type::~Type() {
        SR_UTILS_NS::Reflection::FreeTypeInfo(pTypeInfo);
    }

    AngelScriptBindings::Call::~Call() {
        SR_UTILS_NS::Reflection::FreeTypeInfo(pPropertyType);
        for (auto&& pFrame : frames) {
            delete pFrame;
        }
    }

    AngelScriptBindings::Call::Frame* AngelScriptBindings::Call::AddFrame() {
        SR_TRACY_ZONE;
        auto&& pFrame = new Frame();
        pFrame->arguments.reserve(method.GetParamsCount());
        pFrame->pointers.reserve(method.GetParamsCount());
        for (uint32_t i = 0; i < method.GetParamsCount(); ++i) {
            auto&& pTypeInfo = method.GetParam(i).pTypeInfo;
            pFrame->arguments.emplace_back(AngelScriptBindingHelpers::Primitive(*pTypeInfo) ?
                SR_UTILS_NS::Reflection::Value::CreateDefault(pTypeInfo) : SR_UTILS_NS::Reflection::Value());
            pFrame->pointers.emplace_back(&pFrame->arguments.back());
        }

        frames.emplace_back(pFrame);
        return pFrame;
    }

    AngelScriptBindings::AngelScriptBindings(asIScriptEngine* pEngine)
        : m_pEngine(pEngine)
    {
        m_types.reserve(2048);
        m_calls.reserve(2048);
    }

    AngelScriptBindings::~AngelScriptBindings() {
        for (auto&& pCall : m_calls) {
            delete pCall;
        }

        for (auto&& pType : m_types) {
            delete pType;
        }
    }

    bool AngelScriptBindings::Check(int32_t result, SR_UTILS_NS::StringView declaration) const {
        if (result >= 0) {
            return true;
        }

        SR_ERROR("AngelScriptBindings::Check() : AngelScript registration failed ({}): {}", result, declaration);
        return false;
    }

    AngelScriptBindings::Type* AngelScriptBindings::FindType(const SR_UTILS_NS::Reflection::TypeInfo& info) const {
        SR_TRACY_ZONE;

        if (info.detailedType == "SharedPtr" && info.pNext[0]) {
            return FindType(*info.pNext[0]);
        }

        for (auto&& pType : m_types) {
            if (*pType->pTypeInfo == info || (pType->pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String && info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String)) {
                return pType;
            }
        }

        return nullptr;
    }

    AngelScriptBindings::Type* AngelScriptBindings::FindType(int32_t typeId) const {
        auto&& pInfo = m_pEngine->GetTypeInfoById(typeId);
        if (!pInfo) {
            return nullptr;
        }

        for (auto&& pType : m_types) {
            if (pType->scriptTypeId == pInfo->GetTypeId()) {
                return pType;
            }
        }

        return nullptr;
    }

    SR_UTILS_NS::String AngelScriptBindings::Declaration(const SR_UTILS_NS::Reflection::TypeInfo& info) const {
        SR_TRACY_ZONE;
        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String && info.detailedType != "String" &&
            info.detailedType != "StringAtom" && info.detailedType != "Path" && info.detailedType != "StringView" && info.detailedType != "UnicodeString") {
            return {};
        }

        if (AngelScriptBindingHelpers::Primitive(info)) {
            return info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Arithmetic || FindType(info) ?
                AngelScriptBindingHelpers::PrimitiveName(info) : SR_UTILS_NS::String();
        }

        auto&& pType = FindType(info);
        return pType ? pType->name + "@" : SR_UTILS_NS::String();
    }

    SR_UTILS_NS::String AngelScriptBindings::Argument(const SR_UTILS_NS::Reflection::TypeInfo& info) const {
        const auto declaration = Declaration(info);
        if (declaration.empty() || AngelScriptBindingHelpers::Primitive(info)) {
            return declaration;
        }

        if (info.detailedType == "SharedPtr") {
            return declaration + "+";
        }

        auto&& pType = FindType(info);
        return pType ? "const " + pType->name + " &in" : SR_UTILS_NS::String();
    }

    AngelScriptBindings::Type* AngelScriptBindings::Collect(const SR_UTILS_NS::Reflection::TypeInfo& info) {
        SR_TRACY_ZONE;

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Unknown) {
            return nullptr;
        }

        if (info.detailedType == "SharedPtr") {
            return info.pNext[0] ? Collect(*info.pNext[0]) : nullptr;
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String && info.detailedType != "String" &&
            info.detailedType != "StringAtom" && info.detailedType != "Path" && info.detailedType != "StringView" && info.detailedType != "UnicodeString") {
            return nullptr;
        }

        if (auto&& pFound = FindType(info)) {
            return pFound;
        }

        auto&& infoIdentifier = AngelScriptBindingHelpers::Identifier(info);
        for (auto&& pExisting : m_types) {
            if (pExisting->name == infoIdentifier) {
                SR_ERROR("AngelScriptBindings::Collect() : AngelScript: reflected types have the same script name: {}", pExisting->name);
                m_hasNameConflicts = true;
                return nullptr;
            }
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(info.detailedType);
            if (!pReflector) {
                return nullptr;
            }

            for (auto&& name : pReflector->GetNamesInternal()) {
                const auto number = pReflector->FromStringInternal(name);
                if (!number || *number < INT32_MIN || *number > UINT32_MAX) {
                    return nullptr;
                }
            }
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String && info.detailedType != "String") {
            auto&& pStringType = SR_UTILS_NS::Reflection::LoadTypeInfo("String.String");
            if (!pStringType) {
                return nullptr;
            }

            SR_UTILS_NS::Reflection::FindVTable(*pStringType);
            auto&& pResult = Collect(*pStringType);
            SR_UTILS_NS::Reflection::FreeTypeInfo(pStringType);

            return pResult;
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container &&
            info.detailedType != "Vector" && info.detailedType != "Map" && info.detailedType != "Set" &&
            info.detailedType != "FlatHashMap" && info.detailedType != "FlatHashSet" &&
            info.detailedType != "Optional" && info.detailedType != "EntityRef" && info.detailedType != "ResourceRef") {
            return nullptr;
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container) {
            if (AngelScriptBindingHelpers::HasBorrowedView(info)) {
                return nullptr;
            }

            auto&& pElement = info.pNext[0];
            if (!pElement) {
                return nullptr;
            }

            if (info.detailedType == "Map" || info.detailedType == "FlatHashMap") {
                if (!pElement->pNext[0] || !pElement->pNext[1] || !Collect(*pElement->pNext[0]) || !Collect(*pElement->pNext[1])) {
                    return nullptr;
                }
            }
            else if (!Collect(*pElement)) {
                return nullptr;
            }
        }

        auto&& pType = new Type();
        pType->name = infoIdentifier;
        pType->pTypeInfo = SR_UTILS_NS::Reflection::CopyTypeInfo(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(&info));

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Object) {
            pType->pMeta = SR_UTILS_NS::Factory::Instance().GetType(info.detailedType);

            if (!pType->pMeta) {
                delete pType;
                return nullptr;
            }

            auto&& pRegistration = SR_UTILS_NS::Factory::Instance().GetTypeInfo(info.detailedType);
            auto&& pCpp = ScriptSystem::Instance().GetCppSystem();

            if (pRegistration && pCpp && pCpp->GetModuleManager()->IsRuntimeModule(pRegistration->moduleName)) {
                delete pType;
                return nullptr;
            }
        }

        m_types.emplace_back(pType);
        return pType;
    }

    bool AngelScriptBindings::RegisterFactory() {
        SR_TRACY_ZONE;
        SR_LOG("AngelScriptBindings::RegisterFactory() : registering reflected API.");

        auto&& pStringType = SR_UTILS_NS::Reflection::LoadTypeInfo("String.String");

        if (!pStringType || !SR_UTILS_NS::Reflection::FindVTable(*pStringType)) {
            SR_UTILS_NS::Reflection::FreeTypeInfo(pStringType);
            return false;
        }

        Collect(*pStringType);
        SR_UTILS_NS::Reflection::FreeTypeInfo(pStringType);

        SR_UTILS_NS::Factory::Instance().ForEachClass([this](const SR_UTILS_NS::SRClassMeta* pMeta) {
            // C++ gameplay DLLs can be unloaded; do not retain their function pointers in the VM.
            if (pMeta->IsSameOrInherited("CppBehaviour")) {
                return;
            }

            SR_UTILS_NS::Reflection::TypeInfo info;
            info.category = SR_UTILS_NS::Reflection::ReflectedCategoryType::Object;
            info.detailedType = pMeta->GetFactoryName();
            info.vtable = pMeta->GetVTable();

            auto&& pType = Collect(info);
            if (!pType) {
                return;
            }

            pMeta->ForEachProperty([this](const SR_UTILS_NS::Reflection::Property& property, uint64_t) {
                Collect(property.GetDefaultValue().GetTypeInfo());
            });
            pMeta->ForEachMethod([this](const SR_UTILS_NS::Reflection::Method& method, uint64_t) {
                if (method.GetReturnType()) {
                    Collect(*method.GetReturnType());
                }

                for (uint32_t i = 0; i < method.GetParamsCount(); ++i) {
                    Collect(*method.GetParam(i).pTypeInfo);
                }
            });
        });

        if (m_hasNameConflicts) {
            return false;
        }

        const char* pStorageTypes[] = { "StringAtom", "Path", "UnicodeString" };
        for (auto&& pName : pStorageTypes) {
            if (!Check(m_pEngine->RegisterObjectType(pName, 0, asOBJ_REF | asOBJ_NOCOUNT), pName)) {
                return false;
            }
        }

        const char* pTemplates[] = { "Vector", "Map", "Set", "FlatHashMap", "FlatHashSet", "Optional", "EntityRef", "ResourceRef" };
        for (auto&& pName : pTemplates) {
            const SR_UTILS_NS::String name(pName);
            const bool map = name == "Map" || name == "FlatHashMap";
            const auto declaration = name + (map ? "<class K, class V>" : "<class T>");
            if (!Check(m_pEngine->RegisterObjectType(declaration.c_str(), 0, asOBJ_REF | asOBJ_NOCOUNT | asOBJ_TEMPLATE), declaration)) {
                return false;
            }
        }

        // Register ordinary types before specializations that use them as subtypes.
        for (auto&& pType : m_types) {
            if (pType->pTypeInfo->category != SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && !RegisterType(*pType)) {
                return false;
            }
        }

        for (auto&& pType : m_types) {
            if (pType->pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && !RegisterType(*pType)) {
                return false;
            }
        }

        // Unsupported instances must not be generated once native specializations are registered.
        for (auto&& pName : pTemplates) {
            const SR_UTILS_NS::String name(pName);
            const auto instance = name + ((name == "Map" || name == "FlatHashMap") ? "<K, V>" : "<T>");
            if (!Check(m_pEngine->RegisterObjectBehaviour(instance.c_str(), asBEHAVE_TEMPLATE_CALLBACK, "bool f(int&in, bool&out)", asFUNCTION(AngelScriptBindingHelpers::RejectTemplate), asCALL_GENERIC), instance)) {
                return false;
            }
        }

        if (!Check(m_pEngine->RegisterStringFactory("string", this), "string literals")) {
            return false;
        }

        for (auto&& pType : m_types) {
            if (!RegisterMembers(*pType)) {
                return false;
            }
        }

        auto&& pSingletonManager = SR_UTILS_NS::GetSingletonManager();
        for (auto&& pType : m_types) {
            if (!pType->pMeta) {
                continue;
            }

            auto&& factoryName = pType->pMeta->GetFactoryName();
            const auto singletonHash = SR_UTILS_NS::SingletonManager::GetOrAddSingletonHashName(factoryName.c_str());
            if (!pSingletonManager->GetSingletonMeta(singletonHash)) {
                continue;
            }

            auto&& pBinding = new Call();
            pBinding->pBindings = this;
            pBinding->pOwner = pType;
            m_calls.emplace_back(pBinding);

            if (!Check(m_pEngine->SetDefaultNamespace(factoryName.c_str()), factoryName) ||
                !Check(m_pEngine->RegisterGlobalFunction((pType->name + "@ Instance()").c_str(), asFUNCTION(AngelScriptBindingHelpers::SingletonInstance), asCALL_GENERIC, pBinding), pType->name + "::Instance()") ||
                !Check(m_pEngine->SetDefaultNamespace(""), "global namespace context")) {
                m_pEngine->SetDefaultNamespace("");
                return false;
            }
        }

        if (!Check(m_pEngine->RegisterInterface("IBehaviour"), "IBehaviour")) {
            return false;
        }

        SR_LOG("AngelScriptBindings::RegisterFactory() : API registered, types: {}, call bindings: {}.", m_types.size(), m_calls.size());
        return true;
    }

    bool AngelScriptBindings::RegisterType(Type& type) {
        SR_TRACY_ZONE;
        if (type.pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Arithmetic) {
            return true;
        }

        if (type.pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(type.pTypeInfo->detailedType);

            if (!pReflector || !Check(m_pEngine->RegisterEnum(type.name.c_str()), type.name)) {
                return false;
            }

            for (auto&& name : pReflector->GetNamesInternal()) {
                const auto number = pReflector->FromStringInternal(name);

                if (!number || *number < INT32_MIN || *number > UINT32_MAX) {
                    SR_ERROR("AngelScriptBindings::RegisterType() : AngelScript enum value does not fit int32: {}::{}", type.name, name);

                    return false;
                }

                if (!Check(m_pEngine->RegisterEnumValue(type.name.c_str(), name.c_str(), static_cast<int32_t>(*number)), type.name)) {
                    return false;
                }
            }

            type.scriptTypeId = m_pEngine->GetTypeIdByDecl(type.name.c_str());
            return true;
        }

        if (!Check(m_pEngine->RegisterObjectType(type.name.c_str(), 0, asOBJ_REF), type.name)) {
            return false;
        }

        type.scriptTypeId = m_pEngine->GetTypeIdByDecl(type.name.c_str());
        m_pEngine->GetTypeInfoById(type.scriptTypeId)->SetUserData(this, NativeTypeUserData);
        return Check(m_pEngine->RegisterObjectBehaviour(type.name.c_str(), asBEHAVE_ADDREF, "void f()", asFUNCTION(AngelScriptBindingHelpers::AddRef), asCALL_GENERIC), type.name) &&
            Check(m_pEngine->RegisterObjectBehaviour(type.name.c_str(), asBEHAVE_RELEASE, "void f()", asFUNCTION(AngelScriptBindingHelpers::Release), asCALL_GENERIC), type.name);
    }

    bool AngelScriptBindings::RegisterMembers(Type& type) {
        SR_TRACY_ZONE;

        if (AngelScriptBindingHelpers::Primitive(*type.pTypeInfo)) {
            return true;
        }

        auto&& pGeneral = new Call();
        pGeneral->pBindings = this;
        pGeneral->pOwner = &type;
        m_calls.emplace_back(pGeneral);
        auto&& pRegistration = type.pMeta ? SR_UTILS_NS::Factory::Instance().GetTypeInfo(type.pMeta->GetFactoryName()) : nullptr;

        if ((!type.pMeta && type.pTypeInfo->vtable.pConstructor) || (pRegistration && !pRegistration->isAbstract && pRegistration->allocator)) {
            const auto pDeclaration = type.name + "@ f()";

            if (!Check(m_pEngine->RegisterObjectBehaviour(type.name.c_str(), asBEHAVE_FACTORY, pDeclaration.c_str(), asFUNCTION(AngelScriptBindingHelpers::Construct), asCALL_GENERIC, pGeneral), pDeclaration)) {
                return false;
            }
        }

        if (type.pTypeInfo->vtable.pCopy) {
            const auto pDeclaration = type.name + "& opAssign(const " + type.name + " &in)";

            if (!Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), pDeclaration.c_str(), asFUNCTION(AngelScriptBindingHelpers::Assign), asCALL_GENERIC, pGeneral), pDeclaration)) {
                return false;
            }
        }

        if (type.pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String) {
            const char* pDeclarations[] = { "uint length() const", "bool opEquals(const string &in) const", "string@ opAdd(const string &in) const" };

            for (auto&& pDeclaration : pDeclarations) {
                if (!Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), pDeclaration, asFUNCTION(AngelScriptBindingHelpers::StringOperation), asCALL_GENERIC, pGeneral), pDeclaration)) {
                    return false;
                }
            }
        }

        const auto layout = AngelScriptMathHelpers::Describe(*type.pTypeInfo);

        for (uint32_t i = 0; i < layout.count; ++i) {
            auto&& component = layout.components[i];
            auto&& pScalar = SR_UTILS_NS::Reflection::LoadTypeInfo("Arithmetic." + SR_UTILS_NS::String(component.pScalar));

            if (!pScalar || !SR_UTILS_NS::Reflection::FindVTable(*pScalar)) {
                SR_UTILS_NS::Reflection::FreeTypeInfo(pScalar);
                return false;
            }

            auto&& pBinding = new Call();
            pBinding->pBindings = this;
            pBinding->pOwner = &type;
            pBinding->component = component.offset;
            pBinding->pPropertyType = pScalar;
            m_calls.emplace_back(pBinding);

            const auto getter = AngelScriptBindingHelpers::PrimitiveName(*pScalar) + " get_" + SR_UTILS_NS::String(component.pName) + "() const property";
            const auto setter = "void set_" + SR_UTILS_NS::String(component.pName) + "(" + AngelScriptBindingHelpers::PrimitiveName(*pScalar) + ") property";

            if (!Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), getter.c_str(), asFUNCTION(AngelScriptBindingHelpers::MathComponent), asCALL_GENERIC, pBinding), getter) ||
                !Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), setter.c_str(), asFUNCTION(AngelScriptBindingHelpers::MathComponent), asCALL_GENERIC, pBinding), setter)) {
                return false;
            }
        }

        const bool wrapper = type.pTypeInfo->detailedType == "Optional" || type.pTypeInfo->detailedType == "EntityRef" ||
            type.pTypeInfo->detailedType == "ResourceRef";

        if (wrapper || type.pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
            SR_UTILS_NS::Vector<SR_UTILS_NS::String> declarations;

            if (type.pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
                declarations = { "bool hasValue() const", "void reset()", "void set(const ?&in)", "bool get(?&out) const" };
            }
            else {
                auto&& element = *type.pTypeInfo->pNext[0];
                declarations = { "bool hasValue() const", "void reset()" };

                if (type.pTypeInfo->detailedType == "Optional") {
                    declarations.emplace_back(Declaration(element) + " get() const");
                    declarations.emplace_back("void set(" + Argument(element) + ")");
                }
                else {
                    declarations.emplace_back(Declaration(element) + " get() const");
                    declarations.emplace_back(type.pTypeInfo->detailedType == "EntityRef" ? "void setId(uint64)" : "void setId(const string &in)");
                }
            }

            for (auto&& declaration : declarations) {
                if (!Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), declaration.c_str(), asFUNCTION(AngelScriptBindingHelpers::Wrapper), asCALL_GENERIC, pGeneral), declaration)) {
                    return false;
                }
            }
        }

        if (type.pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && !wrapper) {
            auto&& table = type.pTypeInfo->vtable.containerVTable;

            if (!table.pSize || !table.pClear || !table.pBegin || !table.pEnd || !table.pInsert || !table.pErase ||
                !type.pTypeInfo->vtable.iteratorVTable.pOffset || !type.pTypeInfo->vtable.iteratorVTable.pGetValue) {
                return false;
            }

            SR_UTILS_NS::Vector<SR_UTILS_NS::String> pDeclarations = { "uint size() const", "void clear()" };
            const bool map = type.pTypeInfo->detailedType == "Map" || type.pTypeInfo->detailedType == "FlatHashMap";
            auto&& pElement = type.pTypeInfo->pNext[0];

            if (type.pTypeInfo->detailedType == "Vector") {
                const auto value = Declaration(*pElement);
                pDeclarations.emplace_back(value + " at(uint) const");
                pDeclarations.emplace_back("void set(uint, " + Argument(*pElement) + ")");
                pDeclarations.emplace_back("void pushBack(" + Argument(*pElement) + ")");

                if (table.pResize) {
                    pDeclarations.emplace_back("void resize(uint)");
                }
            }
            else {
                if (!table.pFind) {
                    return false;
                }

                const auto key = Argument(map ? *pElement->pNext[0] : *pElement);
                pDeclarations.emplace_back("bool contains(" + key + ") const");
                pDeclarations.emplace_back("void erase(" + key + ")");

                if (map) {
                    const auto value = Declaration(*pElement->pNext[1]);
                    pDeclarations.emplace_back(value + " at(" + key + ") const");
                    pDeclarations.emplace_back("void insert(" + key + ", " + Argument(*pElement->pNext[1]) + ")");
                }
                else {
                    pDeclarations.emplace_back("void insert(" + key + ")");
                }
            }

            for (auto&& pDeclaration : pDeclarations) {
                if (!Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), pDeclaration.c_str(), asFUNCTION(AngelScriptBindingHelpers::Container), asCALL_GENERIC, pGeneral), pDeclaration)) {
                    return false;
                }
            }
        }

        if (!type.pMeta) {
            return true;
        }

        for (auto&& pTarget : m_types) {
            if (!pTarget->pMeta || pTarget == &type || !type.pMeta->IsInherited(pTarget->pMeta->GetFactoryName())) {
                continue;
            }

            auto&& pBinding = new Call();
            pBinding->pBindings = this;
            pBinding->pOwner = pTarget;
            m_calls.emplace_back(pBinding);
            const auto pDeclaration = pTarget->name + "@ opImplCast()";

            if (!Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), pDeclaration.c_str(), asFUNCTION(AngelScriptBindingHelpers::Cast), asCALL_GENERIC, pBinding), pDeclaration)) {
                return false;
            }
        }

        for (auto&& pTarget : m_types) {
            if (!pTarget->pMeta || pTarget == &type || !pTarget->pMeta->IsInherited(type.pMeta->GetFactoryName())) {
                continue;
            }

            auto&& pBinding = new Call();
            pBinding->pBindings = this;
            pBinding->pOwner = pTarget;
            m_calls.emplace_back(pBinding);
            const auto pDeclaration = pTarget->name + "@ opCast()";

            if (!Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), pDeclaration.c_str(), asFUNCTION(AngelScriptBindingHelpers::Cast), asCALL_GENERIC, pBinding), pDeclaration)) {
                return false;
            }
        }

        bool success = true;
        SR_UTILS_NS::Set<SR_UTILS_NS::String> registered;
        type.pMeta->ForEachProperty([&](const SR_UTILS_NS::Reflection::Property& property, uint64_t) {
            if (!success || property.GetPublicity() == SR_UTILS_NS::PropertyPublicity::Hidden ||
                property.GetPublicity() == SR_UTILS_NS::PropertyPublicity::HiddenReadOnly) {
                return;
            }

            auto&& info = property.GetDefaultValue().GetTypeInfo();
            const auto pDeclaration = Declaration(info);

            if (pDeclaration.empty()) {
                SR_WARN("AngelScriptBindings::RegisterMembers() : AngelScript: unsupported property {}::{}", type.name, property.GetName());
                return;
            }

            Call* pBinding = new Call(property);
            pBinding->pBindings = this;
            pBinding->pOwner = &type;
            pBinding->pPropertyType = SR_UTILS_NS::Reflection::CopyTypeInfo(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(&info));
            m_calls.emplace_back(pBinding);

            const auto getter = pDeclaration + " get_" + property.GetName().ToString() + "() property";
            if (registered.insert(getter).second) {
                SR_TRACY_ZONE_N("Getter");
                success &= Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), getter.c_str(), asFUNCTION(AngelScriptBindingHelpers::GetProperty), asCALL_GENERIC, pBinding), getter);
            }

            if (!property.IsReadOnly()) {
                const auto setter = "void set_" + property.GetName().ToString() + "(" + Argument(info) + ") property";
                if (registered.insert(setter).second) {
                    SR_TRACY_ZONE_N("Setter");
                    success &= Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), setter.c_str(), asFUNCTION(AngelScriptBindingHelpers::SetProperty), asCALL_GENERIC, pBinding), setter);
                }
            }
        });
        type.pMeta->ForEachMethod([&](const SR_UTILS_NS::Reflection::Method& method, uint64_t) {
            if (!success) {
                return;
            }

            SR_UTILS_NS::String pDeclaration = method.HasReturn() ? Declaration(*method.GetReturnType()) : SR_UTILS_NS::String("void");

            if (pDeclaration.empty()) {
                return;
            }

            pDeclaration += " " + method.GetName().ToString() + "(";

            for (uint32_t i = 0; i < method.GetParamsCount(); ++i) {
                if (i) {
                    pDeclaration += ", ";
                }

                auto&& param = method.GetParam(i);
                auto argument = Argument(*param.pTypeInfo);

                if (argument.empty() || (param.IsOutput() && AngelScriptBindingHelpers::HasBorrowedView(*param.pTypeInfo))) {
                    SR_WARN("AngelScriptBindings::RegisterMembers() : AngelScript: unsupported signature {}::{}", type.name, method.GetName());

                    return;
                }

                if (param.IsOutput()) {
                    auto&& pParamType = FindType(*param.pTypeInfo);
                    argument = AngelScriptBindingHelpers::Primitive(*param.pTypeInfo) ? argument + " &inout" : pParamType->name + " &inout";
                }

                pDeclaration += argument;
            }

            pDeclaration += ")";

            if (!registered.insert(pDeclaration).second) {
                return;
            }

            auto&& pBinding = new Call();
            pBinding->pBindings = this;
            pBinding->pOwner = &type;
            pBinding->method = method;
            pBinding->AddFrame();
            m_calls.emplace_back(pBinding);
            success &= Check(m_pEngine->RegisterObjectMethod(type.name.c_str(), pDeclaration.c_str(), asFUNCTION(AngelScriptBindingHelpers::Invoke), asCALL_GENERIC, pBinding), pDeclaration);
        });

        return success;
    }

    SR_UTILS_NS::Reflection::Value AngelScriptBindings::Convert(const SR_UTILS_NS::Reflection::Value& value, const SR_UTILS_NS::Reflection::TypeInfo& expected) const {
        if (!value) {
            return {};
        }

        if (value.IsSharedPtr() && !value.GetSharedPtrBase()->Valid()) {
            return expected.detailedType == "SharedPtr" ? SR_UTILS_NS::Reflection::Value::CreateDefault(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(&expected)) : SR_UTILS_NS::Reflection::Value();
        }

        if (value.GetTypeInfo() == expected) {
            return value.Ref();
        }

        if (expected.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
            return SR_UTILS_NS::Reflection::Value::Create(CopyValue(value));
        }

        if (expected.detailedType == "SharedPtr" && expected.pNext[0]) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(expected.pNext[0]->detailedType);

            if (!pMeta) {
                return {};
            }

            if (value.IsSharedPtr()) {
                return pMeta->Cast(value);
            }

            auto&& pObject = value.GetSRClass();

            if (!pObject || !dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(pObject)) {
                return {};
            }

            return pMeta->Cast(AngelScriptBindingHelpers::ShareObject(pObject));
        }

        if (expected.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Object) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(expected.detailedType);
            auto&& pObject = value.GetSRClass();

            return pMeta && pObject ? pMeta->Cast(SR_UTILS_NS::Reflection::Value::CreateRef(*pObject)) : SR_UTILS_NS::Reflection::Value();
        }

        if (expected.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String && value.GetTypeInfo().category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String) {
            if (value.GetTypeInfo().detailedType != "String") {
                return {};
            }

            auto&& text = *value.Cast<SR_UTILS_NS::String>();
            auto result = SR_UTILS_NS::Reflection::Value::CreateDefault(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(&expected));

            if (expected.detailedType == "StringAtom") {
                *result.Cast<SR_UTILS_NS::StringAtom>() = text;
            }
            else if (expected.detailedType == "Path") {
                *result.Cast<SR_UTILS_NS::Path>() = SR_UTILS_NS::Path(text);
            }
            else if (expected.detailedType == "StringView") {
                *result.Cast<SR_UTILS_NS::StringView>() = text;
            }
            else if (expected.detailedType == "UnicodeString") {
                auto&& unicode = *result.Cast<SR_UTILS_NS::UnicodeString>();
                unicode.resize(text.size());
                const char* pCurrent = text.data();
                const char* pEnd = pCurrent + text.size();
                uint64_t count = 0;
                while (pCurrent != pEnd) {
                    const auto code = SR_UTILS_NS::Localization::Utf::UtfTraits<char>::Decode(pCurrent, pEnd);
                    if (!SR_UTILS_NS::Localization::Utf::IsValidCodePoint(code)) {
                        return {};
                    }
                    unicode[count++] = static_cast<char32_t>(code);
                }
                unicode.resize(count);
            }
            else {
                return {};
            }

            return result;
        }

        return {};
    }

    bool AngelScriptBindings::CopyTo(const SR_UTILS_NS::Reflection::Value& source, SR_UTILS_NS::Reflection::Value& destination) const {
        if (destination.IsConst()) {
            return false;
        }

        if (source.GetTypeInfo() == destination.GetTypeInfo() && source.Data() == destination.Data()) {
            return true;
        }

        auto converted = Convert(source, destination.GetTypeInfo());

        if (!converted) {
            return false;
        }

        auto&& info = destination.GetTypeInfo();

        if (AngelScriptBindingHelpers::Primitive(info)) {
            const auto size = info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum ?
                SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(info.detailedType)->GetIntegralTypeSizeInternal() :
                    SR_UTILS_NS::Reflection::GetReflectedTypeSize(info.detailedType);
            memcpy(destination.Data(), converted.Data(), size);
            return true;
        }

        const auto copy = info.vtable.pCopy;
        if (!copy) {
            return false;
        }

        copy(converted.GetStorage(), destination.GetStorage());

        return true;
    }

    SR_UTILS_NS::Reflection::Value AngelScriptBindings::CopyValue(const SR_UTILS_NS::Reflection::Value& source) const {
        if (!source) {
            return {};
        }

        auto&& info = source.GetTypeInfo();

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
            return SR_UTILS_NS::Reflection::Value::Create(CopyValue(*source.Cast<SR_UTILS_NS::Reflection::Value>()));
        }

        if (source.IsSharedPtr() && !source.GetSharedPtrBase()->Valid()) {
            return SR_UTILS_NS::Reflection::Value::CreateDefault(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(&info));
        }

        if (AngelScriptBindingHelpers::Primitive(info)) {
            auto result = SR_UTILS_NS::Reflection::Value::CreateDefault(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(&info));
            CopyTo(source, result);

            return result;
        }

        if (!info.vtable.pCopy || !info.vtable.pConstructor) {
            return {};
        }

        return source.Copy();
    }

    bool AngelScriptBindings::ReadInto(asIScriptGeneric* pCall, uint32_t index, const SR_UTILS_NS::Reflection::TypeInfo& expected, SR_UTILS_NS::Reflection::Value& destination) const {
        if (!AngelScriptBindingHelpers::Primitive(expected)) {
            destination = Read(pCall, index, expected);
            return static_cast<bool>(destination);
        }

        if (!destination) {
            return false;
        }

        asDWORD flags = 0;
        pCall->GetArgTypeId(index, &flags);
        auto&& pAddress = (flags & asTM_INOUTREF) ? pCall->GetArgAddress(index) : pCall->GetAddressOfArg(index);
        if (expected.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(expected.detailedType);
            if (!pReflector) {
                return false;
            }

            int32_t number = 0;
            memcpy(&number, pAddress, sizeof(number));
            pReflector->WriteEnumValueToPointerInternal(destination.Data(), number);
            return true;
        }

        memcpy(destination.Data(), pAddress, SR_UTILS_NS::Reflection::GetReflectedTypeSize(expected.detailedType));
        return true;
    }

    SR_UTILS_NS::Reflection::Value AngelScriptBindings::Read(asIScriptGeneric* pCall, uint32_t index, const SR_UTILS_NS::Reflection::TypeInfo& expected) const {
        if (AngelScriptBindingHelpers::Primitive(expected)) {
            auto result = SR_UTILS_NS::Reflection::Value::CreateDefault(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(&expected));
            asDWORD flags = 0;
            pCall->GetArgTypeId(index, &flags);
            auto&& pAddress = (flags & asTM_INOUTREF) ? pCall->GetArgAddress(index) : pCall->GetAddressOfArg(index);
            const auto size = expected.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum ? sizeof(int32_t) : SR_UTILS_NS::Reflection::GetReflectedTypeSize(expected.detailedType);

            if (expected.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
                auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(expected.detailedType);
                int32_t number = 0;
                memcpy(&number, pAddress, sizeof(number));

                if (!pReflector) {
                    return {};
                }

                pReflector->WriteEnumValueToPointerInternal(result.Data(), number);
                return result;
            }

            memcpy(result.Data(), pAddress, size);

            return result;
        }

        auto&& pObject = static_cast<AngelScriptNativeObject*>(pCall->GetArgObject(index));
        if (!pObject) {
            if (expected.detailedType == "SharedPtr") {
                return SR_UTILS_NS::Reflection::Value::CreateDefault(const_cast<SR_UTILS_NS::Reflection::TypeInfo*>(&expected));
            }

            return {};
        }

        if (!pObject->IsAlive()) {
            return {};
        }

        return Convert(pObject->value, expected);
    }

    AngelScriptNativeObject* AngelScriptBindings::Wrap(SR_UTILS_NS::Reflection::Value value, AngelScriptNativeObject* pAnchor) const {
        SR_TRACY_ZONE;

        if (!value) {
            return nullptr;
        }

        if (pAnchor && !pAnchor->IsAlive()) {
            return nullptr;
        }

        const SR_HTYPES_NS::SharedPtrDynamicData* pSharedControl = nullptr;

        if (value.IsSharedPtr()) {
            auto&& pPointer = value.GetSharedPtrBase();
            if (!pPointer || !pPointer->Valid()) {
                return nullptr;
            }

            pSharedControl = pPointer->GetPtrData();

            if (auto existing = m_sharedObjects.find(pSharedControl); existing != m_sharedObjects.end()) {
                existing->second->AddRef();
                return existing->second;
            }

            value = value.Copy();
        }

        auto&& pObject = new AngelScriptNativeObject();
        pObject->value = std::move(value);
        pObject->pBindings = const_cast<AngelScriptBindings*>(this);
        pObject->pSharedControl = pSharedControl;

        if (pSharedControl) {
            m_sharedObjects[pSharedControl] = pObject;
        }

        if (pObject->value.IsRef() && pAnchor) {
            pObject->pAnchor = pAnchor;
            pAnchor->AddRef();
        }

        return pObject;
    }

    void AngelScriptBindings::Forget(AngelScriptNativeObject* pObject) const {
        if (pObject->pSharedControl) {
            m_sharedObjects.erase(pObject->pSharedControl);
        }
    }

    void AngelScriptBindings::Return(asIScriptGeneric* pCall, SR_UTILS_NS::Reflection::Value value, AngelScriptNativeObject* pAnchor) const {
        if (!value) {
            AngelScriptBindingHelpers::Exception("Native call returned an unsupported value");
            return;
        }

        auto&& info = value.GetTypeInfo();

        if (AngelScriptBindingHelpers::Primitive(info)) {
            if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
                auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(info.detailedType);

                if (!pReflector) {
                    AngelScriptBindingHelpers::Exception("Unregistered engine enum");
                    return;
                }

                pCall->SetReturnDWord(static_cast<asDWORD>(pReflector->ReadEnumValueFromPointerInternal(value.Data())));
                return;
            }

            if (info.detailedType == "float") {
                pCall->SetReturnFloat(*value.Cast<float_t>());
                return;
            }

            if (info.detailedType == "double") {
                pCall->SetReturnDouble(*value.Cast<double_t>());
                return;
            }

            const auto size = info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum ? sizeof(int32_t) : SR_UTILS_NS::Reflection::GetReflectedTypeSize(info.detailedType);
            uint64_t bits = 0;
            memcpy(&bits, value.Data(), size);

            if (size == 1) {
                pCall->SetReturnByte(static_cast<asBYTE>(bits));
            }
            else if (size == 2) {
                pCall->SetReturnWord(static_cast<asWORD>(bits));
            }
            else if (size == 4) {
                pCall->SetReturnDWord(static_cast<asDWORD>(bits));
            }
            else {
                pCall->SetReturnQWord(bits);
            }

            return;
        }

        if (info.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::String && info.detailedType != "String") {
            SR_UTILS_NS::String text;

            if (info.detailedType == "StringAtom") {
                text = value.Cast<SR_UTILS_NS::StringAtom>()->ToString();
            }
            else if (info.detailedType == "Path") {
                text = value.Cast<SR_UTILS_NS::Path>()->ToString();
            }
            else if (info.detailedType == "StringView") {
                text = SR_UTILS_NS::String(*value.Cast<SR_UTILS_NS::StringView>());
            }
            else if (info.detailedType == "UnicodeString") {
                for (auto&& code : *value.Cast<SR_UTILS_NS::UnicodeString>()) {
                    if (!SR_UTILS_NS::Localization::Utf::IsValidCodePoint(static_cast<uint32_t>(code))) {
                        AngelScriptBindingHelpers::Exception("Invalid Unicode code point");
                        return;
                    }
                    char buffer[4];
                    auto&& pEnd = SR_UTILS_NS::Localization::Utf::UtfTraits<char>::Encode(static_cast<uint32_t>(code), buffer);
                    for (const char* pCurrent = buffer; pCurrent != pEnd; ++pCurrent) {
                        text.push_back(*pCurrent);
                    }
                }
            }
            else {
                AngelScriptBindingHelpers::Exception("Unsupported string representation");
                return;
            }

            value = SR_UTILS_NS::Reflection::Value::Create(std::move(text));
        }

        pCall->SetReturnAddress(Wrap(std::move(value), pAnchor));
    }

    SR_UTILS_NS::Reflection::Value AngelScriptBindings::ReadProperty(asIScriptObject* pObject, uint32_t index) const {
        const auto id = pObject->GetPropertyTypeId(index);
        auto&& pAddress = pObject->GetAddressOfProperty(index);

        if (id & asTYPEID_SCRIPTOBJECT) {
            return {};
        }

        if (id & asTYPEID_MASK_OBJECT) {
            auto&& pNative = (id & asTYPEID_OBJHANDLE) ? *static_cast<AngelScriptNativeObject**>(pAddress) : static_cast<AngelScriptNativeObject*>(pAddress);

            if (!pNative) {
                auto&& pType = FindType(id);
                if (pType && pType->pTypeInfo->category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container) {
                    return SR_UTILS_NS::Reflection::Value::CreateDefault(pType->pTypeInfo);
                }
            }
            return pNative && pNative->IsAlive() ? CopyValue(pNative->value) : SR_UTILS_NS::Reflection::Value();
        }

        const char* pName = m_pEngine->GetTypeDeclaration(id);
        SR_UTILS_NS::String serialized = "Arithmetic.";

        if (id == asTYPEID_INT32) {
            serialized += "int32";
        }
        else if (id == asTYPEID_UINT32) {
            serialized += "uint32";
        }
        else if (auto&& pType = m_pEngine->GetTypeInfoById(id)) {
            serialized = !pType->GetModule() && SR_UTILS_NS::EnumReflectorManager::Instance().TryGetReflector(pType->GetName()) ? "Enum." + SR_UTILS_NS::String(pType->GetName()) : SR_UTILS_NS::String("Arithmetic.int32");
        }
        else {
            serialized += pName;
        }

        auto&& pInfo = SR_UTILS_NS::Reflection::LoadTypeInfo(serialized);

        if (!pInfo) {
            return {};
        }

        SR_UTILS_NS::Reflection::FindVTable(*pInfo);
        auto result = SR_UTILS_NS::Reflection::Value::CreateDefault(pInfo);
        SR_UTILS_NS::Reflection::FreeTypeInfo(pInfo);
        const auto size = m_pEngine->GetSizeOfPrimitiveType(id);

        if (size <= 0) {
            return {};
        }

        memcpy(result.Data(), pAddress, static_cast<uint32_t>(size));

        return result;
    }

    bool AngelScriptBindings::WriteProperty(asIScriptObject* pObject, uint32_t index, const SR_UTILS_NS::Reflection::Value& value) const {
        const auto id = pObject->GetPropertyTypeId(index);
        auto&& pAddress = pObject->GetAddressOfProperty(index);

        if (id & asTYPEID_SCRIPTOBJECT) {
            return false;
        }

        if (id & asTYPEID_MASK_OBJECT) {
            auto&& pType = FindType(id);

            if (!pType) {
                return false;
            }

            if (value.IsSharedPtr() && !value.GetSharedPtrBase()->Valid()) {
                if (!(id & asTYPEID_OBJHANDLE)) {
                    return false;
                }

                auto&& pTarget = static_cast<AngelScriptNativeObject**>(pAddress);

                if (*pTarget) {
                    (*pTarget)->Release();
                }

                *pTarget = nullptr;
                return true;
            }

            auto converted = value.IsSharedPtr() && pType->pMeta ? pType->pMeta->Cast(value) : Convert(value, *pType->pTypeInfo);

            if (!converted) {
                return false;
            }

            if (id & asTYPEID_OBJHANDLE) {
                auto&& pTarget = static_cast<AngelScriptNativeObject**>(pAddress);

                if (!converted.IsSharedPtr() && !converted.GetTypeInfo().vtable.pCopy) {
                    return false;
                }

                auto&& pReplacement = Wrap(converted.Copy());

                if (*pTarget) {
                    (*pTarget)->Release();
                }

                *pTarget = pReplacement;

                return true;
            }

            return CopyTo(converted, static_cast<AngelScriptNativeObject*>(pAddress)->value);
        }

        auto existing = ReadProperty(pObject, index);

        if (!existing || existing.GetTypeInfo() != value.GetTypeInfo()) {
            return false;
        }

        if (value.GetType() == SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
            auto&& pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(value.GetTypeInfo().detailedType);
            const auto number = static_cast<int32_t>(pReflector->ReadEnumValueFromPointerInternal(value.Data()));
            memcpy(pAddress, &number, sizeof(number));

            return true;
        }

        const auto size = m_pEngine->GetSizeOfPrimitiveType(id);
        if (size <= 0) {
            return false;
        }

        memcpy(pAddress, value.Data(), static_cast<uint32_t>(size));

        return true;
    }

    const void* AngelScriptBindings::GetStringConstant(const char* pData, asUINT length) {
        return Wrap(SR_UTILS_NS::Reflection::Value::Create(SR_UTILS_NS::String(pData, length, SR_UTILS_NS::IAllocator::GetDefaultAllocator())));
    }

    int32_t AngelScriptBindings::ReleaseStringConstant(const void* pString) {
        const_cast<AngelScriptNativeObject*>(static_cast<const AngelScriptNativeObject*>(pString))->Release();
        return asSUCCESS;
    }

    int32_t AngelScriptBindings::GetRawStringData(const void* pString, char* pData, asUINT* pLength) const {
        auto&& pObject = static_cast<const AngelScriptNativeObject*>(pString);
        auto&& text = *pObject->value.Cast<SR_UTILS_NS::String>();

        if (pLength) {
            *pLength = static_cast<asUINT>(text.size());
        }

        if (pData) {
            memcpy(pData, text.data(), text.size());
        }

        return asSUCCESS;
    }
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
