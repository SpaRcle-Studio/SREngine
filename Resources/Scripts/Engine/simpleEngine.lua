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
    Script.this:ImportLib("Graphics");
    Script.this:ImportLib("GUI");

    scene   = Scene.Get();
    window  = Window.Get();
    render  = Render.Get();

    collectgarbage() -- collect memory
end;

function LoadCamera()
    camera = scene:Instance("SceneCamera");

    cameraComp = Camera.New();
    cameraComp:SetDirectOutput(true);
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

    local cube1 = scene:Instance("Cube");
    cube1:AddComponent(mesh:Base());
    cube1:GetTransform():Translate(
        Vector3.FMul(cube1:GetTransform():Forward(), 4.0), true
    );
    ---------------------

    local mesh2 = mesh:Copy();
    render:RegisterMesh(mesh2);

    scene:Instance("Cube2"):AddComponent(mesh2:Base());

    ---------------------

    LoadCamera();

    collectgarbage() -- collect memory
end;

function MouseUpdate()
    local dir = Input.GetMouseDrag();

    local wheel = Input.GetMouseWheel();
    if (wheel ~= 0) then
        local forward = camera:GetTransform():Forward();
        camera:GetTransform():Translate(Vector3.FMul(forward, wheel / -10.0), false);
    end;

    if (Input.GetKey(KeyCode.MouseRight)) then
        camera:GetTransform():Rotate(Vector3.New(dir.y / -10.0, dir.x / -10.0, 0.0), false);
    end;

    if (Input.GetKey(KeyCode.MouseMiddle)) then
        local right = camera:GetTransform():Right();
        local up    = camera:GetTransform():Up();

        camera:GetTransform():Translate(
            Vector3.Sum(
                Vector3.FMul(up,    dir.y /  100.0),
                Vector3.FMul(right, dir.x /  -100.0)
            ),
            false
        );
    end;
end;

function FixedUpdate()

end;

function Update()
    MouseUpdate();

    collectgarbage() -- collect memory
end;

function Close()
    Debug.Log("Close main engine script...");

    if (not (scene == nil)) then
        scene:Destroy();
        scene:Free();
    end;

    collectgarbage() -- collect memory
end;