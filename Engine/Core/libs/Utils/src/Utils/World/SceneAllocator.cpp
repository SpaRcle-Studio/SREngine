//
// Created by Monika on 23.08.2022.
//

#include <Utils/World/SceneAllocator.h>

namespace SR_WORLD_NS {
    bool SceneAllocator::Init(const SceneAllocator::Allocator &allocator) {
        if (m_allocator) {
            SR_WARN("SceneAllocator::Init() : allocator already initialized!");
            return false;
        }

        m_allocator = allocator;

        return true;
    }

    SceneAllocator::ScenePtr SceneAllocator::Allocate() {
        if (!m_allocator) {
            SRHalt("SceneAllocator::Allocate() : allocator isn't initialized!");
            Platform::Terminate();
        }

        return *m_allocator();
    }
}