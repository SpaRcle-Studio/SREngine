//
// Created by Monika on 30.10.2021.
//

#ifndef SR_ENGINE_SCRIPTING_CASTING_H
#define SR_ENGINE_SCRIPTING_CASTING_H

#include <Scripting/Compilation/AddressTableGen.h>
#include <Scripting/Compilation/Method.h>
#include <Scripting/IState.h>

namespace EvoScript {
    enum class CastingType { Unknown, Dynamic, Static, Reinterpret };

    static std::string CastingTypeToString(CastingType type) {
        switch (type) {
        case CastingType::Dynamic:
            return "Dynamic";
        case CastingType::Static:
            return "Static";
        case CastingType::Reinterpret:
            return "Reinterpret";
        case CastingType::Unknown:
        default:
            return "Unknown";
        }
    }

    class CastingGen {
    public:
        explicit CastingGen(AddressTableGen* addressTableGen) : m_addressTable(addressTableGen) {};

    private:
        std::set<std::string> m_incomplete;
        std::vector<Method> m_casts;
        AddressTableGen* m_addressTable;

    private:
        std::string Generate();

    public:
        bool RegisterCast(
            const std::function<void(EvoScript::IState*)>& setter, const std::string& from, const std::string& to,
            CastingType type
        );

        bool Save(const std::string& folder);
    };
} // namespace EvoScript

#endif // SR_ENGINE_SCRIPTING_CASTING_H
