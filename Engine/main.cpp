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

#include <glm/gtx/string_cast.hpp>

#include "UnitTests/UnitTests.h"

using namespace Framework::Helper;
using namespace Framework::Helper::Math;
using namespace Framework::Helper::Types;
using namespace Framework::Graphics;
using namespace Framework::Graphics::Types;

int main() {
    Debug::Init(FileSystem::GetPathToExe(), true, Debug::Theme::Dark);
    Debug::SetLevel(Debug::Level::Low);
    ResourceManager::Init(FileSystem::GetPathToExe() + "/../../Resources");

    ResourceManager::RegisterType("Mesh");
    ResourceManager::RegisterType("Texture");

    Environment::Set(new OpenGL());

    Scene *scene = Scene::New("New scene");

    Render *render = new Render();

    WindowFormat format = WindowFormat::_1280_720;
    Window *window = new Window(
            "SpaRcle Engine",
            format,
            render,
            false,
            false,
            4
    );

    GameObject *camera_gm = scene->Instance("Camera");

    Camera *camera = new Camera();
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

    Skybox *skybox = Skybox::Load("Sea.jpg");
    render->SetSkybox(skybox);

    Mesh *mesh = Mesh::Load("cube.obj")[0];
    Mesh *monkey = Mesh::Load("monkey.obj")[0];

    Texture *texture = Texture::Load("steel_cube.png", true, TextureType::Diffuse, TextureFilter::LINEAR);
    //Texture *texture2 = Texture::Load("Cube_triangulate2.png", true, TextureType::Diffuse, TextureFilter::NEAREST);
    render->RegisterTexture(texture);
    //render->RegisterTexture(texture2);

    mesh->GetMaterial()->SetDiffuse(texture);
    mesh->GetMaterial()->SetBloom(true);


    GameObject *test = scene->Instance("CubeStatic");
    {
        Mesh *copy = mesh->Copy();
        render->RegisterMesh(copy);
        test->AddComponent(copy);
    }

    test->GetTransform()->Translate(Transform::right * 5.f);

    /*
    GameObject* cube1 = scene->Instance("Cube1");
    {
        mesh->GetMaterial()->SetColor(Material::GetRandomColor() * 6.f);
        render->RegisterMesh(mesh);
        cube1->AddComponent(mesh);
    }
    cube1->GetTransform()->Translate(Transform::forward * 5.f);

    camera_gm->AddChild(cube1);*/


    GameObject *MonkeyGM = scene->Instance("Monkey");
    {
        //Mesh* copy = mesh->Copy();
        monkey->GetMaterial()->SetColor(Material::GetRandomColor() * 6.f);
        monkey->GetMaterial()->SetDiffuse(texture);
        render->RegisterMesh(monkey);
        MonkeyGM->AddComponent(monkey);
    }
    //MonkeyGM->GetTransform()->Translate(Transform::right * -5.f + Transform::up * 3.f);
    MonkeyGM->GetTransform()->Translate(Transform::forward * 10.f);

    //cube2->GetTransform()->Rotate({ 0, 0, 45 });
    //cube1->AddChild(cube2);

    //camera_gm->AddChild(MonkeyGM);

    //std::cout << cube->Save().dump(4) << std::endl;

    /*
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
    }*/

    Transform *transform = MonkeyGM->GetTransform();
    //transform->SetPosition(Transform::forward * 5.f);
    //transform->RotateAround(camera_gm->GetTransform()->GetPosition(), {1,0,0}, 90.f);

    while (!GetKeyDown(KeyCode::F) && window->IsWindowOpen() && window->IsRun()) {
        //transform->LookAt(test->GetTransform()->GetPosition());
        //transform->LookAt(camera_gm->GetTransform()->GetPosition());
        //transform->SetRotation(Transform::pitch * -90.f);
        //transform->SetRotation(Transform::pitch * 90.f);
        // transform->SetRotation(Transform::yaw * -90.f);


        transform->RotateAround(camera_gm->GetTransform()->GetPosition(), {1,0,0}, 0.001f);

        //camera_gm->GetTransform()->LookAt(transform->GetPosition());

        if (GetKeyDown(KeyCode::_0)) {
            std::cout << glm::to_string(transform->GetPosition()) << std::endl;
            std::cout << glm::to_string(camera_gm->GetTransform()->GetPosition()) << std::endl;

            //std::cout << glm::to_string(transform->GetRotation()) << std::endl;
            //std::cout << glm::to_string(camera_gm->GetTransform()->GetRotation()) << std::endl;

            //std::cout << dist << std::endl;
        }

        /*
        if (GetKey(KeyCode::UpArrow)) {
            test->GetTransform()->Translate(test->GetTransform()->Forward() * 0.0005f);
        } else if (GetKey(KeyCode::DownArrow)) {
            test->GetTransform()->Translate(test->GetTransform()->Forward() * -0.0005f);
        }
        if (GetKey(KeyCode::LeftArrow)) {
            test->GetTransform()->Translate(test->GetTransform()->Right() * -0.0005f);
        } else if (GetKey(KeyCode::RightArrow)) {
            test->GetTransform()->Translate(test->GetTransform()->Right() * 0.0005f);
        }
        if (GetKey(KeyCode::Minus))
            test->GetTransform()->Translate(test->GetTransform()->Up() * -0.0005f);
        if (GetKey(KeyCode::Plus))
            test->GetTransform()->Translate(test->GetTransform()->Up() * 0.0005f);

        if (GetKeyDown(KeyCode::_1)) {
            transform->Rotate(Transform::yaw * -45.f);
        } else if (GetKeyDown(KeyCode::_2)) {
            transform->Rotate(Transform::yaw * 45.f);
        }

        if (GetKeyDown(KeyCode::_3)) {
            transform->Rotate(Transform::pitch * 45.f);
        } else if (GetKeyDown(KeyCode::_4)) {
            transform->Rotate(Transform::pitch * -45.f);
        }

        if (GetKeyDown(KeyCode::_5)) {
            transform->Rotate(Transform::roll * -45.f);
        } else if (GetKeyDown(KeyCode::_6)) {
            transform->Rotate(Transform::roll * 45.f);
        }

        float dist = transform->Distance(camera_gm->GetTransform());
        if (dist > 5.f) {
            //camera_gm->GetTransform()->Translate(camera_gm->GetTransform()->Forward() * 0.0005f);
            //transform->Translate(transform->Forward() * 0.0005f);
        }

        if (GetKey(KeyCode::P)) {
            transform->Translate(transform->Right() * 0.0005f);
        }

        */
        if (GetKey(KeyCode::L)) {
            //transform->Translate(Transform::forward);
            transform->Translate(transform->Forward() * 0.0005f);
            //std::cout << glm::to_string(transform->GetPosition()) << std::endl;
            //std::cout << glm::to_string(transform->GetRotation()) << std::endl;
        }

        if (camera_gm) {
            static float y = 0;
            static float old_x = 0.f;
            static float x = 0;
            static float old_y = 0.f;
            static float z = 0;
            static float old_z = 0.f;
            static glm::vec2 old_pos;
            static glm::vec2 pos;
            static bool mouse = false;

            if (GetKey(KeyCode::E)) z += 0.001f;
            else if (GetKey(KeyCode::Q)) z -= 0.001f;

            if (mouse) {
                old_pos = Input::GetMousePos();
                window->CentralizeCursor();
                pos = Input::GetMousePos();

                x += (float) (old_pos.x - pos.x) / 25.f;
                y -= (float) (old_pos.y - pos.y) / 25.f;
            } else {
                mouse = true;
                window->CentralizeCursor();
                old_pos = Input::GetMousePos();
            }

            if (x != old_x || y != old_y || z != old_x) {
                camera_gm->GetTransform()->SetRotation({y, x, z});

                old_x = x;
                old_y = y;
                old_z = z;
            }

            if (GetKey(KeyCode::W))
                camera_gm->GetTransform()->Translate(camera_gm->GetTransform()->Forward() / 5000.f);
            else if (GetKey(KeyCode::S))
                camera_gm->GetTransform()->Translate(-camera_gm->GetTransform()->Forward() / 5000.f);

            if (GetKey(KeyCode::D))
                camera_gm->GetTransform()->Translate(camera_gm->GetTransform()->Right() / 5000.f);
            else if (GetKey(KeyCode::A))
                camera_gm->GetTransform()->Translate(-camera_gm->GetTransform()->Right() / 5000.f);

            if (GetKey(KeyCode::Space))
                camera_gm->GetTransform()->Translate(camera_gm->GetTransform()->Up() / 5000.f);
            else if (GetKey(KeyCode::LShift))
                camera_gm->GetTransform()->Translate(-camera_gm->GetTransform()->Up() / 5000.f);
        }

        if (camera_gm) {
            if (GetKey(KeyCode::B))
                camera->GetPostProcessing()->SetDisplayBloomMask(true);
            else
                camera->GetPostProcessing()->SetDisplayBloomMask(false);

            if (GetKeyDown(KeyCode::I)) {
                scene->Destroy(camera_gm);
                camera_gm = nullptr;
            }
        }

        /*
        if (GetKey(KeyCode::L)) {
            //std::vector<Mesh *> meshes1 = Mesh::Load("cube.obj");
            //for (auto a : meshes1)
            //    a->Destroy();

            if (mesh) {
                GameObject *cube = scene->Instance("Cube");
                {
                    Mesh *copy = mesh->Copy();

                    render->RegisterMesh(copy);
                    cube->AddComponent(copy);
                }
                scene->Destroy(cube);
            }
        }*/

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
                              "\nCount meshes to remove: " + std::to_string(render->GetCountMeshesToRemove()) +
                              "\nCount new meshes: " + std::to_string(render->GetCountNewMeshes()) +
                              "\nCount meshes: " + std::to_string(render->GetCountMeshes());
            Debug::System(str);
        }
    }

    scene->Destroy();
    scene->Free();

    Sleep(100);

    window->Close();

    Debug::System("All systems successfully closed!");

    ResourceManager::Stop();
    return Debug::Stop();
}