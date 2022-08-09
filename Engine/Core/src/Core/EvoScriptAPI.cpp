//
// Created by Nikita on 11.07.2021.
//

#include <Core/EvoScriptAPI.h>
#include <Core/GUI/GUISystem.h>
#include <Core/Engine.h>

#include <Utils/Input/InputSystem.h>
#include <Loaders/ObjLoader.h>
#include <Types/Skybox.h>

#include <Render/PostProcessing.h>

#include <Utils/ResourceManager/ResourceManager.h>

namespace Framework {
    void API::RegisterEvoScriptClasses() {
        auto&& compiler = SR_SCRIPTING_NS::GlobalEvoCompiler::Instance();
        auto&& generator = compiler.GetGenerator();
        auto&& casts = compiler.GetCasting();

        if (generator) {
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

            generator->Save(Helper::ResourceManager::Instance().GetCachePath().Concat("Scripts/Libraries/"));
        }
        else {
            SR_ERROR("API::RegisterEvoScriptClasses() : generator is nullptr!");
        }

        if (casts) {
            RegisterCasts(casts);

            casts->Save(Helper::ResourceManager::Instance().GetCachePath().Concat("Scripts/Libraries/"));
        }
        else {
            SR_ERROR("API::RegisterEvoScriptClasses() : casts is nullptr!");
        }

        if (generator) {
            compiler.SetApiVersion(generator->GetApiVersion());
        }
    }

    void API::RegisterDebug(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("Debug", "Debug", {"string"});

        ESRegisterCustomStaticMethod(EvoScript::Public, generator, Debug, Log, void, ESArg1(const std::string& msg), {
            SR_UTILS_NS::Debug::Instance().Log(msg);
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

    void API::RegisterEngine(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_WORLD_NS;
        using namespace SR_HTYPES_NS;

        generator->RegisterNewClass("Engine", "Engine", { "Window.h", "Types/SafePointer.h" });
        ESRegisterStaticMethodArg0(EvoScript::Public, generator, Engine, Instance, Engine&)
        ESRegisterMethodArg0(EvoScript::Private, generator, Engine, RegisterLibraries, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, Engine, Reload, void)
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
        ESRegisterMethod(EvoScript::Public, generator, Scene, Instance, SafePtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, Scene, InstanceFromFile, SafePtr<GameObject>, ESArg1(const std::string& name), ESArg1(name))
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

        ESRegisterMethodArg0(EvoScript::Public, generator, Component, IsActive, bool)

        //ESRegisterMethod(EvoScript::Public, generator, Component, SetParent, void, ESArg1(GameObject* gm), ESArg1(gm))
        //ESRegisterMethod(EvoScript::Public, generator, Component, OnRotate, void, ESArg1(const FVector3& v), ESArg1(v))
        //ESRegisterMethod(EvoScript::Public, generator, Component, OnMove, void, ESArg1(const FVector3& v), ESArg1(v))
        //ESRegisterMethod(EvoScript::Public, generator, Component, OnScaled, void, ESArg1(const FVector3& v), ESArg1(v))

        ESRegisterMethod(EvoScript::Public, generator, Component, SetEnabled, void, ESArg1(bool v), ESArg1(v))

        generator->AddIncompleteType("GameObject", "Component");
    }

    void API::RegisterResourceManager(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("IResource", "ResourceManager", {"string"});
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, IsEnabledAutoRemove, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, Destroy, bool)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, AddUsePoint, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, RemoveUsePoint, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, GetCountUses, unsigned int)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, GetResourceName, const char*)
        ESRegisterMethodArg0(EvoScript::Public, generator, IResource, GetResourceId, std::string)
    }

    void API::RegisterMesh(EvoScript::AddressTableGen *generator) {
        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;
        using namespace SR_GTYPES_NS;

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

        //ESRegisterMethod(EvoScript::Public, generator, Mesh, OnMove, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        //ESRegisterMethod(EvoScript::Public, generator, Mesh, OnRotate, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        //ESRegisterMethod(EvoScript::Public, generator, Mesh, OnScaled, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        ESRegisterMethod(EvoScript::Public, generator, Mesh, SetMaterial, void, ESArg1(Material* material), ESArg1(material))

        //ESRegisterMethodArg0(EvoScript::Public, generator, Mesh, WaitCalculate, void)
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
                { "Math/Vector3.h", "string", "Transform.h", "vector", "mutex", "Component.h", "Types/SafePointer.h", "ISavable.h" },
        { { "SafePtr<GameObject>", EvoScript::Public } });

        ESRegisterMethod(EvoScript::Public, generator, GameObject, AddComponent, bool, ESArg1(Component* comp), ESArg1(comp))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, AddChild, bool, ESArg1(const SafePtr<GameObject>& child), ESArg1(child))
        ESRegisterMethod(EvoScript::Public, generator, GameObject, GetComponent, Component*, ESArg1(const std::string& name), ESArg1(name))
        ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetBarycenter, FVector3)
        ESRegisterMethodArg0(EvoScript::Public, generator, GameObject, GetTransform, Transform*)

        using namespace Xml;

        generator->AddIncompleteType("Scene", "GameObject");
    }

    void API::RegisterCamera(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Camera", "Camera",
                { "Math/Vector3.h", "Math/Vector2.h", "Component.h", "PostProcessing.h" }, {
                { "Component", EvoScript::Public }
        });

        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;
        using namespace SR_GTYPES_NS;

        //ESRegisterMethod(EvoScript::Private, generator, Camera, OnRotate, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
        //ESRegisterMethod(EvoScript::Private, generator, Camera, OnMove, void, ESArg1(const FVector3& v), ESArg1(v)) // Component
    }

    void API::RegisterRender(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Render", "Render",
                { "vector", "mutex", "stdint.h", "map", "Skybox.h", "Texture.h", "Shader.h" });

        //ESRegisterMethod(EvoScript::Public, generator, Render, SetSkybox, void, ESArg1(Skybox* skybox), ESArg1(skybox))
        //ESRegisterMethod(EvoScript::Public, generator, Render, RegisterMesh, void, ESArg1(Mesh* mesh), ESArg1(mesh))
        //ESRegisterMethod(EvoScript::Public, generator, Render, RegisterTexture, void, ESArg1(Texture* texture), ESArg1(texture))

        generator->AddIncompleteType("Window", "Render");
        generator->AddIncompleteType("Camera", "Render");
        generator->AddIncompleteType("Mesh", "Render");
    }

    void API::RegisterWindow(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Window", "Window", { "thread", "vector", "mutex", "stdint.h", "Math/Vector2.h" });

        using namespace SR_MATH_NS;
        using namespace SR_GRAPH_NS;

        ESRegisterMethod(EvoScript::Public, generator, Window, SetGUIEnabled, void, ESArg1(bool v), ESArg1(v))
        ESRegisterMethod(EvoScript::Public, generator, Window, Resize, void, ESArg2(uint32_t w, uint32_t h), ESArg2(w, h))

        ESRegisterMethodArg0(EvoScript::Public, generator, Window, Synchronize, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, Window, CentralizeWindow, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, Window, GetWindowSize, IVector2)
        ESRegisterMethodArg0(EvoScript::Public, generator, Window, IsGUIEnabled, bool)

        generator->AddIncompleteType("Camera", "Window");
        generator->AddIncompleteType("Mesh", "Window");
    }

    void API::RegisterTransform(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Transform", "Transform", { "vector", "mutex", "stdint.h", "Math/Vector3.h", "Math/Vector2.h" });

        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;

        ESRegisterMethod(EvoScript::Public, generator, Transform, Rotate, void, ESArg1(const FVector3& eulers), ESArg1(eulers))
        ESRegisterMethod(EvoScript::Public, generator, Transform, Translate, void, ESArg1(const FVector3& translation), ESArg1(translation))
        ESRegisterMethod(EvoScript::Public, generator, Transform, SetTranslation, void, ESArg1(const FVector3& translation), ESArg1(translation))
    }

    void API::RegisterInput(EvoScript::AddressTableGen *generator) {
        using namespace SR_MATH_NS;
        using namespace SR_UTILS_NS;

        generator->RegisterNewClass("Input", "Input", { "Math/Vector2.h" });
        // ESRegisterStaticMethodArg0(EvoScript::Public, generator, Input, GetMouseWheel, int)
        // ESRegisterStaticMethodArg0(EvoScript::Public, generator, Input, GetMouseDrag, FVector2)
        // ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKey, bool, ESArg1(KeyCode key), ESArg1(key))
        // ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKeyDown, bool, ESArg1(KeyCode key), ESArg1(key))
        // ESRegisterStaticMethod(EvoScript::Public, generator, Input, GetKeyUp, bool, ESArg1(KeyCode key), ESArg1(key))

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
                { "mutex", "stdint.h", "ResourceManager.h", "string" },
                {{ "IResource", EvoScript::Public } });
        //ESRegisterMethodArg0(EvoScript::Private, generator, Texture, Destroy, bool) // IResource
        //ESRegisterStaticMethod(EvoScript::Public, generator, Texture, Load, Texture*, ESArg1(const std::string& name), ESArg1(name));
    }

    void API::RegisterMaterial(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Material", "Material", { "Texture.h" });

        //ESRegisterStaticMethod(EvoScript::Public, generator, Material, Load, Material*, ESArg1(const std::string& name), ESArg1(name))

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
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, EndWindow, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, EndChildWindow, void)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, GetWindowSize, IVector2)
        ESRegisterMethodArg0(EvoScript::Public, generator, GUISystem, DrawGuizmoTools, void)

        ESRegisterMethod(EvoScript::Public, generator, GUISystem, BeginWindow, bool, ESArg1(const char* name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, BeginChildWindow, bool, ESArg1(const char* name), ESArg1(name))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawTexture, void, ESArg4(IVector2 win, IVector2 img, uint32_t id, bool center), ESArg4(win, img, id, center))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawWorldEdit, void, ESArg1(SafePtr<Scene> scene), ESArg1(scene))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawInspector, void, ESArg1(SafePtr<Scene> scene), ESArg1(scene))
        ESRegisterMethod(EvoScript::Public, generator, GUISystem, SetGuizmoTool, void, ESArg1(uint8_t id), ESArg1(id))
        //ESRegisterMethod(EvoScript::Public, generator, GUISystem, DrawGuizmo, void, ESArg2(Camera* camera, SafePtr<GameObject> gm), ESArg2(camera, gm))
    }

    void API::RegisterPostProcessing(EvoScript::AddressTableGen *generator) {
        using namespace SR_UTILS_NS;
        using namespace SR_HTYPES_NS;
        using namespace SR_WORLD_NS;

        generator->RegisterNewClass("PostProcessing", "PostProcessing", { "cstdint", "Math/Vector3.h", "vector" });

        generator->AddIncompleteType("Shader", "PostProcessing");
        generator->AddIncompleteType("Camera", "PostProcessing");
        generator->AddIncompleteType("Render", "PostProcessing");
    }

    void API::RegisterISavable(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Document", "ISavable");
        generator->RegisterNewClass("ISavable", "ISavable");
    }

    void API::RegisterCasts(EvoScript::CastingGen *generator) {
        ESRegisterDynamicCast(generator, Graphics::Types::, Mesh, Helper::, Component)
        //ESRegisterDynamicCast(generator, Graphics::, Camera, Helper::, Component)
    }

    void API::RegisterShader(EvoScript::AddressTableGen *generator) {
        generator->RegisterNewClass("Shader", "Shader");
    }

    void API::RegisterBehaviour(EvoScript::AddressTableGen *generator) {

    }
}

