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


--local mesh2 = mesh:Copy();
--render:RegisterMesh(mesh2);
--local cube2 = scene:Instance("Cube2");
--cube2:AddComponent(mesh2:Base());
--cube2:GetTransform():Translate(Vector3.FMul(cube2:GetTransform():Forward(), 8.0), true);
--cube2:GetTransform():Rotate(Vector3.New(0, -90, 0), false);

--local mesh3 = mesh:Copy()
--render:RegisterMesh(mesh3);
--scene:Instance("Cube3"):AddComponent(mesh3:Base());


function Start()
    Debug.Log("Starting main engine script...");

    window:Resize(848, 480);
    window:CentralizeWindow();

    local texture = Texture.Load("brickwall2.jpg", TextureFormat.RGBA8_SRGB, true, TextureType.Diffuse, TextureFilter.LINEAR, TextureComp.None);
    render:RegisterTexture(texture);

    local mesh = Mesh.LoadWithIndices("engine/cube.obj", 0);
    mesh:GetMaterial():SetDiffuse(texture);
    render:RegisterMesh(mesh);

    local cube1 = scene:Instance("Cube");
    cube1:AddComponent(mesh:Base());
    --cube1:GetTransform():Translate(Vector3.FMul(cube1:GetTransform():Forward(), 4.0), true);
    --cube1:GetTransform():Rotate(Vector3.New(45, 45, 45), false);

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