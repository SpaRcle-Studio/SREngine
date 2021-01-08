local scene;  -- Scene*
local window; -- Window*
local camera; -- GameObject*
local render; -- Render*
local skybox; -- Skybox*
local cube;   -- GameObject*

function LoadGeometry()
    local texture = Texture.Load("steel_cube.png", true, TextureType.Diffuse, TextureFilter.LINEAR);
    render:RegisterTexture(texture);

    cube = scene:Instance("Cube");
        local cubeMesh = Mesh.Load("cube.obj", 0);
        render:RegisterMesh(cubeMesh);

        cubeMesh:GetMaterial():SetBloom(true);
        cubeMesh:GetMaterial():SetDiffuse(texture);
        cubeMesh:GetMaterial():SetColor(Vector3.New(6,4,4));

        cube:AddComponent(cubeMesh:Base());
        cube:GetTransform():Translate(Vector3.FMul(cube:GetTransform():Forward(), 8.0));

    collectgarbage() -- collect memory
end;

function LoadCamera()
    camera = scene:Instance("SceneCamera");

    local cameraComp = Camera.New();
    cameraComp:SetFrameSize(1280, 720);

    cameraComp:GetPostProcessing():SetBloomIntensity(3.0);
    cameraComp:GetPostProcessing():SetBloomAmount(10);
    cameraComp:GetPostProcessing():SetGamma(0.9);

    camera:AddComponent(cameraComp:Base());

    window:AddCamera(cameraComp);

    collectgarbage() -- collect memory
end;

function Start ()
    Debug.Log("Main engine script has been started!");

    Script.ImportLib("Math",     LuaState.L);
    Script.ImportLib("Engine",   LuaState.L);
    Script.ImportLib("Graphics", LuaState.L);

    scene = Scene.Get();
    window = Window.Get();
    render = Render.Get();

    skybox = Skybox.Load("Sea.jpg");
    render:SetSkybox(skybox);

    --------------------------------------

    LoadCamera();
    LoadGeometry();

    collectgarbage() -- collect memory
end;

function MouseUpdate()
    local dir = Input.GetMouseDrag();

    local wheel = Input.GetMouseWheel();
    if (wheel ~= 0) then
        local forward = camera:GetTransform():Forward();
        camera:GetTransform():Translate(Vector3.FMul(forward, wheel / 10.0));
    end;

    if (Input.GetKey(KeyCode.MouseRight)) then
        camera:GetTransform():Rotate(Vector3.New(dir.y / 10.0, dir.x / 10.0, 0.0));
    end;

    if (Input.GetKey(KeyCode.MouseMiddle)) then
        local right = camera:GetTransform():Right();
        local up    = camera:GetTransform():Up();

        camera:GetTransform():Translate(
            Vector3.Sum(
                Vector3.FMul(up,    dir.y /  100.0),
                Vector3.FMul(right, dir.x / -100.0)
            )
        );
    end;
end;

function Update()
    MouseUpdate();

    collectgarbage() -- collect memory
end;

function FixedUpdate()

end;

function Close()
    Debug.Log("Close main engine script...");

    scene:Destroy();

    skybox:AwaitDestroy();
    skybox:Free();

    collectgarbage() -- collect memory
end;