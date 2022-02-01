//
// Created by Nikita on 17.11.2020.
//

#include "Types/Mesh.h"
#include <ResourceManager/ResourceManager.h>
#include <Render/Render.h>

#include <Debug.h>
#include <exception>

#include <Loaders/ObjLoader.h>

#include <GUI.h>
#include <FbxLoader/Loader.h>

#include <Math/Matrix4x4.h>

#include <Types/Geometry/Mesh3D.h>
#include <Types/Geometry/SkinnedMesh.h>
#include <Types/Geometry/DebugWireframeMesh.h>
#include <Memory/MeshManager.h>
#include <Memory/MeshAllocator.h>

#include <Window/Window.h>

using namespace Framework::Graphics::Types;

Framework::Graphics::Types::Mesh::Mesh(MeshType type, const std::string& name)
    : IResource(typeid(Mesh).name())
    , Component("Mesh")
    , m_env(Environment::Get())
    , m_type(type)
    , m_pipeline(Environment::Get()->GetPipeLine())
{
    this->m_shader = nullptr;
    this->m_material = nullptr;
    this->m_geometryName = name;
}

Framework::Graphics::Types::Mesh::~Mesh() {
    if (m_material) {
        m_material->UnSubscribe(this);
        m_material = nullptr;
    }
}

bool Framework::Graphics::Types::Mesh::Destroy() {
    if (IsDestroy())
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh::Destroy() : destroy \"" + m_geometryName + "\"...");

    Helper::ResourceManager::Instance().Destroy(this);

    return IResource::Destroy();
}

std::vector<Mesh *> Framework::Graphics::Types::Mesh::Load(const std::string& localPath, MeshType type) {
    auto path = ResourceManager::Instance().GetResPath().Concat("/Models/").Concat(localPath);

    std::vector<Mesh*> meshes = std::vector<Mesh*>();

    uint32_t counter = 0;
ret:
    const auto id = localPath + " - "+ std::to_string(counter) + " " + EnumMeshTypeToString(type);
    if (IResource* find = ResourceManager::Instance().Find<Mesh>(id)) {
        if (IResource* copy = ((Mesh*)(find))->Copy(nullptr)) {
            meshes.push_back((Mesh*)copy);
            counter++;
            goto ret;
        }
        else {
            SRAssert2(false, "Mesh::Load() : [FATAL] An unforeseen situation has arisen, apparently, it is necessary to work out this piece of code...");
        }
    }
    else if (counter > 0)
        return meshes;

    bool withIndices = Environment::Get()->GetPipeLine() == PipeLine::Vulkan;

    std::string ext = StringUtils::GetExtensionFromFilePath(path);

    if (ext == "obj") {
        meshes = ObjLoader::Load(path, withIndices, type);
    }
    else if (ext == "fbx") {
        SRAssert(type == MeshType::Static);

        if (!FbxLoader::Debug::IsInit())
            FbxLoader::Debug::Init([](const std::string& msg) { Helper::Debug::Error(msg); });

        const auto resFolder = Helper::ResourceManager::Instance().GetResPath();

        auto fbx = FbxLoader::Loader::Load(
                resFolder.Concat("Utilities/FbxFormatConverter.exe"),
                resFolder.Concat("Cache"),
                resFolder.Concat("Models"),
                localPath,
                withIndices);

        if (fbx.GetShapes().empty()) {
            Helper::Debug::Error("Mesh::Load() : file not found! \n\tPath: " + localPath);
            return {};
        }

        for (const auto& shape : fbx.GetShapes()) {
            auto* mesh = Memory::MeshAllocator::Allocate<Mesh3D>();
            mesh->SetGeometryName(shape.name);
            mesh->SetMaterial(Material::GetDefault());

            if (withIndices)
                mesh->SetIndexArray(shape.indices);

            auto vertices = std::vector<Vertices::Mesh3DVertex>();
            for (auto vertex : shape.vertices)
                vertices.emplace_back(Vertices::Mesh3DVertex {
                    .pos = { vertex.pos.x, vertex.pos.y, vertex.pos.z },
                    .uv  = { vertex.uv.x, vertex.uv.y },
                }); // TODO
            mesh->SetVertexArray(vertices);
            meshes.emplace_back(mesh);
        }
    } else {
        Helper::Debug::Error("Mesh::Load() : unknown \"" + ext + "\" format!");
        meshes = std::vector<Mesh*>();
    }

    for (uint32_t i = 0; i < static_cast<uint32_t>(meshes.size()); ++i) {
        meshes[i]->SetId(localPath + " - " + std::to_string(i) + " " + EnumMeshTypeToString(type));
    }

    return meshes;
}

void Mesh::OnDestroyGameObject() {
    this->Destroy();
    if (!m_render)
        Debug::Error("Mesh::OnDestroyGameObject() : render is not set! Something went wrong...");
    else
        m_render->RemoveMesh(this);
}

bool Mesh::IsCanCalculate() const {
    if (!m_render) {
        Debug::Error("Mesh::IsCanCalculate() : mesh is not register in render!");
        return false;
    }

    if (!m_shader) {
        Debug::Error("Mesh::IsCanCalculate() : mesh have not shader!");
        return false;
    }

    if (!m_material){
        Debug::Error("Mesh::IsCanCalculate() : mesh have not material!");
        return false;
    }

    return true;
}

void Mesh::OnSelected(bool value) {
    if (value == this->IsSelected())
        return;

    Component::OnSelected(value);
}

bool Mesh::DrawOnInspector() {
    ImGui::Text("Geometry name: %s", GetGeometryName().c_str());
    //ImGui::Text("Vertices count: %u", GetCountVertices());

    if (!m_render)
        ImGui::TextColored({1,0,0,1}, "Render is missing!");

    ImGui::Separator();

    if (m_material) {
        Helper::GUI::DrawTextOnCenter("Material");

        auto color = m_material->GetColor();
        if (ImGui::InputFloat3("Color", &color[0]))
            m_material->SetColor(color);

        bool enabled = m_material->GetBloomEnabled();
        if (ImGui::Checkbox("Bloom enabled", &enabled))
            m_material->SetBloom(enabled);
    } else
        Helper::GUI::DrawTextOnCenter("Material (missing)");

    ImGui::Separator();

    if (m_shader) {
        Helper::GUI::DrawTextOnCenter("Shader");
        ImGui::Text("Name: %s", m_shader->GetName().c_str());
    } else {
        Helper::GUI::DrawTextOnCenter("Shader (missing)");
    }

    return true;
}

Math::FVector3 Mesh::GetBarycenter() const {
    auto baryMat = Math::Matrix4x4(m_barycenter, Math::FVector3(), 1.0);
    auto rotateMat = Math::Matrix4x4(0.0, m_rotation.InverseAxis(2).ToQuat(), 1.0);

    return (rotateMat * baryMat).GetTranslate();
}

IResource *Mesh::Copy(IResource* destination) const {
    if (IsDestroy()) {
        Debug::Error("Mesh::Copy() : mesh already destroyed!");
        return nullptr;
    }

    Mesh* mesh = dynamic_cast<Mesh*>(destination);
    if (!mesh) {
        Debug::Error("Mesh::Copy() : impossible to copy basic mesh!");
        return nullptr;
    }

    if (Debug::GetLevel() >= Debug::Level::Full)
        Debug::Log("Mesh::Copy() : copy \"" + GetResourceId() + "\" mesh...");

    mesh->SetMaterial(m_material);
    mesh->SetShader(nullptr);

    mesh->m_barycenter = m_barycenter;
    mesh->m_position   = m_position;
    mesh->m_rotation   = m_rotation;
    mesh->m_scale      = m_scale;
    mesh->m_skew       = m_skew;

    mesh->m_isCalculated  = m_isCalculated;
    mesh->m_modelMat      = m_modelMat;

    return Helper::IResource::Copy(mesh);
}

bool Mesh::FreeVideoMemory() {
    if (m_pipeline == PipeLine::Vulkan) {
        if (m_descriptorSet >= 0) {
            this->m_env->FreeDescriptorSet(m_descriptorSet);
            this->m_descriptorSet = -5;
        }

        if (m_UBO >= 0) {
            if (!this->m_env->FreeUBO(m_UBO)) {
                Helper::Debug::Error("Mesh::FreeVideoMemory() : failed to free uniform buffer object!");
                return false;
            }
        }
    }

    this->m_isCalculated = false;

    return true;
}

void Mesh::ReCalcModel() {
    glm::mat4 modelMat = glm::mat4(1); //glm::scale(glm::mat4(1), m_skew.ToGLM());

    if (m_pipeline == PipeLine::OpenGL) {
        modelMat = glm::translate(glm::mat4(1), { -m_position.x, m_position.y, m_position.z }) * modelMat;
        modelMat *= mat4_cast(glm::quat(glm::radians(glm::vec3({ m_rotation.x, -m_rotation.y, m_rotation.z } ))));
    }
    else {
        modelMat = glm::translate(glm::mat4(1), { m_position.x, m_position.y, m_position.z}) * modelMat;
        modelMat *= mat4_cast(glm::quat(glm::radians(glm::vec3({ m_rotation.x, m_rotation.y, -m_rotation.z } ))));
    }

    modelMat = glm::scale(modelMat, m_inverse ? -m_scale.ToGLM() : m_scale.ToGLM());

    this->m_modelMat = modelMat;

    this->UpdateUBO();
}

void Mesh::WaitCalculate() const  {
    ret:
    if (!m_render || m_render->GetWindow()->GetCountCameras() == 0) {
        SRAssert2(false, Helper::Format("Mesh::WaitCalculate() : There is no destination render or camera!"
                             " The geometry will never be calculated. \nName: %s", m_geometryName.c_str()).c_str());
        return;
    }

    if (m_isCalculated)
        return;

    goto ret;
}

bool Mesh::Calculate()  {
    m_isCalculated = true;
    return true;
}

void Mesh::SetMaterial(Material *material) {
    if (m_material)
        m_material->UnSubscribe(this);

    if ((m_material = material))
        m_material->Subscribe(this);
    else
        Helper::Debug::Warn("Mesh::SetMaterial() : the material is nullptr!");

    if (m_material && m_render)
        m_material->Register(m_render);

    if (m_isCalculated)
        Environment::Get()->SetBuildState(false);
}

void Mesh::SetShader(Framework::Graphics::Shader *shader) {
    if (m_isCalculated) {
        Environment::Get()->SetBuildState(false);
        m_isCalculated = false;
    }
    m_shader = shader;
}

void Mesh::OnMove(const Math::FVector3 &newValue) {
    m_position = newValue;
    ReCalcModel();
}

void Mesh::OnRotate(const Math::FVector3 &newValue) {
    m_rotation = newValue;
    ReCalcModel();
}

void Mesh::OnScaled(const Math::FVector3 &newValue) {
    m_scale = newValue;
    ReCalcModel();
}

void Mesh::OnSkewed(const Math::FVector3 &newValue) {
    m_skew = newValue;
    ReCalcModel();
}
