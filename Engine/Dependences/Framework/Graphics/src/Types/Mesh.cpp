//
// Created by Nikita on 17.11.2020.
//

#include "Types/Mesh.h"
#include <ResourceManager/ResourceManager.h>
#include <Render/Render.h>

#include <Debug.h>
#include <exception>

#include <Loaders/ObjLoader.h>

#include <imgui.h>

#include <GUI.h>
#include <FbxLoader/Loader.h>

#include <Math/Matrix4x4.h>

#include <Types/Geometry/Mesh3D.h>
#include <Types/Geometry/SkinnedMesh.h>

using namespace Framework::Graphics::Types;

Framework::Graphics::Types::Mesh::Mesh() : IResource("Mesh"), m_env(Environment::Get()), Component("Mesh") {
    this->m_shader        = nullptr;
    this->m_material      = nullptr;
    this->m_geometry_name = "Unsolved";
    this->m_pipeline      = this->m_env->GetPipeLine();
}

Framework::Graphics::Types::Mesh::Mesh(Shader* shader, Material* material, std::string name)
    : IResource("Mesh"), m_env(Environment::Get()), Component("Mesh")
{
    this->m_pipeline = this->m_env->GetPipeLine();
    this->m_shader   = shader;

    this->m_geometry_name = std::move(name);
    this->m_material = material;

    if (!this->m_material)
        Debug::Warn("Mesh::Constructor() : material is nullptr! \n\tMesh name: "+m_geometry_name);

    //TODO: this->ReCalcModel();
}

Framework::Graphics::Types::Mesh::~Mesh() {
    if (!m_material){
        Debug::Error("Mesh::~Mesh() : material is nullptr! Something went wrong...");
    } else{
        if (Debug::GetLevel() >= Debug::Level::High)
            Debug::Log("Mesh::~Mesh() : free material pointer...");
        delete m_material;
        m_material = nullptr;
    }
}

bool Framework::Graphics::Types::Mesh::Destroy() {
    if (m_isDestroy)
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh::Destroy() : destroy \""+m_geometry_name+"\"...");

    this->m_isDestroy = true;

    if (m_material)
        this->m_material->FreeTextures();

    Helper::ResourceManager::Destroy(this);

    return true;
}

std::vector<Mesh *> Framework::Graphics::Types::Mesh::Load(const std::string& localPath) {
    std::string path = ResourceManager::GetResourcesFolder() + "/Models/"+localPath;

#ifdef WIN32
    path = StringUtils::MakePath(path, true);
#else
    path = StringUtils::MakePath(path, false);
#endif
    std::vector<Mesh*> meshes = std::vector<Mesh*>();

    unsigned int counter = 0;
ret:
    IResource* find = ResourceManager::Find("Mesh", localPath + " - "+ std::to_string(counter));
    if (find) {
        Mesh* copy = ((Mesh*)(find))->Copy();
        if (!copy) {
            Debug::Error("Mesh::Load() : [FATAL] An unforeseen situation has arisen, apparently, it is necessary to work out this piece of code...");
            throw "This should never happen.";
        }

        meshes.push_back(copy);
        counter++;
        goto ret;
    } else
        if (counter > 0)
            return meshes;

    bool withIndices = Environment::Get()->GetPipeLine() == PipeLine::Vulkan;

    std::string ext = StringUtils::GetExtensionFromFilePath(path);

    if (ext == "obj") {
        if (withIndices)
            meshes = ObjLoader::LoadWithIndices(path);
        else
            meshes = ObjLoader::Load(path);
    } else if (ext == "fbx") {
        if (!FbxLoader::Debug::IsInit())
            FbxLoader::Debug::Init([](const std::string& msg) { Helper::Debug::Error(msg); });

        auto fbx = FbxLoader::Loader::Load(
                Helper::ResourceManager::GetResourcesFolder() + "/Utilities/FbxFormatConverter.exe",
                Helper::ResourceManager::GetResourcesFolder() + "/Cache/",
                Helper::ResourceManager::GetResourcesFolder() + "/Models/",
                localPath,
                withIndices);

        for (auto shape : fbx.GetShapes()) {
            auto* mesh = new Mesh3D(nullptr, new Material(nullptr, nullptr, nullptr, nullptr), shape.name);

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
        Helper::Debug::Error("Mesh::Load() : unknown \""+ext+"\" format!");
        meshes = std::vector<Mesh*>();
    }

    for (unsigned short i = 0; i < (unsigned short)meshes.size(); i++) {
        meshes[i]->m_resource_id = localPath + " - " + std::to_string(i);
        meshes[i]->m_useIndices = withIndices;
    }

    return meshes;
}

void Mesh::OnDestroyGameObject() noexcept {
    this->Destroy();
    if (!m_render)
        Debug::Error("Mesh::OnDestroyGameObject() : render is not set! Something went wrong...");
    else
        m_render->RemoveMesh(this);
}

/*
nlohmann::json Mesh::Save() {
    nlohmann::json json;
    json["Mesh"]["GeometryName"] = m_geometry_name;

    size_t size = m_resource_id.size();

    for (size_t t = size - 1; t > 0; t--){
        if (m_resource_id[t] == '-'){
            json["Mesh"]["Path"] = StringUtils::Resize(m_resource_id, t - 1);

            std::string id = StringUtils::BackSubstring(m_resource_id, '-');
            json["Mesh"]["ID"] = StringUtils::Resize(id, id.size() - 1);

            json["Mesh"]["Material"]["Color"] = {
                    this->m_material->m_color.r,
                    this->m_material->m_color.g,
                    this->m_material->m_color.b,
                    this->m_material->m_color.a,
            };

            json["Mesh"]["Material"]["Transparent"] = m_material->m_transparent;

            break;
        }
    }

    return json;
}*/

void Mesh::OnSelected(bool value) noexcept {
    //if (!m_render)
    //   return;

    if (value == this->IsSelected())
        return;
    else {
        //if (this->IsSelected())
        //    this->m_render->DeselectMesh(this);
        //else
        //    this->m_render->SelectMesh(this);

        /*if (value)
            this->m_render->GetManipulationTool()->AddMesh(this);
        else
            this->m_render->GetManipulationTool()->RemoveMesh(this);*/
    }

    Component::OnSelected(value);
}

bool Mesh::SimpleDraw() {
    if (m_isDestroy) return false;

    if (!m_isCalculated)
        if (!this->Calculate())
            return false;

    //this->m_env->DrawTriangles(m_VAO, m_countVertices);

    return true;
}

bool Mesh::DrawOnInspector() {
    ImGui::Text("Geometry name: %s", GetGeometryName().c_str());
    ImGui::Text("Vertices count: %zu", GetCountVertices());

    if (!m_render)
        ImGui::TextColored({1,0,0,1}, "Render is missing!");

    ImGui::Separator();

    if (m_material) {
        Helper::GUI::DrawTextOnCenter("Material");

        glm::vec3 color = m_material->GetColor().ToGLM();
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
        auto shader = Shader::GetDefaultGeometryShader();
        if (!shader)
            Helper::GUI::DrawTextOnCenter("Shader (default-missing)");
        else {
            Helper::GUI::DrawTextOnCenter("Shader (default)");
            ImGui::Text("Name: %s", shader->GetName().c_str());
        }
    }

    return true;
}

Math::Vector3 Mesh::GetBarycenter() const {
    auto baryMat = Math::Matrix4x4(m_barycenter, Math::Vector3(), 1.0);
    auto rotateMat = Math::Matrix4x4(0.0, m_rotation.InverseAxis(2).ToQuat(), 1.0);

    return (rotateMat * baryMat).GetTranslate();
}

/*
void Mesh::PrintInfo() {
    Helper::Debug::Info("Mesh::PrintInfo(): "
                        "\n\tGeometry name: "  + m_geometry_name +
                        "\n\tResource ID: "    + m_resource_id +
                        "\n\tUse indices: "    + (m_useIndices ? "true" : "false") +
                        "\n\tCount vertices: " + std::to_string(m_countVertices) +
                        "\n\tCount indices: "  + std::to_string(m_countIndices) +
                        "\n\tInverse: "        + (m_inverse ? "true" : "false") +
                        "\n\tIs calculated: "  + (m_isCalculated ? "true" : "false") +
                        "\n\tVAO: "            + std::to_string(m_VAO));
}*/

