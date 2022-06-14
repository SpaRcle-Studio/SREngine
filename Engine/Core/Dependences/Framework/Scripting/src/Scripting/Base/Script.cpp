//
// Created by Nikita on 11.07.2021.
//

#include <Scripting/Base/Script.h>
#include <Scripting/Impl/EvoScriptImpl.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_SCRIPTING_NS {
    bool Script::IsAutoFree() const {
        return m_autoFree;
    }
}