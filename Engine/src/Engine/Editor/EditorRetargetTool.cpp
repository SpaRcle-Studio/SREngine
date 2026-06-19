//
// Created by Monika on 18.06.2026.
//

#include <Engine/Editor/EditorRetargetTool.h>

#include <Utils/Common/LookAtAxis.h>
#include <Utils/Types/RawMesh.h>

#include <Codegen/EditorRetargetTool.generated.hpp>

#include <map>
#include <unordered_map>
#include <unordered_set>

namespace SR_CORE_NS {
    namespace {
        struct HipsRotationFollowState {
            bool initialized = false;
            SR_MATH_NS::Quaternion sourceToTargetOffset = SR_MATH_NS::Quaternion::Identity();

            bool hasLastLocal = false;
            SR_MATH_NS::Quaternion lastLocal = SR_MATH_NS::Quaternion::Identity();
        };

        static std::unordered_map<const EditorRetargetTool*,
            std::unordered_map<const SR_ANIMATIONS_NS::Skeleton*, std::map<SR_UTILS_NS::StringAtom, HipsRotationFollowState>>
        > g_RotationFollowState;
    }

    void EditorRetargetTool::Update(float_t dt) {
        for (auto&& pTargetSkeleton : m_targetSkeletons) {
            switch (m_testMode) {
                case EditorRetargetToolTestMode::V1:
                    TestV1(pTargetSkeleton.Get().Get());
                    break;
                case EditorRetargetToolTestMode::V2:
                    TestV2(pTargetSkeleton.Get().Get());
                    break;
                case EditorRetargetToolTestMode::V3:
                    TestV3(pTargetSkeleton.Get().Get());
                    break;
                default:
                    break;
            }
        }
        Super::Update(dt);
    }

    void EditorRetargetTool::TestV3(SR_ANIMATIONS_NS::Skeleton* pTargetSkeleton) {
        auto&& pSourceSkeleton = m_sourceSkeleton.Get();

        if (!pSourceSkeleton || !pTargetSkeleton) {
            return;
        }

        auto&& pSourceRig = pSourceSkeleton->GetRig();
        auto&& pTargetRig = pTargetSkeleton->GetRig();

        if (!pSourceRig || !pTargetRig) {
            return;
        }

        auto&& pSourceRawMesh = pSourceRig->GetSkeleton().GetRawMesh();
        auto&& pTargetRawMesh = pTargetRig->GetSkeleton().GetRawMesh();

        if (!pSourceRawMesh || !pTargetRawMesh) {
            return;
        }

        const auto sourceMeshId = pSourceRig->GetSkeleton().GetMeshId();
        const auto targetMeshId = pTargetRig->GetSkeleton().GetMeshId();

        if (sourceMeshId == SR_ID_INVALID || targetMeshId == SR_ID_INVALID) {
            return;
        }

        const auto& srcScene = pSourceRawMesh->GetSceneStructure();
        const auto& tgtScene = pTargetRawMesh->GetSceneStructure();

        const uint16_t srcNodesCount = srcScene.GetNodesCount();
        const uint16_t tgtNodesCount = tgtScene.GetNodesCount();

        if (srcNodesCount == 0 || tgtNodesCount == 0) {
            return;
        }

        const SR_MATH_NS::Quaternion sourceRigSkeletonRot = SR_MATH_NS::Quaternion(pSourceRig->GetSkeletonRotation().Radians()).NormalizeSafe();
        const SR_MATH_NS::Quaternion targetRigSkeletonRot = SR_MATH_NS::Quaternion(pTargetRig->GetSkeletonRotation().Radians()).NormalizeSafe();

        auto buildRefCSRot = [](
            const SR_ANIMATIONS_NS::SkeletonRig& rig,
            const SR_HTYPES_NS::MeshSceneStructure& scene,
            const SR_MATH_NS::Quaternion& rigSkeletonRotation
        ) -> SR_UTILS_NS::Vector<SR_MATH_NS::Quaternion> {
            const uint16_t nodesCount = scene.GetNodesCount();

            SR_UTILS_NS::Vector<SR_MATH_NS::Quaternion> refLocalR;
            SR_UTILS_NS::Vector<SR_MATH_NS::Quaternion> refCSRot;
            refLocalR.resize(nodesCount);
            refCSRot.resize(nodesCount);

            for (uint16_t i = 0; i < nodesCount; ++i) {
                const auto& node = scene.GetNodeByIndex(i);

                refLocalR[i] = node.localTransform.rotation;

                SR_ANIMATIONS_NS::SkeletonRigPoseBone poseOverride;
                if (rig.TryGetRetargetPoseLocal(node.name, poseOverride)) {
                    refLocalR[i] = poseOverride.rotation;
                }

                if (node.parent.has_value()) {
                    const uint16_t parent = node.parent.value();
                    refCSRot[i] = (refCSRot[parent] * refLocalR[i]).NormalizeSafe();
                }
                else {
                    refCSRot[i] = (rigSkeletonRotation * refLocalR[i]).NormalizeSafe();
                }
            }

            return refCSRot;
        };

        const auto srcRefCSRot = buildRefCSRot(*pSourceRig, srcScene, sourceRigSkeletonRot);
        const auto tgtRefCSRot = buildRefCSRot(*pTargetRig, tgtScene, targetRigSkeletonRot);

        /// Precompute node depths for chain ordering (import order guarantees parent < child).
        auto buildNodeDepth = [](const SR_HTYPES_NS::MeshSceneStructure& scene) -> SR_UTILS_NS::Vector<uint32_t> {
            const uint16_t n = scene.GetNodesCount();
            SR_UTILS_NS::Vector<uint32_t> depth;
            depth.resize(n);
            for (uint16_t i = 0; i < n; ++i) {
                const auto& node = scene.GetNodeByIndex(i);
                if (node.parent.has_value()) {
                    const uint16_t parent = node.parent.value();
                    depth[i] = parent < i ? (depth[parent] + 1u) : 0u;
                }
                else {
                    depth[i] = 0u;
                }
            }
            return depth;
        };

        const auto srcNodeDepth = buildNodeDepth(srcScene);
        const auto tgtNodeDepth = buildNodeDepth(tgtScene);

        /// Map target node -> source node using humanoid chains, proportionally along chain depth.
        std::unordered_map<uint16_t, uint16_t> mappedTargetToSource;
        mappedTargetToSource.reserve(128);

        auto orderChainNodesByDepth = [](
            const SR_HTYPES_NS::RawMesh& rawMesh,
            uint32_t meshId,
            const SR_UTILS_NS::Vector<uint32_t>& nodeDepth,
            const SR_ANIMATIONS_NS::SkeletonRigBoneChain& chain
        ) -> SR_UTILS_NS::Vector<uint16_t> {
            SR_UTILS_NS::Vector<uint16_t> nodes;
            nodes.reserve(chain.bones.size());

            for (const auto& bone : chain.bones) {
                const auto& info = rawMesh.GetBoneInfo(meshId, bone.name);
                if (info.nodeIndex.has_value()) {
                    nodes.emplace_back(info.nodeIndex.value());
                }
            }

            std::sort(nodes.begin(), nodes.end(), [&](uint16_t a, uint16_t b) {
                return nodeDepth[a] < nodeDepth[b];
            });

            nodes.erase(std::unique(nodes.begin(), nodes.end()), nodes.end());
            return nodes;
        };

        SR_UTILS_NS::EnumReflector::ForEach<SR_ANIMATIONS_NS::HumanoidBoneType>([&](SR_ANIMATIONS_NS::HumanoidBoneType type) {
            if (type == SR_ANIMATIONS_NS::HumanoidBoneType::Unknown) {
                return;
            }

            const SR_UTILS_NS::StringAtom key = SR_UTILS_NS::EnumReflector::ToStringAtom(type);
            auto&& pSrcChain = pSourceRig->GetBoneChain(key);
            auto&& pTgtChain = pTargetRig->GetBoneChain(key);
            if (!pSrcChain || !pTgtChain) {
                return;
            }

            auto srcNodes = orderChainNodesByDepth(*pSourceRawMesh, sourceMeshId, srcNodeDepth, *pSrcChain);
            auto tgtNodes = orderChainNodesByDepth(*pTargetRawMesh, targetMeshId, tgtNodeDepth, *pTgtChain);

            if (srcNodes.empty() || tgtNodes.empty()) {
                return;
            }

            const float denomT = static_cast<float>(SR_MAX(1, static_cast<int32_t>(tgtNodes.size()) - 1));
            const float denomS = static_cast<float>(SR_MAX(1, static_cast<int32_t>(srcNodes.size()) - 1));

            for (uint32_t k = 0; k < tgtNodes.size(); ++k) {
                const float s = static_cast<float>(k) / denomT;
                const uint32_t j = static_cast<uint32_t>(std::round(s * denomS));

                const uint16_t tgtNode = tgtNodes[k];
                const uint16_t srcNode = srcNodes[SR_MIN(j, static_cast<uint32_t>(srcNodes.size() - 1))];

                if (mappedTargetToSource.count(tgtNode) == 0) {
                    mappedTargetToSource[tgtNode] = srcNode;
                }
            }
        });

        /// Dense mapping table for top-down application on target nodes.
        SR_UTILS_NS::Vector<uint16_t> tgtToSrcNode;
        tgtToSrcNode.resize(tgtNodesCount, SR_UINT16_MAX);
        for (const auto& [tgtNode, srcNode] : mappedTargetToSource) {
            if (tgtNode < tgtToSrcNode.size()) {
                tgtToSrcNode[tgtNode] = srcNode;
            }
        }

        /// Translation retarget only for hips root (avoid stretching).
        std::unordered_set<uint16_t> translationRetargetNodes;
        if (auto&& pTgtHips = pTargetRig->GetBoneChain(SR_UTILS_NS::StringAtom("Hips"))) {
            auto tgtNodes = orderChainNodesByDepth(*pTargetRawMesh, targetMeshId, tgtNodeDepth, *pTgtHips);
            if (!tgtNodes.empty()) {
                translationRetargetNodes.insert(tgtNodes.front());
            }
        }

        const auto sourceSkeletonWorldRot = pSourceSkeleton->GetGameObject()->GetTransform()->GetGlobalRotation();
        const auto targetSkeletonWorldRot = pTargetSkeleton->GetGameObject()->GetTransform()->GetGlobalRotation();

        /// Apply in target import order (parent index < child index) so parent rotations are updated first.
        for (uint16_t tgtNode = 0; tgtNode < tgtNodesCount; ++tgtNode) {
            const uint16_t srcNode = tgtToSrcNode[tgtNode];
            if (srcNode == SR_UINT16_MAX) {
                continue;
            }

            const auto& tgtNodeDesc = tgtScene.GetNodeByIndex(tgtNode);
            const auto& srcNodeDesc = srcScene.GetNodeByIndex(srcNode);

            auto&& pTargetBone = pTargetSkeleton->GetBone(tgtNodeDesc.name);
            auto&& pSourceBone = pSourceSkeleton->GetBone(srcNodeDesc.name);

            if (!pTargetBone || !pSourceBone) {
                continue;
            }

            if (translationRetargetNodes.count(tgtNode) != 0) {
                SR_MATH_NS::Matrix4x4 sourceGlobalMatrix = pSourceBone->GetGameObject()->GetTransform()->GetMatrix();
                SR_MATH_NS::FVector3 sourceGlobalTranslation = sourceGlobalMatrix.GetTranslation();
                SR_MATH_NS::Matrix4x4 targetGlobalParentMatrix = pTargetBone->GetGameObject()->GetParentTransform()->GetMatrix();
                SR_MATH_NS::Matrix4x4 targetLocalMatrix = targetGlobalParentMatrix.Inverse() * SR_MATH_NS::Matrix4x4(sourceGlobalTranslation, SR_MATH_NS::Quaternion::Identity(), SR_MATH_NS::FVector3::One());
                pTargetBone->GetGameObject()->GetTransform()->SetTranslation(targetLocalMatrix.GetTranslation());
            }

            if (srcNode >= srcRefCSRot.size() || tgtNode >= tgtRefCSRot.size()) {
                continue;
            }

            const SR_MATH_NS::Quaternion srcRefWorld = (sourceSkeletonWorldRot * srcRefCSRot[srcNode]).NormalizeSafe();
            const SR_MATH_NS::Quaternion tgtRefWorld = (targetSkeletonWorldRot * tgtRefCSRot[tgtNode]).NormalizeSafe();

            const SR_MATH_NS::Quaternion srcWorld = pSourceBone->GetGameObject()->GetTransform()->GetGlobalRotation().NormalizeSafe();
            const SR_MATH_NS::Quaternion deltaWorld = (srcWorld * srcRefWorld.Inverse()).NormalizeSafe();
            const SR_MATH_NS::Quaternion desiredWorld = (deltaWorld * tgtRefWorld).NormalizeSafe();

            const SR_MATH_NS::Quaternion targetParentWorld = pTargetBone->GetGameObject()->GetParentTransform()->GetGlobalRotation().NormalizeSafe();
            SR_MATH_NS::Quaternion desiredTargetLocal = (targetParentWorld.Inverse() * desiredWorld).NormalizeSafe();

            auto& state = g_RotationFollowState[this][pTargetSkeleton][tgtNodeDesc.name];
            if (state.hasLastLocal && SR_MATH_NS::Quaternion::Dot(desiredTargetLocal, state.lastLocal) < 0.f) {
                desiredTargetLocal = -desiredTargetLocal;
            }
            state.lastLocal = desiredTargetLocal;
            state.hasLastLocal = true;

            pTargetBone->GetGameObject()->GetTransform()->SetRotation(desiredTargetLocal);
        }
    }

    void EditorRetargetTool::TestV2(SR_ANIMATIONS_NS::Skeleton* pTargetSkeleton) {
        auto&& pSourceSkeleton = m_sourceSkeleton.Get();

        if (!pSourceSkeleton || !pTargetSkeleton) {
            return;
        }

        auto&& pSourceRig = pSourceSkeleton->GetRig();
        auto&& pTargetRig = pTargetSkeleton->GetRig();

        if (!pSourceRig || !pTargetRig) {
            return;
        }

        auto&& pSourceRawMesh = pSourceRig->GetSkeleton().GetRawMesh();
        auto&& pTargetRawMesh = pTargetRig->GetSkeleton().GetRawMesh();

        if (!pSourceRawMesh || !pTargetRawMesh) {
            return;
        }

        const auto sourceMeshId = pSourceRig->GetSkeleton().GetMeshId();
        const auto targetMeshId = pTargetRig->GetSkeleton().GetMeshId();

        if (sourceMeshId == SR_ID_INVALID || targetMeshId == SR_ID_INVALID) {
            return;
        }

        const SR_MATH_NS::Quaternion sourceRigSkeletonRot = SR_MATH_NS::Quaternion(pSourceRig->GetSkeletonRotation().Radians()).NormalizeSafe();
        const SR_MATH_NS::Quaternion targetRigSkeletonRot = SR_MATH_NS::Quaternion(pTargetRig->GetSkeletonRotation().Radians()).NormalizeSafe();

        /// Build reference component-space rotations (bind/rest or overridden by rig retarget pose),
        /// including rig-level skeleton transform (GetSkeletonRotation).
        auto buildRefCSRot = [](
            const SR_ANIMATIONS_NS::SkeletonRig& rig,
            const SR_HTYPES_NS::RawMesh& rawMesh,
            uint32_t /*meshId*/,
            const SR_MATH_NS::Quaternion& rigSkeletonRotation
        ) -> SR_UTILS_NS::Vector<SR_MATH_NS::Quaternion> {
            auto&& scene = rawMesh.GetSceneStructure();
            const uint16_t nodesCount = scene.GetNodesCount();

            SR_UTILS_NS::Vector<SR_MATH_NS::Quaternion> refLocalR;
            SR_UTILS_NS::Vector<SR_MATH_NS::Quaternion> refCSRot;
            refLocalR.resize(nodesCount);
            refCSRot.resize(nodesCount);

            for (uint16_t i = 0; i < nodesCount; ++i) {
                const auto& node = scene.GetNodeByIndex(i);

                refLocalR[i] = node.localTransform.rotation;

                SR_ANIMATIONS_NS::SkeletonRigPoseBone poseOverride;
                if (rig.TryGetRetargetPoseLocal(node.name, poseOverride)) {
                    refLocalR[i] = poseOverride.rotation;
                }

                if (node.parent.has_value()) {
                    const uint16_t parent = node.parent.value();
                    refCSRot[i] = (refCSRot[parent] * refLocalR[i]).NormalizeSafe();
                }
                else {
                    /// root node gets rig-level skeleton rotation (same idea as TestV1 global recalculation)
                    refCSRot[i] = (rigSkeletonRotation * refLocalR[i]).NormalizeSafe();
                }
            }

            return refCSRot;
        };

        const auto sourceRefCSRot = buildRefCSRot(*pSourceRig, *pSourceRawMesh, sourceMeshId, sourceRigSkeletonRot);
        const auto targetRefCSRot = buildRefCSRot(*pTargetRig, *pTargetRawMesh, targetMeshId, targetRigSkeletonRot);

        const auto sourceSkeletonWorldRot = pSourceSkeleton->GetGameObject()->GetTransform()->GetGlobalRotation();
        const auto targetSkeletonWorldRot = pTargetSkeleton->GetGameObject()->GetTransform()->GetGlobalRotation();

        for (SR_ANIMATIONS_NS::HumanoidBoneType boneType : SR_ANIMATIONS_NS::GetHumanoidSkeletonHierarchy()) {
            const SR_UTILS_NS::StringAtom humanoidBoneName = SR_UTILS_NS::EnumReflector::ToStringAtom(boneType);

            auto&& sourceBoneName = pSourceRig->GetBoneName(humanoidBoneName);
            auto&& targetBoneName = pTargetRig->GetBoneName(humanoidBoneName);

            auto&& pSourceBone = pSourceSkeleton->GetBone(sourceBoneName);
            auto&& pTargetBone = pTargetSkeleton->GetBone(targetBoneName);

            if (!pSourceBone || !pTargetBone) {
                continue;
            }

            /// Translation retarget is only safe for root / hips-like bones (same as RetargetAnimation).
            static std::set<SR_UTILS_NS::StringAtom> translationBones = {
                "Hips"
            };
            if (translationBones.count(humanoidBoneName) > 0) {
                SR_MATH_NS::Matrix4x4 sourceGlobalMatrix = pSourceBone->GetGameObject()->GetTransform()->GetMatrix();
                SR_MATH_NS::FVector3 sourceGlobalTranslation = sourceGlobalMatrix.GetTranslation();
                SR_MATH_NS::Matrix4x4 targetGlobalParentMatrix = pTargetBone->GetGameObject()->GetParentTransform()->GetMatrix();
                SR_MATH_NS::Matrix4x4 targetLocalMatrix = targetGlobalParentMatrix.Inverse() * SR_MATH_NS::Matrix4x4(sourceGlobalTranslation, SR_MATH_NS::Quaternion::Identity(), SR_MATH_NS::FVector3::One());
                pTargetBone->GetGameObject()->GetTransform()->SetTranslation(targetLocalMatrix.GetTranslation());
            }

            /// Rotation retarget in component-space (hierarchy-aware), with rest pose compensation (T/A).
            const auto& srcBoneInfo = pSourceRawMesh->GetBoneInfo(sourceMeshId, pSourceBone->name);
            const auto& tgtBoneInfo = pTargetRawMesh->GetBoneInfo(targetMeshId, pTargetBone->name);

            if (!srcBoneInfo.nodeIndex.has_value() || !tgtBoneInfo.nodeIndex.has_value()) {
                continue;
            }

            const uint16_t srcNode = srcBoneInfo.nodeIndex.value();
            const uint16_t tgtNode = tgtBoneInfo.nodeIndex.value();

            if (srcNode >= sourceRefCSRot.size() || tgtNode >= targetRefCSRot.size()) {
                continue;
            }

            const SR_MATH_NS::Quaternion srcRefWorld = (sourceSkeletonWorldRot * sourceRefCSRot[srcNode]).NormalizeSafe();
            const SR_MATH_NS::Quaternion tgtRefWorld = (targetSkeletonWorldRot * targetRefCSRot[tgtNode]).NormalizeSafe();

            const SR_MATH_NS::Quaternion srcWorld = pSourceBone->GetGameObject()->GetTransform()->GetGlobalRotation().NormalizeSafe();
            const SR_MATH_NS::Quaternion deltaWorld = (srcWorld * srcRefWorld.Inverse()).NormalizeSafe();
            const SR_MATH_NS::Quaternion desiredWorld = (deltaWorld * tgtRefWorld).NormalizeSafe();

            const SR_MATH_NS::Quaternion targetParentWorld = pTargetBone->GetGameObject()->GetParentTransform()->GetGlobalRotation().NormalizeSafe();
            SR_MATH_NS::Quaternion desiredTargetLocal = (targetParentWorld.Inverse() * desiredWorld).NormalizeSafe();

            auto& state = g_RotationFollowState[this][pTargetSkeleton][targetBoneName];
            if (state.hasLastLocal && SR_MATH_NS::Quaternion::Dot(desiredTargetLocal, state.lastLocal) < 0.f) {
                desiredTargetLocal = -desiredTargetLocal;
            }
            state.lastLocal = desiredTargetLocal;
            state.hasLastLocal = true;

            pTargetBone->GetGameObject()->GetTransform()->SetRotation(desiredTargetLocal);
        }

    }

    void EditorRetargetTool::TestV1(SR_ANIMATIONS_NS::Skeleton* pTargetSkeleton) {
        auto&& pSourceSkeleton = m_sourceSkeleton.Get();

        if (!pSourceSkeleton || !pTargetSkeleton) {
            return;
        }

        auto&& pSourceRig = pSourceSkeleton->GetRig();
        auto&& pTargetRig = pTargetSkeleton->GetRig();

        if (!pSourceRig || !pTargetRig) {
            return;
        }

        SR_UTILS_NS::Vector<SR_HTYPES_NS::MeshSceneStructure::SceneNode> scenePool = pTargetRig->GetSkeleton().GetRawMesh()->GetSceneStructure().GetNodes();
        /// recalculate global transforms
        for (auto&& node : scenePool) {
            if (!node.parent.has_value()) {
                auto&& localMatrix = SR_MATH_NS::Matrix4x4(node.localTransform.translation, node.localTransform.rotation, node.localTransform.scale);
                auto&& skeletonMatrix = SR_MATH_NS::Matrix4x4(pTargetRig->GetSkeletonTranslation(), pTargetRig->GetSkeletonRotation(), pTargetRig->GetSkeletonScale());
                auto&& globalMatrix = skeletonMatrix * localMatrix;
                globalMatrix.Decompose(node.globalTransform.translation, node.globalTransform.rotation, node.globalTransform.scale);
            }
            else {
                auto&& parentNode = scenePool[node.parent.value()];
                auto&& parentGlobalMatrix = SR_MATH_NS::Matrix4x4(parentNode.globalTransform.translation, parentNode.globalTransform.rotation, parentNode.globalTransform.scale);
                auto&& localMatrix = SR_MATH_NS::Matrix4x4(node.localTransform.translation, node.localTransform.rotation, node.localTransform.scale);
                auto&& globalMatrix = parentGlobalMatrix * localMatrix;
                globalMatrix.Decompose(node.globalTransform.translation, node.globalTransform.rotation, node.globalTransform.scale);
            }
        }

        for (SR_ANIMATIONS_NS::HumanoidBoneType boneType : SR_ANIMATIONS_NS::GetHumanoidSkeletonHierarchy()) {
            const SR_UTILS_NS::StringAtom humanoidBoneName = SR_UTILS_NS::EnumReflector::ToStringAtom(boneType);

            auto&& sourceHipsName = pSourceRig->GetBoneName(humanoidBoneName);
            auto&& targetHipsName = pTargetRig->GetBoneName(humanoidBoneName);

            auto&& pSourceHipsBone = pSourceSkeleton->GetBone(sourceHipsName);
            auto&& pTargetHipsBone = pTargetSkeleton->GetBone(targetHipsName);

            if (!pSourceHipsBone || !pTargetHipsBone) {
                continue;
            }

            SR_MATH_NS::Matrix4x4 sourceGlobalHipsMatrix = pSourceHipsBone->GetGameObject()->GetTransform()->GetMatrix();
            SR_MATH_NS::FVector3 sourceGlobalHipsTranslation = sourceGlobalHipsMatrix.GetTranslation();

            SR_MATH_NS::Matrix4x4 targetGlobalHipsParentMatrix = pTargetHipsBone->GetGameObject()->GetParentTransform()->GetMatrix();

            /// переводим глобальную позицию бедра в локальную для таргета, чтобы избежать смещения всего скелета при ретаргетинге
            SR_MATH_NS::Matrix4x4 targetGlobalHipsMatrix = targetGlobalHipsParentMatrix.Inverse() * SR_MATH_NS::Matrix4x4(sourceGlobalHipsTranslation, SR_MATH_NS::Quaternion::Identity(), SR_MATH_NS::FVector3::One());
            SR_MATH_NS::FVector3 targetGlobalHipsTranslation = targetGlobalHipsMatrix.GetTranslation();

            pTargetHipsBone->GetGameObject()->GetTransform()->SetTranslation(targetGlobalHipsTranslation);

            {
                auto& state = g_RotationFollowState[this][pTargetSkeleton][targetHipsName];

                const auto sourceGlobalHipsRotation = pSourceHipsBone->GetGameObject()->GetTransform()->GetGlobalRotation();
                const auto targetGlobalHipsRotation = pTargetHipsBone->GetGameObject()->GetTransform()->GetGlobalRotation();

                auto&& boneInfo = pTargetRig->GetSkeleton().GetRawMesh()->GetBoneInfo(pTargetRig->GetSkeleton().GetMeshId(), pTargetHipsBone->name);
                //auto&& node = scenePool[*boneInfo.nodeIndex];

                if (!state.initialized) {
                    //auto&& targetBindRotation = pTargetRig->GetBoneChain(humanoidBoneName)->bones.front().bindRotation;
                    state.sourceToTargetOffset = sourceGlobalHipsRotation.Inverse() * targetGlobalHipsRotation;
                    //state.sourceToTargetOffset = sourceGlobalHipsRotation.Inverse() * (targetBindRotation * targetGlobalHipsRotation);
                    //state.sourceToTargetOffset = sourceGlobalHipsRotation.Inverse() * (node.globalTransform.rotation);
                    state.initialized = true;
                    state.hasLastLocal = false;
                }

                //auto&& parentNode = scenePool[*node.parent];
                //auto&& targetParentGlobalRotation = parentNode.globalTransform.rotation;
                const auto targetParentGlobalRotation = pTargetHipsBone->GetGameObject()->GetParentTransform()->GetGlobalRotation();

                /// хотим чтобы таргет повторял глобальный поворот сорса, но с сохранением исходного смещения
                SR_MATH_NS::Quaternion desiredTargetGlobalRotation = sourceGlobalHipsRotation * state.sourceToTargetOffset;

                /// переводим глобальный поворот в локальный относительно родителя таргета
                SR_MATH_NS::Quaternion desiredTargetLocalRotation =
                    targetParentGlobalRotation.Inverse() * desiredTargetGlobalRotation;

                desiredTargetLocalRotation = desiredTargetLocalRotation.NormalizeSafe();

                /// стабилизация знака кватерниона (q и -q одинаковые, но знак влияет на непрерывность)
                if (state.hasLastLocal && SR_MATH_NS::Quaternion::Dot(desiredTargetLocalRotation, state.lastLocal) < 0.f) {
                    desiredTargetLocalRotation = -desiredTargetLocalRotation;
                }

                state.lastLocal = desiredTargetLocalRotation;
                state.hasLastLocal = true;

                pTargetHipsBone->GetGameObject()->GetTransform()->SetRotation(desiredTargetLocalRotation);
            }
        }





       /* auto&& bindRotation = pTargetRig->GetBoneChain("Hips")->bones.front().bindRotation;

        SR_MATH_NS::FVector3 up = pSourceHipsBone->GetGameObject()->GetTransform()->Up();
        SR_MATH_NS::FVector3 sourceForward = pSourceHipsBone->GetGameObject()->GetTransform()->Forward();

        SR_MATH_NS::Matrix4x4 lookAt = SR_MATH_NS::Matrix4x4::LookAt(targetGlobalHipsTranslation, targetGlobalHipsTranslation + sourceForward, up);

        SR_MATH_NS::Quaternion lookAtQuat = lookAt.GetQuat();
        pTargetHipsBone->GetGameObject()->GetTransform()->SetRotation(lookAtQuat * bindRotation.Inverse());*/

        //pTargetHipsBone->GetGameObject()->GetTransform()->LookAt(
        //    targetGlobalHipsTranslation + sourceForward,
        //    up
        //);

        //pTargetHipsBone->GetGameObject()->GetTransform()->Rotate(bindRotation.Inverse());
        //pTargetHipsBone->GetGameObject()->GetTransform()->Rotate(bindRotation.Inverse());

        /*pSourceSkeleton->ForEachBone([&](SR_ANIMATIONS_NS::Bone& sourceBone) {
            SR_UTILS_NS::StringAtom retargetBoneName;
            auto&& pSourceChain = pSourceRig->RetargetBone(sourceBone.name, retargetBoneName);
            if (!pSourceChain) {
                return;
            }

            auto&& pTargetChain = pTargetRig->GetBoneChain(retargetBoneName);
            if (!pTargetChain) {
                return;
            }

            auto&& pTargetBone = pTargetSkeleton->GetBone(pTargetChain->bones.front().name);
            if (!pTargetBone) {
                return;
            }

            auto&& pSourceGameObject = sourceBone.GetGameObject();
            auto&& pTargetGameObject = pTargetBone->GetGameObject();
            if (!pSourceGameObject || !pTargetGameObject) {
                return;
            }

            SR_MATH_NS::FVector3 translation = pSourceGameObject->GetTransform()->GetTranslation();
            SR_MATH_NS::Quaternion rotation = pSourceGameObject->GetTransform()->GetRotation();
            SR_MATH_NS::FVector3 scale = pSourceGameObject->GetTransform()->GetScale();

            ConvertTransform(
                pSourceChain->bones.front(),
                pTargetChain->bones.front(),
                sourceBone,
                *pTargetBone,
                *pSourceRig,
                *pTargetRig,
                translation,
                rotation,
                scale
            );

            pTargetGameObject->GetTransform()->SetTranslation(translation);
            pTargetGameObject->GetTransform()->SetRotation(rotation);
            pTargetGameObject->GetTransform()->SetScale(scale);
        });*/
    }
}
