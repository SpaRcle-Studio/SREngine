//
// Created by Nikita on 05.03.2021.
//

#include "Types/ManipulationTool.h"
#include <Render/Render.h>
#include <Render/Camera.h>
#include <Render/Shader.h>
#include <imgui_internal.h>

#include <Window/Window.h>
#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Transform.h>

using namespace Framework::Helper::Math;
using namespace Framework::Graphics::Types;

void ManipulationTool::Process() {
    if (!m_required || !m_isDraw)
        return;

    this->m_oldMouseDist = 0;

    glm::vec2 pos = m_render->GetWindow()->GetGlobalWindowMousePos(m_targetCamera, m_targetWindow);
    glm::vec4 color = m_env->GetTexturePixel(
            pos,
            m_targetCamera->GetPostProcessing()->GetStencilBuffer(),
            m_targetCamera->GetSize().ToGLM());

    if (color == glm::vec4(1,0,0,1))
        m_activeAxis = AXIS_X;
    else if (color == glm::vec4(0,1,0,1))
        m_activeAxis = AXIS_Y;
    else if (color == glm::vec4(0,0,1,1))
        m_activeAxis = AXIS_Z;
    else
        m_activeAxis = NONE;

    this->m_mouseNeedReCalc = true;

    if (m_activeAxis == Axis::AXIS_X) {
        m_Dirs[0] = m_targetCamera->WorldToScreenPoint(m_rotation.Radians().ToQuat() * Transform::right);
        m_Dirs[1] = m_targetCamera->WorldToScreenPoint(m_rotation.Radians().ToQuat() * -Transform::right);

        //Vector2 scrObjCenter = m_targetCamera->WorldToScreenPoint(m_position);
        //Vector2 mouse = Vector2(pos.x, m_targetCamera->GetSize().y - pos.y);

        //Debug::Log(m_Dirs[0].ToString());
        //Debug::Log(mouse.ToString());
        //Debug::Log(m_Dirs[1].ToString());
    }

    //if (m_activeAxis == Axis::AXIS_X || m_activeAxis == Axis::AXIS_Z) {
    //    m_twoDirs[0] = m_targetCamera->WorldToScreenPoint(m_rotation.Radians().ToQuat() * Transform::up);// * 100.0;
    //    m_twoDirs[1] = m_targetCamera->WorldToScreenPoint(m_rotation.Radians().ToQuat() * -Transform::up);// * 100.0;
        //Vector2 scrObjCenter = m_targetCamera->WorldToScreenPoint(m_position);

        //Debug::Log(m_twoDirs[0].ToString());
        //Debug::Log(scrObjCenter.ToString());
        //Debug::Log(m_twoDirs[1].ToString());
    //}

    //Debug::Log(this->m_targetCamera->ScreenToWorldPoint(pos).ToString());
    //if (m_countTargetMeshes == 1) {
    //    Vector2 screen = m_targetCamera->WorldToScreenPoint(m_targetMeshes[0]->GetParent()->GetTransform()->GetPosition());
        //Debug::Log(screen.ToString());
    //}

    this->m_isDraw = false;
    m_required = false;
}

bool ManipulationTool::SelectMeshes() {
    switch (m_operation) {
        case Operation::Translate:
            if (!m_arrowX || !m_arrowY || !m_arrowZ)
                return false;
            x = m_arrowX;
            y = m_arrowY;
            z = m_arrowZ;
            break;
        case Operation::Rotate:
            if (!m_ringX || !m_ringY || !m_ringZ)
                return false;
            x = m_ringX;
            y = m_ringY;
            z = m_ringZ;
            break;
        case Operation::Scale:
            return false;
            break;
    }
    return true;
}

void ManipulationTool::SimpleDraw(Shader* shader) {
    if (!SelectMeshes() || !m_targetCamera || !m_targetWindow || m_countTargetMeshes == 0)
        return;

    m_meshesMutex.lock();

    this->CalculateCenter();
    this->m_env->SetDepthTestEnabled(false);

    x->SetMatrix(m_position.ToGLM(), m_rotation.ToGLM(), Vector3(sqrt(m_distance)).ToGLM());
    glm::mat4 model = x->GetModelMatrix();

    shader->SetMat4("modelMat", model);
    shader->SetInt("id", (int)10000000);

    x->SimpleDraw();
    y->SimpleDraw();
    z->SimpleDraw();

    this->m_env->SetDepthTestEnabled(true);

    m_meshesMutex.unlock();
}

void ManipulationTool::Draw() {
    if (m_countTargetMeshes == 0)
        return;

    if (!m_targetCamera)
        return;

    if (!SelectMeshes())
        return;

    m_meshesMutex.lock();

    this->CalculateCenter();

    m_distance = (float)m_position.Distance(Vector3(m_targetCamera->GetGLPosition()).InverseAxis(2)) / 4.f - 1;
    if (m_distance < 1)
        m_distance = 1;

    x->GetMaterial()->SetColor(m_activeAxis == AXIS_X ? Vector3(2,1,1) : Vector3(1,0,0));
    y->GetMaterial()->SetColor(m_activeAxis == AXIS_Y ? Vector3(1,2,1) : Vector3(0,1,0));
    z->GetMaterial()->SetColor(m_activeAxis == AXIS_Z ? Vector3(1,1,2) : Vector3(0,0,1));

    x->SetMatrix(m_position.ToGLM(), m_rotation.ToGLM(), glm::vec3(1) * sqrt(m_distance));
    y->SetMatrix(m_position.ToGLM(), m_rotation.ToGLM(), glm::vec3(1) * sqrt(m_distance));
    z->SetMatrix(m_position.ToGLM(), m_rotation.ToGLM(), glm::vec3(1) * sqrt(m_distance));

    this->m_env->SetDepthTestEnabled(false);

    x->Draw();
    y->Draw();
    z->Draw();

    this->m_env->SetDepthTestEnabled(true);

    m_meshesMutex.unlock();

    this->m_isDraw = true;
}

//bool ManipulationTool::SetRings(Mesh *_ringX, Mesh *_ringY, Mesh *_ringZ) {

ManipulationTool::ManipulationTool(Framework::Graphics::Render *render) : m_env(Environment::Get()) {
    this->m_render = render;
    //this->m_shader = new Shader(m_render,"simpleShader");
}

bool ManipulationTool::Destroy() {
    if (m_isDestroy) {
        return false;
    }

    Debug::Log("ManipulationTool::Destroy() : destroy tools...");

    //if (m_plane)
     //   m_env->FreeMesh(m_plane);

    //if (m_shader)
    //    m_shader->Free();

    if (m_ringX && m_ringY && m_ringZ) {
        m_ringX->RemoveUsePoint();
        m_ringY->RemoveUsePoint();
        m_ringZ->RemoveUsePoint();

        if (m_ringX->IsCalculated()) m_ringX->FreeVideoMemory();
        if (m_ringY->IsCalculated()) m_ringY->FreeVideoMemory();
        if (m_ringZ->IsCalculated()) m_ringZ->FreeVideoMemory();

        m_ringX->Destroy();
        m_ringY->Destroy();
        m_ringZ->Destroy();
    }

    this->m_isDestroy = true;

    return true;
}

void ManipulationTool::Free() {
    if (!m_isDestroy) {
        Debug::Error("ManipulationTool::Free() : this tools is not destroyed!");
        return;
    }else{
        Debug::Log("ManipulationTool::Free() : free tools pointer...");
        delete this;
    }
}

ManipulationTool *ManipulationTool::Create(Framework::Graphics::Render *render) {
    Debug::Log("ManipulationTool::Create() : create new tools...");
    return new ManipulationTool(render);
}

bool ManipulationTool::RemoveMesh(Mesh *mesh) {
    this->m_meshesMutex.lock();
    bool found = false;

    for (size_t i = 0; i < m_countTargetMeshes; i++) {
        if (m_targetMeshes[i] == mesh) {
            m_countTargetMeshes--;
            m_targetMeshes.erase(m_targetMeshes.begin() + i);
            found = true;
            break;
        }
    }

    this->m_meshesMutex.unlock();
    return found;
}

bool ManipulationTool::AddMesh(Mesh *mesh) {
    this->m_meshesMutex.lock();
    bool notFound = true;

    for (auto & targetMesh : m_targetMeshes)
        if (targetMesh == mesh) {
            notFound = false;
            break;
        }

    if (notFound) {
        m_targetMeshes.push_back(mesh);
        m_countTargetMeshes++;
    }

    this->m_meshesMutex.unlock();
    return notFound;
}

bool ManipulationTool::Clear() {
    if (m_countTargetMeshes == 0)
        return false;
    else {
        this->m_meshesMutex.lock();

        m_countTargetMeshes = 0;
        this->m_targetMeshes.clear();

        this->m_meshesMutex.unlock();

        return true;
    }

    /*this->m_meshesMutex.lock();

    bool empty;
    if (!(empty = m_targetMeshes.empty())) {
        m_countTargetMeshes = 0;
        m_targetMeshes.clear();
    }

    this->m_meshesMutex.unlock();

    return !empty;*/
}

void ManipulationTool::CalculateCenter() {
    glm::vec3 pos = m_targetMeshes[0]->m_position;
    for (size_t t = 1; t < m_countTargetMeshes; t++){
        pos = (pos + m_targetMeshes[t]->m_position) / 2.f;
    }
    m_rotation = m_countTargetMeshes == 1 ? m_targetMeshes[0]->m_rotation : Vector3();
    m_position = pos;
}

void ManipulationTool::Require(Framework::Graphics::Camera *camera, ImGuiWindow *win) {
    if (m_required)
        return;

    this->m_targetCamera = camera;
    this->m_targetWindow = win;

    this->m_required = true;
}

void ManipulationTool::DisableAxis() noexcept {
    //this->m_activeAxis = (Math::Vector3::Axis)axis;
    this->m_activeAxis = Math::Axis::NONE;
    //this->m_activeAxis = Math::Vector3::AXIS_X;
}

double ManipulationTool::GetDrag() {
    Vector2 pos = m_render->GetWindow()->GetGlobalWindowMousePos(m_targetCamera, m_targetWindow);
    pos.y = m_targetCamera->GetSize().y - pos.y;

    double dist1 = pos.Distance(m_Dirs[0]);
    double dist2 = pos.Distance(m_Dirs[1]);

    //printf("%f %f\n", dist1, dist2);
    double drag = m_mouseNeedReCalc ? 0.0 : (dist1 - dist2) - m_oldMouseDist;

    m_mouseNeedReCalc = false;

    m_oldMouseDist = dist1 - dist2;

    if (drag != 0)
        printf("%f\n", drag);

    return drag;
}

bool ManipulationTool::SetArrows(Helper::Types::List<Mesh *> meshes) {
    if (meshes.Size() != 3) {
        Debug::Error("ManipulateTool::SetArrows() : count meshes is not equals 3!");
        return false;
    }

    this->m_arrowX = meshes[0];
    this->m_arrowY = meshes[1];
    this->m_arrowZ = meshes[2];

    m_arrowX->SetRender(m_render);
    m_arrowY->SetRender(m_render);
    m_arrowZ->SetRender(m_render);

    m_arrowX->SetToolID(1);
    m_arrowY->SetToolID(2);
    m_arrowZ->SetToolID(3);

    m_ringX->AddUsePoint();
    m_ringY->AddUsePoint();
    m_ringZ->AddUsePoint();

    return true;
}
bool ManipulationTool::SetRings(Helper::Types::List<Mesh*> meshes) {
    if (meshes.Size() != 3) {
        Debug::Error("ManipulateTool::SetRings() : count meshes is not equals 3!");
        return false;
    }

    this->m_ringX = meshes[0];
    this->m_ringY = meshes[1];
    this->m_ringZ = meshes[2];

    m_ringX->SetRender(m_render);
    m_ringY->SetRender(m_render);
    m_ringZ->SetRender(m_render);

    m_ringX->SetToolID(1);
    m_ringY->SetToolID(2);
    m_ringZ->SetToolID(3);

    //m_ringX->SetRender(m_render);
    //m_ringY->SetRender(m_render);
    //m_ringZ->SetRender(m_render);

    m_ringX->AddUsePoint();
    m_ringY->AddUsePoint();
    m_ringZ->AddUsePoint();

    return true;
}


