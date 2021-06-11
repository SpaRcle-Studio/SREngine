--
-- Created by IntelliJ IDEA.
-- User: Nikita
-- Date: 26.03.2021
-- Time: 23:21
-- To change this template use File | Settings | File Templates.
--

local scene;      -- Scene*
local window;     -- Window*
local render;     -- Render*

local camera;     -- GameObject*
local cameraComp; -- Camera*

function Init()
    Debug.Log("Initialize engine editor GUI...");

    Script.this:ImportLib("Math");
    Script.this:ImportLib("Engine");
    Script.this:ImportLib("Editor");
    Script.this:ImportLib("Graphics");
    Script.this:ImportLib("GUI");

    scene   = Scene.Get();
    window  = Window.Get();
    render  = Render.Get();

    collectgarbage() -- collect memory
end;

function LoadCamera()
    camera = scene:Instance("SceneCamera");

    cameraComp = Camera.New(0);
    cameraComp:SetFrameSize(848, 480);
    camera:AddComponent(cameraComp:Base());
    window:AddCamera(cameraComp);

    collectgarbage() -- collect memory
end;

function Start()
    Debug.Log("Starting main engine script...");

    window:Resize(848, 480);
    window:CentralizeWindow();

    local mesh = Mesh.LoadWithIndices("engine/cube.obj", 0);
    render:RegisterMesh(mesh);

    local cube = scene:Instance("Cube");
    cube:AddComponent(mesh:Base());

    ---------------------

    LoadCamera();

    collectgarbage() -- collect memory
end;

function FixedUpdate()

end;

function Update()

end;

function Close()
    Debug.Log("Close main engine script...");

    if (not (scene == nil)) then
        scene:Destroy();
        scene:Free();
    end;

    collectgarbage() -- collect memory
end;