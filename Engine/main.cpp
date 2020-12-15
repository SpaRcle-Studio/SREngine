//
// Created by Kiper220 on 16.11.2020.
//

#include <iostream>
#include <Debug.h>
#include <FileSystem/FileSystem.h>
#include <ResourceManager/ResourceManager.h>
#include <Types/Mesh.h>
#include <Types/Texture.h>
#include <Input/Input.h>
#include <Window/Window.h>
#include <Environment/OpenGL.h>
#include <Loaders/ObjLoader.h>
#include <FileSystem/FileSystem.h>
#include <EntityComponentSystem/Scene.h>
#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Transform.h>
#include <Types/Skybox.h>

#include "UnitTests/UnitTests.h"

using namespace Framework::Helper;
using namespace Framework::Helper::Math;
using namespace Framework::Helper::Types;
using namespace Framework::Graphics;
using namespace Framework::Graphics::Types;

int main(){
    Debug::Init(FileSystem::GetPathToExe(), true, Debug::Theme::Dark);
    Debug::SetLevel(Debug::Level::Low);
    ResourceManager::Init(FileSystem::GetPathToExe() + "/../../Resources");

    ResourceManager::RegisterType("Mesh");
    ResourceManager::RegisterType("Texture");

    Environment::Set(new OpenGL());

    Scene* scene = Scene::New("New scene");

    Render* render = new Render();

    WindowFormat format = WindowFormat::_1280_720;
    Window* window = new Window(
            "SpaRcle Engine",
            format,
            render,
            false,
            false,
            4
            );

    GameObject* camera_gm = scene->Instance("Camera");

    Camera* camera = new Camera();
    {
        camera->UpdateProjection(format.Width(), format.Height());

        camera->GetPostProcessing()->SetBloom(true);
        camera->GetPostProcessing()->SetBloomIntensity(3.5f);
        camera->GetPostProcessing()->SetBloomAmount(10);
        camera->GetPostProcessing()->SetGamma(0.9);
        camera->GetPostProcessing()->SetExposure(1.0);
        camera->SetActive(true);

        camera_gm->AddComponent(camera);

        window->AddCamera(camera);
    }

    window->Create();
    window->Init();

    if (window->Run()) {
        Debug::System("All systems successfully run!");

        if (!TestProgram(window, render, scene)) {
            Debug::Error("Failed testing program! Exit...");

            return Debug::Stop();
        }

        Debug::System("All tests successfully completed!");
    }

    Skybox* skybox = Skybox::Load("Sea.jpg");
    render->SetSkybox(skybox);

    Mesh *mesh = Mesh::Load("cube.obj")[0];
    Texture *texture = Texture::Load("steel_cube.png", true, TextureType::Diffuse, TextureFilter::LINEAR);
    render->RegisterTexture(texture);

    mesh->GetMaterial()->SetDiffuse(texture);
    mesh->GetMaterial()->SetBloom(true);

    /*
    GameObject* cube = scene->Instance("Cube");
    {
        mesh->GetMaterial()->SetColor(Material::GetRandomColor() * 6.f);
        render->RegisterMesh(mesh);
        cube->AddComponent(mesh);
    }

    cube->GetTransform()->Translate(Transform::Forward * 5.f);
    cube->GetTransform()->Translate(Transform::Right * 5.f);*/

    //scene->Destroy(cube);

    //std::cout << cube->Save().dump(4) << std::endl;

    for (int x = -1; x < 10; x++) {
        for (int y = -1; y < 10; y++) {
            for (int z = -1; z < 10; z++) {
                Mesh *copy = nullptr;
                if (x == -1 && y == -1 && z == -1)
                    copy = mesh;
                else
                    copy = mesh->Copy();

                copy->OnMove(glm::vec3(5 * x, 5 * y, 5 * z));
                //copy->OnRotate(Material::GetRandomColor() * 360.f);
                //copy->OnScaled(Material::GetRandomColor()* 2.f);
                copy->GetMaterial()->SetColor(Material::GetRandomColor() * 7.f);

                render->RegisterMesh(copy);

                GameObject *cube = scene->Instance(
                        "Cube " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z));
                cube->AddComponent(copy);
            }
        }
    }

    while(!GetKeyDown(KeyCode::F) && window->IsWindowOpen() && window->IsRun()) {
        if (camera_gm) {
            static float y = 0;
            static float x = 0;
            static float z = 0;
            static glm::vec2 old_pos;
            static glm::vec2 pos;
            static bool  mouse = false;

            if (GetKey(KeyCode::Q))         z += 0.001f;
            else if (GetKey(KeyCode::E))    z -= 0.001f;

            if (mouse) {
                old_pos = Input::GetMousePos();
                window->CentralizeCursor();
                pos = Input::GetMousePos();

                x += (float)(old_pos.x - pos.x) / 25.f;
                y += (float)(old_pos.y - pos.y) / 25.f;
            }
            else {
                mouse = true;
                window->CentralizeCursor();
                old_pos = Input::GetMousePos();
            }

            camera_gm->GetTransform()->SetRotation({y, x, z});

            if (GetKey(KeyCode::D))
                camera_gm->GetTransform()->Translate(Transform::Right / 5000.f);
            else if (GetKey(KeyCode::A))
                camera_gm->GetTransform()->Translate(-Transform::Right / 5000.f);

            if (GetKey(KeyCode::W))
                camera_gm->GetTransform()->Translate(Transform::Forward / 5000.f);
            else if (GetKey(KeyCode::S))
                camera_gm->GetTransform()->Translate(-Transform::Forward / 5000.f);

            if (GetKey(KeyCode::Space))
                camera_gm->GetTransform()->Translate(Transform::Up / 5000.f);
            else if (GetKey(KeyCode::LShift))
                camera_gm->GetTransform()->Translate(-Transform::Up / 5000.f);
        }

        if (camera_gm) {
            if (GetKey(KeyCode::B))
                camera->GetPostProcessing()->SetDisplayBloomMask(true);
            else
                camera->GetPostProcessing()->SetDisplayBloomMask(false);

            if (GetKeyDown(KeyCode::I)){
                scene->Destroy(camera_gm);
                camera_gm = nullptr;
            }
        }

        if (GetKeyDown(KeyCode::O)) {
            //if (mesh) { mesh->Destroy();mesh = nullptr;}
        }

        if (GetKey(KeyCode::L)) {
            //std::vector<Mesh *> meshes1 = Mesh::Load("cube.obj");
            //for (auto a : meshes1)
            //    a->Destroy();

            /*if (mesh) {
                GameObject *cube = scene->Instance("Cube");
                {
                    Mesh *copy = mesh->Copy();

                    render->RegisterMesh(copy);
                    cube->AddComponent(copy);
                }
                scene->Destroy(cube);
            }*/
        }

        if (GetKey(KeyCode::T)) {
            /*
            Mesh *mesh = Mesh::Load("cube.obj")[0];
            Texture *texture = Texture::Load("steel_cube.png", true, TextureType::Diffuse, TextureFilter::NEAREST);
            render->RegisterTexture(texture);

            mesh->GetMaterial()->SetDiffuse(texture);
            mesh->GetMaterial()->SetBloom(true);
            mesh->GetMaterial()->SetColor(Material::GetRandomColor() * 7.f);

            GameObject* cube = scene->Instance("Cube");
            {
                render->RegisterMesh(mesh);
                cube->AddComponent(mesh);
            }

            scene->Destroy(cube);
            */

            /*
            auto time = clock();

            std::vector<Mesh *> copy = Mesh::Load("monkey.obj");
            std::cout << clock() - time << std::endl;

            for (auto a : copy)
                render->RegisterMesh(a);

            size_t count = 0;
            for (auto a : copy)
                count += a->GetCountVertices();
            std::cout << "Count vertices: " << count << std::endl;

            time = clock();

            for (int i = 0; i < 100000; i++) {
                for (auto a : copy)
                    render->RegisterMesh(a);
                for (auto a : copy)
                    render->RemoveMesh(a);
            }

            for (auto a : copy)
                render->RemoveMesh(a);

            for (auto a : copy)
                a->Destroy();

            std::cout << clock() - time << std::endl;
             */
        }

        /*
        if (GetKeyDown(KeyCode::O)) {
            auto time = clock();

            std::vector<Mesh *> copy = Mesh::Load("monkey.obj");
            std::cout << clock() - time << std::endl;

            size_t count = 0;
            for (auto a : copy)
                count += a->GetCountVertices();
            std::cout << "Count vertices: " << count << std::endl;

            time = clock();

            for (int i = 0; i < 1000000; i++) {
                for (auto a : copy)
                    render->RegisterMesh(a);
                for (auto a : copy)
                    render->RemoveMesh(a);
            }
            for (auto a : copy)
                a->Destroy();

            std::cout << clock() - time << std::endl;
        }*/

        if (GetKeyDown(KeyCode::M)) {
            ResourceManager::PrintMemoryDump();

            std::string str = "\n================== [ RENDER DUMP ] =================="
                              "\nCount meshes to remove: "+ std::to_string(render->GetCountMeshesToRemove()) +
                              "\nCount new meshes: "+ std::to_string(render->GetCountNewMeshes()) +
                              "\nCount meshes: " + std::to_string(render->GetCountMeshes());
            Debug::System(str);
        }
    }

    scene->Destroy();
    scene->Free();

    window->Close();

    Debug::System("All systems successfully closed!");

    ResourceManager::Stop();
    return Debug::Stop();
}
