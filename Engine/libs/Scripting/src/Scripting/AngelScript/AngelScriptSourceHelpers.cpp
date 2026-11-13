//
// Created by Codex on 13.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptSourceHelpers.h>
#include <Scripting/AngelScript/AngelScriptRuntime.h>

#include <Scripting/AngelScript/AngelScriptBindings.h>
#include <Scripting/AngelScript/AngelScriptBehaviourInstance.h>

#include <Utils/Types/LockGuard.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Memory/Allocator.h>
#include <Utils/Common/StringAtomLiterals.h>

#include <scriptbuilder.h>

namespace SR_SCRIPTING_NS {
    namespace AngelScriptSourceHelpers {
        void Message(const asSMessageInfo* pMessage, void*) {
            if (pMessage->type == asMSGTYPE_ERROR) {
                SR_ERROR("AngelScriptSourceHelpers::Message() : AngelScript {}:{}:{}: {}", pMessage->section, pMessage->row, pMessage->col, pMessage->message);
            }
            else {
                SR_WARN("AngelScriptSourceHelpers::Message() : AngelScript {}:{}:{}: {}", pMessage->section, pMessage->row, pMessage->col, pMessage->message);
            }
        }

        int32_t AddSource(CScriptBuilder* pBuilder, const SR_UTILS_NS::Path& path) {
            auto file = SR_UTILS_NS::VFS::Instance().OpenFile(path, SR_UTILS_NS::FileMode::Read);
            SR_UTILS_NS::String source;

            if (!file || !file.Read(source)) {
                SR_ERROR("AngelScriptSourceHelpers::AddSource() : AngelScript: cannot read {}", path);

                return -1;
            }

            return pBuilder->AddSectionFromMemory(path.ToStringRef().c_str(), source.c_str(), static_cast<uint32_t>(source.size()));
        }

        int32_t Include(const char* pInclude, const char* pFrom, CScriptBuilder* pBuilder, void*) {
            SR_UTILS_NS::Path path = SR_UTILS_NS::Path(pFrom).GetFolder().Concat(pInclude);
            SR_UTILS_NS::VFS::Instance().UnResolvePath(path);

            if (!path.IsFile()) {
                path = CoreResLoader::GetResPath().Concat(pInclude);
            }

            return AddSource(pBuilder, path);
        }

        SR_UTILS_NS::StringAtom FullName(const asITypeInfo* pType) {
            SR_UTILS_NS::String result(pType->GetNamespace());

            if (!result.empty()) {
                result += "::";
            }

            result += pType->GetName();

            return SR_UTILS_NS::StringAtom(result);
        }

        // Source discovery does not create a VM. Compilation later validates the candidates.
        SR_UTILS_NS::String Token(const SR_UTILS_NS::String& source, uint64_t& offset) {
            while (offset < source.size()) {
                const auto c = source[offset];

                if (c == '/' && offset + 1 < source.size() && source[offset + 1] == '/') {
                    while (offset < source.size() && source[offset] != '\n') {
                        ++offset;
                    }
                }
                else if (c == '/' && offset + 1 < source.size() && source[offset + 1] == '*') {
                    offset += 2;

                    while (offset + 1 < source.size() && !(source[offset] == '*' && source[offset + 1] == '/')) {
                        ++offset;
                    }

                    offset = std::min<uint64_t>(offset + 2, source.size());
                }
                else if (c == '"' || c == '\'') {
                    ++offset;

                    while (offset < source.size() && source[offset] != c) {
                        if (source[offset] == '\\' && offset + 1 < source.size()) {
                            ++offset;
                        }

                        ++offset;
                    }

                    if (offset < source.size()) {
                        ++offset;
                    }
                }
                else if (c <= ' ') {
                    ++offset;
                }
                else {
                    break;
                }
            }

            if (offset >= source.size()) {
                return {};
            }

            const auto start = offset++;
            const auto first = source[start];

            if (first == ':' && offset < source.size() && source[offset] == ':') {
                ++offset;
            }

            if ((first >= 'a' && first <= 'z') || (first >= 'A' && first <= 'Z') || first == '_') {
                while (offset < source.size()) {
                    const auto c = source[offset];

                    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')) {
                        break;
                    }

                    ++offset;
                }
            }

            return SR_UTILS_NS::String(source.data() + start, offset - start, SR_UTILS_NS::IAllocator::GetDefaultAllocator());
        }
    }
}

#endif
