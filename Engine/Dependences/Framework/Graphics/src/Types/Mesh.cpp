//
// Created by Nikita on 17.11.2020.
//

//#include <easy/profiler.h>

#include "Types/Mesh.h"
#include <ResourceManager/ResourceManager.h>
#include <Render/Render.h>

#include <Utils/StringUtils.h>
#include <Debug.h>
#include <exception>

#include <Loaders/ObjLoader.h>

#include <utility>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <map>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <imgui.h>

#include <GUI.h>
#include <Types/Descriptors.h>

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

    this->ReCalcModel();
}

Framework::Graphics::Types::Mesh::~Mesh() {
    if (!m_material){
        Debug::Error("Mesh::~Mesh() : material is nullptr! Something went wrong...");
    } else{
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

std::vector<Mesh *> Framework::Graphics::Types::Mesh::Load(std::string path, bool withIndices) {
    path = ResourceManager::GetResourcesFolder() + "/Models/"+path;

#ifdef WIN32
    path = StringUtils::MakePath(path, true);
#else
    path = StringUtils::MakePath(path, false);
#endif
    std::vector<Mesh*> meshes = std::vector<Mesh*>();

    unsigned int counter = 0;
ret:
    IResource* find = ResourceManager::Find("Mesh", path + " - "+ std::to_string(counter));
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

    std::string ext = StringUtils::GetExtensionFromFilePath(path);

    if (ext == "obj"){
        if (withIndices)
            meshes = ObjLoader::LoadWithIndices(path);
        else
            meshes = ObjLoader::Load(path);

    } else if (ext == "fbx"){
        meshes = std::vector<Mesh *>();
    } else {
        Helper::Debug::Error("Mesh::Load() : unknown \""+ext+"\" format!");
        meshes = std::vector<Mesh*>();
    }

    for (unsigned short i = 0; i < (unsigned short)meshes.size(); i++) {
        meshes[i]->m_resource_id = path + " - " + std::to_string(i);
        meshes[i]->m_useIndices = withIndices;
    }

    return meshes;
}

void Mesh::ReCalcModel() {
    glm::mat4 modelMat = glm::mat4(1.0f);

    modelMat = glm::translate(modelMat, {
            m_position.x,
            m_position.y,
            m_position.z //-m_position.z
    });

    modelMat *= mat4_cast(glm::quat(glm::radians(glm::vec3(
            {
                    m_rotation.x,//-m_rotation.x,
                    m_rotation.y,// + 180.f, //-m_rotation.y + 180.f,
                    -m_rotation.z // SEE: change form -m_rotation.z
            }
    ))));

    modelMat = glm::scale(modelMat, m_inverse ? -m_scale : m_scale);

    this->m_modelMat = modelMat;
}

void Mesh::OnDestroyGameObject() noexcept {
    this->Destroy();
    if (!m_render)
        Debug::Error("Mesh::OnDestroyGameObject() : render is not set! Something went wrong...");
    else
        m_render->RemoveMesh(this);
}

Mesh *Mesh::LoadJson(std::string json_data, std::vector<Mesh*>* allMeshes) {
    nlohmann::json json = json_data;

    std::vector<Mesh*> meshes = Load(json["Mesh"]["Path"]);
    if (allMeshes)
        *allMeshes = meshes;

    return meshes[(unsigned long)std::atoi(((std::string)json["Mesh"]["ID"]).c_str())];
}

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
}

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

    this->m_env->DrawTriangles(m_VAO, m_countVertices);

    return true;
}

void Mesh::SetMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) {
    this->m_position = pos;
    this->m_rotation = rot;
    this->m_scale    = scale;

    glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), m_position);

    modelMat *= mat4_cast(glm::quat(glm::radians(glm::vec3(
            m_rotation.x,
            m_rotation.y,
            -m_rotation.z
    ))));

    this->m_modelMat = glm::scale(modelMat, m_inverse ? -m_scale : m_scale);
}

bool Mesh::DrawOnInspector() {
    ImGui::Text("Geometry name: %s", GetGeometryName().c_str());
    ImGui::Text("Vertices count: %zu", GetCountVertices());
    ImGui::Text("VAO: %u", this->m_VAO);

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
}

