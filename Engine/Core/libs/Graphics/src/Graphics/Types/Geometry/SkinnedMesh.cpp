//
// Created by Igor on 27/11/2022.
//

#include <Graphics/Types/Geometry/SkinnedMesh.h>

namespace SR_GTYPES_NS {
    SR_REGISTER_COMPONENT(SkinnedMesh);

    SkinnedMesh::SkinnedMesh()
        : MeshComponent(MeshType::Skinned)
        , m_skeletonRef(GetThis())
    { }

    SkinnedMesh::~SkinnedMesh() {
        SetRawMesh(nullptr);
    }

    bool SkinnedMesh::Calculate()  {
        if (IsCalculated()) {
            return true;
        }

        FreeVideoMemory();

        if (!IsCanCalculate()) {
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("SkinnedMesh::Calculate() : calculating \"" + m_geometryName + "\"...");
        }

        if (!CalculateVBO<Vertices::VertexType::SkinnedMeshVertex, Vertices::SkinnedMeshVertex>([this]() {
            return Vertices::CastVertices<Vertices::SkinnedMeshVertex>(GetVertices());
        })) {
            return false;
        }

        return IndexedMesh::Calculate();
    }

    void SkinnedMesh::Draw() {
        auto&& pShader = GetRenderContext()->GetCurrentShader();

        if (!pShader || !IsActive()) {
            return;
        }

        if ((!IsCalculated() && !Calculate()) || m_hasErrors) {
            return;
        }

        m_skeleton = FindSkeleton();

        if (!IsSkeletonUsable()) {
            return;
        }

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = m_uboManager.ReAllocateUBO(m_virtualUBO, pShader->GetUBOBlockSize(), pShader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                m_uboManager.BindUBO(m_virtualUBO);
            }
            else {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            pShader->InitUBOBlock();
            pShader->Flush();

            m_material->UseSamplers();
        }

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                pShader->InitUBOBlock();
                pShader->Flush();
                m_material->UseSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                m_pipeline->DrawIndices(m_countIndices);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }
    }

    SR_HTYPES_NS::Marshal::Ptr SR_GTYPES_NS::SkinnedMesh::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = MeshComponent::Save(pMarshal, flags);

        /// TODO: use unicode
        pMarshal->Write<std::string>(GetMeshStringPath());
        pMarshal->Write<int32_t>(GetMeshId());

        pMarshal->Write<std::string>(m_material ? m_material->GetResourceId() : "None");

        return pMarshal;
    }

    SR_UTILS_NS::Component* SR_GTYPES_NS::SkinnedMesh::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto&& type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto&& path = marshal.Read<std::string>();
        const auto&& id = marshal.Read<uint32_t>();

        const auto&& material = marshal.Read<std::string>();

        if (id < 0) {
            return nullptr;
        }

        auto&& pMesh = Mesh::Load(SR_UTILS_NS::Path(path, true), type, id);

        if (pMesh && material != "None") {
            if (auto&& pMaterial = SR_GTYPES_NS::Material::Load(SR_UTILS_NS::Path(material, true))) {
                pMesh->SetMaterial(pMaterial);
            }
            else {
                SR_ERROR("SkinnedMesh::LoadComponent() : failed to load material! Name: " + material);
            }
        }

        return dynamic_cast<Component*>(pMesh);
    }

    std::vector<uint32_t> SkinnedMesh::GetIndices() const {
        return GetRawMesh()->GetIndices(GetMeshId());
    }

    bool SkinnedMesh::IsCanCalculate() const {
        return IsValidMeshId() && Mesh::IsCanCalculate();
    }

    bool SkinnedMesh::IsSkeletonUsable() const {
        if (m_skeleton) {
            return m_skeleton->GetRootBone();
        }

        return false;
    }

    void SkinnedMesh::Update(float dt) {
        auto&& pNewSkeleton = FindSkeleton();
        if (m_skeleton != pNewSkeleton) {
            m_renderScene->SetDirty();
            m_bonesIds.clear();
        }
        m_skeleton = pNewSkeleton;

        MeshComponent::Update(dt);
    };

    void SkinnedMesh::UseMaterial() {
        MeshComponent::UseMaterial();
        UseModelMatrix();
    }

    void SkinnedMesh::UseModelMatrix() {
        /// TODO: А не стоило бы изменить ColorBufferPass так, чтобы он вызывал не UseModelMatrix, а более обощённый метод?
        /// Нет, не стоило бы.
        PopulateSkeletonMatrices();
        GetRenderContext()->GetCurrentShader()->SetCustom(SHADER_SKELETON_MATRICES_128, m_skeletonMatrices.data());
        GetRenderContext()->GetCurrentShader()->SetCustom(SHADER_SKELETON_MATRIX_OFFSETS_128, m_skeletonOffsets.data());
        GetRenderContext()->GetCurrentShader()->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);
    }

    void SkinnedMesh::OnResourceReloaded(SR_UTILS_NS::IResource* pResource) {
        if (GetRawMesh() == pResource) {
            OnRawMeshChanged();
            return;
        }
        Mesh::OnResourceReloaded(pResource);
    }

    void SkinnedMesh::PopulateSkeletonMatrices() {
        auto&& pNewSkeleton = FindSkeleton();
        if (m_skeleton != pNewSkeleton) {
            m_renderScene->SetDirty();
            return;
        }

        static SR_MATH_NS::Matrix4x4 identityMatrix = SR_MATH_NS::Matrix4x4().Identity();

        auto&& bones = GetRawMesh()->GetBones(GetMeshId());

        if (bones.empty()) {
            return;
        }

        if (m_bonesIds.empty()) {
            const uint64_t bonesCount = SR_MAX(SR_HUMANOID_MAX_BONES, bones.size());

            m_bonesIds.resize(bonesCount);
            m_skeletonOffsets.resize(bonesCount);
            m_skeletonMatrices.resize(bonesCount);

            for (uint64_t i = 0; i < bonesCount; ++i) {
                m_skeletonMatrices[i] = identityMatrix;
                m_skeletonOffsets[i] = identityMatrix;
            }
        }

        if (m_skeleton && !m_skeleton->GetRootBone()) {
            return;
        }

        if (!m_isOffsetsInitialized) {
            for (auto&& [hashName, boneId] : bones) {
                m_skeletonOffsets[boneId] = GetRawMesh()->GetBoneOffset(hashName);
                m_bonesIds[boneId] = m_skeleton->GetBoneIndex(hashName);
            }
            m_isOffsetsInitialized = true;
        }

        for (uint64_t boneId = 0; m_skeleton && boneId < m_bonesIds.size(); ++boneId) {
            if (auto&& bone = m_skeleton->GetBoneByIndex(m_bonesIds[boneId]); bone && bone->gameObject) {
                m_skeletonMatrices[boneId] = bone->gameObject->GetTransform()->GetMatrix();
            }
            else {
                m_skeletonMatrices[boneId] = identityMatrix;
            }
        }
    }

    void SkinnedMesh::OnRawMeshChanged() {
        IRawMeshHolder::OnRawMeshChanged();

        if (GetRawMesh() && IsValidMeshId()) {
            SetGeometryName(GetRawMesh()->GetGeometryName(GetMeshId()));
        }

        MarkPipelineUnBuild();

        m_dirtyMaterial = true;
        m_isCalculated = false;
    }

    SR_ANIMATIONS_NS::Skeleton* SkinnedMesh::FindSkeleton() const {
        if (auto&& pSkeleton = FindSkeletonImpl(GetGameObject())) {
            return pSkeleton;
        }

        if (auto&& pScene = GetScene()) {
            return pScene->GetComponent<Animations::Skeleton>();
        }

        return nullptr;
    }

    SR_ANIMATIONS_NS::Skeleton* SkinnedMesh::FindSkeletonImpl(SR_UTILS_NS::GameObject::Ptr gameObject) const {
        /// TODO: переделать на какой-нибудь RefComponent
        auto&& pSkeleton = dynamic_cast<SR_ANIMATIONS_NS::Skeleton*>(gameObject->GetComponent<SR_ANIMATIONS_NS::Skeleton>());
        if (!pSkeleton && gameObject->GetParent()) {
            return FindSkeletonImpl(gameObject->GetParent());
        }
        return pSkeleton;
    }

    SR_UTILS_NS::Component* SkinnedMesh::CopyComponent() const {
        if (auto&& pComponent = dynamic_cast<SkinnedMesh*>(MeshComponent::CopyComponent())) {
            pComponent->SetRawMesh(GetRawMesh());
            pComponent->SetMeshId(GetMeshId());
            return pComponent;
        }

        return nullptr;
    }

    std::string SkinnedMesh::GetMeshIdentifier() const {
        if (auto&& pRawMesh = GetRawMesh()) {
            return SR_UTILS_NS::Format("%s|%i|%i", pRawMesh->GetResourceId().c_str(), GetMeshId(), pRawMesh->GetReloadCount());
        }

        return MeshComponent::GetMeshIdentifier();
    }
}