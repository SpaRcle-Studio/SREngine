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

SafePtr<Scene> g_scene;
SafePtr<GameObject> g_camera;
SafePtr<GameObject> g_miku;

Skybox* g_skybox = nullptr;
Window* g_window = nullptr;

EXTERN void Awake() {

}

void LoadTsumi() {
    Render* render = Engine::Get()->GetRender();

    auto hair = Texture::Load("Tsumi/hair.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    //auto face = Texture::Load("Tsumi/face.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    render->RegisterTexture(hair);
    //render->RegisterTexture(face);

    std::vector<Texture*> textures = {
            hair,
    };

    auto fbx_meshes = Mesh::Load("Tsumi.fbx", MeshType::Static);
    auto tsumi = g_scene->Instance("Tsumi");

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

void LoadCubes() {
    Render* render = Engine::Get()->GetRender();
    auto texture = Texture::Load("default.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::NEAREST, TextureCompression::None, 1);
    auto mesh = Mesh::Load("engine/cube.obj", MeshType::Static)[0];
    render->RegisterTexture(texture);

    auto cube = g_scene->Instance("Cube");
    render->RegisterMesh(mesh);
    mesh->WaitCalculate();
    mesh->GetMaterial()->SetDiffuse(texture);
    cube->AddComponent(DynamicCastMeshToComponent(mesh));
    cube->GetTransform()->Translate(Vector3(4, 0, 0));

    for (uint32_t i = 1; i <= 4; i++) {
        mesh = mesh->Copy(nullptr);
        render->RegisterMesh(mesh);
        mesh->WaitCalculate();
        mesh->GetMaterial()->SetDiffuse(texture);

        auto newCube = g_scene->Instance("Cube");
        newCube->AddComponent(DynamicCastMeshToComponent(mesh));
        cube->AddChild(newCube);
        cube = newCube;

        cube->GetTransform()->Translate(Vector3(2, 0, 0));
    }
}

void LoadMiku() {
    Render* render = Engine::Get()->GetRender();

    auto body = Texture::Load("Miku_Bodytex_DM.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    auto face = Texture::Load("Miku_Facetex_A.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    render->RegisterTexture(body);
    render->RegisterTexture(face);

    std::vector<Texture*> textures = {
            body, body, face, face, body, body
    };

    auto fbx_meshes = Mesh::Load("Miku.fbx", MeshType::Static);

    g_miku = g_scene->Instance("Miku");

    for (uint32_t i = 0; i < 6; i++) {
        Mesh* mesh = fbx_meshes[i];
        Texture* texture = textures[i];
        render->RegisterMesh(mesh);
        mesh->WaitCalculate();
        mesh->GetMaterial()->SetDiffuse(texture);
        auto cube = g_scene->Instance(mesh->GetGeometryName());
        cube->AddComponent(DynamicCastMeshToComponent(mesh));

        g_miku->AddChild(cube);
    }
}

EXTERN void Start() {
    Engine* engine = Engine::Get();
    g_scene = Scene::New("New scene");
    engine->SetScene(g_scene);

    Vector2 size = { 1366, 768 }; // 848, 480

    g_window = engine->GetWindow();
    g_window->SetGUIEnabled(false);
    g_window->Resize(size.x, size.y);
    g_window->CentralizeWindow();

    g_skybox = Skybox::Load("Sea.jpg");

    Render* render = engine->GetRender();
    render->SetSkybox(g_skybox);

    LoadMiku();
    LoadCubes();

    Camera* camera = Camera::Allocate(size.x, size.y);
    camera->SetDirectOutput(true);
    g_window->AddCamera(camera);
    g_camera = g_scene->Instance("Camera");
    g_camera->AddComponent(DynamicCastCameraToComponent(camera));
}

void CameraMove(float dt) {
    auto dir = Input::GetMouseDrag() * dt;
    auto wheel = Input::GetMouseWheel() * dt;

    if (wheel != 0) {
        auto forward = g_camera->GetTransform()->Forward();
        g_camera->GetTransform()->Translate(forward * wheel);
    }

    if (Input::GetKey(KeyCode::MouseRight)) {
        g_camera->GetTransform()->Rotate(Vector3(dir.y, dir.x, 0.0));
    }

    if (Input::GetKey(KeyCode::MouseMiddle)) {
        auto right = g_camera->GetTransform()->Right() * dt;
        auto up = g_camera->GetTransform()->Up() * dt;

        g_camera->GetTransform()->Translate(
                (up * dir.y) + (right * -dir.x)
        );
    }
}

void KeyCombinations() {
    if (Input::GetKey(KeyCode::Q))
        GUISystem::Get()->SetGuizmoTool(0);
    else if (Input::GetKey(KeyCode::W))
        GUISystem::Get()->SetGuizmoTool(1);
    else if (Input::GetKey(KeyCode::E))
        GUISystem::Get()->SetGuizmoTool(2);
}

double deltaTime = 0;
unsigned int frames = 0;
clock_t beginFrame;

EXTERN void FixedUpdate() {
    deltaTime += double(clock() - beginFrame) / (double) CLOCKS_PER_SEC;
    frames++;
    beginFrame = clock();

    if (deltaTime > 1.0) { //every second
        Debug::ScriptLog("FixedUpdate | " + std::to_string(frames) + " frames");
        frames = 0; deltaTime = 0; }

    if (Input::GetKeyDown(KeyCode::F2)) {
        auto camera = (Camera*)g_camera->GetComponent("Camera");
        camera->SetDirectOutput(!camera->IsDirectOutput());
        g_window->SetGUIEnabled(!g_window->IsGUIEnabled());
    }

    CameraMove(0.1f);
    KeyCombinations();

    //g_miku->GetTransform()->RotateAround(g_miku->GetBarycenter(), Vector3(1, 1, 0), 0.2);
}

EXTERN void Update(float dt) {
    //Debug::ScriptLog("Update | " + std::to_string(dt) + " ms");
}

EXTERN void Close() {
    g_scene.Lock();
    g_scene.Free([](Scene* scene) {
        g_scene->Destroy();
        g_scene->Free();
    });
    g_scene.Unlock();
}