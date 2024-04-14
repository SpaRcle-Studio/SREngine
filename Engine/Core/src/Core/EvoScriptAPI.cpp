//
// Created by Nikita on 11.07.2021.
//

#include <Core/EvoScriptAPI.h>
#include <Core/Engine.h>

#include <EvoScript/Compilation/CMakeCodeGen.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/Math/Noise.h>
#include <Utils/ECS/TransformZero.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/Resources/ResourceManager.h>

#include <Graphics/Loaders/ObjLoader.h>
#include <Graphics/Types/Skybox.h>
#include <Graphics/Font/Text2D.h>
#include <Graphics/Font/Text3D.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>

#include <Physics/3D/Rigidbody3D.h>
#include <Physics/3D/Raycast3D.h>

namespace SpaRcle {
    void API::RegisterEvoScriptClasses(SR_CORE_NS::Engine* pEngine) {
        Initialize();

        auto&& compiler = SR_SCRIPTING_NS::GlobalEvoCompiler::Instance();
        auto&& generator = compiler.GetGenerator();
        auto&& casts = compiler.GetCasting();

        if (generator) {
            generator->SetPointer<SR_CORE_NS::Engine>(pEngine);

            RegisterScene(generator);
            RegisterDebug(generator);
            RegisterEngine(generator);
            RegisterComponent(generator);
            RegisterUtils(generator);
            RegisterMesh(generator);
            RegisterProceduralMesh(generator);
            RegisterResourceManager(generator);
            RegisterGameObject(generator);
            RegisterCamera(generator);
            RegisterShader(generator);
            RegisterWindow(generator);
            RegisterRender(generator);
            RegisterTransform(generator);
            RegisterInput(generator);
            RegisterSkybox(generator);
            RegisterTexture(generator);
            RegisterMaterial(generator);
            RegisterGUISystem(generator);
            RegisterRigidbody(generator);
            RegisterPostProcessing(generator);
            RegisterISavable(generator);
            RegisterObserver(generator);
            RegisterText(generator);
            RegisterMath(generator);
            RegisterRaycast(generator);

            generator->Save(SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Scripts/Libraries/"));
        }
        else {
            SR_ERROR("API::RegisterEvoScriptClasses() : generator is nullptr!");
        }

        if (casts) {
            RegisterCasts(casts);

            casts->Save(SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Scripts/Libraries/"));
        }
        else {
            SR_ERROR("API::RegisterEvoScriptClasses() : casts is nullptr!");
        }

        if (generator) {
            compiler.SetApiVersion(generator->GetApiVersion());
        }

        EvoScript::CMakeCodeGen::Generate(SR_UTILS_NS::ResourceManager::Instance().GetResPath().ToStringRef());
    }

    void API::RegisterDebug(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("Debug", "Debug", {"string"});

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Debug, Log, void, ESArg1(const std::string& msg), {
            SR_UTILS_NS::Debug::Instance().Log(msg);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Debug, Error, void, ESArg1(const std::string& msg), {
            SR_UTILS_NS::Debug::Instance().Error(msg);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Debug, Warn, void, ESArg1(const std::string& msg), {
            SR_UTILS_NS::Debug::Instance().Warn(msg);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Debug, Halt, void, ESArg1(const std::string& msg), {
            SR_UTILS_NS::Debug::Instance().Assert(msg);
        });

        //ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Warn, void, ESArg1(const std::string& msg), ESArg1(msg))
        //ESRegisterStaticMethod(EvoScript::Public, generator, Debug, System, void, ESArg1(const std::string& msg), ESArg1(msg))
        //ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Shader, void, ESArg1(const std::string& msg), ESArg1(msg))
        //ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Error, void, ESArg1(const std::string& msg), ESArg1(msg))
        //ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Info, void, ESArg1(const std::string& msg), ESArg1(msg))
        //ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Script, void, ESArg1(const std::string& msg), ESArg1(msg))
        //ESRegisterStaticMethod(EvoScript::Public, generator, Debug, ScriptError, void, ESArg1(const std::string& msg), ESArg1(msg))
        //ESRegisterStaticMethod(EvoScript::Public, generator, Debug, ScriptLog, void, ESArg1(const std::string& msg), ESArg1(msg))
    }

    void API::RegisterRaycast(EvoScript::AddressTableGen *generator){
        using namespace SR_UTILS_NS;
        using namespace SR_MATH_NS;
        using namespace SR_PHYSICS_NS;

        generator->RegisterNewClass("Raycast3D", "Raycast", {"string"});

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Raycast3D, Cast, std::vector<RaycastHit>, ESArg4(const FVector3& origin, const FVector3& direction, float_t maxDistance, uint32_t maxHits), {
            return Raycast3D::Instance().Cast(origin, direction, maxDistance, maxHits);
        });
    }

    void API::RegisterEngine(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_WORLD_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_GRAPH_NS;
        using namespace SR_CORE_NS;

        generator->RegisterNewClass("Engine", "Engine", { "Libraries/Window.h", "Libraries/Types/SharedPtr.h" });

        auto pEngine = generator->GetPointer<Engine>();

        ESRegisterCustomStaticMethodPassArg0(EvoScript::Public, generator, Engine, Instance, Engine&, pEngine, {
            return *pEngine;
        });

        //ESRegisterMethodArg0(EvoScript::Private, generator, Engine, RegisterLibraries, bool)
        //ESRegisterMethodArg0(EvoScript::Public, generator, Engine, Reload, void)
        //ESRegisterMethodArg0(EvoScript::Public, generator, Engine, GetScene, SafePtr<Scene>)
        //ESRegisterMethodArg0(EvoScript::Public, generator, Engine, IsRun, bool)
        //ESRegisterMethod(EvoScript::Public, generator, Engine, SetScene, bool, ESArg1(const SafePtr<Scene>& scene), ESArg1(scene))

        ESRegisterCustomMethodArg0(EvoScript::Public, generator, Engine, GetMainWindow, Window*, {
            return ptr->GetMainWindow().Get();
        })

        ESRegisterCustomMethodArg0(EvoScript::Public, generator, Engine, GetFramesPerSecond, uint32_t, {
            return ptr->GetRenderContext()->GetPipeline()->GetFramesPerSecond();
        })

        generator->RegisterTypedef("Time", "Engine", "void");
        generator->RegisterTypedef("PhysEngine", "Engine", "void");

        generator->AddIncompleteType("Scene", "Engine");
        generator->AddIncompleteType("Render", "Engine");
        generator->AddIncompleteType("Camera", "Engine");
    }

    void API::RegisterScene(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_MATH_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_WORLD_NS;

        generator->AddIncompleteType("Observer", "Scene");

        generator->RegisterNewClass("HierarchyElem", "Scene");

        generator->RegisterNewClass("SceneLogic", "Scene");

        generator->RegisterNewClass(
                "Scene", "Scene",
                { "map", "string", "mutex", "vector", "stdint.h", "set", "unordered_set", "Libraries/GameObject.h", "Libraries/Types/SafePointer.h", "Libraries/Observer.h" },
                { {"SafePtr<Scene>", EvoScript::Public } }
        );

        ESRegisterMethodArg0(EvoScript::Public, generator, Scene, GetName, std::string)
        ESRegisterMethod(EvoScript::Public, generator, Scene, Instance, SharedPtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, Scene, InstanceFromFile, SharedPtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, Scene, FindByComponent,  SharedPtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, Scene, Find, SharedPtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, Scene, FindOrInstance, SharedPtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethodArg0(EvoScript::Public, generator, Scene, GetLogicBase, SafePtr<SceneLogic>)
        ESRegisterStaticMethod(EvoScript::Public, generator, Scene, New, SafePtr<Scene>, ESArg1(const std::string& name), ESArg1(name))

        generator->RegisterNewClass("SceneCubeChunkLogic", "Scene");

        ESRegisterMethodArg0(EvoScript::Public, generator, SceneCubeChunkLogic, GetObserver, Observer*)
        ESRegisterMethod(EvoScript::Public, generator, SceneCubeChunkLogic, GetRegionAndChunk, ESMakePair(IVector3, IVector3), ESArg1(const FVector3& position), ESArg1(position))
        ESRegisterMethod(EvoScript::Public, generator, SceneCubeChunkLogic, GetWorldPosition, FVector3, ESArg2(const IVector3& region, const IVector3& chunk), ESArg2(region, chunk))
        ESRegisterMethod(EvoScript::Public, generator, SceneCubeChunkLogic, IsChunkLoaded, bool, ESArg2(const IVector3& region, const IVector3& chunk), ESArg2(region, chunk))
        ESRegisterMethod(EvoScript::Public, generator, SceneCubeChunkLogic, ScopeCheckFunction, bool, ESArg3(int32_t x, int32_t y, int32_t z), ESArg3(x, y, z))
    }

    void API::RegisterUtils(EvoScript::AddressTableGen *generator) {

    }

    void API::RegisterComponent(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_MATH_NS;
        using namespace SR_HTYPES_NS;

        generator->RegisterNewClass("Component", "Component", { "Libraries/Math/Vector3.h", "string" });

        ESRegisterCustomMethodArg0(EvoScript::Public, generator, Component, GetComponentName, std::string, {
            return ptr->GetComponentName();
        })

        ESRegisterMethodArg0(EvoScript::Public, generator, Component, BaseComponent, Component*)
        ESRegisterMethodArg0(EvoScript::Public, generator, Component, GetGameObject, SharedPtr<GameObject>)
        ESRegisterMethodArg0(EvoScript::Public, generator, Component, GetBarycenter, FVector3)

        ESRegisterMethodArg0(EvoScript::Public, generator, Component, IsActive, bool)

        ESRegisterMethod(EvoScript::Public, generator, Component, SetEnabled, void, ESArg1(bool v), ESArg1(v))

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Component, Create, Component*, ESArg1(const std::string& name), {
            return SR_UTILS_NS::ComponentManager::Instance().CreateComponentOfName(name);
        });

        generator->AddIncompleteType("GameObject", "Component");
    }

    void API::RegisterResourceManager(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("IResource", "ResourceManager", { "string" });
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, Destroy, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, GetCountUses, unsigned int)
    }

    void API::RegisterMesh(EvoScript::AddressTableGen *generator) {
        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;
        using namespace SR_GTYPES_NS;
        using namespace SR_GRAPH_NS;

        generator->AddIncompleteType("Mesh", "Mesh");

        generator->RegisterEnum("MeshType", "Mesh", true, {
                { "Unknown",    0 },
                { "Static",     1 },
                { "Wireframe",  2 },
                { "Skinned",    3 },
                { "Sprite",   4 },
                { "Procedural", 5 },
        });

        generator->RegisterNewClass("Mesh", "Mesh", {
            "Libraries/ResourceManager.h", "Libraries/Component.h", "Libraries/Math/Vector3.h", "Libraries/Material.h"
        }, { });

        ESRegisterStaticMethod(EvoScript::Public, generator, Mesh, Load, std::vector<Mesh*>, ESArg2(const std::string& path, MeshType type), ESArg2(path, type))

        ESRegisterMethod(EvoScript::Public, generator, Mesh, SetMaterial, void, ESArg1(Material* material), ESArg1(material))
        ESRegisterMethodArg0(EvoScript::Public, generator, Mesh, GetGeometryName, std::string)
        ESRegisterMethodArg0(EvoScript::Public, generator, Mesh, GetMaterial, Material*)
    }

    void API::RegisterProceduralMesh(EvoScript::AddressTableGen *generator) {
        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;
        using namespace SR_GTYPES_NS;
        using namespace SR_GRAPH_NS::Vertices;

        generator->RegisterNewClass("ProceduralMesh", "ProceduralMesh", {
            "Libraries/ResourceManager.h", "Libraries/Component.h", "Libraries/Math/Vector3.h", "Libraries/Material.h", "Libraries/Math/Vertices.h"
        }, { { "IResource", EvoScript::Public }, { "Component", EvoScript::Public } });

        ESRegisterMethod(EvoScript::Public, generator, ProceduralMesh, SetMaterial, void, ESArg1(Material* material), ESArg1(material))
        ESRegisterMethodArg0(EvoScript::Public, generator, ProceduralMesh, GetGeometryName, std::string)
        ESRegisterMethodArg0(EvoScript::Public, generator, ProceduralMesh, GetMaterial, Material*)
        ESRegisterMethod(EvoScript::Public, generator, ProceduralMesh, SetVertices, void, ESArg1(const std::vector<StaticMeshVertex>& vertices), ESArg1(vertices))
        ESRegisterMethod(EvoScript::Public, generator, ProceduralMesh, SetIndexedVertices, void, ESArg2(void* pData, uint64_t count), ESArg2(pData, count))
        ESRegisterMethod(EvoScript::Public, generator, ProceduralMesh, SetIndices, void, ESArg2(void* pData, uint64_t count), ESArg2(pData, count))
    }

    void API::RegisterGameObject(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_MATH_NS;
        using namespace SR_WORLD_NS;

        generator->RegisterNewClass("GameObject", "GameObject",
                { "Libraries/Math/Vector3.h", "string", "Libraries/Transform.h", "vector", "mutex", "Libraries/Component.h", "Libraries/Types/SafePointer.h", "Libraries/Types/SharedPtr.h", "Libraries/ISavable.h" },
        { { "SharedPtr<GameObject>", EvoScript::Public } });

        ESRegisterMethod(EvoScript::Public, generator, GameObject, AddComponent, bool, ESArg1(Component* comp), ESArg1(comp))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, AddChild, bool, ESArg1(const SharedPtr<GameObject>& child), ESArg1(child))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, GetComponent, Component*, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, Find, SharedPtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, SetName, void, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, GetOrCreateComponent, Component*, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, SetTransform, void, ESArg1(Transform* pTransform), ESArg1(pTransform))
        ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetBarycenter, FVector3)
        ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetName, std::string)
        ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetTagString, std::string)
        ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetTransform, Transform*)
        ESRegisterCustomMethodArg0(EvoScript::Public, generator, GameObject, GetScene, SafePtr<Scene>, {
            return ptr->GetScene()->GetThis();
        })
        ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetChildrenRef, std::vector<SharedPtr<GameObject>>&)

        using namespace Xml;

        generator->AddIncompleteType("Scene", "GameObject");
    }

    void API::RegisterCamera(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Camera", "Camera",
                { "Libraries/Math/Vector3.h", "Libraries/Math/Vector2.h", "Libraries/Component.h" }, {
                { "Component", EvoScript::Public }
        });

        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;
        using namespace SR_GTYPES_NS;

        //ESRegisterMethod(EvoScript::Private, generator, Camera, OnRotate, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        //ESRegisterMethod(EvoScript::Private, generator, Camera, OnMove, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
    }

    void API::RegisterRigidbody(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Rigidbody3D", "Rigidbody3D",
                { "Libraries/Math/Vector3.h", "Libraries/Math/Vector2.h", "Libraries/Component.h" }, {
                { "Component", EvoScript::Public }
        });

        using namespace SR_MATH_NS;
        using namespace SR_PHYSICS_NS::Types;

        ESRegisterMethod(EvoScript::Public, generator, Rigidbody3D, AddLinearVelocity, void, ESArg1(const FVector3& velocity), ESArg1(velocity))
        ESRegisterMethod(EvoScript::Public, generator, Rigidbody3D, AddAngularVelocity, void, ESArg1(const FVector3& velocity), ESArg1(velocity))
        ESRegisterMethod(EvoScript::Public, generator, Rigidbody3D, SetLinearVelocity, void, ESArg1(const FVector3& velocity), ESArg1(velocity))
        ESRegisterMethod(EvoScript::Public, generator, Rigidbody3D, SetAngularVelocity, void, ESArg1(const FVector3& velocity), ESArg1(velocity))
        ESRegisterMethodArg0(EvoScript::Public, generator, Rigidbody3D, GetLinearVelocity, FVector3)
        ESRegisterMethodArg0(EvoScript::Public, generator, Rigidbody3D, GetAngularVelocity, FVector3)

        generator->RegisterNewClass("Rigidbody", "Rigidbody",
                { "Libraries/Math/Vector3.h", "Libraries/Math/Vector2.h", "Libraries/Component.h" }, {
                { "Component", EvoScript::Public }
        });
    }

    void API::RegisterRender(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Render", "Render",
                { "vector", "mutex", "stdint.h", "map", "Libraries/Skybox.h", "Libraries/Texture.h", "Libraries/Shader.h" });

        //ESRegisterMethod(EvoScript::Public, generator, Render, SetSkybox, void, ESArg1(Skybox* skybox), ESArg1(skybox))
        //ESRegisterMethod(EvoScript::Public, generator, Render, RegisterMesh, void, ESArg1(Mesh* mesh), ESArg1(mesh))
        //ESRegisterMethod(EvoScript::Public, generator, Render, RegisterTexture, void, ESArg1(Texture* texture), ESArg1(texture))

        generator->AddIncompleteType("Window", "Render");
        generator->AddIncompleteType("Camera", "Render");
        generator->AddIncompleteType("Mesh", "Render");
    }

    void API::RegisterWindow(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Window", "Window", { "thread", "vector", "mutex", "stdint.h", "Libraries/Math/Vector2.h" });

        using namespace SR_MATH_NS;
        using namespace SR_GRAPH_NS;

        //ESRegisterMethod(EvoScript::Public, generator, Window, SetGUIEnabled, void, ESArg1(bool v), ESArg1(v))
        //ESRegisterMethod(EvoScript::Public, generator, Window, Resize, void, ESArg2(uint32_t w, uint32_t h), ESArg2(w, h))

        //ESRegisterMethodArg0(EvoScript::Public, generator, Window, Synchronize, void)
        //ESRegisterMethodArg0(EvoScript::Public, generator, Window, CentralizeWindow, void)
        ////ESRegisterMethodArg0(EvoScript::Public, generator, Window, GetWindowSize, IVector2)
        //ESRegisterMethodArg0(EvoScript::Public, generator, Window, IsGUIEnabled, bool)

        //ESRegisterMethodArg0(EvoScript::Public, generator, Window, GetFramesPerSecond, uint32_t)

        generator->AddIncompleteType("Camera", "Window");
        generator->AddIncompleteType("Mesh", "Window");
    }

    void API::RegisterTransform(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Transform", "Transform", { "vector", "mutex", "stdint.h", "Libraries/Math/Vector3.h", "Libraries/Math/Vector2.h" });

        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;

        ESRegisterMethod(EvoScript::Public, generator, Transform, Rotate, void, ESArg1(const FVector3& eulers), ESArg1(eulers))
        ESRegisterMethod(EvoScript::Public, generator, Transform, GlobalRotate, void, ESArg1(const FVector3& eulers), ESArg1(eulers))
        ESRegisterMethod(EvoScript::Public, generator, Transform, Translate, void, ESArg1(const FVector3& translation), ESArg1(translation))
        ESRegisterMethod(EvoScript::Public, generator, Transform, SetTranslation, void, ESArg1(const FVector3& translation), ESArg1(translation))
        ESRegisterMethod(EvoScript::Public, generator, Transform, SetRotation, void, ESArg1(const FVector3& eulerAngles), ESArg1(eulerAngles))
        ESRegisterMethodArg0(EvoScript::Public, generator, Transform, GetRotation, FVector3)

        ESRegisterMethodArg0(EvoScript::Public, generator, Transform, GetTranslation, FVector3)

        ESRegisterCustomStaticMethodArg0(EvoScript::Public, generator, Transform, NewHolder, Transform*, {
            return new TransformHolder();
        });

        ESRegisterCustomStaticMethodArg0(EvoScript::Public, generator, Transform, NewZero, Transform*, {
            return new TransformZero();
        });

        ESRegisterCustomStaticMethodArg0(EvoScript::Public, generator, Transform, New2D, Transform*, {
            return new Transform2D();
        });

        ESRegisterCustomStaticMethodArg0(EvoScript::Public, generator, Transform, New3D, Transform*, {
            return new Transform3D();
        });
    }

    void API::RegisterInput(EvoScript::AddressTableGen *generator) {
        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("Input", "Input", { "Libraries/Math/Vector2.h" });
        // ESRegisterStaticMethodArg0(EvoScript::Public, generator, Input, GetMouseWheel, int)
        // ESRegisterStaticMethodArg0(EvoScript::Public, generator, Input, GetMouseDrag, FVector2)
        // ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKey, bool, ESArg1(KeyCode key), ESArg1(key))
        // ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKeyDown, bool, ESArg1(KeyCode key), ESArg1(key))
        // ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKeyUp, bool, ESArg1(KeyCode key), ESArg1(key))

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Input, GetKey, bool, ESArg1(KeyCode key), {
            return SR_UTILS_NS::Input::Instance().GetKey(key);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Input, LockCursor, void, ESArg1(bool lock), {
            SR_UTILS_NS::Input::Instance().LockCursor(lock);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Input, GetKeyDown, bool, ESArg1(KeyCode key), {
            return SR_UTILS_NS::Input::Instance().GetKeyDown(key);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Input, GetKeyUp, bool, ESArg1(KeyCode key), {
            return SR_UTILS_NS::Input::Instance().GetKeyUp(key);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Input, GetMouseDown, bool, ESArg1(MouseCode key), {
            return SR_UTILS_NS::Input::Instance().GetMouseDown(key);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Input, GetMouse, bool, ESArg1(MouseCode key), {
            return SR_UTILS_NS::Input::Instance().GetMouse(key);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Input, GetMouseUp, bool, ESArg1(MouseCode key), {
            return SR_UTILS_NS::Input::Instance().GetMouseUp(key);
        });

        ESRegisterCustomStaticMethodArg0(EvoScript::Public, generator, Input, GetMouseDrag, FVector2, {
            return SR_UTILS_NS::Input::Instance().GetMouseDrag();
        });

        generator->RegisterEnum("MouseCode", "Input", true, {
                { "MouseLeft",  1 },
                { "MouseRight", 2 },
                { "MouseMiddle", 4 },
        });

        generator->RegisterEnum("KeyCode", "Input", true, {
                { "BackSpace", 8 },
                { "Tab", 9 },
                { "Enter", 13 },
                { "LShift", 16 },
                { "Ctrl", 17 },
                { "Alt", 18 },
                { "Esc", 27 },
                { "Space", 32 },
                { "LeftArrow", 37 },
                { "UpArrow", 38 },
                { "RightArrow", 39 },
                { "DownArrow", 40 },
                { "Del", 46 },
                { "A", 65 },
                { "B", 66 },
                { "C", 67 },
                { "D", 68 },
                { "E", 69 },
                { "F", 70 },
                { "G", 71 },
                { "H", 72 },
                { "I", 73 },
                { "J", 74 },
                { "K", 75 },
                { "L", 76 },
                { "M", 77 },
                { "N", 78 },
                { "O", 79 },
                { "P", 80 },
                { "Q", 81 },
                { "S", 83 },
                { "R", 82 },
                { "T", 84 },
                { "U", 85 },
                { "V", 86 },
                { "W", 87 },
                { "X", 88 },
                { "Y", 89 },
                { "Z", 90 },
                { "F1", 112 },
                { "F2", 113 },
                { "F3", 114 },
                { "F4", 115 },
                { "F5", 116 },
                { "F6", 117 },
                { "F7", 118 },
                { "F8", 119 },
                { "F9", 120 },
                { "F10", 121 },
                { "F11", 122 },
                { "F12", 123 },
        });
    }

    void API::RegisterSkybox(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Skybox", "Skybox", { "stdint.h", "vector", "string", "array" });

        //ESRegisterStaticMethod(EvoScript::Public, generator, Skybox, Load, Skybox*, ESArg1(const std::string& path), ESArg1(path))
    }

    void API::RegisterTexture(EvoScript::AddressTableGen *generator) {
        generator->RegisterEnum("TextureCompression", "Texture", true, {
                { "None", 0 },
                { "BC1",  1 },
                { "BC2",  2 },
                { "BC3",  3 },
                { "BC4",  4 },
                { "BC5",  5 },
                { "BC6",  6 },
                { "BC7",  7 },
        });

        generator->RegisterEnum("ColorFormat", "Texture", true, {
                { "Unknown",          0 },
                { "RGBA8_UNORM",  10000 },
                { "RGBA16_UNORM", 10001 },
                { "RGBA8_SRGB",   20000 },
        });

        generator->RegisterEnum("TextureType", "Texture", true, {
                { "Unknown",    0 },
                { "Diffuse",    1 },
                { "Normal",     2 },
                { "Specular",   3 },
                { "Roughness",  4 },
                { "Glossiness", 5 },
        });

        generator->RegisterEnum("TextureFilter", "Texture", true, {
                { "Unknown",    0 },
                { "NEAREST",    1 },
                { "LINEAR",     2 },
        });

        generator->RegisterNewClass("Texture", "Texture",
                { "mutex", "stdint.h", "Libraries/ResourceManager.h", "string" },
                {{ "IResource", EvoScript::Public } });
        //ESRegisterMethodArg0(EvoScript::Private, generator, Texture, Destroy, bool) // IResource
        //ESRegisterStaticMethod(EvoScript::Public, generator, Texture, Load, Texture*, ESArg1(const std::string& name), ESArg1(name));
    }

    void API::RegisterMaterial(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Material", "Material", { "Libraries/Texture.h" });

        //ESRegisterStaticMethod(EvoScript::Public, generator, Material, Load, Material*, ESArg1(const std::string& name), ESArg1(name))

        generator->AddIncompleteType("Mesh", "Material");
    }

    void API::RegisterGUISystem(EvoScript::AddressTableGen *generator) {

    }

    void API::RegisterPostProcessing(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_WORLD_NS;

        generator->RegisterNewClass("PostProcessing", "PostProcessing", { "cstdint", "Libraries/Math/Vector3.h", "vector" });

        generator->AddIncompleteType("Shader", "PostProcessing");
        generator->AddIncompleteType("Camera", "PostProcessing");
        generator->AddIncompleteType("Render", "PostProcessing");
    }

    void API::RegisterISavable(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Document", "ISavable");
        generator->RegisterNewClass("ISavable", "ISavable");
    }

    void API::RegisterCasts(EvoScript::CastingGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_WORLD_NS;
        using namespace SR_MATH_NS;
        using namespace SR_GTYPES_NS;
        using namespace SR_PHYSICS_NS::Types;

        ESRegisterDynamicCast(generator, ProceduralMesh, Component)
        ESRegisterDynamicCast(generator, Rigidbody3D, Component)
        ESRegisterDynamicCast(generator, Rigidbody, Component)
        ESRegisterDynamicCast(generator, Text2D, Component)
        ESRegisterDynamicCast(generator, Text3D, Component)
        ESRegisterDynamicCast(generator, SceneLogic, SceneCubeChunkLogic)
    }

    void API::RegisterShader(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Shader", "Shader");
    }

    void API::RegisterBehaviour(EvoScript::AddressTableGen *generator) {

    }

    void API::RegisterObserver(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_WORLD_NS;
        using namespace SR_MATH_NS;

        generator->RegisterNewClass("Observer", "Observer", { "Libraries/Math/Vector2.h", "Libraries/Math/Vector3.h" });

        ESRegisterMethodArg0(EvoScript::Public, generator, Observer, GetRegion, IVector3)
        ESRegisterMethodArg0(EvoScript::Public, generator, Observer, GetChunk, IVector3)
        ESRegisterMethodArg0(EvoScript::Public, generator, Observer, GetChunkSize, IVector2)
        ESRegisterMethodArg0(EvoScript::Public, generator, Observer, GetRegionSize, int32_t)
        ESRegisterMethodArg0(EvoScript::Public, generator, Observer, GetScope, int32_t)
        ESRegisterMethodArg0(EvoScript::Public, generator, Observer, HasTarget, bool)
        ESRegisterCustomMethod(EvoScript::Public, generator, Observer, MathNeighbour, ESMakePair(IVector3, IVector3), ESArg1(const IVector3& offset), {
            auto&& neighbourOffset = ptr->MathNeighbour(offset);
            return std::make_pair(neighbourOffset.GetRegion(), neighbourOffset.GetChunk());
        });
    }

    void API::RegisterText(EvoScript::AddressTableGen* generator) {
        using namespace SR_GTYPES_NS;
        using namespace SR_GRAPH_NS;

       generator->RegisterNewClass("Text2D", "Text", {
           "Libraries/Component.h", "Libraries/Mesh.h"
       }, { { "Component", EvoScript::Public }, { "Mesh", EvoScript::Public  } });

        ESRegisterMethod(EvoScript::Public, generator, Text2D, SetText, void, ESArg1(const std::string& text), ESArg1(text))

       generator->RegisterNewClass("Text3D", "Text", {
           "Libraries/Component.h", "Libraries/Mesh.h"
       }, { { "Component", EvoScript::Public }, { "Mesh", EvoScript::Public  } });

       ESRegisterMethod(EvoScript::Public, generator, Text3D, SetText, void, ESArg1(const std::string& text), ESArg1(text))
    }

    void API::RegisterMath(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("Mathf", "Mathf", { "Libraries/Math/Vector2.h", "Libraries/Math/Vector3.h", "Libraries/Math/CoreMath.h" });

        class Mathf {

        };

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Mathf, SNoise2D, double_t, ESArg2(double_t x, double_t y), {
            return SR_MATH_NS::SNoise(x, y);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Mathf, SNoise3D, double_t, ESArg3(double_t x, double_t y, double_t z), {
            return SR_MATH_NS::SNoise(x, y, z);
        });

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Mathf, SNoise4D, double_t, ESArg4(double_t x, double_t y, double_t z, double_t t), {
            return SR_MATH_NS::SNoise(x, y, z, t);
        });
    }

    void API::Initialize() {
        EvoScript::Tools::ESDebug::Error = [](const std::string& msg) { SR_ERROR(msg); };
        EvoScript::Tools::ESDebug::Log   = [](const std::string& msg) { SR_LOG(msg);   };
        EvoScript::Tools::ESDebug::Warn  = [](const std::string& msg) { SR_WARN(msg);  };
        EvoScript::Tools::ESDebug::Info  = [](const std::string& msg) { SR_INFO(msg);  };

        EvoScript::Tools::ESFileSystem::Delete = [](const std::string& path) -> bool {
            return SR_PLATFORM_NS::Delete(path);
        };

        EvoScript::Tools::ESFileSystem::IsExists = [](const std::string& path) -> bool {
            return SR_PLATFORM_NS::IsExists(path);
        };

        EvoScript::Tools::ESFileSystem::CreateFolder = [](const std::string& path) -> bool {
            return SR_PLATFORM_NS::CreateFolder(path);
        };

        EvoScript::Tools::ESFileSystem::GetAllInDir = [](const std::string& path) -> std::vector<std::string> {
            std::vector<std::string> elements;
            auto&& cached = SR_PLATFORM_NS::GetInDirectory(path, SR_UTILS_NS::Path::Type::Undefined);
            for (auto&& element : cached) {
                elements.emplace_back(element);
            }
            return elements;
        };

        EvoScript::Tools::ESFileSystem::GetAllFoldersInDir = [](const std::string& path) -> std::vector<std::string> {
            std::vector<std::string> elements;
            auto&& cached = SR_PLATFORM_NS::GetInDirectory(path, SR_UTILS_NS::Path::Type::Folder);
            for (auto&& element : cached) {
                elements.emplace_back(element);
            }
            return elements;
        };

        EvoScript::Tools::ESFileSystem::GetAllFilesInDir = [](const std::string& path) -> std::vector<std::string> {
            std::vector<std::string> elements;
            auto&& cached = SR_PLATFORM_NS::GetInDirectory(path, SR_UTILS_NS::Path::Type::File);
            for (auto&& element : cached) {
                elements.emplace_back(element);
            }
            return elements;
        };

        EvoScript::Tools::ESFileSystem::Copy = [](const std::string& from, const std::string& to) -> bool {
            return SR_PLATFORM_NS::Copy(from, to);
        };
    }
}

