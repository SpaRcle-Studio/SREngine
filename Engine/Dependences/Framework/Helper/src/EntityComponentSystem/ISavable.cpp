//
// Created by Monika on 22.09.2021.
//

#include <EntityComponentSystem/ISavable.h>
#include <EntityComponentSystem/Scene.h>
#include <Utils/Numeric.h>
#include <Utils/StringFormat.h>
#include <Debug.h>

std::mutex Framework::Helper::ISavable::g_mutex = std::mutex();
std::set<uint64_t> Framework::Helper::ISavable::g_entities = {};

Framework::Helper::ISavable::ISavable() {
    const std::lock_guard<std::mutex> lock(g_mutex);

    ret:
    auto rnd = Helper::Random::Instance().Int64();
    if (g_entities.count(rnd))
        goto ret;
    else {
        g_entities.insert(rnd);
        m_id = rnd;
    }
}

Framework::Helper::ISavable::~ISavable() {
    const std::lock_guard<std::mutex> lock(g_mutex);

    if (g_entities.count(m_id))
        g_entities.erase(m_id);
    else
        Debug::Error(Helper::Format("ISavable::~ISavable() : entity %llu isn't exists!", m_id));
}
