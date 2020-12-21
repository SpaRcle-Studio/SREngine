//
// Created by Nikita on 17.11.2020.
//

#include "Types/Mesh.h"
#include <ResourceManager/ResourceManager.h>
#include <Render/Render.h>
#include <Render/Shader.h>
#include <Types/Material.h>
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

using namespace Framework::Graphics::Types;

inline static std::map<unsigned int, unsigned long> VAO_usages = std::map<unsigned int, unsigned long>();
inline static std::map<std::string, unsigned int> VAO_names = std::map<std::string, unsigned int>();

Framework::Graphics::Types::Mesh::Mesh(Shader* shader, Material* material, std::string name)
    : IResource("Mesh"), m_env(Environment::Get()), Component("Mesh")
    {
    this->m_shader = shader;

    if (!m_shader)
        Debug::Error("Mesh::Constructor() : shader is nullptr!");

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

    this->m_isDestroy = true;

    this->m_material->FreeTextures();

    Helper::ResourceManager::Destroy(this);

    return true;
}

std::vector<Mesh *> Framework::Graphics::Types::Mesh::Load(std::string path) {
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
        //std::string file = path;
        //file.resize(path.size() - 4);
        meshes = ObjLoader::Load(path);
    } else if (ext == "fbx"){
        meshes = std::vector<Mesh *>();
    } else {
        Helper::Debug::Error("Mesh::Load() : unknown \""+ext+"\" format!");
        meshes = std::vector<Mesh*>();
    }

    for (unsigned short i = 0; i < meshes.size(); i++) {
        meshes[i]->m_resource_id = path + " - " + std::to_string(i);
    }

    return meshes;
}

void Mesh::ReCalcModel() {
    glm::mat4 modelMat = glm::mat4(1.0f);

    //std::cout << glm::to_string(m_position) << std::endl;

    /*modelMat = glm::translate(modelMat, {
            //-m_position.z, m_position.y, -m_position.x
            m_position.x, m_position.y, -m_position.z
             //0, -8, -25
    }); // */

    modelMat = glm::translate(modelMat, {
            m_position.x,
            m_position.y,
            -m_position.z
    });

    const glm::mat4 rotationMatrix = mat4_cast(glm::quat(glm::radians(glm::vec3(
            {
                m_rotation.x,
                -m_rotation.y + 180.f,
                m_rotation.z // SEE: change form -m_rotation.z
            }
            ))));

    //modelMat = glm::rotate(modelMat, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
    //modelMat = glm::rotate(modelMat, glm::radians(-m_rotation.y + 180.f), glm::vec3(0, 1, 0));
    //modelMat = glm::rotate(modelMat, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));

    //glm::vec3 rad = glm::radians(m_rotation);

    //glm::mat4 rotMatrix = glm::eulerAngleXYZ(rad.x, rad.y, rad.z);

    modelMat *= rotationMatrix;

    //if (m_rotation != glm::vec3(0))

    //glm::fquat q = glm::radians(m_rotation);
    //modelMat *= q;

    modelMat = glm::scale(modelMat, m_scale);



    this->m_modelMat = modelMat;
}

bool Mesh::Calculate() {
    if (!m_render){
        Debug::Error("Mesh::Calculate() : mesh is not register in render!");
        return false;
    }

    m_mutex.lock();

    {
        /*
            Check exists pre-calculated meshes
         */
        unsigned int exists = VAO_names[m_resource_id];
        if (exists) {
            if (Debug::GetLevel() >= Debug::Level::High)
                Debug::Log("Mesh::Calculate() : copy VAO...");

            m_VAO = exists;

            VAO_usages[m_VAO]++;
            m_isCalculated = true;
            m_mutex.unlock();

            return true;
        }
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh::Calculate() : calculating \""+ m_geometry_name +"\"...");

    unsigned int VBO = 0;
    if (!this->m_env->CalculateMesh(VBO, m_VAO, m_vertices, m_countVertices)) {
        Debug::Error("Mesh::Calculate() : failed calculate \"" + m_geometry_name + "\" mesh!");
        m_mutex.unlock();
        return false;
    }

    VAO_usages[m_VAO]++;
    VAO_names[m_resource_id] = m_VAO;

    m_isCalculated = true;

    m_mutex.unlock();

    return true;
}

Mesh *Mesh::Copy() {
    if (m_isDestroy) {
        Debug::Error("Mesh::Copy() : mesh already destroyed!");
        return nullptr;
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh::Copy() : copy \""+m_resource_id+ "\" mesh...");

    if (!m_material){
        Debug::Error("Mesh::Copy() : material is nullptr! Something went wrong...");
        return nullptr;
    }

    m_mutex.lock();

    Material* mat = new Material(
            m_material->m_diffuse,
            m_material->m_normal,
            m_material->m_specular,
            m_material->m_glossiness
        );

    Mesh* copy = new Mesh(this->m_shader, mat, this->m_geometry_name);

    {
        mat->m_mesh         = copy;
        mat->m_bloom        = m_material->m_bloom;
        mat->m_transparent  = m_material->m_transparent;
        mat->m_color        = m_material->m_color;
    }

    copy->m_countVertices = m_countVertices;
    copy->m_position = m_position;
    copy->m_rotation = m_rotation;
    copy->m_scale = m_scale;
    if (m_isCalculated) {
        VAO_usages[m_VAO]++;
        copy->m_VAO = m_VAO;
    }else{
        copy->m_vertices = m_vertices;
    }
    copy->m_isCalculated = m_isCalculated;
    copy->m_autoRemove = m_autoRemove;
    //copy->m_render = m_render;
    copy->m_modelMat = m_modelMat;

    copy->m_resource_id = m_resource_id; // Fuck, I remember this

    m_mutex.unlock();

    return copy;
}

bool Mesh::Draw() {
    if (m_isDestroy) return false;

    if (!m_isCalculated)
        if (!this->Calculate())
            return false;

    this->m_shader->SetMat4("modelMat", m_modelMat);
    this->m_shader->SetVec3("color", m_material->m_color); //TODO: change to vec4
    this->m_shader->SetInt("bloom", (int)m_material->m_bloom);

    this->m_material->Use();

    this->m_env->DrawTriangles(m_VAO, m_countVertices);

    return true;
}

bool Mesh::FreeVideoMemory() {
    if (m_VAO > 0) {
        VAO_usages[m_VAO]--;
        if (VAO_usages[m_VAO] == 0)
            m_env->FreeMesh(m_VAO);
        m_isCalculated = false;
        return true;
    }
    else {
        Debug::Error("Mesh:FreeVideoMemory() : VAO is zero! Something went wrong...");
        return false;
    }
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
