//
// Created by Monika on 11.01.2023.
//

#include <Graphics/Animations/Skeleton.h>

#include <Utils/Types/RawMesh.h>

namespace SR_ANIMATIONS_NS {
    SR_REGISTER_COMPONENT(Skeleton);

    Skeleton::~Skeleton() {
        m_bonesById.clear();
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
        m_bonesById.clear();
        m_bonesByName.clear();

        if (!m_rootBone) {
            return false;
        }

        m_bonesById.reserve(SR_HUMANOID_MAX_BONES);
        m_bonesByName.reserve(SR_HUMANOID_MAX_BONES);

        bool hasErrors = false;

        const SR_HTYPES_NS::Function<void(SR_ANIMATIONS_NS::Bone*)> processBone = [&](SR_ANIMATIONS_NS::Bone* pBone) {
            m_bonesById.emplace_back(pBone);

#ifdef SR_DEBUG
            if (m_bonesByName.count(pBone->hashName) == 1) {
                SR_ERROR("Skeleton::ReCalculateSkeleton() : bone with name \"" + pBone->name + "\" already exists in hash table!");
                hasErrors = true;
                return;
            }
#endif

            m_bonesByName.insert(std::make_pair(pBone->hashName, pBone));

            for (auto&& pSubBone : pBone->bones) {
                processBone(pSubBone);
            }
        };

        processBone(m_rootBone);

        if (hasErrors) {
            m_bonesById.clear();
            m_bonesByName.clear();
            SR_SAFE_DELETE_PTR(m_rootBone);
        }

        return true;
    }
}
