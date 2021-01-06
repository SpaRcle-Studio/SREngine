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

function Keyboard()
    local direction = Vector3.New(0,0,0);

    if Input.GetKey(KeyCode.W) then
        direction = Vector3.Sum(direction, camera:GetTransform():Forward());
    end;
    if Input.GetKey(KeyCode.S) then
        direction = Vector3.Sub(direction, camera:GetTransform():Forward());
    end;

    if Input.GetKey(KeyCode.A) then
        direction = Vector3.Sub(direction, camera:GetTransform():Right());
    end;
    if Input.GetKey(KeyCode.D) then
        direction = Vector3.Sum(direction, camera:GetTransform():Right());
    end;

    if Input.GetKey(KeyCode.Space) then
        direction = Vector3.Sum(direction, camera:GetTransform():Up());
    end;
    if Input.GetKey(KeyCode.LShift) then
        direction = Vector3.Sub(direction, camera:GetTransform():Up());
    end;

    if (Vector3.Empty(direction) == false) then
        camera:GetTransform():Translate(Vector3.FDiv(direction, 100.0));
    end;
end;

function FixedUpdate()

end;
