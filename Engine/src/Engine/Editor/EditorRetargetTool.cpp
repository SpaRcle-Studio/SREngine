//
// Created by Monika on 18.06.2026.
//

#include <Engine/Editor/EditorRetargetTool.h>

#include <Utils/Common/LookAtAxis.h>
#include <Utils/Types/RawMesh.h>
#include <Utils/Types/Time.h>

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

        struct TwoBoneIKState {
            bool initialized = false;

            float upperLen = 0.f;
            float lowerLen = 0.f;
            float totalLen = 0.f;

            SR_MATH_NS::FVector3 rootToMidLocal = SR_MATH_NS::FVector3::Forward();
            SR_MATH_NS::FVector3 midToTipLocal = SR_MATH_NS::FVector3::Forward();

            SR_MATH_NS::Quaternion rootInitialWorld = SR_MATH_NS::Quaternion::Identity();
            SR_MATH_NS::Quaternion midInitialWorld  = SR_MATH_NS::Quaternion::Identity();

            SR_MATH_NS::Quaternion lastRootWorld = SR_MATH_NS::Quaternion::Identity();
            SR_MATH_NS::Quaternion lastMidWorld  = SR_MATH_NS::Quaternion::Identity();

            SR_MATH_NS::FVector3 lastBendNormal = SR_MATH_NS::FVector3::Up();
            bool hasLastBendNormal = false;

            SR_MATH_NS::Quaternion lastTipWorld = SR_MATH_NS::Quaternion::Identity();
            bool hasLastTipWorld = false;

            /// When applying tip rotation from target, we need a stable offset between
            /// "desired target rotation space" and actual tip bone space (axes differ between skeletons).
            bool tipOffsetInitialized = false;
            SR_MATH_NS::Quaternion tipRotationOffset = SR_MATH_NS::Quaternion::Identity();
        };

        static std::unordered_map<const EditorRetargetTool*,
            std::unordered_map<const SR_ANIMATIONS_NS::Skeleton*, std::unordered_map<SR_UTILS_NS::StringAtom, TwoBoneIKState>>
        > g_TwoBoneIKState;

        struct TwoBoneIKParams {
            float weight = 1.f;
            float smoothing = 12.f;
            bool preventTwist = true;
            float maxTwistChangePerFrame = 60.f;
            bool tipRotationFromTarget = true;
        };

        static SR_MATH_NS::FVector3 CalculateBendNormal(
            const SR_MATH_NS::FVector3& rootPos,
            const SR_MATH_NS::FVector3& targetPos,
            const SR_MATH_NS::FVector3* pHintPos,
            TwoBoneIKState& state,
            const TwoBoneIKParams& params
        ) {
            const SR_MATH_NS::FVector3 rootToTarget = targetPos - rootPos;
            const float dist = rootToTarget.Magnitude();
            if (dist < 0.0001f) {
                return state.hasLastBendNormal ? state.lastBendNormal : SR_MATH_NS::FVector3::Up();
            }

            const SR_MATH_NS::FVector3 dir = rootToTarget / dist;

            SR_MATH_NS::FVector3 bendNormal;
            if (pHintPos) {
                const SR_MATH_NS::FVector3 rootToHint = (*pHintPos) - rootPos;
                SR_MATH_NS::FVector3 projected = SR_MATH_NS::ProjectOnPlane(rootToHint, dir);
                const float mag = projected.Magnitude();
                bendNormal = mag > 0.0001f ? (projected / mag) : SR_MATH_NS::SafePerpendicular(dir);
            }
            else {
                bendNormal = SR_MATH_NS::SafePerpendicular(dir);
            }

            if (params.preventTwist && state.hasLastBendNormal) {
                const float angle = SR_MATH_NS::FVector3::Angle(bendNormal, state.lastBendNormal);
                if (angle > params.maxTwistChangePerFrame) {
                    SR_MATH_NS::FVector3 axis = SR_MATH_NS::FVector3::Cross(state.lastBendNormal, bendNormal);
                    const float axisMag = axis.Magnitude();
                    if (axisMag > 0.0001f) {
                        axis /= axisMag;
                        const SR_MATH_NS::Quaternion correction = SR_MATH_NS::Quaternion::AngleAxis(params.maxTwistChangePerFrame, axis);
                        bendNormal = correction * state.lastBendNormal;
                    }
                }
            }

            return bendNormal;
        }

        static void SolveTwoBoneLocalTarget(
            SR_UTILS_NS::Transform& root,
            SR_UTILS_NS::Transform& mid,
            SR_UTILS_NS::Transform& tip,
            const SR_MATH_NS::FVector3& targetWorldPos,
            const SR_MATH_NS::Quaternion& targetWorldRot,
            const SR_MATH_NS::FVector3* pHintWorldPos,
            TwoBoneIKState& state,
            const TwoBoneIKParams& params,
            float dt
        ) {
            if (params.weight <= 0.f) {
                return;
            }

            const SR_MATH_NS::FVector3 rootPos = root.GetGlobalTranslation();
            const SR_MATH_NS::FVector3 midPos  = mid.GetGlobalTranslation();
            const SR_MATH_NS::FVector3 tipPos  = tip.GetGlobalTranslation();

            if (!state.initialized) {
                state.upperLen = SR_MATH_NS::FVector3::Distance(rootPos, midPos);
                state.lowerLen = SR_MATH_NS::FVector3::Distance(midPos, tipPos);
                state.totalLen = state.upperLen + state.lowerLen;

                state.lastTipWorld = tip.GetGlobalRotation().NormalizeSafe();
                state.hasLastTipWorld = true;

                state.initialized = true;
            }

            /// Update IK reference axes from current (already retargeted) animated pose.
            /// This avoids using a "frozen" basis from the very first frame, which can make IK look ignored.
            {
                const SR_MATH_NS::FVector3 rootToMid = (midPos - rootPos);
                const SR_MATH_NS::FVector3 midToTip  = (tipPos - midPos);

                const float rmMag = rootToMid.Magnitude();
                const float mtMag = midToTip.Magnitude();

                if (rmMag > 0.0001f) {
                    state.rootToMidLocal = root.InverseTransformDirection(rootToMid / rmMag).Normalized();
                }
                if (mtMag > 0.0001f) {
                    state.midToTipLocal  = mid.InverseTransformDirection(midToTip / mtMag).Normalized();
                }

                state.rootInitialWorld = root.GetGlobalRotation().NormalizeSafe();
                state.midInitialWorld  = mid.GetGlobalRotation().NormalizeSafe();

                if (state.lastRootWorld.IsIdentity() && state.lastMidWorld.IsIdentity()) {
                    state.lastRootWorld = state.rootInitialWorld;
                    state.lastMidWorld  = state.midInitialWorld;
                }
            }

            const SR_MATH_NS::Quaternion rootOriginal = root.GetGlobalRotation().NormalizeSafe();
            const SR_MATH_NS::Quaternion midOriginal  = mid.GetGlobalRotation().NormalizeSafe();
            const SR_MATH_NS::Quaternion tipOriginal  = tip.GetGlobalRotation().NormalizeSafe();

            const SR_MATH_NS::FVector3 rootToTarget = targetWorldPos - rootPos;
            const float distToTarget = rootToTarget.Magnitude();

            if (distToTarget > 0.0001f) {
                const SR_MATH_NS::FVector3 dirToTarget = rootToTarget / distToTarget;

                if (distToTarget >= state.totalLen - 0.0001f) {
                    /// fully extend
                    const SR_MATH_NS::FVector3 rootForward = state.rootInitialWorld * state.rootToMidLocal;
                    const SR_MATH_NS::Quaternion rootRot = (SR_MATH_NS::Quaternion::FromToRotation(rootForward, dirToTarget) * state.rootInitialWorld).NormalizeSafe();

                    const SR_MATH_NS::FVector3 newMidPos = rootPos + rootRot * state.rootToMidLocal * state.upperLen;
                    const SR_MATH_NS::FVector3 midToTargetDir = (targetWorldPos - newMidPos).Normalized();
                    const SR_MATH_NS::FVector3 midForward = rootRot * state.midToTipLocal;
                    const SR_MATH_NS::Quaternion midRot = (SR_MATH_NS::Quaternion::FromToRotation(midForward, midToTargetDir) * rootRot).NormalizeSafe();

                    root.SetGlobalRotation(rootRot);
                    mid.SetGlobalRotation(midRot);
                }
                else if (distToTarget <= SR_MATH_NS::Abs(state.upperLen - state.lowerLen) + 0.0001f) {
                    /// retract (fold) toward target direction
                    const SR_MATH_NS::FVector3 rootForward = state.rootInitialWorld * state.rootToMidLocal;
                    const SR_MATH_NS::Quaternion rootRot = (SR_MATH_NS::Quaternion::FromToRotation(rootForward, dirToTarget) * state.rootInitialWorld).NormalizeSafe();

                    const SR_MATH_NS::FVector3 newMidPos = rootPos + rootRot * state.rootToMidLocal * state.upperLen;
                    const SR_MATH_NS::FVector3 midToTargetDir = (targetWorldPos - newMidPos).Normalized();
                    const SR_MATH_NS::FVector3 midForward = rootRot * state.midToTipLocal;
                    const SR_MATH_NS::Quaternion midRot = (SR_MATH_NS::Quaternion::FromToRotation(midForward, midToTargetDir) * rootRot).NormalizeSafe();

                    root.SetGlobalRotation(rootRot);
                    mid.SetGlobalRotation(midRot);
                }
                else {
                    /// reachable: solve triangle in bend plane
                    const SR_MATH_NS::FVector3 bendNormal = CalculateBendNormal(rootPos, targetWorldPos, pHintWorldPos, state, params);

                    float cosRootAngle =
                        ((state.upperLen * state.upperLen) + (distToTarget * distToTarget) - (state.lowerLen * state.lowerLen)) /
                        (2.f * state.upperLen * distToTarget);
                    cosRootAngle = SR_MATH_NS::Clamp(cosRootAngle, -1.f, 1.f);
                    const float rootAngle = SR_ACOS(cosRootAngle);

                    const float along = state.upperLen * SR_COS(rootAngle);
                    const float perp  = state.upperLen * SR_SIN(rootAngle);

                    SR_MATH_NS::FVector3 desiredMid = rootPos + dirToTarget * along + bendNormal * perp;
                    const SR_MATH_NS::FVector3 rootToMidDir = (desiredMid - rootPos).Normalized();

                    const SR_MATH_NS::FVector3 rootForward = state.rootInitialWorld * state.rootToMidLocal;
                    const SR_MATH_NS::Quaternion rootRot = (SR_MATH_NS::Quaternion::FromToRotation(rootForward, rootToMidDir) * state.rootInitialWorld).NormalizeSafe();

                    /// recompute mid position after root rotation for consistency
                    const SR_MATH_NS::FVector3 midPosSolved = rootPos + rootRot * state.rootToMidLocal * state.upperLen;
                    const SR_MATH_NS::FVector3 midToTargetDir = (targetWorldPos - midPosSolved).Normalized();
                    const SR_MATH_NS::FVector3 midForward = rootRot * state.midToTipLocal;
                    const SR_MATH_NS::Quaternion midRot = (SR_MATH_NS::Quaternion::FromToRotation(midForward, midToTargetDir) * rootRot).NormalizeSafe();

                    root.SetGlobalRotation(rootRot);
                    mid.SetGlobalRotation(midRot);

                    state.lastBendNormal = bendNormal;
                    state.hasLastBendNormal = true;
                }
            }

            /// Apply weight first
            if (params.weight < 1.f) {
                root.SetGlobalRotation(SR_MATH_NS::Quaternion::Slerp(rootOriginal, root.GetGlobalRotation().NormalizeSafe(), params.weight));
                mid.SetGlobalRotation(SR_MATH_NS::Quaternion::Slerp(midOriginal,  mid.GetGlobalRotation().NormalizeSafe(),  params.weight));
            }

            /// Apply smoothing (continuous, frame-rate independent)
            if (params.smoothing > 0.f) {
                const float smoothFactor = SR_MATH_NS::Clamp(dt * params.smoothing, 0.f, 1.f);
                root.SetGlobalRotation(SR_MATH_NS::Quaternion::Slerp(state.lastRootWorld, root.GetGlobalRotation().NormalizeSafe(), smoothFactor));
                mid.SetGlobalRotation(SR_MATH_NS::Quaternion::Slerp(state.lastMidWorld,  mid.GetGlobalRotation().NormalizeSafe(),  smoothFactor));
            }

            state.lastRootWorld = root.GetGlobalRotation().NormalizeSafe();
            state.lastMidWorld  = mid.GetGlobalRotation().NormalizeSafe();

            if (params.tipRotationFromTarget) {
                SR_MATH_NS::Quaternion desiredTip = targetWorldRot.NormalizeSafe();

                /// Calibrate a constant offset so the first application doesn't flip the bone.
                /// This fixes the common "hand/foot rotates to the wrong side" issue caused by different bone axes.
                if (!state.tipOffsetInitialized) {
                    state.tipRotationOffset = (SR_MATH_NS::Quaternion::Inverse(desiredTip) * tipOriginal).NormalizeSafe();
                    state.tipOffsetInitialized = true;
                }

                desiredTip = (desiredTip * state.tipRotationOffset).NormalizeSafe();
                if (state.hasLastTipWorld && SR_MATH_NS::Quaternion::Dot(desiredTip, state.lastTipWorld) < 0.f) {
                    desiredTip = -desiredTip;
                }

                SR_MATH_NS::Quaternion blended = desiredTip;
                if (params.weight < 1.f) {
                    blended = SR_MATH_NS::Quaternion::Slerp(tipOriginal, desiredTip, params.weight).NormalizeSafe();
                }

                if (params.smoothing > 0.f) {
                    const float smoothFactor = SR_MATH_NS::Clamp(dt * params.smoothing, 0.f, 1.f);
                    blended = SR_MATH_NS::Quaternion::Slerp(state.lastTipWorld, blended, smoothFactor).NormalizeSafe();
                }

                tip.SetGlobalRotation(blended);
                state.lastTipWorld = blended;
                state.hasLastTipWorld = true;
            }
        }
    }

    void EditorRetargetTool::Update(float_t dt) {
        if (!m_sourceSkeleton) {
            return;
        }

        auto&& pSourceSkeleton = m_sourceSkeleton.Get();
        auto&& pSourceRig = pSourceSkeleton->GetRig();
        if (!pSourceRig) {
            return;
        }

        for (auto&& targetSkeleton : m_targetSkeletons) {
            if (!targetSkeleton || !targetSkeleton.Get()->IsActive()) {
                continue;
            }

            auto&& pTargetSkeleton = targetSkeleton.Get();
            auto&& pTargetRig = pTargetSkeleton->GetRig();
            if (!pTargetRig) {
                continue;
            }

            SR_ANIMATIONS_NS::RetargetReferencePoseDeltaAlgorithmState::RetargetFrameContext context(m_retargetState);
            context.pSourceSkeleton = m_sourceSkeleton.Get();
            context.pTargetSkeleton = targetSkeleton.Get();
            context.scaleFactor = m_scaleFactor;
            context.targetHipsOffset = m_targetHipsOffset;
            SR_ANIMATIONS_NS::RetargetReferencePoseDeltaAlgorithm::RetargetFrame(context, 0);

            if (m_twoBoneIKEnabled) {
                TwoBoneIK(targetSkeleton.Get().Get());
            }
        }

        Super::Update(dt);
    }

    void EditorRetargetTool::TwoBoneIK(SR_ANIMATIONS_NS::Skeleton* pTargetSkeleton) {
        auto&& pSourceSkeleton = m_sourceSkeleton.Get();

        if (!pSourceSkeleton || !pTargetSkeleton) {
            return;
        }

        auto&& pSourceRig = pSourceSkeleton->GetRig();
        auto&& pTargetRig = pTargetSkeleton->GetRig();
        if (!pSourceRig || !pTargetRig) {
            return;
        }

        auto&& pSourceGO = pSourceSkeleton->GetGameObject();
        auto&& pTargetGO = pTargetSkeleton->GetGameObject();
        if (!pSourceGO || !pTargetGO) {
            return;
        }

        auto&& pSourceTr = pSourceGO->GetTransform();
        auto&& pTargetTr = pTargetGO->GetTransform();
        if (!pSourceTr || !pTargetTr) {
            return;
        }


        /// IK is solved strictly in WORLD space.
        /// The desired target for limbs/spine is the real global transform of the source skeleton,
        /// because in the editor the models are already placed/scaled correctly relative to each other.

        auto&& pSourceRawMesh = pSourceRig->GetSkeleton().GetRawMesh();
        auto&& pTargetRawMesh = pTargetRig->GetSkeleton().GetRawMesh();
        const auto srcMeshId = pSourceRig->GetSkeleton().GetMeshId();
        const auto tgtMeshId = pTargetRig->GetSkeleton().GetMeshId();

        if (!pSourceRawMesh || !pTargetRawMesh || srcMeshId == SR_ID_INVALID || tgtMeshId == SR_ID_INVALID) {
            return;
        }

        const auto& srcScene = pSourceRawMesh->GetSceneStructure();
        const auto& tgtScene = pTargetRawMesh->GetSceneStructure();

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

        auto pickMappedBoneName = [](
            const SR_ANIMATIONS_NS::SkeletonRig& rig,
            const SR_HTYPES_NS::RawMesh& rawMesh,
            uint32_t meshId,
            const SR_UTILS_NS::Vector<uint32_t>& nodeDepth,
            SR_UTILS_NS::StringAtom humanoidKey
        ) -> SR_UTILS_NS::StringAtom {
            if (auto&& pChain = rig.GetBoneChain(humanoidKey)) {
                uint32_t bestDepth = SR_UINT32_MAX;
                SR_UTILS_NS::StringAtom bestName;

                for (const auto& boneInfo : pChain->bones) {
                    if (boneInfo.name.empty()) {
                        continue;
                    }
                    const auto& info = rawMesh.GetBoneInfo(meshId, boneInfo.name);
                    if (!info.nodeIndex.has_value()) {
                        continue;
                    }
                    const uint16_t node = info.nodeIndex.value();
                    if (node >= nodeDepth.size()) {
                        continue;
                    }
                    const uint32_t d = nodeDepth[node];
                    if (d < bestDepth) {
                        bestDepth = d;
                        bestName = boneInfo.name;
                    }
                }

                if (!bestName.empty()) {
                    return bestName;
                }
            }

            return rig.GetBoneName(humanoidKey);
        };

        auto solveHumanoidChain = [&](
            SR_UTILS_NS::StringAtom stateKey,
            SR_ANIMATIONS_NS::HumanoidBoneType rootType,
            SR_ANIMATIONS_NS::HumanoidBoneType midType,
            SR_ANIMATIONS_NS::HumanoidBoneType tipType,
            float dt,
            const TwoBoneIKParams& ikParams
        ) {
            const SR_UTILS_NS::StringAtom rootKey = SR_UTILS_NS::EnumReflector::ToStringAtom(rootType);
            const SR_UTILS_NS::StringAtom midKey  = SR_UTILS_NS::EnumReflector::ToStringAtom(midType);
            const SR_UTILS_NS::StringAtom tipKey  = SR_UTILS_NS::EnumReflector::ToStringAtom(tipType);

            const auto srcRootName = pickMappedBoneName(*pSourceRig, *pSourceRawMesh, srcMeshId, srcNodeDepth, rootKey);
            const auto srcMidName  = pickMappedBoneName(*pSourceRig, *pSourceRawMesh, srcMeshId, srcNodeDepth, midKey);
            const auto srcTipName  = pickMappedBoneName(*pSourceRig, *pSourceRawMesh, srcMeshId, srcNodeDepth, tipKey);

            const auto tgtRootName = pickMappedBoneName(*pTargetRig, *pTargetRawMesh, tgtMeshId, tgtNodeDepth, rootKey);
            const auto tgtMidName  = pickMappedBoneName(*pTargetRig, *pTargetRawMesh, tgtMeshId, tgtNodeDepth, midKey);
            const auto tgtTipName  = pickMappedBoneName(*pTargetRig, *pTargetRawMesh, tgtMeshId, tgtNodeDepth, tipKey);

            auto&& pSrcRootBone = pSourceSkeleton->GetBone(srcRootName);
            auto&& pSrcMidBone  = pSourceSkeleton->GetBone(srcMidName);
            auto&& pSrcTipBone  = pSourceSkeleton->GetBone(srcTipName);

            auto&& pTgtRootBone = pTargetSkeleton->GetBone(tgtRootName);
            auto&& pTgtMidBone  = pTargetSkeleton->GetBone(tgtMidName);
            auto&& pTgtTipBone  = pTargetSkeleton->GetBone(tgtTipName);

            if (!pSrcRootBone || !pSrcMidBone || !pSrcTipBone || !pTgtRootBone || !pTgtMidBone || !pTgtTipBone) {
                return;
            }

            auto&& pSrcRootT = pSrcRootBone->GetGameObject()->GetTransform();
            auto&& pSrcMidT  = pSrcMidBone->GetGameObject()->GetTransform();
            auto&& pSrcTipT  = pSrcTipBone->GetGameObject()->GetTransform();

            auto&& pTgtRootT = pTgtRootBone->GetGameObject()->GetTransform();
            auto&& pTgtMidT  = pTgtMidBone->GetGameObject()->GetTransform();
            auto&& pTgtTipT  = pTgtTipBone->GetGameObject()->GetTransform();

            if (!pSrcRootT || !pSrcMidT || !pSrcTipT || !pTgtRootT || !pTgtMidT || !pTgtTipT) {
                return;
            }

            const SR_MATH_NS::FVector3 srcRootWorldPos = pSrcRootT->GetGlobalTranslation();
            const SR_MATH_NS::FVector3 srcMidWorldPos = pSrcMidT->GetGlobalTranslation();

            SR_MATH_NS::FVector3 tipOffset;
            if (stateKey == "IK_LeftArm") {
                tipOffset = m_IKLeftHandOffset / m_scaleFactor;
            }
            else if (stateKey == "IK_RightArm") {
                tipOffset = m_IKRightHandOffset / m_scaleFactor;
            }
            else if (stateKey == "IK_LeftLeg") {
                tipOffset = m_IKLeftFootOffset / m_scaleFactor;
            }
            else if (stateKey == "IK_RightLeg") {
                tipOffset = m_IKRightFootOffset / m_scaleFactor;
            }

            const SR_MATH_NS::FVector3 srcTipWorldPos = pSrcTipT->GetGlobalTranslation() + tipOffset;
            const SR_MATH_NS::Quaternion srcTipWorldRot = pSrcTipT->GetGlobalRotation().NormalizeSafe();

            const SR_MATH_NS::FVector3 tgtRootWorldPos = pTgtRootT->GetGlobalTranslation();

            const SR_MATH_NS::FVector3 desiredTipWorldPos = srcTipWorldPos;
            const SR_MATH_NS::Quaternion desiredTipWorldRot = srcTipWorldRot;

            /// Pole vector: use SOURCE bend direction (deviation of mid from root->tip axis), mapped into target root space.
            const SR_MATH_NS::FVector3 srcRootToTip = srcTipWorldPos - srcRootWorldPos;
            const float rtMag = srcRootToTip.Magnitude();
            SR_MATH_NS::FVector3 srcRootToTipDir = rtMag > 0.0001f ? (srcRootToTip / rtMag) : SR_MATH_NS::FVector3::Forward();

            SR_MATH_NS::FVector3 srcRootToMid = srcMidWorldPos - srcRootWorldPos;
            SR_MATH_NS::FVector3 srcBendDir = SR_MATH_NS::ProjectOnPlane(srcRootToMid, srcRootToTipDir);
            const float bendDirMag = srcBendDir.Magnitude();
            if (bendDirMag > 0.0001f) {
                srcBendDir /= bendDirMag;
            }
            else {
                srcBendDir = SR_MATH_NS::SafePerpendicular(srcRootToTipDir);
            }

            /// Pole vector is also taken in WORLD space (same "apple on the table" logic).
            const SR_MATH_NS::FVector3 bendDirWorldForTarget = srcBendDir;

            auto& state = g_TwoBoneIKState[this][pTargetSkeleton][stateKey];

            const float upperLen = state.initialized
                ? state.upperLen
                : SR_MATH_NS::FVector3::Distance(pTgtRootT->GetGlobalTranslation(), pTgtMidT->GetGlobalTranslation());

            const SR_MATH_NS::FVector3 hintWorldPos = tgtRootWorldPos + bendDirWorldForTarget * SR_MAX(upperLen, 0.01f);

            SolveTwoBoneLocalTarget(
                *pTgtRootT,
                *pTgtMidT,
                *pTgtTipT,
                desiredTipWorldPos,
                desiredTipWorldRot,
                &hintWorldPos,
                state,
                ikParams,
                dt
            );
        };

        /// Spine IK (CCD) to improve torso alignment (WORLD space goal).
        {
            const SR_UTILS_NS::StringAtom srcHeadName = pickMappedBoneName(*pSourceRig, *pSourceRawMesh, srcMeshId, srcNodeDepth, "Head");
            const SR_UTILS_NS::StringAtom tgtHeadName = pickMappedBoneName(*pTargetRig, *pTargetRawMesh, tgtMeshId, tgtNodeDepth, "Head");

            auto&& pSrcHead = pSourceSkeleton->GetBone(srcHeadName);
            auto&& pTgtHead = pTargetSkeleton->GetBone(tgtHeadName);

            if (pSrcHead && pTgtHead) {
                auto&& pSrcHeadT = pSrcHead->GetGameObject()->GetTransform();
                auto&& pTgtHeadT = pTgtHead->GetGameObject()->GetTransform();

                if (pSrcHeadT && pTgtHeadT) {
                    const SR_MATH_NS::FVector3 srcHeadWorldPos = pSrcHeadT->GetGlobalTranslation();
                    const SR_MATH_NS::FVector3 desiredHeadWorldPos = srcHeadWorldPos;

                    SR_UTILS_NS::Vector<SR_UTILS_NS::Transform*> spineChain;
                    spineChain.reserve(4);

                    auto pushIf = [&](SR_UTILS_NS::StringAtom humanoidKey) {
                        const SR_UTILS_NS::StringAtom tgtName = pickMappedBoneName(*pTargetRig, *pTargetRawMesh, tgtMeshId, tgtNodeDepth, humanoidKey);
                        if (auto&& pBone = pTargetSkeleton->GetBone(tgtName)) {
                            if (auto&& pT = pBone->GetGameObject()->GetTransform()) {
                                spineChain.emplace_back(const_cast<SR_UTILS_NS::Transform*>(pT.Get()));
                            }
                        }
                    };

                    /// From upper to lower will be handled by CCD loop; we store in order root->... (Spine is root-most in chain list).
                    pushIf("Spine");
                    pushIf("Chest");
                    pushIf("UpperChest");
                    pushIf("Neck");

                    if (!spineChain.empty()) {
                        auto ccdStep = [&](SR_UTILS_NS::Transform& joint, const SR_MATH_NS::FVector3& targetPos, float weight) {
                            const SR_MATH_NS::FVector3 jointPos = joint.GetGlobalTranslation();
                            const SR_MATH_NS::FVector3 endPos = pTgtHeadT->GetGlobalTranslation();
                            SR_MATH_NS::FVector3 toEnd = endPos - jointPos;
                            SR_MATH_NS::FVector3 toTarget = targetPos - jointPos;

                            const float a = toEnd.Magnitude();
                            const float b = toTarget.Magnitude();
                            if (a < 0.0001f || b < 0.0001f) {
                                return;
                            }

                            toEnd /= a;
                            toTarget /= b;

                            SR_MATH_NS::Quaternion delta = SR_MATH_NS::Quaternion::FromToRotation(toEnd, toTarget).NormalizeSafe();
                            const SR_MATH_NS::Quaternion current = joint.GetGlobalRotation().NormalizeSafe();
                            const SR_MATH_NS::Quaternion next = (delta * current).NormalizeSafe();
                            joint.SetGlobalRotation(SR_MATH_NS::Quaternion::Slerp(current, next, weight).NormalizeSafe());
                        };

                        for (uint32_t iter = 0; iter < m_ccdIterations; ++iter) {
                            for (int32_t i = static_cast<int32_t>(spineChain.size()) - 1; i >= 0; --i) {
                                ccdStep(*spineChain[i], desiredHeadWorldPos, m_ccdWeight);
                            }
                        }
                    }
                }
            }
        }

        TwoBoneIKParams ikParams;
        ikParams.weight = m_twoBoneWeight;
        /// For retarget post-pass we want the limb to match the source immediately.
        /// Smoothing here makes it look like IK "doesn't follow the target".
        ikParams.smoothing = m_smoothing;
        ikParams.preventTwist = true;
        ikParams.maxTwistChangePerFrame = 75.f;

        for (uint8_t iter = 0; iter < m_twoBoneIterations; ++iter) {
            float dt = 1.f / static_cast<float>(m_twoBoneIterations);
            /// Arms: UpperArm -> LowerArm -> Hand
            ikParams.tipRotationFromTarget = m_handTipRotationFromTarget;
            solveHumanoidChain("IK_LeftArm",  SR_ANIMATIONS_NS::HumanoidBoneType::LeftUpperArm,  SR_ANIMATIONS_NS::HumanoidBoneType::LeftLowerArm,  SR_ANIMATIONS_NS::HumanoidBoneType::LeftHand, dt, ikParams);
            solveHumanoidChain("IK_RightArm", SR_ANIMATIONS_NS::HumanoidBoneType::RightUpperArm, SR_ANIMATIONS_NS::HumanoidBoneType::RightLowerArm, SR_ANIMATIONS_NS::HumanoidBoneType::RightHand, dt, ikParams);

            /// Legs: UpperLeg -> LowerLeg -> Foot
            ikParams.tipRotationFromTarget = m_footTipRotationFromTarget;
            solveHumanoidChain("IK_LeftLeg",  SR_ANIMATIONS_NS::HumanoidBoneType::LeftUpperLeg,  SR_ANIMATIONS_NS::HumanoidBoneType::LeftLowerLeg,  SR_ANIMATIONS_NS::HumanoidBoneType::LeftFoot, dt, ikParams);
            solveHumanoidChain("IK_RightLeg", SR_ANIMATIONS_NS::HumanoidBoneType::RightUpperLeg, SR_ANIMATIONS_NS::HumanoidBoneType::RightLowerLeg, SR_ANIMATIONS_NS::HumanoidBoneType::RightFoot, dt, ikParams);
        }
    }
}
