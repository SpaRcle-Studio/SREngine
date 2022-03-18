//
// Created by Nikita on 02.06.2021.
//

#include <Types/Geometry/Mesh3D.h>

#define ConfigureShader(shader) \
            shader->SetMat4("modelMat", m_modelMat); \
            shader->SetVec3("color", m_material->m_color.ToGLM()); \
            shader->SetIVec2("config", { (int)m_material->m_bloom, (int)this->m_isSelected }); \

bool Framework::Graphics::Types::Mesh3D::Calculate()  {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    if (m_isCalculated)
        return true;

    bool iboOK = ((m_IBO != SR_ID_INVALID && m_useIndices) || !m_useIndices);
    if (m_VBO != SR_ID_INVALID && iboOK && !m_hasErrors) {
        this->m_isCalculated = true;
        return true;
    }

    if (!IsCanCalculate())
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh3D::Calculate() : calculating \"" + m_geometryName + "\"...");

    if (!m_vertices.empty())
        m_barycenter = Vertices::Barycenter(m_vertices);
    SRAssert(m_barycenter != Math::FVector3(Math::UnitMAX));

    if (!CalculateVBO<Vertices::Type::Mesh3DVertex>(m_vertices.data()))
        return false;

    return IndexedMesh::Calculate();
}

Framework::Helper::IResource* Framework::Graphics::Types::Mesh3D::Copy(IResource* destination) const {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    auto* mesh3D = dynamic_cast<Mesh3D *>(destination ? destination : new Mesh3D(m_geometryName));
    mesh3D = dynamic_cast<Mesh3D *>(IndexedMesh::Copy(mesh3D));

    if (mesh3D->IsCalculated()) {
        auto &&manager = Memory::MeshManager::Instance();
        mesh3D->m_VBO = manager.CopyIfExists<Vertices::Type::Mesh3DVertex, Memory::MeshManager::VBO>(GetResourceId());
    }
    else
        mesh3D->m_vertices = m_vertices;

    return mesh3D;
}

bool Framework::Graphics::Types::Mesh3D::FreeVideoMemory() {
    if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
        Helper::Debug::Log("Mesh3D::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");

    if (!FreeVBO<Vertices::Type::Mesh3DVertex>())
        return false;

    return IndexedMesh::FreeVideoMemory();
}

void Framework::Graphics::Types::Mesh3D::SetVertexArray(const std::any& vertices) {
    try {
        auto mesh3DVertices = std::any_cast<Vertices::Mesh3DVertices>(vertices);
        m_countVertices = mesh3DVertices.size();
        m_vertices      = mesh3DVertices;
        m_isCalculated  = false;
    }
    catch (const std::bad_any_cast& e) {
        Helper::Debug::Error("Mesh3D::SetVertexArray() : failed to cast any to vertices! \n\tMessage: " + std::string(e.what()));
    }
}

void Framework::Graphics::Types::Mesh3D::DrawVulkan() {
    if (!IsReady() || IsDestroy())
        return;

    if (!m_isCalculated)
        if (m_hasErrors || !Calculate())
            return;

    if (m_descriptorSet < 0) {
        if (m_descriptorSet = m_env->AllocDescriptorSet({ DescriptorType::Uniform }); m_descriptorSet < 0) {
            SR_ERROR("Mesh3D::DrawVulkan() : failed to calculate descriptor set!");
            m_hasErrors = true;
            return;
        }

        if (m_UBO = m_env->AllocateUBO(sizeof(Mesh3dUBO)); m_UBO < 0) {
            SR_ERROR("Mesh3D::DrawVulkan() : failed to allocate uniform buffer object!");
            m_hasErrors = true;
            return;
        }

        this->m_env->UpdateDescriptorSets(m_descriptorSet, {
                { DescriptorType::Uniform, { 0, m_UBO               } },
                { DescriptorType::Uniform, { 1, m_shader->GetUBO(0) } },
        });

        UpdateUBO();

        //!==========================

        m_env->BindDescriptorSet(m_descriptorSet);
        this->m_material->UseVulkan();
    }

    this->m_env->BindDescriptorSet(m_descriptorSet);

    this->m_env->DrawIndices(this->m_countIndices);
}

void Framework::Graphics::Types::Mesh3D::DrawOpenGL()  {
    if (IsDestroy() || (!m_isCalculated && !Calculate()))
        return;

    ConfigureShader(m_shader)
    this->m_material->UseOpenGL();

    if (!m_useIndices)
        this->m_env->DrawTriangles(m_countVertices);
    else
        SRAssert2Once(false, "Mesh::DrawOpenGL() : isn't support indices!");
}

void Framework::Graphics::Types::Mesh3D::UpdateUBO() {
    if (m_UBO >= 0 && m_material) {
        Mesh3dUBO ubo = { m_modelMat, m_material->m_color.ToGLM() };
        m_env->UpdateUBO(m_UBO, &ubo, sizeof(Mesh3dUBO));
    }
}

MarshalEncodeNode Mesh3D::Save(SavableFlags flags) const {
    MarshalEncodeNode marshal("Mesh3D");

    marshal.AppendDef("Enabled", IsEnabled(), true);

    if (!(flags & SAVABLE_FLAG_ECS_NO_ID)) {
        marshal.Append("EntityId", static_cast<uint64_t>(GetEntityId()));
    }

    marshal.AppendDef("Type", static_cast<int32_t>(m_type), static_cast<int32_t>(MeshType::Static));

    marshal.Append("Path", GetPath());
    marshal.Append("Id", m_meshId);
    marshal.AppendDef("Inverse", IsInverse(), false);

    if (m_shader)
        marshal.Append(MarshalEncodeNode("Shader").Append("Name", m_shader->GetName()));

    if (m_material)
        marshal.Append(MarshalEncodeNode("Material").Append("Name", m_material->GetResourceId()));

    return marshal;
}

Component *Mesh3D::LoadComponent(const MarshalDecodeNode& node, const Helper::Types::DataStorage *dataStorage) {
    const MeshType type = static_cast<MeshType>(node.GetAttributeDef<int32_t>("Type", static_cast<int32_t>(MeshType::Static)));
    const auto&& path = node.GetAttribute<std::string>("Path");
    const auto&& id = node.GetAttribute<uint32_t>("Id");

    Render* render = dataStorage->GetPointer<Render>("Render");

    if (!render) {
        SRAssert(false);
        return nullptr;
    }

    auto&& mesh = Load(path, type, id);

    if (mesh) {
        if (const auto& shaderNode = node.TryGetNode("Shader"); shaderNode.Valid()) {
            const std::string& shaderName = shaderNode.GetAttribute<std::string>("Name");

            if (Shader* pShader = Shader::Load(render, shaderName)) {
                mesh->SetShader(pShader);
            }
            else {
                SR_ERROR("Mesh3D::LoadComponent() : failed to load shader! Name: " + shaderName);
            }
        }

        render->RegisterMesh(mesh);

        if (const auto& materialNode = node.TryGetNode("Material"); materialNode.Valid()) {
            const std::string& materialName = materialNode.GetAttribute<std::string>("Name");

            if (Material* pMaterial = Material::Load(materialName)) {
                mesh->SetMaterial(pMaterial);
            }
            else {
                SR_ERROR("Mesh3D::LoadComponent() : failed to load material! Name: " + materialName);
            }
        }
    }

    return mesh;
}
