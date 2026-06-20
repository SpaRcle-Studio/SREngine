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

        static SR_FORCE_INLINE SR_MATH_NS::FVector3 SafePerpendicular(const SR_MATH_NS::FVector3& v) {
            SR_MATH_NS::FVector3 perp = SR_MATH_NS::GetPerpendicularVector(v);
            const float mag = perp.Magnitude();
            if (mag > 0.0001f) {
                return perp / mag;
            }
            return SR_MATH_NS::FVector3::Up();
        }

        static SR_FORCE_INLINE SR_MATH_NS::FVector3 ProjectOnPlane(
            const SR_MATH_NS::FVector3& v,
            const SR_MATH_NS::FVector3& planeNormal /* must be normalized */
        ) {
            return v - SR_MATH_NS::FVector3::Project(v, planeNormal);
        }

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
                SR_MATH_NS::FVector3 projected = ProjectOnPlane(rootToHint, dir);
                const float mag = projected.Magnitude();
                bendNormal = mag > 0.0001f ? (projected / mag) : SafePerpendicular(dir);
            }
            else {
                bendNormal = SafePerpendicular(dir);
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
        for (auto&& targetSkeleton : m_targetSkeletons) {
            if (!targetSkeleton || !targetSkeleton.Get()->IsActive()) {
                continue;
            }
            switch (m_testMode) {
                case EditorRetargetToolTestMode::V1:
                    TestV1(targetSkeleton.Get().Get());
                    break;
                case EditorRetargetToolTestMode::V2:
                    TestV2(targetSkeleton.Get().Get());
                    break;
                case EditorRetargetToolTestMode::V3:
                    TestV3(targetSkeleton.Get().Get());
                    break;
                default:
                    break;
            }

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


        const auto& sourceWorldSettings = pSourceRig->GetWorldSettings();
        const auto& targetWorldSettings = pTargetRig->GetWorldSettings();

        const SR_MATH_NS::Matrix4x4 srcSkelWorldMOffset = SR_MATH_NS::Matrix4x4(
                sourceWorldSettings.translationOffset,
                SR_MATH_NS::FVector3(),
                sourceWorldSettings.scaleFactor
        );
        const SR_MATH_NS::Matrix4x4 tgtSkelWorldMOffset = SR_MATH_NS::Matrix4x4(
                targetWorldSettings.translationOffset,
                SR_MATH_NS::FVector3(),
                targetWorldSettings.scaleFactor
        );
        //const SR_MATH_NS::Matrix4x4 srcSkelWorldMOffset = SR_MATH_NS::Matrix4x4::Identity();
        //const SR_MATH_NS::Matrix4x4 tgtSkelWorldMOffset = SR_MATH_NS::Matrix4x4::Identity();

        /*

        const SR_MATH_NS::Matrix4x4 srcSkelWorldInv = srcSkelWorldM.Inverse();

        const SR_MATH_NS::Quaternion srcSkelWorldR = SR_MATH_NS::Quaternion(sourceWorldSettings.rotationOffset.Radians()).NormalizeSafe();
        const SR_MATH_NS::Quaternion tgtSkelWorldR = SR_MATH_NS::Quaternion(targetWorldSettings.rotationOffset.Radians()).NormalizeSafe();*/


        /// Target is defined in SOURCE skeleton global space, then mapped into TARGET skeleton global space.
        /// This keeps the goal consistent even if skeleton GameObjects are placed differently in the scene.
        const SR_MATH_NS::Matrix4x4 srcSkelWorldM = pSourceTr->GetMatrix() * srcSkelWorldMOffset;
        const SR_MATH_NS::Matrix4x4 tgtSkelWorldM = pTargetTr->GetMatrix() * tgtSkelWorldMOffset;
        const SR_MATH_NS::Matrix4x4 srcSkelWorldInv = srcSkelWorldM.Inverse();

        const SR_MATH_NS::Quaternion srcSkelWorldR = pSourceTr->GetGlobalRotation().NormalizeSafe();
        const SR_MATH_NS::Quaternion tgtSkelWorldR = pTargetTr->GetGlobalRotation().NormalizeSafe();

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

            const SR_MATH_NS::FVector3 srcTipWorldPos = pSrcTipT->GetGlobalTranslation();
            const SR_MATH_NS::Quaternion srcTipWorldRot = pSrcTipT->GetGlobalRotation().NormalizeSafe();

            const SR_MATH_NS::FVector3 tgtRootWorldPos = pTgtRootT->GetGlobalTranslation();

            const SR_MATH_NS::FVector3 srcTipSkelLocal = srcSkelWorldInv.TransformPoint(srcTipWorldPos).XYZ();
            const SR_MATH_NS::FVector3 desiredTipWorldPos = tgtSkelWorldM.TransformPoint(srcTipSkelLocal).XYZ();

            const SR_MATH_NS::Quaternion srcTipSkelLocalRot = (srcSkelWorldR.Inverse() * srcTipWorldRot).NormalizeSafe();
            const SR_MATH_NS::Quaternion desiredTipWorldRot = (tgtSkelWorldR * srcTipSkelLocalRot).NormalizeSafe();

            /// Pole vector: use SOURCE bend direction (deviation of mid from root->tip axis), mapped into target root space.
            const SR_MATH_NS::FVector3 srcRootToTip = srcTipWorldPos - srcRootWorldPos;
            const float rtMag = srcRootToTip.Magnitude();
            SR_MATH_NS::FVector3 srcRootToTipDir = rtMag > 0.0001f ? (srcRootToTip / rtMag) : SR_MATH_NS::FVector3::Forward();

            SR_MATH_NS::FVector3 srcRootToMid = srcMidWorldPos - srcRootWorldPos;
            SR_MATH_NS::FVector3 srcBendDir = ProjectOnPlane(srcRootToMid, srcRootToTipDir);
            const float bendDirMag = srcBendDir.Magnitude();
            if (bendDirMag > 0.0001f) {
                srcBendDir /= bendDirMag;
            }
            else {
                srcBendDir = SafePerpendicular(srcRootToTipDir);
            }

            /// Convert bend direction through skeleton space, not limb root space.
            const SR_MATH_NS::FVector3 bendDirSkelLocal = (srcSkelWorldR.Inverse() * srcBendDir).Normalized();
            const SR_MATH_NS::FVector3 bendDirWorldForTarget = (tgtSkelWorldR * bendDirSkelLocal).Normalized();

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

        /// Spine IK (CCD) to improve torso alignment.
        /// End-effector: Head position from source, mapped through skeleton world settings (including scale).
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
                    const SR_MATH_NS::FVector3 srcHeadSkelLocal = srcSkelWorldInv.TransformPoint(srcHeadWorldPos).XYZ();
                    const SR_MATH_NS::FVector3 desiredHeadWorldPos = tgtSkelWorldM.TransformPoint(srcHeadSkelLocal).XYZ();

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

                        const float weight = 0.35f; /// conservative to not break the current good retarget+limb IK
                        for (uint32_t iter = 0; iter < 6; ++iter) {
                            for (int32_t i = static_cast<int32_t>(spineChain.size()) - 1; i >= 0; --i) {
                                ccdStep(*spineChain[i], desiredHeadWorldPos, weight);
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

        auto&& sourceSkeletonWorldSettings = pSourceRig->GetWorldSettings();
        auto&& targetSkeletonWorldSettings = pTargetRig->GetWorldSettings();

        const SR_MATH_NS::Quaternion sourceRigSkeletonRot = SR_MATH_NS::Quaternion(sourceSkeletonWorldSettings.rotationOffset.Radians()).NormalizeSafe();
        const SR_MATH_NS::Quaternion targetRigSkeletonRot = SR_MATH_NS::Quaternion(targetSkeletonWorldSettings.rotationOffset.Radians()).NormalizeSafe();

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

                SR_MATH_NS::DecomposedMatrix poseOverride;
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

        auto&& sourceSkeletonWorldSettings = pSourceRig->GetWorldSettings();
        auto&& targetSkeletonWorldSettings = pTargetRig->GetWorldSettings();

        const SR_MATH_NS::Quaternion sourceRigSkeletonRot = SR_MATH_NS::Quaternion(sourceSkeletonWorldSettings.rotationOffset.Radians()).NormalizeSafe();
        const SR_MATH_NS::Quaternion targetRigSkeletonRot = SR_MATH_NS::Quaternion(targetSkeletonWorldSettings.rotationOffset.Radians()).NormalizeSafe();

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

                SR_MATH_NS::DecomposedMatrix poseOverride;
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
                auto&& skeletonWorldSettings = pTargetRig->GetWorldSettings();
                auto&& localMatrix = SR_MATH_NS::Matrix4x4(node.localTransform.translation, node.localTransform.rotation, node.localTransform.scale);
                auto&& skeletonMatrix = SR_MATH_NS::Matrix4x4(skeletonWorldSettings.translationOffset, skeletonWorldSettings.rotationOffset, SR_MATH_NS::FVector3::One());
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
