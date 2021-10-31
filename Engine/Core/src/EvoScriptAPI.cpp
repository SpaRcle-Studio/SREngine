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
    using namespace Core::GUI;
    using namespace Helper::Math;
    using namespace Helper::Types;
    using namespace Graphics;
    using namespace Graphics::GUI;
    using namespace Physics;

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

        generator->Save(Helper::ResourceManager::Instance().GetResourcesFolder() + "/Scripts/Libraries/");
        casts->Save(Helper::ResourceManager::Instance().GetResourcesFolder() + "/Scripts/Libraries/");
    }

    void API::RegisterDebug(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Debug", "Debug", {"string"});
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, Log, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, Warn, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, System, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, Shader, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, Error, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, Info, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, Script, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, ScriptError, void, ESArg1(const std::string& msg), ESArg1(msg))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Debug, ScriptLog, void, ESArg1(const std::string& msg), ESArg1(msg))
    }

    void API::RegisterEngine(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Engine", "Engine", { "Window.h", "Types/SafePointer.h" });
        ESRegisterStaticMethodArg0(Framework::, EvoScript::Public, generator, Engine, Get, Engine*)
        ESRegisterMethodArg0(Framework::,       EvoScript::Private, generator, Engine, RegisterLibraries, bool)
        ESRegisterStaticMethodArg0(Framework::, EvoScript::Public, generator, Engine, Reload, void)
        ESRegisterMethodArg0(Framework::,       EvoScript::Public, generator, Engine, GetTime, Time*)
        ESRegisterMethodArg0(Framework::,       EvoScript::Public, generator, Engine, GetWindow, Window*)
        ESRegisterMethodArg0(Framework::,       EvoScript::Public, generator, Engine, GetRender, Render*)
        ESRegisterMethodArg0(Framework::,       EvoScript::Public, generator, Engine, GetScene, SafePtr<Scene>)
        ESRegisterMethodArg0(Framework::,       EvoScript::Public, generator, Engine, IsRun, bool)
        ESRegisterMethod(Framework::,           EvoScript::Public, generator, Engine, SetScene, bool, ESArg1(const SafePtr<Scene>& scene), ESArg1(scene))

        generator->RegisterTypedef("Time", "Engine", "void");
        generator->RegisterTypedef("PhysEngine", "Engine", "void");

        generator->AddIncompleteType("Scene", "Engine");
        generator->AddIncompleteType("Render", "Engine");
        generator->AddIncompleteType("Camera", "Engine");
    }

    void API::RegisterScene(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("HierarchyElem", "Scene");

        generator->RegisterNewClass("Scene", "Scene", { "map", "string", "mutex", "vector", "stdint.h", "set", "GameObject.h", "Types/SafePointer.h" });
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Scene, Destroy, bool)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Scene, Free, bool)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Scene, GetName, std::string)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Scene, GetGameObjects, std::vector<SafePtr<GameObject>>)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Scene, GetRootGameObjects, std::vector<SafePtr<GameObject>>&)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Scene, GetSelected, SafePtr<GameObject>)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Scene, UnselectAll, void)
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Scene, RemoveSelected, bool, ESArg1(const SafePtr<GameObject>& gm), ESArg1(gm))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Scene, AddSelected, void, ESArg1(const SafePtr<GameObject>& gm), ESArg1(gm))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Scene, Instance, SafePtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Scene, FindByComponent,  SafePtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))

        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Scene, New, SafePtr<Scene>, ESArg1(const std::string& name), ESArg1(name))
    }

    void API::RegisterUtils(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("_64byte", "Utils", { "vector","string", "vector", "stdint.h",  });

        generator->RegisterNewClass("_128byte", "Utils");
        generator->RegisterNewClass("_52byte", "Utils");
        generator->RegisterNewClass("_16byte", "Utils");
    }

    void API::RegisterComponent(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Component", "Component", { "Math/Vector3.h", "string" });
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Component, GetComponentName, std::string)

        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Component, BaseComponent, Component*)
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Component, SetParent, void, ESArg1(GameObject* gm), ESArg1(gm))
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Component, GetParent, GameObject*)

        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Component, GetBarycenter, Vector3)
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Component, OnRotate, void, ESArg1(const Vector3& v), ESArg1(v))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Component, OnMove, void, ESArg1(const Vector3& v), ESArg1(v))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Component, OnScaled, void, ESArg1(const Vector3& v), ESArg1(v))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Component, OnSelected, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Component, OnReady, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Component, OnAttachComponent, void)

        ESRegisterMethod(Helper::, EvoScript::Public, generator, Component, SetActive, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Component, SetEnabled, void, ESArg1(bool v), ESArg1(v))

        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Component, IsActive, bool)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Component, IsSelected, bool)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Component, IsReady, bool)

        ESRegisterMethodArg0(Helper::, EvoScript::Protected, generator, Component, OnRemoveComponent, void)
        ESRegisterMethodArg0(Helper::, EvoScript::Protected, generator, Component, OnDestroyGameObject, void)

        generator->AddIncompleteType("GameObject", "Component");
    }

    void API::RegisterResourceManager(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("IResource", "ResourceManager", {"string"});
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, IResource, IsEnabledAutoRemove, bool)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, IResource, Destroy, bool)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, IResource, IsDestroy, bool)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, IResource, AddUsePoint, void)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, IResource, RemoveUsePoint, void)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, IResource, GetCountUses, unsigned int)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, IResource, GetResourceName, const char*)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, IResource, GetResourceID, std::string)
    }

    void API::RegisterMesh(EvoScript::AddressTableGen *generator) {
        generator->AddIncompleteType("Mesh", "Mesh");

        generator->RegisterEnum("MeshType", "Mesh", true, {
                { "Unknown",    0 },
                { "Static",     1 },
                { "Wireframe",  2 },
                { "Skinned",    3 },
        });

        generator->RegisterNewClass("Mesh", "Mesh", {
            "ResourceManager.h", "Component.h", "mutex", "Math/Vector3.h", "Utils.h", "Material.h"
        }, { { "IResource", EvoScript::Public }, { "Component", EvoScript::Public } });

        ESRegisterStaticMethod(Graphics::, EvoScript::Public, generator, Mesh, Load, std::vector<Mesh*>, ESArg2(const std::string& path, MeshType type), ESArg2(path, type))

        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Mesh, Destroy, bool) // IResource
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Mesh, Copy, Mesh* const, ESArg1(Mesh* dest), ESArg1(dest))

        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Mesh, OnMove, void, ESArg1(const Vector3& v), ESArg1(v)) // Component
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Mesh, OnRotate, void, ESArg1(const Vector3& v), ESArg1(v)) // Component
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Mesh, OnScaled, void, ESArg1(const Vector3& v), ESArg1(v)) // Component
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Mesh, OnSelected, void, ESArg1(bool v), ESArg1(v)) // Component

        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Mesh, WaitCalculate, void)
        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Mesh, IsCanCalculate, bool)
        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Mesh, GetGeometryName, std::string)
        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Mesh, GetMaterial, Material*)

        generator->AddIncompleteType("Render", "Mesh");
    }

    void API::RegisterGameObject(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("GameObject", "GameObject",
                { "Math/Vector3.h", "string", "vector", "mutex", "Component.h", "Transform.h", "Types/SafePointer.h", "ISavable.h" },
        { { "ISavable", EvoScript::Public } });

        ESRegisterMethod(Helper::, EvoScript::Public, generator, GameObject, AddComponent, bool, ESArg1(Component* comp), ESArg1(comp))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, GameObject, AddChild, bool, ESArg1(const SafePtr<GameObject>& child), ESArg1(child))
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, GameObject, GetTransform, Transform*)
        ESRegisterMethod(Helper::, EvoScript::Public, generator, GameObject, GetComponent, Component*, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, GameObject, GetBarycenter, Vector3)

        using namespace Xml;

        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, GameObject, Save, Document)
        ESRegisterMethod(Helper::, EvoScript::Public, generator, GameObject, Load, bool, ESArg1(const Document& xml), ESArg1(xml))

        generator->AddIncompleteType("Scene", "GameObject");
    }

    void API::RegisterCamera(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Camera", "Camera",
                { "Math/Vector3.h", "Math/Vector2.h", "Utils.h", "Component.h", "PostProcessing.h" }, {
                { "Component", EvoScript::Public }
        });

        ESRegisterStaticMethod(Graphics::, EvoScript::Public, generator, Camera, Allocate, Camera*, ESArg2(uint32_t w, uint32_t h), ESArg2(w, h))

        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Camera, SetDirectOutput, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Camera, GetPostProcessing, PostProcessing*)
        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Camera, IsDirectOutput, bool)

        ESRegisterMethod(Graphics::, EvoScript::Private, generator, Camera, OnRotate, void, ESArg1(const Vector3& v), ESArg1(v)) // Component
        ESRegisterMethod(Graphics::, EvoScript::Private, generator, Camera, OnMove, void, ESArg1(const Vector3& v), ESArg1(v)) // Component
        ESRegisterMethod(Graphics::, EvoScript::Private, generator, Camera, OnReady, void, ESArg1(bool v), ESArg1(v)) // Component
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Camera, OnAttachComponent, void) // Component

        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Camera, OnRemoveComponent, void) // Component
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Camera, OnDestroyGameObject, void) // Component
    }

    void API::RegisterRender(EvoScript::AddressTableGen *generator) {
        const std::string meshCluster = "[" + std::to_string(sizeof(MeshCluster)) + "]";

        generator->RegisterNewClass("MeshCluster", "Render");

        const std::string renderSkybox = "[" + std::to_string(sizeof(RenderSkybox)) + "]";

        generator->RegisterNewClass("Render", "Render",
                { "vector", "mutex", "Utils.h", "stdint.h", "map", "Skybox.h", "Texture.h" });

        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Render, DrawGeometry, bool)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Render, DrawDebugWireframe, bool)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Render, DrawSkybox, bool)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Render, DrawGrid, void)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Render, DrawSingleColors, void)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Render, DrawTransparentGeometry, bool)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Render, DrawSettingsPanel, bool)

        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Render, SetSkybox, void, ESArg1(Skybox* skybox), ESArg1(skybox))
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Render, RegisterMesh, void, ESArg1(Mesh* mesh), ESArg1(mesh))
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Render, RegisterTexture, void, ESArg1(Texture* texture), ESArg1(texture))

        generator->AddIncompleteType("Window", "Render");
        generator->AddIncompleteType("Camera", "Render");
        generator->AddIncompleteType("Mesh", "Render");
    }

    void API::RegisterWindow(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Window", "Window", { "thread", "vector", "mutex", "stdint.h", "Math/Vector2.h" });

        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Window, AddCamera, void, ESArg1(Camera* camera), ESArg1(camera))
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Window, Resize, void, ESArg2(uint32_t w, uint32_t h), ESArg2(w, h))
        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Window, CentralizeWindow, void)
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Window, SetGUIEnabled, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Window, GetWindowSize, Vector2)
        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, Window, IsGUIEnabled, bool)

        generator->AddIncompleteType("Camera", "Window");
        generator->AddIncompleteType("Mesh", "Window");
    }

    void API::RegisterTransform(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Transform", "Transform", { "Math/Vector3.h" });

        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Transform, Forward, Vector3)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Transform, Right, Vector3)
        ESRegisterMethodArg0(Helper::, EvoScript::Public, generator, Transform, Up, Vector3)
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Transform, Translate, void, ESArg1(Vector3 v), ESArg1(v))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Transform, Rotate, void, ESArg1(Vector3 v), ESArg1(v))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Transform, Scaling, void, ESArg1(Vector3 v), ESArg1(v))
        ESRegisterMethod(Helper::, EvoScript::Public, generator, Transform, RotateAround, void, ESArg4(Vector3 point, Vector3 axis, Unit angle, bool local), ESArg4(point, axis, angle, local))

        generator->AddIncompleteType("GameObject", "Transform");
    }

    void API::RegisterInput(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Input", "Input", { "Math/Vector2.h" });
        ESRegisterStaticMethodArg0(Helper::, EvoScript::Public, generator, Input, GetMouseWheel, int)
        ESRegisterStaticMethodArg0(Helper::, EvoScript::Public, generator, Input, GetMouseDrag, Vector2)
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Input, GetKey, bool, ESArg1(KeyCode key), ESArg1(key))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Input, GetKeyDown, bool, ESArg1(KeyCode key), ESArg1(key))
        ESRegisterStaticMethod(Helper::, EvoScript::Public, generator, Input, GetKeyUp, bool, ESArg1(KeyCode key), ESArg1(key))

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

        ESRegisterStaticMethod(Graphics::, EvoScript::Public, generator, Skybox, Load, Skybox*, ESArg1(const std::string& path), ESArg1(path))
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
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, Texture, Destroy, bool) // IResource
        ESRegisterStaticMethod(Graphics::, EvoScript::Public, generator, Texture, Load, Texture*,
                ESArg7(const std::string& path, TextureFormat format, bool autoRemove, TextureType type, TextureFilter filter, TextureCompression compress, uint8_t mip),
                ESArg7(path, format, autoRemove, type, filter, compress, mip))
    }

    void API::RegisterMaterial(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Material", "Material", { "Utils.h", "Texture.h" });

        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Material, SetDiffuse, void, ESArg1(Texture* texture), ESArg1(texture))
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Material, SetNormal, void, ESArg1(Texture* texture), ESArg1(texture))
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Material, SetSpecular, void, ESArg1(Texture* texture), ESArg1(texture))
        ESRegisterMethod(Graphics::, EvoScript::Public, generator, Material, SetGlossiness, void, ESArg1(Texture* texture), ESArg1(texture))

        generator->AddIncompleteType("Mesh", "Material");
    }

    void API::RegisterGUISystem(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("GUISystem", "GUISystem", { "cstdint", "Math/Vector2.h", "map", "Scene.h", "Camera.h", "GameObject.h" });
        ESRegisterStaticMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, Get, GUISystem*)
        ESRegisterMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, BeginMenuBar, bool)
        ESRegisterMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, EndMenuBar, void)
        ESRegisterMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, BeginDockSpace, void)
        ESRegisterMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, EndDockSpace, void)
        ESRegisterMethod(GUI::, EvoScript::Public, generator, GUISystem, BeginWindow, bool, ESArg1(const char* name), ESArg1(name))
        ESRegisterMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, EndWindow, void)
        ESRegisterMethod(GUI::, EvoScript::Public, generator, GUISystem, BeginChildWindow, bool, ESArg1(const char* name), ESArg1(name))
        ESRegisterMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, EndChildWindow, void)
        ESRegisterMethod(GUI::, EvoScript::Public, generator, GUISystem, DrawTexture, void, ESArg4(Vector2 win, Vector2 img, uint32_t id, bool center), ESArg4(win, img, id, center))
        ESRegisterMethod(GUI::, EvoScript::Public, generator, GUISystem, DrawHierarchy, void, ESArg1(SafePtr<Scene> scene), ESArg1(scene))
        ESRegisterMethod(GUI::, EvoScript::Public, generator, GUISystem, DrawInspector, void, ESArg1(SafePtr<Scene> scene), ESArg1(scene))
        ESRegisterMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, GetWindowSize, Vector2)
        ESRegisterMethodArg0(GUI::, EvoScript::Public, generator, GUISystem, DrawGuizmoTools, void)
        ESRegisterMethod(GUI::, EvoScript::Public, generator, GUISystem, SetGuizmoTool, void, ESArg1(uint8_t id), ESArg1(id))
        ESRegisterMethod(GUI::, EvoScript::Public, generator, GUISystem, DrawGuizmo, void, ESArg2(Camera* camera, SafePtr<GameObject> gm), ESArg2(camera, gm))
    }

    void API::RegisterPostProcessing(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("PostProcessing", "PostProcessing", { "cstdint", "Math/Vector3.h", "vector" });

        ESRegisterMethod(Graphics::, EvoScript::Private, generator, PostProcessing, Init, bool, ESArg1(Render* render), ESArg1(render))
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, PostProcessing, Destroy, bool)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, PostProcessing, Free, bool)
        ESRegisterMethod(Graphics::, EvoScript::Private, generator, PostProcessing, OnResize, bool, ESArg2(uint32_t w, uint32_t h), ESArg2(w, h))
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, PostProcessing, BeginSkybox, void)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, PostProcessing, EndSkybox, void)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, PostProcessing, BeginGeometry, bool)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, PostProcessing, EndGeometry, void)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, PostProcessing, Complete, void)
        ESRegisterMethodArg0(Graphics::, EvoScript::Private, generator, PostProcessing, Draw, void)

        ESRegisterMethodArg0(Graphics::, EvoScript::Public, generator, PostProcessing, GetFinally, uint32_t)

        generator->AddIncompleteType("Shader", "PostProcessing");
        generator->AddIncompleteType("Camera", "PostProcessing");
        generator->AddIncompleteType("Render", "PostProcessing");
    }

    void API::RegisterISavable(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Document", "ISavable");
        generator->RegisterNewClass("ISavable", "ISavable");

        using namespace Xml;

        ESRegisterMethodArg0(Helper::, EvoScript::Protected, generator, ISavable, Save, Document)
        ESRegisterMethod(Helper::, EvoScript::Protected, generator, ISavable, Load, bool, ESArg1(const Document& xml), ESArg1(xml))
    }

    void API::RegisterCasts(EvoScript::CastingGen *generator) {
        ESRegisterDynamicCast(generator, Graphics::, Mesh, Helper::, Component)
        ESRegisterDynamicCast(generator, Graphics::, Camera, Helper::, Component)
    }
}

