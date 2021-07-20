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

#include <iostream>
#include <ctime>

GameObject* g_camera = nullptr;
Scene*      g_scene  = nullptr;
Skybox*     g_skybox = nullptr;

EXTERN void Awake() {

}

EXTERN void Start() {
    Engine* engine = Engine::Get();
    g_scene = Scene::New("New scene");
    engine->SetScene(g_scene);

    Window* window = engine->GetWindow();
    window->SetGUIEnabled(false);
    window->Resize(848, 480);
    window->CentralizeWindow();

    g_skybox = Skybox::Load("Sea.jpg");

    Render* render = engine->GetRender();
    render->SetSkybox(g_skybox);

    Texture* texture = Texture::Load("brickwall2.jpg", TextureFormat::RGBA8_SRGB, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    render->RegisterTexture(texture);

    Mesh* mesh = Mesh::Load("engine/cube.obj")[0];
    render->RegisterMesh(mesh);
    mesh->WaitCalculate();
    mesh->GetMaterial()->SetDiffuse(texture);
    GameObject* cube = g_scene->Instance("Cube");
    cube->AddComponent(mesh);
    cube->GetTransform()->Translate(-cube->GetTransform()->Forward() * 4.f);

    Camera* camera = Camera::Allocate(848, 480);
    camera->SetDirectOutput(true);
    window->AddCamera(camera);
    g_camera = g_scene->Instance("Camera");
    g_camera->AddComponent(camera);
}

void CameraMove(float dt) {
    auto dir = Input::GetMouseDrag() * dt * -1.0;
    auto wheel = Input::GetMouseWheel() * dt * -1.0;

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
                (up * dir.y * -1.0) + (right * dir.x)
        );
    }
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

    CameraMove(0.1f);
}

EXTERN void Update(float dt) {
    //Debug::ScriptLog("Update | " + std::to_string(dt) + " ms");
}

EXTERN void Close() {
    if (g_scene) {
        g_scene->Destroy();
        g_scene->Free();
    }
}