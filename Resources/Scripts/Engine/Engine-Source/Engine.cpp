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

SafePtr<Scene> g_scene;
SafePtr<GameObject> g_camera;

Skybox*     g_skybox = nullptr;
Window*     g_window = nullptr;

EXTERN void Awake() {

}

EXTERN void Start() {
    Engine* engine = Engine::Get();
    g_scene = Scene::New("New scene");
    engine->SetScene(g_scene);

    Vector2 size = { 1366, 768 };

    g_window = engine->GetWindow();
    g_window->SetGUIEnabled(false);
    //g_window->Resize(848, 480);
    g_window->Resize(size.x, size.y);
    g_window->CentralizeWindow();

    g_skybox = Skybox::Load("Sea.jpg");

    Render* render = engine->GetRender();
    render->SetSkybox(g_skybox);

    auto body = Texture::Load("Miku_Bodytex_DM.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    auto face = Texture::Load("Miku_Facetex_A.png", TextureFormat::RGBA8_UNORM, true, TextureType::Diffuse, TextureFilter::LINEAR, TextureCompression::None, 1);
    render->RegisterTexture(body);
    render->RegisterTexture(face);

    std::vector<Texture*> textures = {
        body, body, face, face, body, body
    };

    auto fbx_meshes = Mesh::Load("Miku.fbx");

    auto miku = g_scene->Instance("Miku");

    for (uint32_t i = 0; i < 6; i++) {
        Mesh* mesh = fbx_meshes[i];
        Texture* texture = textures[i];

        render->RegisterMesh(mesh);
        mesh->WaitCalculate();
        mesh->GetMaterial()->SetDiffuse(texture);
        auto cube = g_scene->Instance(mesh->GetGeometryName());
        cube->AddComponent(mesh);

        miku->AddChild(cube);
    }

    /*Mesh* mesh = Mesh::Load("engine/cube.obj")[0];
    for (uint32_t i = 0; i < 1; i++) {
        for (uint32_t j = 0; j < 1; j++) {
            if (i != 0 && j != 0)
                mesh = mesh->Copy();

            render->RegisterMesh(mesh);
            mesh->WaitCalculate();
            mesh->GetMaterial()->SetDiffuse(texture);
            GameObject *cube = g_scene->Instance("Cube");
            cube->AddComponent(mesh);
            cube->GetTransform()->Translate(cube->GetTransform()->Forward() * 4.f * i + cube->GetTransform()->Right() * 4.f * j);
        }
    }*/


    Camera* camera = Camera::Allocate(size.x, size.y);
    camera->SetDirectOutput(true);
    g_window->AddCamera(camera);
    g_camera = g_scene->Instance("Camera");
    g_camera->AddComponent(camera);
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