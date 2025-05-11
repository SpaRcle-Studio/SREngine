

# File AddressTableGen.h

[**File List**](files.md) **>** [**Compilation**](dir_f4efc9bee95c06127bdf4e6c5eda8bf7.md) **>** [**AddressTableGen.h**](AddressTableGen_8h.md)

[Go to the documentation of this file](AddressTableGen_8h.md)


```C++
//
// Created by Nikita on 09.07.2021.
//

#ifndef SR_ENGINE_SCRIPTING_ADDRESS_TABLE_GEN_H
#define SR_ENGINE_SCRIPTING_ADDRESS_TABLE_GEN_H

#include <Scripting/Tools/SetUtils.h>
#include <Scripting/Tools/StringUtils.h>
#include <Scripting/Compilation/EvoClass.h>
#include <Scripting/IState.h>

namespace EvoScript {
    struct EvoEnum {
        std::string m_name;
        std::string m_header;
        bool        m_asClass;
        std::vector<std::pair<std::string, int32_t>> m_values;

        [[nodiscard]] std::string ToString() const {
            std::string result = "enum ";

            if (m_asClass)
                result += "class ";
            result += m_name + " {\n\t";

            for (const auto& [name, value] : m_values)
                result += name + " = " + std::to_string(value) + ", ";

            result += "\n};";

            return result;
        }
    };

    struct Header {
        std::string              m_name;
        std::set<std::string>    m_includes;
        std::vector<std::string> m_incompleteTypes;
        std::vector<std::string> m_typedefs;
        std::vector<EvoEnum>     m_enums;
        std::vector<Class>       m_classes;
        std::vector<Method>      m_functions;

        Class* FindClass(const std::string& name) {
            for (auto& _class : m_classes)
                if (_class.m_name == name)
                    return &_class;
            return nullptr;
        }

        [[nodiscard]] std::string GetIncludes() const {
            std::string result;
            for (const auto& inc : m_includes)
                result += "#include \"" + inc + "\"\n";
            return result;
        }

        [[nodiscard]] std::string ToString() const {
            std::string result;

            result += "//\n// Created by Evo Script code generator on "
                      + Tools::GetDate() + " | Author - Monika\n//\n\n";

            result += "#ifndef EVOSCRIPTLIB_" + Tools::ToUpper(m_name) + "_H\n";
            result += "#define EVOSCRIPTLIB_" + Tools::ToUpper(m_name) + "_H\n\n";

            result += "#ifndef EXTERN\n";
        #ifdef ES_MSVC
            result += "#define EXTERN extern \"C\" __declspec(dllexport)\n";
        #elif defined(ES_GCC)
            result += "#define EXTERN extern \"C\" __attribute__((visibility(\"default\")))\n";
        #endif
            result += "#endif\n\n";

            result += "#include <functional>\n\n";

            if (std::string inc = GetIncludes(); !inc.empty())
                result +=  inc + "\n";

            for (const auto& _enum : m_enums)
                result += _enum.ToString() + "\n\n";

            for (const auto& incomplete : m_incompleteTypes)
                result += "class " + incomplete + ";\n";
            if (!m_incompleteTypes.empty())
                result += "\n";

            for (const auto& _class : m_classes)
                result += _class.GetAsIncomplete() + "\n";
            result += "\n";

            for (const auto& _typedef : m_typedefs)
                result += _typedef;
            if (!m_typedefs.empty())
                result += "\n";

            for (const auto& _class : m_classes) {
                for (const auto &_method : _class.m_methods) {
                    if (_method.m_type == Virtual) {
                        continue;
                    }

                    result += _method.GetSetterWithVar().append("\n");
                }
            }

            for (const auto& _class : m_classes)
                result += _class.ToString() + "\n\n";

            for (auto&& function : m_functions) {
                result += function.GetSetterWithVar().append("\n");
                result += function.ToString();
            }

            result += "#endif";

            return result;
        }
    };

    class AddressTableGen {
        using SetterFn = std::function<void(EvoScript::IState*)>;
    public:
        AddressTableGen()  = default;
        ~AddressTableGen() = default;

        AddressTableGen(const AddressTableGen&) = delete;

    public:
        template<typename T> void SetPointer(T* pointer) {
            m_pointers[typeid(T).hash_code()] = (void*)pointer;
        }

        template<typename T> T* GetPointer() const {
            auto&& pIt = m_pointers.find(typeid(T).hash_code());
            if (pIt == m_pointers.end()) {
                return nullptr;
            }
            return (T*)pIt->second;
        }

        SR_NODISCARD size_t GetApiHash() const { return m_hash; }
        SR_NODISCARD std::string GetApiVersion() const { return std::to_string(GetApiHash()); }
        SR_NODISCARD std::vector<std::function<void(EvoScript::IState*)>> GetAddresses() const { return m_methodPointers; }
        SR_NODISCARD Header GetHeader(const std::string& name) const {
            if (auto f = m_headers.find(name); f == m_headers.end()) {
                SR_ERROR("AddressTableGen::GetHeader() : header isn't exists!");
                return { };
            } else
                return m_headers.at(name);
        }
        bool Save(const std::string& libFolder);

    public:
        bool RegisterMethod(
                const SetterFn& setter,
                const std::string& className,
                const std::string& methodName,
                const std::string& returnType,
                const std::vector<std::string>& argTypes,
                MethodType type,
                const std::string& _overrideClass = "",
                Publicity publicity = Publicity::Public);

        bool RegisterFunction(
                const SetterFn& setter,
                const std::string& methodName,
                const std::string& returnType,
                const std::vector<std::string>& argTypes,
                const std::string& header);

        bool RegisterMethod(
                const std::string& className,
                const std::string& methodName,
                const std::string& returnType,
                const std::vector<std::string>& argTypes,
                MethodType type,
                const std::string& _overrideClass = "",
                Publicity publicity = Publicity::Public);

        bool RegisterHeader(const std::string& name, const std::set<std::string>& includes = {});

        bool RegisterNewClass(
                const std::string& name,
                const std::string& header,
                const std::set<std::string>& includes = {},
                const std::vector<InheritClass>& inherit = {});

        bool RegisterEnum(
                const std::string& name,
                const std::string& header,
                bool asClass,
                const std::vector<std::pair<std::string, int32_t>>& values);

        bool RegisterTypedef(const std::string& name, const std::string& header, const std::string& value);
        bool RegisterUsing(const std::string& name, const std::string& header, const std::string& value);
        bool RegisterDefine(const std::string& name, const std::string& header, const std::string& value);
        bool AddIncompleteType(const std::string& className, const std::string& header);
        void AddMethodPointer(const std::function<void(EvoScript::IState*)>& setter);
        void HashCombine(const std::string& hashString);

    private:
        std::map<std::string, std::string>                   m_classes;
        std::map<std::string, Header>                        m_headers;
        std::vector<std::function<void(EvoScript::IState*)>> m_methodPointers;
        size_t                                               m_hash = 0;
        std::map<uint64_t, void*> m_pointers;

    };
}

#endif //SR_ENGINE_SCRIPTING_ADDRESS_TABLE_GEN_H
```


