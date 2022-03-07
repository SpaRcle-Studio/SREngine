//
// Created by Nikita on 11.07.2021.
//

#include <EvoScriptAPI.h>

#include <Engine.h>
#include <Input/InputSystem.h>
#include <Loaders/ObjLoader.h>
#include <EntityComponentSystem/Transform.h>
#include <Types/Skybox.h>

#include <Debug.h>
#include <ResourceManager/ResourceManager.h>
#include <GUI/GUISystem.h>

namespace Framework {
    void API::RegisterEvoScriptClasses(Scripting::EvoCompiler* compiler)  {
        auto generator = compiler->GetGenerator();

        RegisterScene(generator);
        RegisterDebug(generator);
        RegisterEngine(generator);
        RegisterComponent(generator);
        RegisterUtils(generator);
        RegisterMesh(generator);
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
        RegisterPostProcessing(generator);
        RegisterISavable(generator);

        auto casts = compiler->GetCasting();

        RegisterCasts(casts);

        generator->Save(Helper::ResourceManager::Instance().GetResPath().Concat("/Scripts/Libraries/"));
        casts->Save(Helper::ResourceManager::Instance().GetResPath().Concat("/Scripts/Libraries/"));

        compiler->GetEvoScriptCompiler()->SetApiVersion(generator->GetApiVersion());
    }

    void API::RegisterDebug(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("Debug", "Debug", {"string"});
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Log, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Warn, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, System, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Shader, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Error, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Info, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, Script, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, ScriptError, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(EvoScript::Public, generator, Debug, ScriptLog, void, ESArg1(const std::string& msg), ESArg1(msg))
    }

    void API::RegisterEngine(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_WORLD_NS;
        using namespace SR_HTYPES_NS;

        generator->RegisterNewClass("Engine", "Engine", { "Window.h", "Types/SafePointer.h" });
        ESRegisterStaticMethodArg0(EvoScript::Public, generator, Engine, Instance, Engine&)
        ESRegisterMethodArg0(EvoScript::Private, generator, Engine, RegisterLibraries, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, Engine, Reload, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, Engine, GetTime, Time*)
        ESRegisterMethodArg0(EvoScript::Public, generator, Engine, GetWindow, Window*)
        ESRegisterMethodArg0(EvoScript::Public, generator, Engine, GetRender, Render*)
        ESRegisterMethodArg0(EvoScript::Public, generator, Engine, GetScene, SafePtr<Scene>)
        ESRegisterMethodArg0(EvoScript::Public, generator, Engine, IsRun, bool)
        ESRegisterMethod(EvoScript::Public, generator, Engine, SetScene, bool, ESArg1(const SafePtr<Scene>& scene), ESArg1(scene))

        generator->RegisterTypedef("Time", "Engine", "void");
        generator->RegisterTypedef("PhysEngine", "Engine", "void");

        generator->AddIncompleteType("Scene", "Engine");
        generator->AddIncompleteType("Render", "Engine");
        generator->AddIncompleteType("Camera", "Engine");
    }

    void API::RegisterScene(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_WORLD_NS;

        generator->RegisterNewClass("HierarchyElem", "Scene");

        generator->RegisterNewClass(
                "Scene", "Scene",
                { "map", "string", "mutex", "vector", "stdint.h", "set", "unordered_set", "GameObject.h", "Types/SafePointer.h" },
                { {"SafePtr<Scene>", EvoScript::Public } }
        );

        ESRegisterMethodArg0(EvoScript::Public, generator, Scene, Destroy, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, Scene, Free, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, Scene, GetName, std::string)
        ESRegisterMethodArg0(EvoScript::Public, generator, Scene, GetGameObjects, std::unordered_set<SafePtr<GameObject>>)
        ESRegisterMethodArg0(EvoScript::Public, generator, Scene, GetRootGameObjects, std::unordered_set<SafePtr<GameObject>>&)
        ESRegisterMethodArg0(EvoScript::Public, generator, Scene, GetSelected, SafePtr<GameObject>)
        ESRegisterMethod(EvoScript::Public, generator, Scene, SetObserver, void, ESArg1(const SafePtr<GameObject>& gm), ESArg1(gm))
        ESRegisterMethod(EvoScript::Public, generator, Scene, RemoveSelected, bool, ESArg1(const SafePtr<GameObject>& gm), ESArg1(gm))
        ESRegisterMethod(EvoScript::Public, generator, Scene, AddSelected, void, ESArg1(const SafePtr<GameObject>& gm), ESArg1(gm))
        ESRegisterMethod(EvoScript::Public, generator, Scene, Instance, SafePtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, Scene, FindByComponent,  SafePtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))

        ESRegisterStaticMethod(EvoScript::Public, generator, Scene, New, SafePtr<Scene>, ESArg1(const std::string& name), ESArg1(name))
    }

    void API::RegisterUtils(EvoScript::AddressTableGen *generator) {

    }

    void API::RegisterComponent(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_MATH_NS;

        generator->RegisterNewClass("Component", "Component", { "Math/Vector3.h", "string" });
        ESRegisterMethodArg0(EvoScript::Public, generator, Component, GetComponentName, std::string)

        ESRegisterMethodArg0(EvoScript::Public, generator, Component, BaseComponent, Component*)
        ESRegisterMethodArg0(EvoScript::Public, generator, Component, GetParent, GameObject*)
        ESRegisterMethodArg0(EvoScript::Public, generator, Component, GetBarycenter, FVector3)
        ESRegisterMethodArg0(EvoScript::Public, generator, Component, OnAttachComponent, void)

        ESRegisterMethodArg0(EvoScript::Public, generator, Component, IsActive, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, Component, IsSelected, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, Component, IsReady, bool)

        ESRegisterMethodArg0(EvoScript::Protected, generator, Component, OnRemoveComponent, void)
        ESRegisterMethodArg0(EvoScript::Protected, generator, Component, OnDestroyGameObject, void)

        ESRegisterMethod(EvoScript::Public, generator, Component, SetParent, void, ESArg1(GameObject* gm), ESArg1(gm))
        ESRegisterMethod(EvoScript::Public, generator, Component, OnRotate, void, ESArg1(const FVector3& v), ESArg1(v))
        ESRegisterMethod(EvoScript::Public, generator, Component, OnMove, void, ESArg1(const FVector3& v), ESArg1(v))
        ESRegisterMethod(EvoScript::Public, generator, Component, OnScaled, void, ESArg1(const FVector3& v), ESArg1(v))
        ESRegisterMethod(EvoScript::Public, generator, Component, OnSelected, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethod(EvoScript::Public, generator, Component, OnReady, void, ESArg1(bool v), ESArg1(v))

        ESRegisterMethod(EvoScript::Public, generator, Component, SetActive, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethod(EvoScript::Public, generator, Component, SetEnabled, void, ESArg1(bool v), ESArg1(v))


        generator->AddIncompleteType("GameObject", "Component");
    }

    void API::RegisterResourceManager(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("IResource", "ResourceManager", {"string"});
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, IsEnabledAutoRemove, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, Destroy, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, IsDestroy, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, AddUsePoint, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, RemoveUsePoint, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, GetCountUses, unsigned int)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, GetResourceName, const char*)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, GetResourceId, std::string)
    }

    void API::RegisterMesh(EvoScript::AddressTableGen *generator) {
        using namespace SR_MATH_NS;

        generator->AddIncompleteType("Mesh", "Mesh");

        generator->RegisterEnum("MeshType", "Mesh", true, {
                { "Unknown",    0 },
                { "Static",     1 },
                { "Wireframe",  2 },
                { "Skinned",    3 },
        });

        generator->RegisterNewClass("Mesh", "Mesh", {
            "ResourceManager.h", "Component.h", "mutex", "Math/Vector3.h", "Material.h"
        }, { { "IResource", EvoScript::Public }, { "Component", EvoScript::Public } });

        ESRegisterStaticMethod(EvoScript::Public, generator, Mesh, Load, std::vector<Mesh*>, ESArg2(const std::string& path, MeshType type), ESArg2(path, type))

        ESRegisterMethod(EvoScript::Public, generator, Mesh, Copy, IResource*, ESArg1(IResource* dest), ESArg1(dest))

        ESRegisterMethod(EvoScript::Public, generator, Mesh, OnMove, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        ESRegisterMethod(EvoScript::Public, generator, Mesh, OnRotate, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        ESRegisterMethod(EvoScript::Public, generator, Mesh, OnScaled, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        ESRegisterMethod(EvoScript::Public, generator, Mesh, OnSelected, void, ESArg1(bool v), ESArg1(v)) // Component
        ESRegisterMethod(EvoScript::Public, generator, Mesh, SetShader, void, ESArg1(Shader* shader), ESArg1(shader))
        ESRegisterMethod(EvoScript::Public, generator, Mesh, SetMaterial, void, ESArg1(Material* material), ESArg1(material))

        ESRegisterMethodArg0(EvoScript::Public, generator, Mesh, WaitCalculate, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, Mesh, IsCanCalculate, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, Mesh, GetGeometryName, std::string)
        ESRegisterMethodArg0(EvoScript::Public, generator, Mesh, GetMaterial, Material*)
        ESRegisterMethodArg0(EvoScript::Public, generator, Mesh, Destroy, bool) // IResource


        generator->AddIncompleteType("Render", "Mesh");
    }

    void API::RegisterGameObject(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_MATH_NS;

        generator->RegisterNewClass("GameObject", "GameObject",
                { "Math/Vector3.h", "string", "vector", "mutex", "Component.h", "Types/SafePointer.h", "ISavable.h" },
        { { "SafePtr<GameObject>", EvoScript::Public } });

        ESRegisterMethod(EvoScript::Public, generator, GameObject, AddComponent, bool, ESArg1(Component* comp), ESArg1(comp))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, AddChild, bool, ESArg1(const SafePtr<GameObject>& child), ESArg1(child))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, GetComponent, Component*, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetBarycenter, FVector3)
        ///ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetTransform, Transform*)

        using namespace Xml;

        generator->AddIncompleteType("Scene", "GameObject");
    }

    void API::RegisterCamera(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Camera", "Camera",
                { "Math/Vector3.h", "Math/Vector2.h", "Component.h", "PostProcessing.h" }, {
                { "Component", EvoScript::Public }
        });

        using namespace SR_MATH_NS;

        ESRegisterStaticMethod(EvoScript::Public, generator, Camera, Allocate, Camera*, ESArg2(uint32_t w, uint32_t h), ESArg2(w, h))

        ESRegisterMethodArg0(EvoScript::Public, generator, Camera, GetPostProcessing, PostProcessing*)
        ESRegisterMethodArg0(EvoScript::Public, generator, Camera, IsDirectOutput, bool)
        ESRegisterMethodArg0(EvoScript::Private, generator, Camera, OnRemoveComponent, void) // Component
        ESRegisterMethodArg0(EvoScript::Private, generator, Camera, OnDestroyGameObject, void) // Component
        ESRegisterMethodArg0(EvoScript::Private, generator, Camera, OnAttachComponent, void) // Component

        ESRegisterMethod(EvoScript::Public, generator, Camera, SetDirectOutput, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethod(EvoScript::Private, generator, Camera, OnRotate, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        ESRegisterMethod(EvoScript::Private, generator, Camera, OnMove, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        ESRegisterMethod(EvoScript::Private, generator, Camera, OnReady, void, ESArg1(bool v), ESArg1(v)) // Component
    }

    void API::RegisterRender(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Render", "Render",
                { "vector", "mutex", "stdint.h", "map", "Skybox.h", "Texture.h", "Shader.h" });

        ESRegisterMethod(EvoScript::Public, generator, Render, FindShader, Shader*, ESArg1(uint32_t id), ESArg1(id))

        ESRegisterMethod(EvoScript::Public, generator, Render, SetSkybox, void, ESArg1(Skybox* skybox), ESArg1(skybox))
        ESRegisterMethod(EvoScript::Public, generator, Render, RegisterMesh, void, ESArg1(Mesh* mesh), ESArg1(mesh))
        ESRegisterMethod(EvoScript::Public, generator, Render, RegisterTexture, void, ESArg1(Texture* texture), ESArg1(texture))

        generator->AddIncompleteType("Window", "Render");
        generator->AddIncompleteType("Camera", "Render");
        generator->AddIncompleteType("Mesh", "Render");
    }

    void API::RegisterWindow(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Window", "Window", { "thread", "vector", "mutex", "stdint.h", "Math/Vector2.h" });

        using namespace SR_MATH_NS;

        ESRegisterMethod(EvoScript::Public, generator, Window, SetGUIEnabled, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethod(EvoScript::Public, generator, Window, AddCamera, void, ESArg1(Camera* camera), ESArg1(camera))
        ESRegisterMethod(EvoScript::Public, generator, Window, Resize, void, ESArg2(uint32_t w, uint32_t h), ESArg2(w, h))

        ESRegisterMethodArg0(EvoScript::Public, generator, Window, Synchronize, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, Window, CentralizeWindow, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, Window, GetWindowSize, IVector2)
        ESRegisterMethodArg0(EvoScript::Public, generator, Window, IsGUIEnabled, bool)

        generator->AddIncompleteType("Camera", "Window");
        generator->AddIncompleteType("Mesh", "Window");
    }

    void API::RegisterTransform(EvoScript::AddressTableGen *generator) {

    }

    void API::RegisterInput(EvoScript::AddressTableGen *generator) {
        using namespace SR_MATH_NS;

        generator->RegisterNewClass("Input", "Input", { "Math/Vector2.h" });
        ESRegisterStaticMethodArg0(EvoScript::Public, generator, Input, GetMouseWheel, int)
        ESRegisterStaticMethodArg0(EvoScript::Public, generator, Input, GetMouseDrag, FVector2)
        ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKey, bool, ESArg1(KeyCode key), ESArg1(key))
        ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKeyDown, bool, ESArg1(KeyCode key), ESArg1(key))
        ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKeyUp, bool, ESArg1(KeyCode key), ESArg1(key))

        generator->RegisterEnum("KeyCode", "Input", true, {
                { "MouseLeft",  1 },
                { "MouseRight", 2 },
                { "MouseMiddle", 4 },
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

        ESRegisterStaticMethod(EvoScript::Public, generator, Skybox, Load, Skybox*, ESArg1(const std::string& path), ESArg1(path))
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

        generator->RegisterEnum("TextureFormat", "Texture", true, {
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
                { "mutex", "stdint.h", "ResourceManager.h", "string" },
                {{ "IResource", EvoScript::Public } });
        ESRegisterMethodArg0(EvoScript::Private, generator, Texture, Destroy, bool) // IResource
        ESRegisterStaticMethod(EvoScript::Public, generator, Texture, Load, Texture*, ESArg1(const std::string& name), ESArg1(name));
    }

    void API::RegisterMaterial(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Material", "Material", { "Texture.h" });

        ESRegisterMethod(EvoScript::Public, generator, Material, SetDiffuse, void, ESArg1(Texture* texture), ESArg1(texture))
        ESRegisterMethod(EvoScript::Public, generator, Material, SetNormal, void, ESArg1(Texture* texture), ESArg1(texture))
        ESRegisterMethod(EvoScript::Public, generator, Material, SetSpecular, void, ESArg1(Texture* texture), ESArg1(texture))
        ESRegisterMethod(EvoScript::Public, generator, Material, SetGlossiness, void, ESArg1(Texture* texture), ESArg1(texture))
        ESRegisterMethod(EvoScript::Public, generator, Material, SetColor, void, ESArg3(float r, float g, float b), ESArg3(r, g, b))
        ESRegisterMethod(EvoScript::Public, generator, Material, Register, bool, ESArg1(Render* render), ESArg1(render))
        ESRegisterStaticMethod(EvoScript::Public, generator, Material, Load, Material*, ESArg1(const std::string& name), ESArg1(name))

        generator->AddIncompleteType("Mesh", "Material");
    }

    void API::RegisterGUISystem(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_WORLD_NS;

        generator->RegisterNewClass("GUISystem", "GUISystem", { "cstdint", "Math/Vector2.h", "map", "Scene.h", "Camera.h", "GameObject.h" });
        ESRegisterStaticMethodArg0(EvoScript::Public, generator, GUISystem, Instance, GUISystem&)

        using namespace SR_MATH_NS;

        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, BeginMenuBar, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, EndMenuBar, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, BeginDockSpace, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, EndDockSpace, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, EndWindow, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, EndChildWindow, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, GetWindowSize, IVector2)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, DrawGuizmoTools, void)

        ESRegisterMethod(EvoScript::Public, generator, GUISystem, BeginWindow, bool, ESArg1(const char* name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, BeginChildWindow, bool, ESArg1(const char* name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawTexture, void, ESArg4(IVector2 win, IVector2 img, uint32_t id, bool center), ESArg4(win, img, id, center))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawHierarchy, void, ESArg1(SafePtr<Scene> scene), ESArg1(scene))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawWorldEdit, void, ESArg1(SafePtr<Scene> scene), ESArg1(scene))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawInspector, void, ESArg1(SafePtr<Scene> scene), ESArg1(scene))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, SetGuizmoTool, void, ESArg1(uint8_t id), ESArg1(id))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawGuizmo, void, ESArg2(Camera* camera, SafePtr<GameObject> gm), ESArg2(camera, gm))
    }

    void API::RegisterPostProcessing(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_WORLD_NS;

        generator->RegisterNewClass("PostProcessing", "PostProcessing", { "cstdint", "Math/Vector3.h", "vector" });

        ESRegisterMethod(EvoScript::Private, generator, PostProcessing, OnResize, bool, ESArg2(uint32_t w, uint32_t h), ESArg2(w, h))
        ESRegisterMethod(EvoScript::Private, generator, PostProcessing, Init, bool, ESArg1(Render* render), ESArg1(render))

        ESRegisterMethodArg0(EvoScript::Private, generator, PostProcessing, Destroy, bool)
        ESRegisterMethodArg0(EvoScript::Private, generator, PostProcessing, Free, bool)
        ESRegisterMethodArg0(EvoScript::Private, generator, PostProcessing, BeginSkybox, void)
        ESRegisterMethodArg0(EvoScript::Private, generator, PostProcessing, EndSkybox, void)
        ESRegisterMethodArg0(EvoScript::Private, generator, PostProcessing, BeginGeometry, bool)
        ESRegisterMethodArg0(EvoScript::Private, generator, PostProcessing, EndGeometry, void)
        ESRegisterMethodArg0(EvoScript::Private, generator, PostProcessing, Complete, void)
        ESRegisterMethodArg0(EvoScript::Private, generator, PostProcessing, Draw, void)

        ESRegisterMethodArg0(EvoScript::Public, generator, PostProcessing, GetFinally, uint32_t)

        generator->AddIncompleteType("Shader", "PostProcessing");
        generator->AddIncompleteType("Camera", "PostProcessing");
        generator->AddIncompleteType("Render", "PostProcessing");
    }

    void API::RegisterISavable(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Document", "ISavable");
        generator->RegisterNewClass("ISavable", "ISavable");

        using namespace Xml;
    }

    void API::RegisterCasts(EvoScript::CastingGen *generator) {
        ESRegisterDynamicCast(generator, Graphics::, Mesh, Helper::, Component)
        ESRegisterDynamicCast(generator, Graphics::, Camera, Helper::, Component)
    }

    void API::RegisterShader(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Shader", "Shader");

        generator->RegisterEnum("StandardID", "Shader", true, {
                { "Geometry",       Shader::StandardID::Geometry       },
                { "Skybox",         Shader::StandardID::Skybox         },
                { "Transparent",    Shader::StandardID::Transparent    },
                { "DebugWireframe", Shader::StandardID::DebugWireframe },
                { "Grid",           Shader::StandardID::Grid           },
        });
    }
}

