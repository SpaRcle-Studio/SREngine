//
// Created by Monika on 28.09.2026.
//

#include <Engine/World/TerrainGrassBender.h>

#include <Utils/ECS/Transform.h>

#include <Codegen/TerrainGrassBender.generated.hpp>

namespace SR_CORE_NS {
    static SR_UTILS_NS::Vector<TerrainGrassBender*>& GetBendersRegistry() {
        static SR_UTILS_NS::Vector<TerrainGrassBender*> benders;
        return benders;
    }

    const SR_UTILS_NS::Vector<TerrainGrassBender*>& TerrainGrassBender::GetActiveBenders() noexcept {
        return GetBendersRegistry();
    }

    void TerrainGrassBender::OnEnable() {
        auto&& benders = GetBendersRegistry();
        if (std::find(benders.begin(), benders.end(), this) == benders.end()) {
            benders.emplace_back(this);
        }
        Super::OnEnable();
    }

    void TerrainGrassBender::OnDisable() {
        auto&& benders = GetBendersRegistry();
        benders.erase(std::remove(benders.begin(), benders.end(), this), benders.end());
        Super::OnDisable();
    }

    void TerrainGrassBender::OnDestroy() {
        auto&& benders = GetBendersRegistry();
        benders.erase(std::remove(benders.begin(), benders.end(), this), benders.end());
        Super::OnDestroy();
    }

    SR_MATH_NS::FVector3 TerrainGrassBender::GetBendPosition() const {
        if (auto&& pTransform = GetTransform()) {
            return pTransform->GetTranslation() + m_offset;
        }
        return m_offset;
    }
}
