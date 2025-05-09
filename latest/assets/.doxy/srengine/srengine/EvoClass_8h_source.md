

# File EvoClass.h

[**File List**](files.md) **>** [**Compilation**](dir_851141f4261c6b16b58da121ff8aacd8.md) **>** [**EvoClass.h**](EvoClass_8h.md)

[Go to the documentation of this file](EvoClass_8h.md)


```C++
//
// Created by Nikita on 10.07.2021.
//

#ifndef EVOSCRIPT_EVOCLASS_H
#define EVOSCRIPT_EVOCLASS_H

#include <Scripting/Compilation/Method.h>

namespace EvoScript {
    struct InheritClass {
        std::string m_name;
        Publicity   m_pub;

        bool operator<(const InheritClass& rhs) const {
            return m_name < rhs.m_name && m_pub < rhs.m_pub;
        }
    };

    struct Class {
        std::string               m_header;
        std::string               m_name;
        std::vector<Property>     m_properties;
        std::vector<Method>       m_methods;
        std::vector<InheritClass> m_inherit;

        [[nodiscard]] std::string GetAsIncomplete() const {
            return "class " + m_name + ";";
        }

        [[nodiscard]] std::string GetInherit() const {
            return m_inherit.empty() ? "" : m_inherit[0].m_name;
        }

        [[nodiscard]] std::string ToString() const {
            std::string result;

            result += "class " + m_name;

            if (!m_inherit.empty()) {
                result += " : ";
                uint32_t i = 0;
                for (const auto& inherit : m_inherit) {
                    result += PublicityToString(inherit.m_pub, false) + " " + inherit.m_name;
                    if (i++; i != m_inherit.size())
                        result += ", ";
                }
            }

            result += " {\n";

            result += "public:\n";
            result += "\t" + m_name + "() = delete;\n";
            result += "\t~" + m_name + "() = default;\n";
            result += "\t" + m_name + "(" + m_name + " &) = delete;\n";
            result += "\t" + m_name + "(const " + m_name + " &) = delete;\n";

            Publicity currentPub = Unknown;
            for (const Property& property : m_properties) {
                if (currentPub != property.m_pub) {
                    currentPub = property.m_pub;
                    result += PublicityToString(currentPub) + "\n";
                }

                result += "\t" + property.m_type + " " + property.m_name + ";\n";
            }

            if (!m_methods.empty()) {
                currentPub = m_methods[0].m_public;
                result += PublicityToString(currentPub) + "\n";
            }

            for (const auto& method : m_methods) {
                if (currentPub != method.m_public) {
                    currentPub = method.m_public;
                    result += PublicityToString(currentPub) + "\n";
                }

                result += Tools::TabString(method.ToString()) + "\n";
            }

            result += "};";

            return result;
        }
    };
}

#endif //EVOSCRIPT_EVOCLASS_H
```


