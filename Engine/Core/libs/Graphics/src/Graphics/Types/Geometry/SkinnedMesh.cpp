//
// Created by Igor on 27/11/2022.
//

#include <Graphics/Types/Geometry/SkinnedMesh.h>

namespace SR_GTYPES_NS {
    SkinnedMesh::SkinnedMesh()
        : Super(MeshType::Skinned)
    {
        m_entityMessages.AddCustomProperty<SR_UTILS_NS::LabelProperty>("SkeletonInv")
            .SetLabel("Skeleton is not usable!")
            .SetColor(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f))
            .SetActiveCondition([this] { return !IsSkeletonUsable(); })
            .SetDontSave();
    }

    SkinnedMesh::~SkinnedMesh() {
        SetRawMesh(nullptr);
    }

    bool SkinnedMesh::Calculate()  {
        SR_TRACY_ZONE;

        if (IsCalculated()) {
            return true;
        }

        FreeVideoMemory();

        if (!IsCalculatable()) {
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
        SR_TRACY_ZONE;

        auto&& pShader = GetRenderContext()->GetCurrentShader();

        if (!pShader || !IsActive()) {
            return;
        }

        if ((!IsCalculated() && !Calculate()) || m_hasErrors) {
            return;
        }

        if (!IsSkeletonUsable()) {
            return;
        }

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = m_uboManager.ReAllocateUBO(m_virtualUBO, pShader->GetUBOBlockSize(), pShader->GetSamplersCount());

            if (m_virtualUBO == SR_ID_INVALID || m_uboManager.BindUBO(m_virtualUBO) == Memory::UBOManager::BindResult::Failed) {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            pShader->InitUBOBlock();
            pShader->Flush();

            m_material->UseSamplers();
            pShader->FlushSamplers();
        }

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                pShader->InitUBOBlock();
                pShader->Flush();
                m_material->UseSamplers();
                pShader->FlushSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                pShader->FlushConstants();
                m_pipeline->DrawIndices(m_countIndices);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }
    }

    std::vector<uint32_t> SkinnedMesh::GetIndices() const {
        return GetRawMesh()->GetIndices(GetMeshId());
    }

    bool SkinnedMesh::IsCalculatable() const {
        return IsValidMeshId() && Mesh::IsCalculatable();
    }

    bool SkinnedMesh::IsSkeletonUsable() const {
        return GetSkeleton().GetComponent<SR_ANIMATIONS_NS::Skeleton>();
    }

    void SkinnedMesh::Update(float dt) {
        const bool usable = IsSkeletonUsable();

        if (m_skeletonIsBroken && !usable) {
            return Super::Update(dt);
        }

        if (!m_skeletonIsBroken && usable) {
            return Super::Update(dt);
        }

        m_skeletonIsBroken = !usable;
        m_renderScene->SetDirty();

        Super::Update(dt);
    };

    void SkinnedMesh::UseMaterial() {
        Super::UseMaterial();
        UseModelMatrix();
    }

    void SkinnedMesh::UseModelMatrix() {
        /// TODO: А не стоило бы изменить ColorBufferPass так, чтобы он вызывал не UseModelMatrix, а более обощённый метод?
        /// Нет, не стоило бы.
        if (!PopulateSkeletonMatrices()) {
            return;
        }

        auto&& pShader = GetRenderContext()->GetCurrentShader();
        SRAssert(pShader);

        pShader->SetMat4(SHADER_MODEL_MATRIX, m_modelMatrix);

        auto&& pSkeleton = GetSkeleton().GetComponent<SR_ANIMATIONS_NS::Skeleton>();
        auto&& pRenderScene = GetRenderScene();

        SRAssert(pRenderScene);

        if (pRenderScene->GetCurrentSkeleton() == pSkeleton.Get()) {
            return;
        }

        pRenderScene->SetCurrentSkeleton(pSkeleton.Get());

        switch (GetMaxBones()) {
            case 128:
                pShader->SetValue<false>(SHADER_SKELETON_MATRICES_128, pSkeleton->GetMatrices().data());
                pShader->SetValue<false>(SHADER_SKELETON_MATRIX_OFFSETS_128, pSkeleton->GetOffsets().data());
                break;
            case 256:
                pShader->SetValue<false>(SHADER_SKELETON_MATRICES_256, pSkeleton->GetMatrices().data());
                pShader->SetValue<false>(SHADER_SKELETON_MATRIX_OFFSETS_256, pSkeleton->GetOffsets().data());
                break;
            case 384:
                pShader->SetValue<false>(SHADER_SKELETON_MATRICES_384, pSkeleton->GetMatrices().data());
                pShader->SetValue<false>(SHADER_SKELETON_MATRIX_OFFSETS_384, pSkeleton->GetOffsets().data());
                break;
            case 0:
                break;
            default:
                SRHaltOnce0();
                return;
        }
    }

    void SkinnedMesh::OnResourceReloaded(SR_UTILS_NS::IResource* pResource) {
        if (GetRawMesh() == pResource) {
            OnRawMeshChanged();
            return;
        }
        Mesh::OnResourceReloaded(pResource);
    }

    bool SkinnedMesh::PopulateSkeletonMatrices() {
        auto&& bones = GetRawMesh()->GetOptimizedBones();

        if (bones.empty()) {
            return false;
        }

        auto&& pSkeleton = GetSkeleton().GetComponent<SR_ANIMATIONS_NS::Skeleton>();

        if (!pSkeleton || !pSkeleton->GetRootBone()) {
            return false;
        }

        pSkeleton->SetOptimizedBones(GetRawMesh()->GetOptimizedBones());
        pSkeleton->SetBonesOffsets(GetRawMesh()->GetBoneOffsets());

        return true;
    }

    void SkinnedMesh::OnRawMeshChanged() {
        IRawMeshHolder::OnRawMeshChanged();

        if (GetRawMesh() && IsValidMeshId()) {
            SetGeometryName(GetRawMesh()->GetGeometryName(GetMeshId()));
        }

        if (auto&& pSkeleton = GetSkeleton().GetComponent<SR_ANIMATIONS_NS::Skeleton>()) {
            pSkeleton->ResetSkeleton();
        }

        MarkPipelineUnBuild();

        m_dirtyMaterial = true;
        m_isCalculated = false;
    }

    std::string SkinnedMesh::GetMeshIdentifier() const {
        if (auto&& pRawMesh = GetRawMesh()) {
            return SR_FORMAT("{}|{}|{}", pRawMesh->GetResourceId().c_str(), GetMeshId(), pRawMesh->GetReloadCount());
        }

        return Super::GetMeshIdentifier();
    }

    uint32_t SkinnedMesh::GetMaxBones() const {
        if (!GetRawMesh()) {
            return 0;
        }

        return SR_GRAPH_NS::RoundBonesCount(GetRawMesh()->GetOptimizedBones().size());
    }

    bool SkinnedMesh::InitializeEntity() noexcept {
        m_properties.AddCustomProperty<SR_UTILS_NS::PathProperty>("Mesh")
            .AddFileFilter("Mesh", SR_GRAPH_NS::SR_SUPPORTED_MESH_FORMATS)
            .SetGetter([this]()-> SR_UTILS_NS::Path {
                return GetRawMesh() ? GetRawMesh()->GetResourcePath() : SR_UTILS_NS::Path();
            })
            .SetSetter([this](const SR_UTILS_NS::Path& path) {
                SetRawMesh(path);
            });

        m_properties.AddCustomProperty<SR_UTILS_NS::StandardProperty>("Index")
            .SetGetter([this](void* pData) {
                *reinterpret_cast<int16_t*>(pData) = static_cast<int16_t>(GetMeshId());
            })
            .SetSetter([this](void* pData) {
                SetMeshId(static_cast<MeshIndex>(*reinterpret_cast<int16_t*>(pData)));
            })
            .SetType(SR_UTILS_NS::StandardType::Int16);

        m_properties.AddEntityRefProperty(SR_SKELETON_REF_PROP_NAME, GetThis())
            .SetWidth(260.f);

        return Super::InitializeEntity();
    }

    SR_UTILS_NS::EntityRef& SkinnedMesh::GetSkeleton() const {
        auto&& pSkeletonRefProperty = GetComponentProperties().Find<SR_UTILS_NS::EntityRefProperty>(SR_SKELETON_REF_PROP_NAME);
        if (pSkeletonRefProperty) {
            return pSkeletonRefProperty->GetEntityRef();
        }
        SRHaltOnce0();
        static SR_UTILS_NS::EntityRef defaultEntityRef;
        return defaultEntityRef;
    }
}