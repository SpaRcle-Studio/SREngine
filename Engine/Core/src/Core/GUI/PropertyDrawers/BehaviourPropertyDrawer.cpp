//
// Created by Monika on 04.05.2025.
//

#include <Core/GUI/PropertyDrawers/BehaviourPropertyDrawer.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Cpp/CppBehaviour.h>
#include <Scripting/Cpp/ModuleManager.h>

#include <Codegen/BehaviourPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    BehaviourPropertyDrawer::BehaviourPropertyDrawer() {
        m_moduleReloadSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_SCRIPT_MODULE_RELOADED_ID, [this](auto&& msg) {
            m_pObjectPropertyDrawer.Reset();
        });
    }

    PropertyDrawerFeedback BehaviourPropertyDrawer::DrawCustomProperties(const PropertyDrawerContext& context) {
        auto&& pCppBehaviour = dynamic_cast<SR_SCRIPTING_NS::Behaviour*>(context.pOwner)->GetBehaviour();
        if (!pCppBehaviour) {
            return {};
        }

        if (!m_pObjectPropertyDrawer) {
            m_pObjectPropertyDrawer = SRNew<SR_CORE_GUI_NS::ObjectPropertyDrawer>();
        }

        auto&& valueRef = SR_UTILS_NS::Reflection::Value::CreateRef(*dynamic_cast<SR_UTILS_NS::SRClass*>(pCppBehaviour));

        PropertyDrawerContext newContext = context;
        newContext.pValue = &valueRef;
        newContext.noHeader = true;

        return m_pObjectPropertyDrawer->Draw(newContext);
    }
}
