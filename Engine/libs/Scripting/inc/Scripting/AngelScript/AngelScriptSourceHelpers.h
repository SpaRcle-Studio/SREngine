//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGELSCRIPTSOURCEHELPERS_H
#define SR_ENGINE_SCRIPTING_ANGELSCRIPTSOURCEHELPERS_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptRuntime.h>

#include <scriptbuilder.h>

namespace SR_SCRIPTING_NS::AngelScriptSourceHelpers {
    void Message(const asSMessageInfo* pMessage, void*);
    int32_t AddSource(CScriptBuilder* pBuilder, const SR_UTILS_NS::Path& path);
    int32_t Include(const char* pInclude, const char* pFrom, CScriptBuilder* pBuilder, void*);
    SR_UTILS_NS::StringAtom FullName(const asITypeInfo* pType);
    SR_UTILS_NS::String Token(const SR_UTILS_NS::String& source, uint64_t& offset);
}

#endif

#endif
