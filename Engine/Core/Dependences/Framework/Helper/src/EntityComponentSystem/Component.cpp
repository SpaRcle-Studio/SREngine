//
// Created by Nikita on 27.11.2020.
//

#include "EntityComponentSystem/Component.h"
#include <EntityComponentSystem/GameObject.h>

Framework::Helper::Component::Component(const std::string& name)
    : m_name(name)
{ }

Framework::Helper::Component::~Component() = default;

void Framework::Helper::Component::OnAttachComponent()  {
    const std::lock_guard<std::mutex> lock(g_mutex);
    if (auto event = g_events.find(m_name); event != g_events.end())
        event->second(this);
}

bool Framework::Helper::Component::RegisterComponent(const std::string &name, const std::function<Component *(void)> &constructor)  {
    const std::lock_guard<std::mutex> lock(g_mutex);

    if (auto find = g_compList.find(name); find == g_compList.end()) {
        Debug::System("Component::RegisterComponent() : register \""+name+"\"...");
        g_compList.insert(std::make_pair(name, constructor));
        g_names.emplace_back(name);
        return true;
    }
    else{
        Debug::Error("Component::RegisterComponent() : component \""+name+"\" already registered!");
        return false;
    }
}

bool Framework::Helper::Component::RegisterEvents(const std::string &compName, const Framework::Helper::Component::Event &onAttach)  {
    const std::lock_guard<std::mutex> lock(g_mutex);

    if (auto find = g_events.find(compName); find == g_events.end()) {
        g_events.insert(std::make_pair(compName, onAttach));
        return true;
    } else {
        Debug::Error("Component::RegisterEvents() : events for component \""+compName+"\" already registered!");
        return false;
    }
}

std::vector<std::string> Framework::Helper::Component::GetComponentsNames()  {
    const std::lock_guard<std::mutex> lock(g_mutex);
    return g_names;
}

Framework::Helper::Component *Framework::Helper::Component::CreateComponentOfName(const std::string &name)  {
    const std::lock_guard<std::mutex> lock(g_mutex);

    auto find = g_compList.find(name);
    if (find == g_compList.end()) {
        Debug::Error("Component::CreateComponentOfName() : component \"" + name + "\" is not exists!");
        return nullptr;
    }
    else
        return find->second();
}

