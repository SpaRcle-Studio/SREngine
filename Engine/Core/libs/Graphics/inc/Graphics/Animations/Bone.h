//
// Created by Monika on 19.08.2021.
//

#ifndef GAMEENGINE_BONE_H
#define GAMEENGINE_BONE_H

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>

#include <Graphics/Types/Mesh.h>
#include <Graphics/Render/Render.h>

namespace SR_ANIMATIONS_NS {
    struct Bone : public SR_UTILS_NS::NonCopyable {
    public:
        ~Bone() override {
            for (auto&& pBone : bones) {
                delete pBone;
            }
        }

        SR_NODISCARD Bone* CloneRoot() const noexcept {
            Bone* pRootBone = new Bone();

            pRootBone->hashName = hashName;
            pRootBone->name = name;
            pRootBone->gameObject = gameObject;
            pRootBone->pRoot = pRootBone;
            pRootBone->pParent = nullptr;
            pRootBone->pScene = pScene;

            pRootBone->bones.reserve(bones.size());

            for (auto&& pSubBone : bones) {
                pRootBone->bones.emplace_back(pSubBone->Clone(pRootBone));
            }

            return pRootBone;
        }

        bool Initialize() {
            if (!pRoot->gameObject && !pRoot->pScene) {
                SRHalt0();
                hasError = true;
                return false;
            }

            std::vector<uint64_t> names = { hashName };

            Bone* pParentBone = pParent;
            /// рутовую ноду в расчет не берем
            while (pParentBone && pParentBone->pParent) {
                names.emplace_back(pParentBone->hashName);
                pParentBone = pParentBone->pParent;
            }

            if (pRoot->gameObject) {
                gameObject = pRoot->gameObject;
            }

            for (int32_t i = names.size() - 1; i >= 0; i--) {
                if (gameObject) {
                    if (!(gameObject = gameObject->Find(names[i]))) {
                        break;
                    }
                }
                else {
                    if (!(gameObject = pRoot->pScene->Find(names[i]))) {
                        break;
                    }
                }
            }

            hasError = !gameObject.Valid();

            return !hasError;
        }

    private:
        SR_NODISCARD Bone* Clone(Bone* pParentBone) const noexcept {
            Bone* pBone = new Bone();

            pBone->hashName = hashName;
            pBone->name = name;
            pBone->gameObject = gameObject;
            pBone->pParent = pParentBone;
            pBone->pRoot = pParentBone->pRoot;
            pBone->pScene = pParentBone->pScene;

            pBone->bones.reserve(bones.size());

            for (auto&& pSubBone : bones) {
                pBone->bones.emplace_back(pSubBone->Clone(pBone));
            }

            return pBone;
        }

    public:
        uint64_t hashName = 0;
        std::string name;
        SR_WORLD_NS::Scene* pScene = nullptr;
        SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject> gameObject;
        std::vector<Bone*> bones;
        Bone* pParent = nullptr;
        Bone* pRoot = nullptr;
        bool hasError = false;

    };
}

#endif //GAMEENGINE_BONE_H
