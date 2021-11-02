//
// Created by Monika on 18.08.2021.
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
#include "../../Libraries/Casts.h"

#include <iostream>
#include <ctime>

Skybox* g_skybox = nullptr;
Window* g_window = nullptr;

Vector2 size = { 1366, 768 };
SafePtr<Scene> g_scene;

void CreateScene() {
    g_scene = Scene::New("New scene");
    Engine::Get()->SetScene(g_scene);
}

void CreateCamera() {
    Camera* camera = Camera::Allocate(size.x, size.y);
    camera->SetDirectOutput(true);
    g_window->AddCamera(camera);
    auto gm = g_scene->Instance("Camera");
    gm->AddComponent(DynamicCastCameraToComponent(camera));
}

void FullScene() {
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

void FreeScene() {
    g_scene.Lock();
    g_scene.Free([](Scene* scene) {
        g_scene->Destroy();
        g_scene->Free();
    });
    g_scene.Unlock();
}

EXTERN void Awake() {

}

EXTERN void Start() {
    Engine* engine = Engine::Get();

    g_window = engine->GetWindow();
    g_window->SetGUIEnabled(false);
    g_window->Resize(size.x, size.y);
    g_window->CentralizeWindow();

    g_skybox = Skybox::Load("Sea.jpg");

    Render* render = engine->GetRender();
    render->SetSkybox(g_skybox);
}

EXTERN void FixedUpdate() {
    Debug::Script("Run benchmark iteration...");

    CreateScene();
    CreateCamera();
    FullScene();
    FreeScene();

    Debug::Script("End benchmark iteration.");
}

EXTERN void Update(float dt) {

}

EXTERN void Close() {

}