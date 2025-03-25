//
// Created by Nikita on 11.07.2021.
//

#include <EvoScript/Compilation/Method.h>
#include <EvoScript/Tools/StringUtils.h>

void EvoScript::Method::MathArguments() {
    for (uint32_t i = 0; i < m_args.size(); i++) {
        m_stringArgs  += m_args[i];
        m_argNames += EvoScript::Tools::BackReadTo(m_args[i], ' ');
        if (i + 1 != m_args.size()) {
            m_stringArgs  += ", ";
            m_argNames += ", ";
        }
    }
}

std::string EvoScript::Method::ToString() const  {
    std::string result;
    switch (m_type) {
        case Normal:
            result += m_return + " " + m_name + "(" + m_stringArgs + ") {\n";
            break;
        case Virtual:
            result += "virtual " + m_return + " " + m_name + "(" + m_stringArgs + ")";
            break;
        case Override:
            result += m_return + " " + m_name + "(" + m_stringArgs + ") override {\n";
            break;
        case Static:
            result += "static " + m_return + " " + m_name + "(" + m_stringArgs + ") {\n";
            break;
        case VirtualOverride:
            result += "virtual " + m_return + " " + m_name + "(" + m_stringArgs + ") override {\n";
            break;
    }

    if (m_type == Virtual) {
        if (m_return == "void") {
            result += " { }";
        }
        else {
            result += " = 0;";
        }

        return result;
    }

    if (m_type == Static) {
        if (m_argNames.empty())
            result += "\treturn g_" + m_class + m_name + "FnPtr();\n";
        else
            result += "\treturn g_" + m_class + m_name + "FnPtr(" + m_argNames + ");\n";
    }
    else {
        if (m_argNames.empty())
            result += "\treturn g_" + m_class + m_name + "FnPtr(this);\n";
        else
            result += "\treturn g_" + m_class + m_name + "FnPtr(this, " + m_argNames + ");\n";
    }

    result += "}";

    return result;
}

std::string EvoScript::Method::GetTypedef() const {
    std::string name = m_class + m_name + "FnPtr";

    if (m_type == Static) {
        if (m_stringArgs.empty())
            return "std::function<" + m_return + "()> " + name + ";";
        else
            return "std::function<" + m_return + "(" + m_stringArgs + ")> " + name + ";";
    } else {
        if (m_stringArgs.empty())
            return "std::function<" + m_return + "(" + m_class + "*)> " + name + ";";
        else
            return "std::function<" + m_return + "(" + m_class + "*, " + m_stringArgs + ")> " + name + ";";
    }
}

std::string EvoScript::Method::GetSetter() const {
    std::string _typedef = m_class + m_name + "FnPtr";

    if (m_type == Static) {
        if (m_stringArgs.empty())
            return "EXTERN void " + _typedef + "Setter(const std::function<" + m_return +
                   +"()>& fnPtr) { \n\tg_" + _typedef + " = fnPtr; \n}\n";
        else
            return "EXTERN void " + _typedef + "Setter(const std::function<" + m_return +
                   +"(" + m_stringArgs + ")>& fnPtr) { \n\tg_" + _typedef + " = fnPtr; \n}\n";
    } else {
        if (m_stringArgs.empty())
            return "EXTERN void " + _typedef + "Setter(const std::function<" + m_return +
                   +"(" + m_class + "*)>& fnPtr) { \n\tg_" + _typedef + " = fnPtr; \n}\n";
        else
            return "EXTERN void " + _typedef + "Setter(const std::function<" + m_return +
                   +"(" + m_class + "*, " + m_stringArgs + ")>& fnPtr) { \n\tg_" + _typedef + " = fnPtr; \n}\n";
    }
}

std::string EvoScript::Method::GetSetterWithVar() const {
    auto _typedef = m_class + m_name + "FnPtr";
    std::string result = "typedef " + GetTypedef() + "\n";
    result += (_typedef + " g_").append(_typedef) + ";\n";
    return result + GetSetter();
}
