//
// Created by Monika on 11.01.2023.
//

#include <Graphics/Animations/Skeleton.h>

#include <Utils/Types/RawMesh.h>
#include <Utils/DebugDraw.h>

namespace SR_ANIMATIONS_NS {
    SR_REGISTER_COMPONENT(Skeleton);

    Skeleton::~Skeleton() {
        DisableDebug();
        m_bonesByName.clear();
        SR_SAFE_DELETE_PTR(m_rootBone);
    }

    SR_UTILS_NS::Component* Skeleton::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pComponent = new Skeleton();

        if (marshal.Read<bool>()) {
            const SR_HTYPES_NS::Function<void(SR_ANIMATIONS_NS::Bone*)> processBone = [&](SR_ANIMATIONS_NS::Bone* pBone) {
                pBone = pComponent->AddBone(pBone, marshal.Read<std::string>(), false);

                const uint8_t count = marshal.Read<uint8_t>();

                for (uint8_t i = 0; i < count; ++i) {
                    processBone(pBone);
                }
            };

            processBone(nullptr);

            pComponent->ReCalculateSkeleton();
        }

        return pComponent;
    }

    SR_UTILS_NS::Component* Skeleton::CopyComponent() const {
        auto&& pComponent = new Skeleton();

        pComponent->m_rootBone = m_rootBone->CloneRoot();
        pComponent->ReCalculateSkeleton();

        return pComponent;
    }

    SR_HTYPES_NS::Marshal::Ptr Skeleton::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Super::Save(pMarshal, flags);

        const SR_HTYPES_NS::Function<void(SR_ANIMATIONS_NS::Bone*)> processBone = [&](SR_ANIMATIONS_NS::Bone* pBone) {
            pMarshal->Write<std::string>(pBone->name);
            pMarshal->Write<uint8_t>(pBone->bones.size());

            for (auto&& pSubNode : pBone->bones) {
                processBone(pSubNode);
            }
        };

        if (GetRootBone()) {
            pMarshal->Write<bool>(true);
            processBone(GetRootBone());
        }
        else {
            pMarshal->Write<bool>(false);
        }

        return pMarshal;
    }

    void Skeleton::OnDestroy() {
        Super::OnDestroy();
        delete this;
    }

    void Skeleton::OnLoaded() {
        Super::OnLoaded();
    }

    Bone* Skeleton::AddBone(Bone *pParent, const std::string& name, bool recalculate) {
        if ((!pParent && m_rootBone) || (pParent && !m_rootBone)) {
            SRHalt0();
            return nullptr;
        }

        auto&& pBone = new Bone();

        pBone->pRoot = m_rootBone ? m_rootBone : pBone;
        pBone->pParent = pParent;
        pBone->name = name;
        pBone->hashName = SR_HASH_STR(name);

        if (m_rootBone) {
            pParent->bones.emplace_back(pBone);
        }
        else {
            m_rootBone = pBone;
        }

        if (recalculate) {
            ReCalculateSkeleton();
        }

        return pBone;
    }

    bool Skeleton::ReCalculateSkeleton() {
        m_bonesByName.clear();
        m_bonesByIndex.clear();

        if (!m_rootBone) {
            return false;
        }

        if (m_rootBone) {
            m_rootBone->gameObject = GetGameObject();
            m_rootBone->pScene = TryGetScene();
        }

        m_bonesByName.reserve(SR_HUMANOID_MAX_BONES);
        m_bonesByIndex.reserve(SR_HUMANOID_MAX_BONES);

        bool hasErrors = false;

        const SR_HTYPES_NS::Function<void(SR_ANIMATIONS_NS::Bone*)> processBone = [&](SR_ANIMATIONS_NS::Bone* pBone) {
#ifdef SR_DEBUG
            if (m_bonesByName.count(pBone->hashName) == 1) {
                SR_ERROR("Skeleton::ReCalculateSkeleton() : bone with name \"" + pBone->name + "\" already exists in hash table!");
                hasErrors = true;
                return;
            }
#endif

            m_bonesByIndex.emplace_back(pBone);
            m_bonesByName.insert(std::make_pair(pBone->hashName, pBone));

            for (auto&& pSubBone : pBone->bones) {
                processBone(pSubBone);
            }
        };

        processBone(m_rootBone);

        if (hasErrors) {
            m_bonesByName.clear();
            SR_SAFE_DELETE_PTR(m_rootBone);
        }

        return true;
    }

    Bone* Skeleton::GetBone(uint64_t hashName) {
        auto&& pBoneIt = m_bonesByName.find(hashName);
        if (pBoneIt == m_bonesByName.end()) {
            return nullptr;
        }

        if (!pBoneIt->second->gameObject && !pBoneIt->second->hasError && !pBoneIt->second->Initialize()) {
            SR_WARN("Skeleton::GetBone() : failed to find bone game object!\n\tName: " + pBoneIt->second->name);
        }

        return pBoneIt->second;
    }

    void Skeleton::OnAttached() {
        ReCalculateSkeleton();
        Super::OnAttached();
    }

    void Skeleton::Update(float_t dt) {
        if (m_bonesByName.empty()) { /// Update не должен вызываться, если кости ещё не загружены
            return;
        }

        if (m_debugEnabled) {
            UpdateDebug();
        }
        else {
            DisableDebug();
        }

        Super::Update(dt);
    }

    void Skeleton::DisableDebug() {
        if (m_debugLines.empty()) {
            return;
        }

        for (auto&& [pBone, debugId] : m_debugLines) {
            SR_UTILS_NS::DebugDraw::Instance().DrawLine(debugId);
        }

        m_debugLines.clear();
    }

    void Skeleton::UpdateDebug() {
        if (!m_rootBone) {
            DisableDebug();
            return;
        }

        for (auto&& [hashName, pBone] : m_bonesByName) {
            if (!pBone->pParent || pBone->pParent == pBone->pRoot) {
                continue;
            }

            if (m_debugLines.count(pBone) == 0) {
                m_debugLines.insert(std::make_pair(pBone, SR_ID_INVALID));
            }

            auto&& debugId = m_debugLines[pBone];

            auto&& fromGameObject = GetBone(pBone->hashName);
            auto&& toGameObject = GetBone(pBone->pParent->hashName);

            if (!fromGameObject->gameObject || !toGameObject->gameObject) {
                continue;
            }

            debugId = SR_UTILS_NS::DebugDraw::Instance().DrawLine(
                    debugId,
                    fromGameObject->gameObject->GetTransform()->GetMatrix().GetTranslate(),
                    toGameObject->gameObject->GetTransform()->GetMatrix().GetTranslate(),
                    SR_MATH_NS::FColor(38, 37, 45, 255)
            );
        }
    }

    Bone *Skeleton::GetBoneByIndex(uint64_t index) {
        if (index >= m_bonesByIndex.size()) {
            return nullptr;
        }

        if (!m_bonesByIndex[index]->gameObject && !m_bonesByIndex[index]->hasError && !m_bonesByIndex[index]->Initialize()) {
            SR_WARN("Skeleton::GetBoneByIndex() : failed to find bone game object!\n\tName: " + m_bonesByIndex[index]->name);
        }

        return m_bonesByIndex.at(index);
    }

    uint64_t Skeleton::GetBoneIndex(uint64_t hashName) {
        for (uint64_t i = 0; i < m_bonesByIndex.size(); ++i) {
            if (m_bonesByIndex[i]->hashName == hashName) {
                return i;
            }
        }

        return SR_ID_INVALID;
    }
}
