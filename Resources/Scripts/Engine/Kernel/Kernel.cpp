//
// Created by Nikita on 11.07.2021.
//

#include "../../Libraries/Debug.h"
#include "../../Libraries/Engine.h"
#include "../../Libraries/Camera.h"
#include "../../Libraries/GameObject.h"
#include "../../Libraries/Mesh.h"
#include "../../Libraries/Scene.h"
#include "../../Libraries/Window.h"
#include "../../Libraries/Render.h"
#include "../../Libraries/Input.h"
#include "../../Libraries/GUISystem.h"
#include "../../Libraries/Casts.h"

#include <iostream>
#include <ctime>

Skybox* g_skybox = nullptr;
Window* g_window = nullptr;

double deltaTime = 0;
unsigned int frames = 0;
clock_t beginFrame;
FVector3 velocity;

EXTERN void Awake() {

}

/*

void LoadTsumi() {
    Render* render = Engine::Instance().GetRender();

    auto hair = Texture::Load("Tsumi/hair.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    //auto face = Texture::Load("Tsumi/face.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    render->RegisterTexture(hair);
    //render->RegisterTexture(face);

    std::vector<Texture*> textures = {
            hair,
    };

    auto fbx_meshes = Mesh::Load("Tsumi.fbx", MeshType::Static);
    auto tsumi = g_scene->Instance("Tsumi");

    if (false)
    for (uint32_t i = 0; i < fbx_meshes.size(); i++) {
        Mesh* mesh = fbx_meshes[i];
        Texture* texture = textures[0];

        render->RegisterMesh(mesh);
        mesh->WaitCalculate();
        mesh->GetMaterial()->SetDiffuse(texture);
        auto object = g_scene->Instance(mesh->GetGeometryName());
        object->AddComponent(DynamicCastMeshToComponent(mesh));

        tsumi->AddChild(object);
    }
}

void LoadWireframe() {
    Render* render = Engine::Instance().GetRender();

    auto mesh = Mesh::Load("engine/cubeWireframe.obj", MeshType::Wireframe)[0];

    mesh->SetShader(render->FindShader(static_cast<uint32_t>(StandardID::DebugWireframe)));
    mesh->GetMaterial()->SetColor(0.0, 1.0, 0.0);

    auto cube = g_scene->Instance("Wireframe");
    render->RegisterMesh(mesh);
    mesh->WaitCalculate();
    cube->AddComponent(DynamicCastMeshToComponent(mesh));
}*/

void LoadCubes() {
    Render* render = Engine::Instance().GetRender();
    auto mesh = Mesh::Load("Engine/cube.obj", MeshType::Static)[0];
    auto scene = Engine::Instance().GetScene();

    mesh->SetShader(render->FindShader(static_cast<uint32_t>(StandardID::Geometry)));

    auto cube = scene->Instance("Cube");
    render->RegisterMesh(mesh);
    mesh->WaitCalculate();
    cube->AddComponent(DynamicCastMeshToComponent(mesh));
    ///cube->GetTransform()->Translate(FVector3(4, 0, 0));

    for (uint32_t i = 1; i <= 4; i++) {
        mesh = (Mesh*)mesh->Copy(nullptr);
        mesh->SetShader(render->FindShader(static_cast<uint32_t>(StandardID::Geometry)));

        render->RegisterMesh(mesh);
        mesh->WaitCalculate();

        auto newCube = scene->Instance("Cube");
        newCube->AddComponent(DynamicCastMeshToComponent(mesh));
        cube->AddChild(newCube);
        cube = newCube;

        ///cube->GetTransform()->Translate(FVector3(2, 0, 0));
    }
}

void LoadNemesis() {
    Render* render = Engine::Instance().GetRender();
    auto scene = Engine::Instance().GetScene();

    std::vector<Material*> materials = {
        Material::Load("Game/body_nemesis"),
        Material::Load("Game/face_nemesis"),
        Material::Load("Game/hair_nemesis")
    };

    auto fbx_meshes = Mesh::Load("Game/Nemesis.fbx", MeshType::Static);
    auto character = scene->Instance("Nemesis");

    for (uint32_t i = 0; i < fbx_meshes.size(); i++) {
        Mesh *mesh = fbx_meshes[i];

        mesh->SetShader(render->FindShader(static_cast<uint32_t>(StandardID::Geometry)));

        render->RegisterMesh(mesh);
        mesh->WaitCalculate();
        mesh->SetMaterial(materials[i]);
    }

    if (character.LockIfValid()) {
        for (uint32_t i = 0; i < fbx_meshes.size(); i++) {
            Mesh *mesh = fbx_meshes[i];

            auto object = scene->Instance(mesh->GetGeometryName());
            object->AddComponent(DynamicCastMeshToComponent(mesh));

            character->AddChild(object);
        }
        character.Unlock();
    }
    ///character->GetTransform()->Rotate(FVector3(-90, 0, 0));
}

void LoadMiku() {
    Render* render = Engine::Instance().GetRender();
    auto scene = Engine::Instance().GetScene();

    Material* body = Material::Load("Game/miku_body");
    Material* face = Material::Load("Game/miku_face");

    std::vector<Material*> materials = {
            body, body, face, face, body, body
    };

    auto fbx_meshes = Mesh::Load("Game/Miku.fbx", MeshType::Static);
    auto character = scene->Instance("Miku");

    for (uint32_t i = 0; i < 6; i++) {
        Mesh* mesh = fbx_meshes[i];

        mesh->SetShader(render->FindShader(static_cast<uint32_t>(StandardID::Geometry)));

        render->RegisterMesh(mesh);
        mesh->SetMaterial(materials[i]);

        mesh->WaitCalculate();

        auto cube = scene->Instance(mesh->GetGeometryName());
        cube->AddComponent(DynamicCastMeshToComponent(mesh));

        character->AddChild(cube);
    }

    ///character->GetTransform()->Translate(character->GetTransform()->Right());
}

void LoadKurumi() {
    Render* render = Engine::Instance().GetRender();
    auto scene = Engine::Instance().GetScene();

    Material* material = Material::Load("Game/kurumi");

    auto fbx_meshes = Mesh::Load("Game/Kurumi.fbx", MeshType::Static);
    auto character = scene->Instance("Kurumi");

    for (uint32_t i = 0; i < fbx_meshes.size(); i++) {
        Mesh* mesh = fbx_meshes[i];

        mesh->SetShader(render->FindShader(static_cast<uint32_t>(StandardID::Geometry)));

        render->RegisterMesh(mesh);
        mesh->WaitCalculate();
        mesh->SetMaterial(material);
        auto object = scene->Instance(mesh->GetGeometryName());
        object->AddComponent(DynamicCastMeshToComponent(mesh));

        character->AddChild(object);
    }

    ///character->GetTransform()->Translate(-character->GetTransform()->Right());
}

EXTERN void Start() {
    auto&& engine = Engine::Instance();
    g_window = engine.GetWindow();

    engine.SetScene(Scene::New("New scene"));

    //Vector2 size = { 1366, 768 }; // 848, 480
    //Vector2 size = { 1366, 768 }; // 848, 480
    //Vector2 size = { 1600, 900 }; // 848, 480


    Vector2 size = g_window->GetWindowSize();
    //g_window->SetGUIEnabled(false);
    //g_window->Resize(size.x, size.y);

    g_skybox = Skybox::Load("Sea.jpg");

    Render* render = engine.GetRender();
    render->SetSkybox(g_skybox);

    /*Camera* camera = Camera::Allocate(size.x, size.y);
    camera->SetDirectOutput(true);
    g_window->AddCamera(camera);
    g_camera = g_scene->Instance("Camera");
    g_camera->AddComponent(DynamicCastCameraToComponent(camera));

    g_scene->SetObserver(g_camera);*/

    g_window->Synchronize();

    //LoadMiku();
    //LoadKurumi();
    LoadNemesis();
    //LoadCubes();
}

void CameraMove(float dt) {
    auto dir = Input::GetMouseDrag() * dt;
    auto wheel = Input::GetMouseWheel() * dt;

    /*if (g_camera.LockIfValid()) {
        if (wheel != 0) {
            auto forward = g_camera->GetTransform()->Forward();
            g_camera->GetTransform()->Translate(forward * wheel);
        }

        if (Input::GetKey(KeyCode::MouseRight)) {
            g_camera->GetTransform()->Rotate(FVector3(dir.y, dir.x, 0.0));
        }

        if (Input::GetKey(KeyCode::MouseMiddle)) {

            auto right = g_camera->GetTransform()->Right() * dt;
            auto up = g_camera->GetTransform()->Up() * dt;

            g_camera->GetTransform()->Translate(
                    (up * dir.y) + (right * -dir.x)
            );
        }

        g_camera.Unlock();
    }*/
}

void KeyCombinations() {
    if (Input::GetKey(KeyCode::Q))
        GUISystem::Instance().SetGuizmoTool(0);
    else if (Input::GetKey(KeyCode::W))
        GUISystem::Instance().SetGuizmoTool(1);
    else if (Input::GetKey(KeyCode::E))
        GUISystem::Instance().SetGuizmoTool(2);
}

EXTERN void FixedUpdate() {
    deltaTime += double(clock() - beginFrame) / (double) CLOCKS_PER_SEC;
    frames++;
    beginFrame = clock();

    if (deltaTime > 1.0) { //every second
        Debug::ScriptLog("FixedUpdate | " + std::to_string(frames) + " frames");
        frames = 0; deltaTime = 0; }

    if (Input::GetKeyDown(KeyCode::F2)) {
        g_window->Synchronize();
        /*if (g_camera.LockIfValid()) {
            auto camera = (Camera *) g_camera->GetComponent("Camera");
            camera->SetDirectOutput(!camera->IsDirectOutput());
            g_window->SetGUIEnabled(!g_window->IsGUIEnabled());
            g_camera.Unlock();
        }*/
    }

    CameraMove(0.1f);
    KeyCombinations();
}

EXTERN void Update(float dt) {
    //Debug::ScriptLog("Update | " + std::to_string(dt) + " ms");
}

EXTERN void Close() {
    Engine::Instance().CloseScene();
}