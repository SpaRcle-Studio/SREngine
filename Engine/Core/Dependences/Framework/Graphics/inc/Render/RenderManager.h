//
// Created by Monika on 07.04.2022.
//

#ifndef SRENGINE_RENDERMANAGER_H
#define SRENGINE_RENDERMANAGER_H

#include <Utils/Singleton.h>

namespace SR_GRAPH_NS {
    class Render;

    class RenderManager : public SR_UTILS_NS::Singleton<RenderManager> {
        friend class SR_UTILS_NS::Singleton<RenderManager>;

    public:
        Render* Allocate(const std::string& name);
        Render* Get(const std::string& name);

    private:
        std::map<std::string, Render*> m_renders;

    };
}

#endif //SRENGINE_RENDERMANAGER_H
