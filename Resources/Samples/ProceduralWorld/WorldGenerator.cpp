//
// Created by Monika on 26.02.2023.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>
#include <Libraries/Math/Quaternion.h>

#include <Libraries/Debug.h>
#include <Libraries/Input.h>
#include <Libraries/Casts.h>

class WorldGenerator : public Behaviour {
public:
    void Update(float_t dt) {
        auto&& pLogic = DynamicCastSceneLogicToSceneCubeChunkLogic(scene->GetLogicBase());
        // if (auto&& pObserver = scene->GetObserver()) {
        // }
    }

private:
    IVector3 m_region;
    IVector3 m_chunk;

    int32_t m_scope = 0;
    int32_t m_regionWidth = 0;

};

REGISTER_BEHAVIOUR(WorldGenerator)
