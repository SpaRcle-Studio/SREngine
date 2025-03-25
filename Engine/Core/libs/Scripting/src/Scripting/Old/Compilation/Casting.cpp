//
// Created by Monika on 30.10.2021.
//

#include <EvoScript/Compilation/Casting.h>
#include <EvoScript/Tools/FileSystem.h>

#include <set>

bool EvoScript::CastingGen::RegisterCast(
        const std::function<void(EvoScript::IState *)> &setter,
        const std::string &from,
        const std::string &to,
        EvoScript::CastingType type)
{
    m_addressTable->HashCombine("Cast_from_" + from + "_to_" + to);
    m_addressTable->AddMethodPointer(setter);

    m_incomplete.insert(from);
    m_incomplete.insert(to);

    Method method = {
            .m_name       = CastingTypeToString(type) + "Cast" + from + "To" + to,
            .m_class      = "",
            .m_return     = to + "*",
            .m_args       = { },
            .m_type       = MethodType::Static,
            .m_override   = "",
            .m_public     = Publicity::Unknown,
            .m_stringArgs = from + "* from",
            .m_argNames   = "from"
    };

    m_casts.emplace_back(method);

    return true;
}

bool EvoScript::CastingGen::Save(const std::string& folder) {
    Tools::CreatePath(Tools::FixPath(folder));

    std::string path = folder + "Casts.h";
    std::ofstream file(path);
    if (!file.is_open()) {
        ES_ERROR("CastingGen::Save() : failed to create file! \n\tPath: " + path);
        return false;
    }

    file << this->Generate();

    file.close();

    return true;
}

std::string EvoScript::CastingGen::Generate() {
    std::string result = "//\n// Created by Evo Script code generator on "
              + Tools::GetDate() + " | Author - Monika\n//\n\n";

    result += "#ifndef EVOSCRIPTLIB_CASTS_H\n";
    result += "#define EVOSCRIPTLIB_CASTS_H\n\n";

    result += "#ifndef EXTERN\n";
    result += "\t#ifdef __GNUC__\n";
    result += "\t#define EXTERN extern \"C\" __attribute__((visibility(\"default\")))\n";
    result += "\t#else\n";
    result += "\t#define EXTERN extern \"C\" __declspec(dllexport)\n";
    result += "\t#endif\n";
    result += "#endif\n\n";

    result += "#include <functional>\n\n";

    if (!m_incomplete.empty()) {
        for (const auto& name : m_incomplete)
            result.append("class ").append(name).append(";\n");

        result.append("\n");
    }

    if (!m_casts.empty()) {
        for (const auto& cast : m_casts) {
            result += cast.GetSetterWithVar().append("\n");
            result += cast.ToString().append("\n\n");
        }
    }

    result += "#endif // EVOSCRIPTLIB_CASTS_H";

    return result;
}
