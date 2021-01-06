local scene;  -- Scene*
local window; -- Window*
local camera; -- GameObject*
local render; -- Render*

function Start ()
    Debug.Log("Main engine script has been started!");

    Script.ImportLib("Math", LuaState.L);
    Script.ImportLib("Engine", LuaState.L);
    Script.ImportLib("Graphics", LuaState.L);

    scene = Scene.Get();
    window = Window.Get();
    render = Render.Get();

    camera = scene:Instance("SceneCamera");

    local cameraComp = Camera.New();
    cameraComp:SetFrameSize(1280, 720);

    camera:AddComponent(cameraComp:Base());

    window:AddCamera(cameraComp);

    --------------------------------------

    local cube = scene:Instance("Cube");
        local cubeMesh = Mesh.Load("cube.obj", 0);
        render:RegisterMesh(cubeMesh);
        cube:AddComponent(cubeMesh:Base());
        cube:GetTransform():Translate(Vector3.FMul(cube:GetTransform():Forward(), 8.0));
end;

function Update()

end;

function FixedUpdate()
    local direction = Vector3.New();

    if Input.GetKey(KeyCode.W()) then
        direction = Vector3.Sum(direction, camera:GetTransform():Forward());
    end;
    if Input.GetKey(KeyCode.S()) then
        direction = Vector3.Sub(direction, camera:GetTransform():Forward());
    end;

    if Input.GetKey(KeyCode.A()) then
        direction = Vector3.Sub(direction, camera:GetTransform():Right());
    end;
    if Input.GetKey(KeyCode.D()) then
        direction = Vector3.Sum(direction, camera:GetTransform():Right());
    end;

    if Input.GetKey(KeyCode.Space()) then
        direction = Vector3.Sum(direction, camera:GetTransform():Up());
    end;
    if Input.GetKey(KeyCode.LShift()) then
        direction = Vector3.Sub(direction, camera:GetTransform():Up());
    end;

    if (Vector3.Empty(direction) == false) then
        camera:GetTransform():Translate(Vector3.FDiv(direction, 100.0));
    end;
end;
