//
// Created by Nikita on 09.07.2021.
//

#include <EvoScript/Tools/Debug.h>
#include <EvoScript/Tools/FileSystem.h>
#include "EvoScript/Compilation/AddressTableGen.h"

bool EvoScript::AddressTableGen::RegisterNewClass(
        const std::string &name,
        const std::string &header,
        const std::set<std::string>& includes,
        const std::vector<InheritClass>& inherit)
{
    HashCombine("Class_" + name);

    if (auto f = m_classes.find(name); f != m_classes.end()) {
        ES_ERROR("AddressTableGen::RegisterClass() : class \"" + name + "\" is already exists!");
        return false;
    } else m_classes[name] = header;

    Class _class = {
        .m_header     = header,
        .m_name       = name,
        .m_properties = { },
        .m_methods    = { },
        .m_inherit    = inherit,
    };

    if (auto f = m_headers.find(header); f != m_headers.end()) { // add in exists header
        m_headers[header].m_classes.emplace_back(_class);
        m_headers[header].m_includes = Tools::Merge<std::string>(m_headers[header].m_includes, includes);
    }
    else { // create new header
        m_headers[header] = { header, includes, { }, { }, { }, { _class } };
    }

    return true;
}

bool EvoScript::AddressTableGen::RegisterMethod(
    const std::function<void(EvoScript::IState*)>& setter,
    const std::string &className,
    const std::string &methodName,
    const std::string &returnType,
    const std::vector<std::string>& argTypes,
    MethodType type,
    const std::string& _overrideClass,
    Publicity publicity)
{
    HashCombine("Class_" + className + "_Method_" + methodName);

    if (auto _class = m_classes.find(className); _class == m_classes.end()) {
        ES_ERROR("AddressTableGen::RegisterMethod() : class \"" + className + "\" isn't exists!")
        return false;
    }
    else {
        if (setter) {
            AddMethodPointer(setter);
        }

        Method method = {
            .m_name       = methodName,
            .m_class      = className,
            .m_return     = returnType,
            .m_args       = argTypes,
            .m_type       = type,
            .m_override   = _overrideClass,
            .m_public     = publicity,
            .m_stringArgs = "",
            .m_argNames   = ""
        };
        method.MathArguments();

        auto& [key, header] = *_class;
        m_headers[header].FindClass(className)->m_methods.emplace_back(method);

        return true;
    }
}

bool EvoScript::AddressTableGen::Save(const std::string& libFolder) {
    Tools::CreatePath(Tools::FixPath(libFolder));

    for (const auto& [key, header] : m_headers) {
        std::string path = libFolder + key + ".h";
        std::ofstream file(path);
        if (!file.is_open()) {
            ES_ERROR("AddressTableGen::Save() : failed to create file! \n\tPath: " + path);
            return false;
        }

        file << header.ToString();

        file.close();
    }

    /// Allocator
    {
        std::string path = libFolder + "MemoryAllocator.h";
        std::ofstream file(path);
        if (!file.is_open()) {
            ES_ERROR("AddressTableGen::Save() : failed to create file! \n\tPath: " + path);
            return false;
        }

        file <<
                "//\n// Created by Evo Script code generator on " + Tools::GetDate() + " | Author - Monika\n//\n\n"
                "#ifndef EVOSCRIPTLIB_MEMORY_ALLOCATOR_H\n"
                "#define EVOSCRIPTLIB_MEMORY_ALLOCATOR_H\n"
                "\n"
                "#include <memory>\n\n"
                "#ifdef __GNUC__\n"
                "\t#define ES_GCC\n"
                "\t#include <cstdlib>\n"
                "\t#ifndef ES_EXTERN\n"
                "\t\t#define ES_EXTERN extern \"C\" __attribute__((visibility(\"default\")))\n"
                "\t#endif\n"
                "#endif\n\n"
                "#ifdef __linux__\n"
                "\t#define ES_LINUX\n"
                "\t#define SR_LINUX\n"
                "#endif\n\n"
                "#ifndef ES_EXTERN\n"
                "\t#define ES_EXTERN extern \"C\" __declspec(dllexport)\n"
                "#endif\n"
                "\n"
                "typedef void*(*AllocateMemoryFnPtr)(size_t sz);\n"
                "typedef void(*FreeMemoryFnPtr)(void* ptr);\n"
                "\n"
                "AllocateMemoryFnPtr g_allocateMemory = nullptr;\n"
                "FreeMemoryFnPtr g_freeMemory = nullptr;\n"
                "\n"
                "ES_EXTERN void SetAllocateMemoryFnPtr(AllocateMemoryFnPtr fn) {\n"
                "\tg_allocateMemory = fn;\n"
                "}\n"
                "\n"
                "ES_EXTERN void SetFreeMemoryFnPtr(FreeMemoryFnPtr fn) {\n"
                "\tg_freeMemory = fn;\n"
                "}\n"
                "\n"
                "void* ESMemoryAlloc(size_t sz) {\n"
                "\tif (g_allocateMemory) {\n"
                "\t\treturn g_allocateMemory(sz);\n"
                "\t}\n"
                "\treturn malloc(sz);\n"
                "}\n"
                "\n"
                "void ESMemoryFree(void* ptr) {\n"
                "\tif (g_freeMemory) {\n"
                "\t\tg_freeMemory(ptr);\n"
                "\t}\n"
                "\telse {\n"
                "\t\tfree(ptr);\n"
                "\t}\n"
                "}\n"
                "\n"
                "#endif //EVOSCRIPTLIB__MEMORY_ALLOCATOR_H";

        file.close();
    }

    return true;
}

bool EvoScript::AddressTableGen::RegisterEnum(
        const std::string &name,
        const std::string &header,
        bool asClass,
        const std::vector<std::pair<std::string, int32_t>>& values)
{
    HashCombine("Enum_" + name);

    EvoEnum evoEnum = {
            .m_name = name,
            .m_header = header,
            .m_asClass = asClass,
            .m_values = values
    };

    if (auto f = m_headers.find(header); f != m_headers.end()) // add in exists header
        m_headers[header].m_enums.emplace_back(evoEnum);
    else // create new header
        m_headers[header] = { header, { /* includes */ }, { /* incomplete */ }, { }, { evoEnum }, { } };

    return true;
}

bool EvoScript::AddressTableGen::AddIncompleteType(const std::string &className, const std::string &header) {
    HashCombine("IncompleteClass_" + className);

    if (auto f = m_headers.find(header); f != m_headers.end()) // add in exists header
        m_headers[header].m_incompleteTypes.emplace_back(className);
    else // create new header
        m_headers[header] = { header, { /* includes */ }, { className }, { }, { }, { } };

    return true;
}

bool EvoScript::AddressTableGen::RegisterTypedef(
        const std::string &name,
        const std::string& header,
        const std::string &value)
{
    HashCombine("Typedef_" + name);

    std::string _typedef = "typedef " + value + " " + name + ";\n";
    if (auto f = m_headers.find(header); f != m_headers.end()) // add in exists header
        m_headers[header].m_typedefs.emplace_back(_typedef);
    else // create new header
        m_headers[header] = { header, { /* includes */ }, { /*incomplete*/ }, { _typedef }, { /*enums*/ }, { /*classes*/ } };

    return true;
}

bool EvoScript::AddressTableGen::RegisterUsing(
        const std::string &name,
        const std::string& header,
        const std::string &value)
{
    HashCombine("Using_" + name);

    std::string _using = "using " + name + " = " + value + ";\n";
    if (auto f = m_headers.find(header); f != m_headers.end()) // add in existing header
        m_headers[header].m_typedefs.emplace_back(_using);
    else // create new header
        m_headers[header] = { header, { /* includes */ }, { /*incomplete*/ }, { _using }, { /*enums*/ }, { /*classes*/ } };

    return true;
}

bool EvoScript::AddressTableGen::RegisterDefine(
        const std::string &name,
        const std::string& header,
        const std::string &value)
{
    HashCombine("Define_" + name);

    std::string _define = "#define " + name + " " + value + ";\n";
    if (auto f = m_headers.find(header); f != m_headers.end()) // add in existing header
        m_headers[header].m_typedefs.emplace_back(_define);
    else // create new header
        m_headers[header] = { header, { /* includes */ }, { /*incomplete*/ }, { _define }, { /*enums*/ }, { /*classes*/ } };

    return true;
}

void EvoScript::AddressTableGen::AddMethodPointer(const std::function<void(EvoScript::IState *)> &setter) {
    this->m_methodPointers.emplace_back(setter);
}

void EvoScript::AddressTableGen::HashCombine(const std::string& hashString) {
    std::hash<std::string> h;
    m_hash ^= h(hashString) + 0x9e3779b9 + (m_hash << 6) + (m_hash >> 2);
}

bool EvoScript::AddressTableGen::RegisterMethod(const std::string &className, const std::string &methodName,
                                                const std::string &returnType, const std::vector<std::string> &argTypes,
                                                EvoScript::MethodType type, const std::string &_overrideClass,
                                                EvoScript::Publicity publicity)
{
    return RegisterMethod(SetterFn(), className, methodName, returnType, argTypes, type, _overrideClass, publicity);
}

bool EvoScript::AddressTableGen::RegisterFunction(const EvoScript::AddressTableGen::SetterFn &setter,
                                                  const std::string &methodName,
                                                  const std::string &returnType,
                                                  const std::vector<std::string> &argTypes,
                                                  const std::string& header) {
    HashCombine("Function_" + methodName);

    if (setter) {
        AddMethodPointer(setter);
    }

    Method method = {
            .m_name       = methodName,
            .m_class      = "",
            .m_return     = returnType,
            .m_args       = argTypes,
            .m_type       = MethodType::Normal,
            .m_override   = "",
            .m_public     = Publicity::Unknown,
            .m_stringArgs = "",
            .m_argNames   = ""
    };
    method.MathArguments();

    m_headers[header].m_functions.emplace_back(method);

    return true;
}

bool EvoScript::AddressTableGen::RegisterHeader(const std::string &name, const std::set<std::string>& includes) {
    if (m_headers.count(name) == 1) {
        ES_ERROR("AddressTableGen::RegisterHeader() : header already registered!");
        return false;
    }

    m_headers[name] = { name, { includes }, { /* incomplete */ }, { }, {  }, { } };

    return true;
}
