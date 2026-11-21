//
// Created by Codex on 13.11.2026.
//

#include <Scripting/AngelScript/AngelScriptRuntime.h>
#include <Scripting/AngelScript/AngelScriptSourceHelpers.h>
#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptBindings.h>
#include <Scripting/AngelScript/AngelScriptBehaviourInstance.h>
#include <Scripting/AngelScript/AngelScriptObjectGraph.h>

#if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
	#include <Scripting/AngelScript/AngelScriptDebugger.h>
#endif

#include <Utils/Types/LockGuard.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/Memory/MemoryLiterals.h>

#include <scriptbuilder.h>

namespace SR_SCRIPTING_NS {
    AngelScriptRuntime::AngelScriptRuntime() {
    #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
        m_pDebugger = new AngelScriptDebugger();
    #endif
    }

    AngelScriptRuntime::~AngelScriptRuntime() {
    #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
        m_pDebugger->Stop();
    #endif
        SRAssert2(m_instances.empty(), "AngelScriptRuntime::~AngelScriptRuntime() : behaviours must be released before the script system!");

        for (auto&& pInstance : m_instances) {
            delete pInstance;
        }

        if (m_pEngine) {
            SR_LOG("AngelScriptRuntime::~AngelScriptRuntime() : shutting down AngelScript.");
            m_pEngine->ShutDownAndRelease();
        }

        delete m_pBindings;
    #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
        delete m_pDebugger;
    #endif
    }

    bool AngelScriptRuntime::EnsureInitialized() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (m_initializing) {
            return false;
        }

        if (m_initializationAttempted) {
            return m_pEngine != nullptr;
        }

        m_initializationAttempted = true;
        m_initializing = true;
        SR_LOG("AngelScriptRuntime::EnsureInitialized() : initializing AngelScript.");
        m_pEngine = asCreateScriptEngine();

        if (!m_pEngine) {
            SR_ERROR("AngelScriptRuntime::EnsureInitialized() : failed to create the AngelScript engine.");
            m_hasErrors = true;
            m_initializing = false;
            return false;
        }

        m_pEngine->SetMessageCallback(asFUNCTION(AngelScriptSourceHelpers::Message), nullptr, asCALL_CDECL);
        m_pEngine->SetEngineProperty(asEP_PROPERTY_ACCESSOR_MODE, 2);
        m_pEngine->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES, true);
        m_pEngine->SetEngineProperty(asEP_INIT_GLOBAL_VARS_AFTER_BUILD, false);
        // Implicit copy constructors replace preallocated nested objects; use default construction and assignment for native value templates.
        m_pEngine->SetEngineProperty(asEP_ALWAYS_IMPL_DEFAULT_COPY_CONSTRUCT, 2);
    #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
        if (m_pDebugger->IsListening()) {
            m_pEngine->SetContextCallbacks(AngelScriptDebugger::RequestContext, AngelScriptDebugger::ReturnContext, m_pDebugger);
        }
    #endif
        m_pBindings = new AngelScriptBindings(m_pEngine);

        if (!m_pBindings->RegisterFactory()) {
            SR_ERROR("AngelScriptRuntime::EnsureInitialized() : API registration failed.");
            m_pEngine->ShutDownAndRelease();
            m_pEngine = nullptr;
            delete m_pBindings;
            m_pBindings = nullptr;
            m_hasErrors = true;
            m_initializing = false;

            return false;
        }

        SR_UTILS_NS::String api;

        SR_UTILS_NS::Vector<asITypeInfo*> objectTypes;
        SR_UTILS_NS::Set<int32_t> exportedTypes;
        for (uint32_t i = 0; i < m_pEngine->GetObjectTypeCount(); ++i) {
            auto&& pType = m_pEngine->GetObjectTypeByIndex(i);
            objectTypes.emplace_back(pType);
            exportedTypes.insert(pType->GetTypeId());
        }
        for (auto&& pBindingType : m_pBindings->GetTypes()) {
            auto&& pType = m_pEngine->GetTypeInfoById(pBindingType->scriptTypeId);
            if (pType && pBindingType->pTypeInfo->kind != SR_UTILS_NS::Reflection::TypeKind::Enum &&
                exportedTypes.insert(pType->GetTypeId()).second) {
                objectTypes.emplace_back(pType);
            }
        }

        for (auto&& pType : objectTypes) {
            api += "class " + SR_UTILS_NS::String(m_pEngine->GetTypeDeclaration(pType->GetTypeId(), false)) + "\n{\n";

            for (uint32_t j = 0; j < pType->GetMethodCount(); ++j) {
                auto&& pMethod = pType->GetMethodByIndex(j);
                api += "    " + SR_UTILS_NS::String(pMethod->GetDeclaration(false)) + (pMethod->IsProperty() ? " property;\n" : ";\n");
            }

            api += "}\n\n";
        }

        const auto apiPath = CoreResLoader::GetCachePath().Concat("Scripts/AngelScriptAPI.txt");

        if (apiPath.GetFolder().CreateDirectories()) {
            if (auto file = SR_UTILS_NS::VFS::Instance().OpenFile(apiPath, SR_UTILS_NS::FileMode::Write)) {
                file.Write(api.data(), api.size());
            }
        }

        m_moduleDirty = true;
        const bool result = BuildModule();
        m_initializing = false;
        SR_LOG("AngelScriptRuntime::EnsureInitialized() : initialization finished, gameplay module ready: {}.", result);

        return result;
    }

    void AngelScriptRuntime::GeneratePredefined(const SR_UTILS_NS::String& behaviourDeclaration) const {
        SR_TRACY_ZONE;

        SR_UTILS_NS::String api;
        SR_UTILS_NS::Vector<asITypeInfo*> objectTypes;
        SR_UTILS_NS::SortedVector<int32_t> exportedTypes;
        SR_UTILS_NS::String tmpBuffer;
        tmpBuffer.reserve(128);
        api.reserve(512_KiB);
        api += "// Generated from the registered AngelScript API. Do not edit.\n\n";

        auto openNamespace = [&api](const char* pNamespace) {
            if (pNamespace && *pNamespace) {
                api += "namespace ";
                api += pNamespace;
                api += " {\n";
            }
        };
        auto closeNamespace = [&api](const char* pNamespace) {
            if (pNamespace && *pNamespace) {
                api += "}\n";
            }
            api += "\n";
        };

        for (uint32_t i = 0; i < m_pEngine->GetEnumCount(); ++i) {
            auto&& pType = m_pEngine->GetEnumByIndex(i);
            openNamespace(pType->GetNamespace());
            api += "enum ";
            api += pType->GetName();
            if (pType->GetUnderlyingTypeId() != asTYPEID_INT32) {
                api += " : ";
                api += m_pEngine->GetTypeDeclaration(pType->GetUnderlyingTypeId());
            }
            api += " {\n";
            for (uint32_t j = 0; j < pType->GetEnumValueCount(); ++j) {
                asINT64 value = 0;
                const auto name = pType->GetEnumValueByIndex(j, &value);
                SR_UTILS_NS::FormatTo(api, "    {} = {},\n", name, value);
            }
            api += "}\n";
            closeNamespace(pType->GetNamespace());
        }

        objectTypes.reserve(m_pEngine->GetObjectTypeCount() + m_pBindings->GetTypes().size());
        exportedTypes.reserve(objectTypes.capacity());

        for (uint32_t i = 0; i < m_pEngine->GetObjectTypeCount(); ++i) {
            auto&& pType = m_pEngine->GetObjectTypeByIndex(i);
            objectTypes.emplace_back(pType);
            exportedTypes.insert(pType->GetTypeId());
        }
        for (auto&& pBindingType : m_pBindings->GetTypes()) {
            auto&& pType = m_pEngine->GetTypeInfoById(pBindingType->scriptTypeId);
            if (pType && pBindingType->pTypeInfo->kind != SR_UTILS_NS::Reflection::TypeKind::Enum && exportedTypes.insert(pType->GetTypeId())) {
                objectTypes.emplace_back(pType);
            }
        }

        for (auto&& pType : objectTypes) {
            openNamespace(pType->GetNamespace());
            api += "class ";
            api += m_pEngine->GetTypeDeclaration(pType->GetTypeId(), false);
            bool hasBase = false;
            if (auto&& pBase = pType->GetBaseType()) {
                api += " : ";
                api += m_pEngine->GetTypeDeclaration(pBase->GetTypeId(), true);
                hasBase = true;
            }
            for (uint32_t j = 0; j < pType->GetInterfaceCount(); ++j) {
                api += hasBase ? ", " : " : ";
                api += m_pEngine->GetTypeDeclaration(pType->GetInterface(j)->GetTypeId(), true);
                hasBase = true;
            }
            api += " {\n";
            for (uint32_t j = 0; j < pType->GetFactoryCount(); ++j) {
                tmpBuffer = pType->GetFactoryByIndex(j)->GetDeclaration(false, true, true);
                const auto params = tmpBuffer.find('(');
                if (params != SR_UTILS_NS::String::npos) {
                    api += "    ";
                    api += pType->GetName();
                    api += tmpBuffer.ToStringView().substr(params);
                    api += ";\n";
                }
            }
            for (uint32_t j = 0; j < pType->GetBehaviourCount(); ++j) {
                asEBehaviours behaviour;
                auto&& pFunction = pType->GetBehaviourByIndex(j, &behaviour);
                if (behaviour == asBEHAVE_CONSTRUCT || behaviour == asBEHAVE_DESTRUCT) {
                    api += "    ";
                    api += pFunction->GetDeclaration(false, true, true);
                    api += ";\n";
                }
            }
            for (uint32_t j = 0; j < pType->GetMethodCount(); ++j) {
                auto&& pMethod = pType->GetMethodByIndex(j);
                api += "    ";
                api += pMethod->GetDeclaration(false, true, true);
                api += pMethod->IsProperty() ? " property;\n" : ";\n";
            }
            for (uint32_t j = 0; j < pType->GetPropertyCount(); ++j) {
                api += "    ";
                api += pType->GetPropertyDeclaration(j, true);
                api += ";\n";
            }
            for (uint32_t j = 0; j < pType->GetChildFuncdefCount(); ++j) {
                api += "    funcdef ";
                api += pType->GetChildFuncdef(j)->GetFuncdefSignature()->GetDeclaration(false, true, true);
                api += ";\n";
            }
            api += "}\n";
            closeNamespace(pType->GetNamespace());
        }

        for (uint32_t i = 0; i < m_pEngine->GetTypedefCount(); ++i) {
            auto&& pType = m_pEngine->GetTypedefByIndex(i);
            openNamespace(pType->GetNamespace());
            api += "typedef ";
            api += m_pEngine->GetTypeDeclaration(pType->GetUnderlyingTypeId(), true);
            api += " ";
            api += pType->GetName();
            api += ";\n";
            closeNamespace(pType->GetNamespace());
        }
        for (uint32_t i = 0; i < m_pEngine->GetFuncdefCount(); ++i) {
            auto&& pType = m_pEngine->GetFuncdefByIndex(i);
            if (pType->GetParentType()) {
                continue;
            }
            openNamespace(pType->GetNamespace());
            api += "funcdef ";
            api += pType->GetFuncdefSignature()->GetDeclaration(false, true, true);
            api += ";\n";
            closeNamespace(pType->GetNamespace());
        }
        for (uint32_t i = 0; i < m_pEngine->GetGlobalFunctionCount(); ++i) {
            auto&& pFunction = m_pEngine->GetGlobalFunctionByIndex(i);
            openNamespace(pFunction->GetNamespace());
            api += pFunction->GetDeclaration(false, false, true);
            api += ";\n";
            closeNamespace(pFunction->GetNamespace());
        }
        for (uint32_t i = 0; i < m_pEngine->GetGlobalPropertyCount(); ++i) {
            const char* pName = nullptr;
            const char* pNamespace = nullptr;
            int32_t typeId = 0;
            bool isConst = false;
            m_pEngine->GetGlobalPropertyByIndex(i, &pName, &pNamespace, &typeId, &isConst);
            openNamespace(pNamespace);
            if (isConst) {
                api += "const ";
            }
            api += m_pEngine->GetTypeDeclaration(typeId, true);
            api += " ";
            api += pName;
            api += ";\n";
            closeNamespace(pNamespace);
        }
        api += behaviourDeclaration;

        const auto path = CoreResLoader::GetResPath().Concat("as.predefined");
        if (!SR_UTILS_NS::VFS::Instance().IsWritable(path.GetFolder().ToStringView())) {
            return;
        }
        if (!path.GetFolder().CreateDirectories()) {
            SR_WARN("AngelScriptRuntime::GeneratePredefined() : failed to create output directory for {}.", path);
            return;
        }
        auto file = SR_UTILS_NS::VFS::Instance().OpenFile(path, SR_UTILS_NS::FileMode::Write);
        if (!file || file.Write(api.data(), api.size()) != api.size()) {
            SR_WARN("AngelScriptRuntime::GeneratePredefined() : failed to write {}.", path);
            return;
        }
        SR_LOG("AngelScriptRuntime::GeneratePredefined() : generated {}.", path);
    }

    bool AngelScriptRuntime::Execute(asIScriptContext* pContext) const {
        SR_TRACY_ZONE;
    #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
        std::lock_guard lock(m_mutex);
        m_pDebugger->PrepareContext(pContext);
    #endif
        const auto result = pContext->Execute();
    #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
        m_pDebugger->ExecutionFinished(pContext);
    #endif

        if (result == asEXECUTION_FINISHED) {
            return true;
        }

        auto&& pFunction = pContext->GetExceptionFunction();

        SR_ERROR("AngelScriptRuntime::Execute() : AngelScript execution failed ({}): {} at {}:{}",
            result, pContext->GetExceptionString(), pFunction ? pFunction->GetDeclaration() : "<unknown>", pContext->GetExceptionLineNumber()
        );

        return false;
    }

    asIScriptObject* AngelScriptRuntime::CreateObject(asIScriptModule* pModule, SR_UTILS_NS::StringAtom name) {
        auto&& pType = pModule->GetTypeInfoByDecl(name.c_str());
        if (!pType) {
            return nullptr;
        }

        asIScriptFunction* pFactory = nullptr;

        for (uint32_t i = 0; i < pType->GetFactoryCount(); ++i) {
            auto&& pCandidate = pType->GetFactoryByIndex(i);

            if (pCandidate->GetParamCount() == 0) {
                pFactory = pCandidate;
                break;
            }
        }

        if (!pFactory) {
            return nullptr;
        }

        auto&& pContext = m_pEngine->RequestContext();

        if (!pContext) {
            return nullptr;
        }

        asIScriptObject* pObject = nullptr;

        if (pContext->Prepare(pFactory) >= 0 && Execute(pContext)) {
            SR_TRACY_ZONE;

            pObject = *static_cast<asIScriptObject**>(pContext->GetAddressOfReturnValue());

            if (pObject) {
                pObject->AddRef();
            }
        }

        m_pEngine->ReturnContext(pContext);

        return pObject;
    }

    bool AngelScriptRuntime::BuildModule() {
        SR_TRACY_ZONE;

        m_moduleDirty = false;
        m_hasErrors = false;
        const SR_UTILS_NS::String moduleName = "Gameplay_{}"_format(++m_generation);
        SR_LOG("AngelScriptRuntime::BuildModule() : {} module {}, source files: {}, behaviour instances: {}.",
            m_pModule ? "reloading" : "building", moduleName, m_sourceFiles.size(), m_instances.size());
        CScriptBuilder builder;

        if (builder.StartNewModule(m_pEngine, moduleName.c_str()) < 0) {
            SR_ERROR("AngelScriptRuntime::BuildModule() : failed to create module {}.", moduleName);
            m_hasErrors = true;

            return false;
        }

        auto&& pCandidate = builder.GetModule();
        auto fail = [&]() {
            SR_ERROR("AngelScriptRuntime::BuildModule() : module {} failed; previous module retained: {}.", moduleName, m_pModule != nullptr);
            pCandidate->Discard();
        #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
            m_pDebugger->ModuleBuilt(m_pModule);
        #endif
            m_hasErrors = true;

            return false;
        };
        builder.SetIncludeCallback(AngelScriptSourceHelpers::Include, nullptr);

        SR_UTILS_NS::String base = "class ScriptBehaviour : IBehaviour {\n";

        for (auto&& pName : {
            "SceneObject", "GameObject", "Transform"
        }) {
            if (auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(pName)) {
                const SR_UTILS_NS::String field = SR_UTILS_NS::String(pName) == "SceneObject" ? "sceneObject" : SR_UTILS_NS::String(pName) == "GameObject" ? "gameObject" : "transform";
                base += SR_UTILS_NS::String(pMeta->GetFactoryName()) + "@ " + field + ";\n";
            }
        }

        base += "}\n";

        if (m_initializing) {
            GeneratePredefined(base);
        }

        if (builder.AddSectionFromMemory("<engine behaviour>", base.c_str(), static_cast<uint32_t>(base.size())) < 0) {
            return fail();
        }

        for (auto&& path : m_sourceFiles) {
            if (AngelScriptSourceHelpers::AddSource(&builder, path) < 0) {
                return fail();
            }
        }

        {
            SR_TRACY_ZONE_N("CScriptBuilder");
            if (builder.BuildModule() < 0) {
                return fail();
            }
        }

    #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
        m_pDebugger->ModuleBuilt(pCandidate);
    #endif

        SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> names;
        names.reserve(pCandidate->GetObjectTypeCount());
        auto&& pMarker = m_pEngine->GetTypeInfoByDecl("IBehaviour");

        for (uint32_t i = 0; i < pCandidate->GetObjectTypeCount(); ++i) {
            auto&& pType = pCandidate->GetObjectTypeByIndex(i);
            const auto name = AngelScriptSourceHelpers::FullName(pType);

            if (!pType->Implements(pMarker) || name == "ScriptBehaviour") {
                continue;
            }

            if (SR_UTILS_NS::Factory::Instance().GetTypeInfo(name)) {
                SR_ERROR("AngelScriptRuntime::BuildModule() : AngelScript behaviour name is already registered in the engine factory: {}", name);
                return fail();
            }

            names.emplace_back(name);
        }

        auto&& pContext = m_pEngine->RequestContext();
        if (!pContext) {
            return fail();
        }

        const auto globals = pCandidate->ResetGlobalVars(pContext);
        m_pEngine->ReturnContext(pContext);

        if (globals < 0) {
            return fail();
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::Pair<AngelScriptBehaviourInstance*, asIScriptObject*>> replacements;
        replacements.reserve(m_instances.size());

        for (auto&& pInstance : m_instances) {
            auto&& pObject = CreateObject(pCandidate, pInstance->GetBehaviourName());

            if (std::find(names.begin(), names.end(), pInstance->GetBehaviourName()) != names.end() && !pObject) {
                for (auto&& replacement : replacements) {
                    if (replacement.second) {
                        replacement.second->Release();
                    }
                }

                return fail();
            }

            replacements.emplace_back(SR_UTILS_NS::Pair<AngelScriptBehaviourInstance*, asIScriptObject*> {
                pInstance, pObject
            });
        }

        for (auto&& pInstance : m_instances) {
            if (pInstance->IsValid() && pInstance->GetPreReloadCallback()) {
                pInstance->GetPreReloadCallback()();
            }
        }

        asIScriptModule* pPrevious = m_pModule;
        m_pModule = pCandidate;
        m_behaviourNames = std::move(names);
        m_namesDirty = false;

        {
            AngelScriptObjectGraph reloadGraph;
            uint64_t rootId = 1;
            for (auto&& replacement : replacements) {
                reloadGraph.RegisterRoot(replacement.first->GetScriptObject(), replacement.second, rootId++);
            }
            for (auto&& replacement : replacements) {
                replacement.first->SetInstance(replacement.second);
            }
        }
        for (auto&& replacement : replacements) {
            if (replacement.second && replacement.first->GetLoadedCallback()) {
                replacement.first->GetLoadedCallback()();
            }
        }

        if (pPrevious) {
            pPrevious->Discard();
        }

        m_pEngine->GarbageCollect();
        SR_LOG("AngelScriptRuntime::BuildModule() : module {} ready, behaviours: {}, replaced instances: {}.",
            moduleName, m_behaviourNames.size(), replacements.size());

        if (!m_initializing) {
            SR_UTILS_NS::Broadcaster::Instance().Broadcast(SR_UTILS_NS::Events::EVENT_ON_SCRIPT_MODULE_RELOADED_ID);
        }

        return true;
    }

    BehaviourInstance* AngelScriptRuntime::AllocateBehaviourInstance(SR_UTILS_NS::StringAtom name) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;
        EnsureInitialized();
        auto&& pInstance = new AngelScriptBehaviourInstance(this, name);
        auto&& pType = m_pModule ? m_pModule->GetTypeInfoByDecl(name.c_str()) : nullptr;
        auto&& pMarker = m_pEngine ? m_pEngine->GetTypeInfoByDecl("IBehaviour") : nullptr;
        pInstance->SetInstance(pType && pMarker && pType->Implements(pMarker) ? CreateObject(m_pModule, name) : nullptr);
        m_instances.insert(pInstance);
        // A missing class remains a stable instance until it returns on reload.
        return pInstance;
    }

    void AngelScriptRuntime::FreeBehaviourInstance(BehaviourInstance* pInstance) {
        SR_LOCK_GUARD;
        auto&& pTyped = dynamic_cast<AngelScriptBehaviourInstance*>(pInstance);

        if (!pTyped || m_instances.erase(pTyped) == 0) {
            SRHalt("AngelScriptRuntime::FreeBehaviourInstance() : unknown AngelScript behaviour instance!");

            return;
        }

        delete pTyped;
    }

    void AngelScriptRuntime::HandleFileEvent(const SR_UTILS_NS::Path& path) {
        SR_LOCK_GUARD;

        if (path.IsFile()) {
            m_sourceFiles.insert(path);
        }
        else {
            m_sourceFiles.erase(path);
        }

        m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
        m_moduleDirty = true;
        m_namesDirty = true;
    }

    void AngelScriptRuntime::SetReloadRequest() {
        SR_LOCK_GUARD;
        m_moduleDirty = true;

        if (!m_pEngine) {
            m_initializationAttempted = false;
        }

        m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
    }

    void AngelScriptRuntime::ReloadModuleIfNeeded() {
    #if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
        if (m_pDebugger->IsPaused()) {
            return;
        }
    #endif
        SR_LOCK_GUARD;

        if (m_initializing || !m_moduleDirty ||
            m_lastFileSystemEvent + std::chrono::milliseconds(200) > SR_HTYPES_NS::Time::Instance().Now()) {
            return;
        }

        if (!m_pEngine) {
            if (!m_instances.empty()) {
                m_initializationAttempted = false;
                m_moduleDirty = false;
                EnsureInitialized();
            }

            return;
        }

        BuildModule();
    }

    void AngelScriptRuntime::DiscoverSourceNames() const {
        SR_TRACY_ZONE;

        if (!m_namesDirty || m_pModule) {
            return;
        }

        m_behaviourNames.clear();
        struct Candidate {
            SR_UTILS_NS::StringAtom name;
            SR_UTILS_NS::String prefix;
            SR_UTILS_NS::Vector<SR_UTILS_NS::String> bases;
        };
        SR_UTILS_NS::Vector<Candidate> candidates;

        for (auto&& path : m_sourceFiles) {
            auto file = SR_UTILS_NS::VFS::Instance().OpenFile(path, SR_UTILS_NS::FileMode::Read);
            SR_UTILS_NS::String source;

            if (!file || !file.Read(source)) {
                continue;
            }

            uint64_t offset = 0;
            SR_UTILS_NS::String prefix;
            SR_UTILS_NS::Vector<SR_UTILS_NS::String> scopes;

            while (offset < source.size()) {
                const auto token = AngelScriptSourceHelpers::Token(source, offset);

                if (token == "namespace") {
                    SR_UTILS_NS::String pendingNamespace = AngelScriptSourceHelpers::Token(source, offset);

                    while (offset < source.size()) {
                        const auto next = AngelScriptSourceHelpers::Token(source, offset);

                        if (next == "{") {
                            scopes.emplace_back(prefix);
                            prefix += pendingNamespace + "::";
                            break;
                        }

                        pendingNamespace += next;
                    }
                }
                else if (token == "{") {
                    scopes.emplace_back(prefix);
                }
                else if (token == "}" && !scopes.empty()) {
                    prefix = scopes.back();
                    scopes.pop_back();
                }
                else if (token == "class") {
                    Candidate candidate;
                    candidate.prefix = prefix;
                    candidate.name = SR_UTILS_NS::StringAtom(prefix + AngelScriptSourceHelpers::Token(source, offset));
                    bool inBases = false;
                    SR_UTILS_NS::String base;

                    while (offset < source.size()) {
                        const auto next = AngelScriptSourceHelpers::Token(source, offset);

                        if (next == ":" && !inBases) {
                            inBases = true;
                        }
                        else if (next == "," || next == "{" || next == ";") {
                            if (!base.empty()) {
                                candidate.bases.emplace_back(std::move(base));
                                base.clear();
                            }

                            if (next == "{") {
                                scopes.emplace_back(prefix);
                                break;
                            }

                            if (next == ";") {
                                break;
                            }
                        }
                        else if (inBases) {
                            base += next;
                        }
                    }

                    candidates.emplace_back(std::move(candidate));
                }
            }
        }

        SR_UTILS_NS::Set<SR_UTILS_NS::StringAtom> known;
        bool changed = true;

        while (changed) {
            changed = false;

            for (auto&& candidate : candidates) {
                if (known.count(candidate.name)) {
                    continue;
                }

                for (auto&& base : candidate.bases) {
                    if (base == "IBehaviour" || base == "ScriptBehaviour" || known.count(SR_UTILS_NS::StringAtom(base)) ||
                        known.count(SR_UTILS_NS::StringAtom(candidate.prefix + base))) {
                        known.insert(candidate.name);
                        m_behaviourNames.emplace_back(candidate.name);
                        changed = true;
                        break;
                    }
                }
            }
        }

        m_namesDirty = false;
    }

    SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> AngelScriptRuntime::GetBehaviourNames() const {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;
        DiscoverSourceNames();
        return m_behaviourNames;
    }

    SR_UTILS_NS::Set<SR_UTILS_NS::Path> AngelScriptRuntime::GetSourceFiles() const {
        SR_LOCK_GUARD;
        return m_sourceFiles;
    }

    bool AngelScriptRuntime::IsModuleDirty() const {
        SR_LOCK_GUARD;
        return m_moduleDirty;
    }

    bool AngelScriptRuntime::HasErrors() const {
        SR_LOCK_GUARD;
        return m_hasErrors;
    }

    bool AngelScriptRuntime::IsAvailable() const {
        SR_LOCK_GUARD;
        return m_pEngine != nullptr;
    }
}

#else

#include <Utils/Types/LockGuard.h>

namespace SR_SCRIPTING_NS {
    AngelScriptRuntime::AngelScriptRuntime() = default;

    AngelScriptRuntime::~AngelScriptRuntime() = default;

    bool AngelScriptRuntime::EnsureInitialized() {
        SR_TRACY_ZONE;

        return false;
    }

    void AngelScriptRuntime::HandleFileEvent(const SR_UTILS_NS::Path& path) {
        SR_LOCK_GUARD;

        if (path.IsFile()) {
            m_sourceFiles.insert(path);
        }
        else {
            m_sourceFiles.erase(path);
        }
    }

    void AngelScriptRuntime::SetReloadRequest() {
    }

    void AngelScriptRuntime::ReloadModuleIfNeeded() {
    }

    SR_UTILS_NS::Set<SR_UTILS_NS::Path> AngelScriptRuntime::GetSourceFiles() const {
        SR_LOCK_GUARD;

        return m_sourceFiles;
    }

    SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> AngelScriptRuntime::GetBehaviourNames() const {
        return {};
    }

    bool AngelScriptRuntime::IsModuleDirty() const {
        return false;
    }

    bool AngelScriptRuntime::HasErrors() const {
        return false;
    }

    bool AngelScriptRuntime::IsAvailable() const {
        return false;
    }

    BehaviourInstance* AngelScriptRuntime::AllocateBehaviourInstance(SR_UTILS_NS::StringAtom name) {
        SR_ERROR("AngelScriptRuntime::AllocateBehaviourInstance() : AngelScript support is disabled: {}", name);

        return nullptr;
    }

    void AngelScriptRuntime::FreeBehaviourInstance(BehaviourInstance* pInstance) {
        SRAssert2(!pInstance, "AngelScriptRuntime::FreeBehaviourInstance() : AngelScript support is disabled!");
    }
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
