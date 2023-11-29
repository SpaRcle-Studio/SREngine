//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/Animator.h>

#include <Utils/ECS/ComponentManager.h>

namespace SR_ANIMATIONS_NS {
    SR_REGISTER_COMPONENT(Animator);

    Animator::~Animator() {
        SR_SAFE_DELETE_PTR(m_graph);
        SR_SAFE_DELETE_PTR(m_workingPose);
        SR_SAFE_DELETE_PTR(m_staticPose);
    }

    SR_UTILS_NS::Component* Animator::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pController = new Animator();
        return pController;
    }

    SR_UTILS_NS::Component* Animator::CopyComponent() const {
        auto&& pController = new Animator();
        return pController;
    }

    SR_HTYPES_NS::Marshal::Ptr Animator::Save(SR_UTILS_NS::SavableSaveData data) const {
        return Super::Save(data);
    }

    void Animator::OnDestroy() {
        Super::OnDestroy();
        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    void Animator::FixedUpdate() {
        if (m_sync) {
            UpdateInternal(1.f / 60.f);
        }

        Super::FixedUpdate();
    }

    void Animator::Update(float_t dt) {
        SR_TRACY_ZONE;

        m_skeleton = GetParent()->GetComponent<Skeleton>();

        if (!m_sync) {
            UpdateInternal(dt);
        }

        Super::Update(dt);
    }

    void Animator::UpdateInternal(float_t dt) {
        SR_TRACY_ZONE;

        if (!GetGameObject() || !m_skeleton) {
            return;
        }

        if (!m_workingPose) {
            m_workingPose = new AnimationPose();
            m_workingPose->Initialize(m_skeleton);
        }

        if (!m_staticPose) {
            m_staticPose = new AnimationPose();
            m_staticPose->Initialize(m_skeleton);
        }
        else if (m_allowOverride) {
            m_staticPose->Update(m_skeleton, m_workingPose);
        }

        if (m_graph) {
            UpdateContext context;

            context.pStaticPose = m_staticPose;
            context.pWorkingPose = m_workingPose;
            context.now = SR_HTYPES_NS::Time::Instance().Now();
            context.weight = 1.f;
            context.dt = dt;

            m_graph->Update(context);
        }

        m_workingPose->Apply(m_skeleton);
    }

    void Animator::OnAttached() {
        m_graph = new AnimationGraph(nullptr);

        auto&& pAnimationClip = AnimationClip::Load("Samples/Tsumugi/Tsumugi.fbx", 3);

        auto&& pStateMachineNode = m_graph->AddNode<AnimationGraphNodeStateMachine>();
        auto&& pStateMachine = pStateMachineNode->GetMachine();

        auto&& pSetPoseState = pStateMachine->AddState<AnimationSetPoseState>(pAnimationClip);
        //pSetPoseState->SetClip(pAnimationClip);

        auto&& pClipState = pStateMachine->AddState<AnimationClipState>(pAnimationClip);
        //pClipState->SetClip(pAnimationClip);

        pStateMachine->GetEntryPoint()->AddTransition(pSetPoseState);
        pSetPoseState->AddTransition(pClipState);

        pStateMachine->GetEntryPoint()->AddTransition(pClipState);

        m_graph->GetFinal()->AddInput(pStateMachineNode, 0, 0);

        Super::OnAttached();
    }

    void Animator::Start() {
        Super::Start();
    }
}